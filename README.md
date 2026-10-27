# GPE

> Programming-exam practice archive and a searchable Traditional Chinese study library.

## Overview

- **50 solutions**: 49 in C++, 1 in Python.
- File names follow `<problem number> - <title>.<ext>`; problems without a number are listed by title only.
- The original solution files are retained unchanged; the web library adds summaries, walkthroughs, complexity notes, and caveats.

## Main features and content

The repository contains 50 programming-exam solutions: 49 C++ files and one Python file. The website lists all of them, with number/title/Chinese keyword search, language and algorithm filters, shareable detail pages, and code copy/download.

## Study library

Python 3 is the only build prerequisite. From the repository root:

```bash
python3 scripts/build.py
python3 -m unittest discover -s tests -p 'test_*.py' -v
python3 -m http.server 8000 --bind 127.0.0.1 --directory dist
```

Serve **only `dist/`**, which contains the four public website assets. Do not serve the checkout root. Stop the local server with Ctrl+C.

The generated `dist/index.html` also embeds its CSS, JavaScript and all 50 problem entries, so an HTML file preview does not need to load sibling files. Open the generated file rather than `web/index.html`, which is the source template. Inline assets use content hashes in the Content Security Policy; no `unsafe-inline` is enabled.

## GitHub Pages

`.github/workflows/pages.yml` builds and tests on pushes to `main` or a manual run, then publishes only `dist/` to GitHub Pages. The workflow requests Pages enablement; if repository settings require owner action, select **GitHub Actions** under Settings → Pages → Build and deployment and rerun it. A successful local build or push is not proof the site has deployed; verify the workflow result and public page after publishing.

Editorial content lives in `content/problems.json`; source code is read directly from the original solution files during the build. UTF-8 and legacy CP950 comments are supported without rewriting those files. Add a new solution and its matching editorial entry together: the build rejects missing, duplicate, or unsafe entries.

Optional browser checks require Python Playwright and an installed Chromium browser. In an environment providing these tools, run `python3 tests/browser_checks.py`; the checks launch their own temporary local server. They cover all 50 detail pages, search/filter/navigation, mobile layout, clipboard/download, error recovery, and inert rendering of HTML-like source text.

The SDLC notes and current acceptance evidence are in `docs/01-project-plan.md` through `docs/04-mvp-release-gate.md`.

## Status and known limitations

- Chinese explanations are code-derived summaries, not verified full translations of the original statements.
- 43 entries have candidate official UVa PDF links. These have not yet been checked against the original statements because the current environment denies those destinations. Seven entries have no confirmed original source; filenames alone do not prove judge identity.
- PDF viewing is on demand and depends on browser/site support; the external official link remains available. Original statements are not copied into this repository.
- Historical source code is not guaranteed accepted or correct. Known concerns appear alongside the explanation; syntax compilation does not establish runtime correctness.

## License and sources

No license file is present in the repository root; this README does not declare reuse rights. Problem statements remain at their original sources. Newly written summaries are kept distinct from original statements; source identity, statement matching, and any permission needed for full reproduction must be checked before adding original full text.

---

## Build and run

C++ files use `#include <bits/stdc++.h>` and read from standard input:

```bash
g++ -std=c++17 -O2 "572 - Oil Deposit.cpp" -o solution
./solution < input.txt
```

Python:

```bash
python "10007 - Count the Trees.py" < input.txt
```

## Problems

| Problem | Language |
|---|---|
| 147 - Dollars | C++ |
| 151 - Power Crisis | C++ |
| 166 - Making Change | C++ |
| 256 - Quirksome Squares | C++ |
| 378 - Unique Lines | C++ |
| 382 - Perfection | C++ |
| 572 - Oil Deposit | C++ |
| 719 - Glass Beads | C++ |
| 900 - Brick Wall Patterns | C++ |
| 10007 - Count the Trees | Python |
| 10015 - Joseph's Cousin | C++ |
| 10036 - Divisibility | C++ |
| 10074 - Take the Land | C++ |
| 10081 - Tight Words | C++ |
| 10110 - Light, more light | C++ |
| 10125 - Sumsets | C++ |
| 10162 - Last Digit | C++ |
| 10169 - Urn-ball Probabilities | C++ |
| 10170 - The Hotel with Infinite Rooms | C++ |
| 10182 - Bee Maja | C++ |
| 10188 - Automated Judge Script | C++ |
| 10193 - All You Need Is Love | C++ |
| 10209 - Is This Integration | C++ |
| 10220 - I Love Big Numbers | C++ |
| 10252 - Common Permutation | C++ |
| 10295 - Hay Points | C++ |
| 10308 - Roads in the North | C++ |
| 10324 - Zeros and Ones | C++ |
| 10336 - Rank the Languages | C++ |
| 10404 - Bachet's Game | C++ |
| 10405 - Longest Common Subsequence | C++ |
| 10409 - Die Game | C++ |
| 10533 - Digit Primes | C++ |
| 10664－Luggage | C++ |
| 10718 - Bit Mask | C++ |
| 10908 - Largest Square | C++ |
| 10912 - Simple Minded Hashing | C++ |
| 11150 - Cola | C++ |
| 11286 - Conformity | C++ |
| 11309 - Counting Chaos | C++ |
| 11413 - Fill the Containers | C++ |
| 11634 - Generate random numbers | C++ |
| 12503 - Robot Instructions | C++ |
| 24941 - Uncompress | C++ |
| Binary Tree Traversals | C++ |
| Longest Increasing Subsequence | C++ |
| Longest Monotonically Increasing Subsequence | C++ |
| Minimum Path Sum | C++ |
| Prefix Expression Evaluation | C++ |
| p1210 - Sum of Consecutive Prime Numbers | C++ |
