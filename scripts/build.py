#!/usr/bin/env python3
"""Build the practice library using only Python's standard library."""
import json
import base64
import hashlib
from pathlib import Path
import re
import shutil
from urllib.parse import urlparse

ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / 'dist'


def read_source(path):
    raw = path.read_bytes()
    for encoding in ('utf-8', 'cp950'):
        try:
            return raw.decode(encoding).replace('\r\n', '\n')
        except UnicodeDecodeError:
            pass
    raise ValueError(f'Unsupported source encoding: {path.name}')


def load_problems():
    problems = json.loads((ROOT / 'content/problems.json').read_text(encoding='utf-8'))
    expected = {p.name for p in ROOT.iterdir() if p.suffix in ('.cpp', '.py') and p.is_file()}
    files, ids = set(), set()
    required = ('id', 'file', 'title', 'titleZh', 'language', 'tags', 'summary',
                'steps', 'complexity', 'pitfalls', 'source', 'originalStatus',
                'editorialStatus', 'codeStatus')
    for problem in problems:
        if any(not problem.get(key) for key in required):
            raise ValueError(f'Missing editorial content: {problem.get("file")}')
        filename, ident = problem['file'], problem['id']
        if filename not in expected or filename in files:
            raise ValueError(f'Unknown or duplicate source: {filename}')
        if not re.fullmatch(r'[a-z0-9-]+', ident) or ident in ids:
            raise ValueError(f'Unsafe or duplicate ID: {ident}')
        if any(not isinstance(problem[k], list) or not all(isinstance(s, str) and s.strip() for s in problem[k]) for k in ('tags', 'steps', 'pitfalls')):
            raise ValueError(f'Invalid editorial lists: {filename}')
        url = problem.get('originalUrl')
        if url:
            parsed = urlparse(url)
            if (parsed.scheme != 'https' or parsed.hostname not in ('onlinejudge.org', 'www.onlinejudge.org', 'zerojudge.tw')
                    or parsed.username or parsed.password or parsed.port):
                raise ValueError(f'Untrusted original source: {filename}')
        if problem['originalStatus'] not in ('verified', 'unverified', 'unknown'):
            raise ValueError(f'Unknown original status: {filename}')
        if problem['originalStatus'] == 'verified' and not problem.get('sourceCheckedAt'):
            raise ValueError(f'Verification evidence is missing: {filename}')
        problem['code'] = read_source(ROOT / filename)
        files.add(filename)
        ids.add(ident)
    if files != expected:
        raise ValueError(f'Missing sources: {sorted(expected - files)}')
    return sorted(problems, key=lambda p: (not bool(p['number']), int(p['number'].lstrip('p') or 0), p['title']))


def build():
    problems = load_problems()  # Validate before replacing any generated files.
    OUTPUT.mkdir(exist_ok=True)
    for name in ('styles.css', 'app.js'):
        shutil.copyfile(ROOT / 'web' / name, OUTPUT / name)
    data = json.dumps(problems, ensure_ascii=False, indent=2)
    (OUTPUT / 'problems.json').write_text(data + '\n', encoding='utf-8')
    # A file preview may serve only index.html, with no sibling assets or fetch route.
    # Embed the exact same data and assets, while retaining CSP without unsafe-inline.
    style = (ROOT / 'web/styles.css').read_text(encoding='utf-8').removeprefix('@charset "UTF-8";\n')
    script = (ROOT / 'web/app.js').read_text(encoding='utf-8')
    if '</script' in script.lower() or '</style' in style.lower():
        raise ValueError('Inline asset contains an unsafe HTML closing tag')
    safe_data = data.replace('<', '\\u003c').replace('>', '\\u003e').replace('&', '\\u0026')

    def csp_hash(content):
        digest = base64.b64encode(hashlib.sha256(content.encode('utf-8')).digest()).decode('ascii')
        return "'sha256-" + digest + "'"

    html = (ROOT / 'web/index.html').read_text(encoding='utf-8')
    html = html.replace("script-src 'self'", "script-src 'self' " + csp_hash(script) + ' ' + csp_hash(safe_data))
    html = html.replace("style-src 'self'", "style-src 'self' " + csp_hash(style))
    html = html.replace('<link rel="stylesheet" href="./styles.css">', '<style>' + style + '</style>')
    html = html.replace('  <script src="./app.js" defer></script>\n', '')
    embedded = '<script id="problem-data" type="application/json">' + safe_data + '</script>\n'
    embedded += '<script type="module">' + script + '</script>\n'
    html = html.replace('</body>', embedded + '</body>')
    (OUTPUT / 'index.html').write_text(html, encoding='utf-8')
    print(f'Built {len(problems)} problems in dist/')


if __name__ == '__main__':
    build()
