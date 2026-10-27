"""Content integrity and publication-boundary checks, no third-party packages."""
import importlib.util
import hashlib
import base64
import json
import re
from pathlib import Path
import subprocess
import unittest
from unittest.mock import patch
import tempfile

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('build', ROOT / 'scripts/build.py')
builder = importlib.util.module_from_spec(spec)
spec.loader.exec_module(builder)


class CatalogTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        subprocess.run(['python3', 'scripts/build.py'], cwd=ROOT, check=True)
        cls.problems = json.loads((ROOT / 'dist/problems.json').read_text(encoding='utf-8'))

    def test_every_archived_solution_is_available_once_and_unchanged(self):
        expected = {p.name for p in ROOT.iterdir() if p.suffix in ('.cpp', '.py')}
        self.assertEqual(len(self.problems), len(expected))
        self.assertEqual(len({p['id'] for p in self.problems}), len(expected))
        self.assertEqual({p['file'] for p in self.problems}, expected)
        for p in self.problems:
            self.assertEqual(p['code'], builder.read_source(ROOT / p['file']))

    def test_all_problem_details_have_useful_editorial_content(self):
        for p in self.problems:
            with self.subTest(problem=p['file']):
                self.assertGreater(len(p['summary']), 20)
                self.assertGreaterEqual(len(p['steps']), 3)
                self.assertTrue(p['complexity'])
                self.assertTrue(p['pitfalls'])
                self.assertEqual(p['editorialStatus'], 'code-derived')
                if p['originalStatus'] == 'verified':
                    self.assertTrue(p.get('sourceCheckedAt'))
                    self.assertTrue(p.get('originalTitle'))
                    self.assertRegex(p.get('originalSha256', ''), r'^[a-f0-9]{64}$')

    def test_ambiguous_numbers_are_not_linked_to_an_unrelated_uva_problem(self):
        for p in self.problems:
            if p['number'] in ('378', '24941') or not p['number']:
                self.assertIsNone(p['originalUrl'])
                self.assertEqual(p['source'], '待確認')

    def test_legacy_chinese_comments_survive_export(self):
        p = next(p for p in self.problems if p['number'] == '10308')
        self.assertIn('深度優先', p['code'])
        self.assertNotIn('\ufffd', p['code'])

    def test_build_publishes_only_explicit_web_assets(self):
        self.assertEqual({p.name for p in (ROOT / 'dist').iterdir()}, {'index.html', 'app.js', 'styles.css', 'problems.json'})
        self.assertNotIn('AGENTS.md', (ROOT / 'dist/index.html').read_text())

    def test_single_html_contains_assets_and_script_safe_data_with_valid_csp(self):
        html = (ROOT / 'dist/index.html').read_text(encoding='utf-8')
        self.assertNotIn('href="./styles.css"', html)
        self.assertNotIn('src="./app.js"', html)
        data = re.search(r'<script id="problem-data" type="application/json">(.*?)</script>', html, re.S).group(1)
        self.assertEqual(json.loads(data), self.problems)
        self.assertNotIn('<', data)
        blocks = [data, re.search(r'<style>(.*?)</style>', html, re.S).group(1), re.search(r'<script type="module">(.*?)</script>', html, re.S).group(1)]
        for block in blocks:
            digest = base64.b64encode(hashlib.sha256(block.encode('utf-8')).digest()).decode()
            self.assertIn("'sha256-" + digest + "'", html)
        self.assertNotIn('unsafe-inline', html)

    def assert_rejected(self, mutate):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            (root / 'content').mkdir()
            source = ROOT / self.problems[0]['file']
            (root / source.name).write_bytes(source.read_bytes())
            p = dict(self.problems[0])
            mutate(p)
            (root / 'content/problems.json').write_text(json.dumps([p]))
            with patch.object(builder, 'ROOT', root), self.assertRaises(ValueError):
                builder.load_problems()

    def test_unsafe_source_urls_are_rejected(self):
        for url in ('javascript:alert(1)', 'https://example.com/problem', 'https://onlinejudge.org@evil.example/problem', 'http://onlinejudge.org/problem'):
            with self.subTest(url=url):
                self.assert_rejected(lambda p: p.update(originalUrl=url))

    def test_missing_solutions_and_fake_verification_fail_build(self):
        self.assert_rejected(lambda p: p.update(file='../outside.cpp'))
        self.assert_rejected(lambda p: p.update(originalStatus='verified', sourceCheckedAt=''))
        self.assert_rejected(lambda p: p.update(originalStatus='verified', originalSha256=''))
        self.assert_rejected(lambda p: p.update(steps=[]))


if __name__ == '__main__':
    unittest.main()
