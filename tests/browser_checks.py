"""End-to-end checks. Requires Playwright Python and a Chromium installation.

Run from the repository root: python3 tests/browser_checks.py
The script builds and serves dist itself; it does not expose the checkout.
"""
import functools
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
import json
import re
import hashlib
import base64
from pathlib import Path
import shutil
import subprocess
import tempfile
import threading
from playwright.sync_api import sync_playwright, expect

ROOT = Path(__file__).resolve().parents[1]
subprocess.run(['python3', 'scripts/build.py'], cwd=ROOT, check=True)


class QuietHandler(SimpleHTTPRequestHandler):
    def log_message(self, *args):
        pass


handler = functools.partial(QuietHandler, directory=str(ROOT / 'dist'))
server = ThreadingHTTPServer(('127.0.0.1', 0), handler)
threading.Thread(target=server.serve_forever, daemon=True).start()
base = f'http://127.0.0.1:{server.server_port}/'
data = json.loads((ROOT / 'dist/problems.json').read_text(encoding='utf-8'))
html = (ROOT / 'dist/index.html').read_text(encoding='utf-8')
passed = 0


def check(label):
    global passed
    passed += 1
    print('PASS', label)


try:
    with sync_playwright() as playwright:
        chromium = shutil.which('chromium') or shutil.which('chromium-browser')
        browser = playwright.chromium.launch(executable_path=chromium, headless=True, args=['--no-sandbox'])
        context = browser.new_context(viewport={'width': 1440, 'height': 1000}, permissions=['clipboard-read', 'clipboard-write'])
        page = context.new_page()
        errors = []
        page.on('pageerror', lambda error: errors.append(str(error)))
        page.goto(base)
        expect(page.locator('.problem-row')).to_have_count(50)
        check('all 50 archived solutions are listed')

        # Model a file preview that exposes only the HTML, with no sibling files.
        portable = context.new_page()
        sibling_requests = []
        def portable_route(route):
            if route.request.is_navigation_request():
                route.fulfill(body=html, content_type='text/html; charset=utf-8')
            else:
                sibling_requests.append(route.request.url)
                route.abort()
        portable.route('**/*', portable_route)
        portable.goto(base + 'standalone/index.html')
        expect(portable.locator('.problem-row')).to_have_count(50)
        assert portable.locator('body').evaluate('(node)=>getComputedStyle(node).backgroundColor') == 'rgb(247, 246, 242)'
        expect(portable.locator('#catalog-heading')).to_have_text('題目列表')
        portable.locator('#query').fill('油田')
        portable.locator('.problem-row').click()
        expect(portable.locator('#detail-title')).to_have_text('Oil Deposit')
        assert not sibling_requests, sibling_requests
        portable.close()
        check('a standalone HTML preview loads CSS, data, search and detail without sibling requests')

        page.locator('#query').fill('油田')
        expect(page.locator('.problem-row')).to_have_count(1)
        expect(page.locator('.problem-row')).to_contain_text('Oil Deposit')
        page.locator('#language').select_option('Python')
        expect(page.locator('#empty')).to_be_visible()
        page.locator('#empty-reset').click()
        page.locator('#language').select_option('Python')
        expect(page.locator('.problem-row')).to_have_count(1)
        page.locator('#reset').click()
        page.locator('#query').fill('572')
        page.locator('#tag').select_option('DFS')
        page.locator('.problem-row').click()
        expect(page.locator('#detail-title')).to_have_text('Oil Deposit')
        expect(page.locator('#summary')).to_contain_text('斜對角')
        page.reload()
        expect(page.locator('#detail-title')).to_have_text('Oil Deposit')
        page.locator('.back-link').click()
        expect(page.locator('#query')).to_have_value('572')
        expect(page.locator('#tag')).to_have_value('DFS')
        expect(page.locator('.problem-row')).to_have_count(1)
        check('Chinese search, combined filters, empty state, deep links and retained filters')

        for p in data:
            page.goto(base + '#/problem/' + p['id'])
            expect(page.locator('#detail-title')).to_have_text(p['title'])
            assert page.locator('.source-code code').text_content() == p['code']
            expect(page.locator('#steps li')).to_have_count(len(p['steps']))
        check('every detail page renders its complete code and explanation')

        page.goto(base + '#/problem/problem-572')
        page.get_by_role('button', name='複製', exact=True).click()
        expect(page.locator('.copy-status')).to_have_text('已複製程式碼')
        assert page.evaluate('navigator.clipboard.readText()') == next(p['code'] for p in data if p['number'] == '572')
        with page.expect_download() as download:
            page.get_by_role('button', name='下載', exact=True).click()
        assert download.value.suggested_filename == '572 - Oil Deposit.cpp'
        with tempfile.TemporaryDirectory() as folder:
            target = Path(folder) / 'download.cpp'
            download.value.save_as(target)
            assert target.read_text() == next(p['code'] for p in data if p['number'] == '572')
        check('clipboard and downloaded code match the archive')

        requests = []
        page.route('https://onlinejudge.org/**', lambda route: (requests.append(route.request.url), route.abort()))
        assert not requests
        page.get_by_role('button', name='在此閱讀 PDF').click()
        expect(page.locator('iframe')).to_have_attribute('src', 'https://onlinejudge.org/external/5/572.pdf')
        expect(page.locator('.pdf-reader')).to_be_visible()
        page.get_by_role('button', name='收起 PDF').click()
        expect(page.locator('.pdf-reader')).to_be_hidden()
        check('PDF loads only on request and retains an official-link fallback')

        page.goto(base + '#/problem/does-not-exist')
        expect(page.locator('#detail-title')).to_have_text('找不到這道題')
        page.locator('.back-link').click()
        expect(page.locator('.problem-row')).to_have_count(50)
        page.goto(base + '#/problem/%E0%A4%A')
        expect(page.locator('#detail-title')).to_have_text('找不到這道題')
        check('unknown and malformed routes recover to the catalog')

        for width in (390, 768):
            page.set_viewport_size({'width': width, 'height': 844})
            page.goto(base)
            expect(page.locator('.problem-row')).to_have_count(50)
            assert page.evaluate('document.documentElement.scrollWidth <= innerWidth')
            page.locator('#query').fill('10007')
            page.locator('.problem-row').click()
            expect(page.locator('#detail-title')).to_have_text('Count the Trees')
            assert page.evaluate('document.documentElement.scrollWidth <= innerWidth')
        check('phone and tablet layouts have no page overflow and support navigation')

        page.set_viewport_size({'width': 1440, 'height': 1000})
        page.goto(base)
        page.locator('#query').focus()
        page.keyboard.type('Luggage')
        page.keyboard.press('Tab')
        assert page.locator('#language').evaluate('(node) => node === document.activeElement')
        page.goto(base + '#/problem/problem-10664')
        expect(page.locator('#steps')).to_contain_text('索引上限')
        check('keyboard filters and existing-solution warnings are usable')

        # Hostile source text stays text; the browser must not create an image or execute it.
        hostile = json.loads(json.dumps(data))
        hostile[0]['title'] = '<img src=x onerror="window.__injected=1">'
        hostile[0]['code'] = '</code><img src=x onerror="window.__injected=1">'
        safe_hostile = json.dumps(hostile, ensure_ascii=False).replace('<', '\\u003c').replace('>', '\\u003e').replace('&', '\\u0026')
        old_data = re.search(r'<script id="problem-data" type="application/json">(.*?)</script>', html, re.S).group(1)
        def data_hash(value):
            return base64.b64encode(hashlib.sha256(value.encode('utf-8')).digest()).decode()
        hostile_html = html.replace(old_data, safe_hostile).replace(data_hash(old_data), data_hash(safe_hostile))
        page.route(base, lambda route: route.fulfill(body=hostile_html, content_type='text/html; charset=utf-8'))
        page.goto(base + '#/problem/' + hostile[0]['id'])
        page.reload()
        expect(page.locator('#detail-title')).to_have_text(hostile[0]['title'])
        expect(page.locator('.source-code code')).to_have_text(hostile[0]['code'])
        assert page.locator('#detail img').count() == 0
        assert page.evaluate('window.__injected') is None
        check('HTML-like titles and code are rendered as inert text')

        page.unroute(base)
        fallback_html = re.sub(r'<script id="problem-data" type="application/json">.*?</script>', '', html, flags=re.S)
        page.route(base, lambda route: route.fulfill(body=fallback_html, content_type='text/html; charset=utf-8'))
        page.route('**/problems.json', lambda route: route.fulfill(status=503, body='unavailable'))
        page.goto(base)
        expect(page.locator('#load-error')).to_be_visible()
        page.unroute('**/problems.json')
        page.get_by_role('button', name='重新載入', exact=True).click()
        expect(page.locator('.problem-row')).to_have_count(50)
        check('data-fetch failures provide a working retry')

        assert not errors, errors
        check('no uncaught browser errors')
        browser.close()
finally:
    server.shutdown()
    server.server_close()
print(f'{passed} browser checks passed')
