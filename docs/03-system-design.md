# GPE 題庫設計

## 架構與決策

- Python 3 標準函式庫建置：`python3 scripts/build.py`，從 repo 根目錄產生 `dist/`。不需安裝依賴。
- `content/problems.json` 保存人工整理的題意、標籤、步驟、複雜度、陷阱與來源；根目錄 `.cpp`／`.py` 是原始碼唯一來源。
- 讀檔依序嘗試 UTF-8、CP950，僅在產物正規化換行，保留原檔位元組。
- 建置時拒絕遺漏、多餘、重複題目、空欄位、不安全 ID 與非官方來源 URL；產物只有 `index.html`、`styles.css`、`app.js`、`problems.json`，不發布整個 repo。
- 原生 HTML／CSS／JavaScript。以 hash 路由 `#/problem/<id>` 支援子目錄部署與書籤；未知題目顯示錯誤及返回入口。
- 搜尋／語言／演算法篩選採交集，存在 URL 查詢字串；閱讀題目、返回列表或重新整理會保留篩選。
- PDF 透過明確按鈕按需載入官方站；保留另開來源選項，不以 iframe 是否載入判定內容正確或可達。
- 原始碼使用文字節點、下載 Blob 與 Clipboard API；無 eval、innerHTML 或遠端套件。
- 產出的 index.html 內嵌 CSS、module script 與 JSON，支援只提供單一 HTML 的檔案預覽。JSON 的 HTML 特殊字元先跳脫，CSS／JS 以 SHA-256 CSP hash 授權；不使用 unsafe-inline。外部 problems.json 保留給資料檢查，來源範本仍支援 fetch 模式。
- GitHub Pages workflow 僅上傳 dist，先跑標準函式庫測試再部署；GitHub Actions 依已核對的官方 tag commit 固定版本。
- 不建立收藏或帳號，先穩定內容與來源。

## 任務順序

資料盤點 → 50 題編輯內容 → 建置與資料驗證 → 列表／詳情頁 → 瀏覽器整合驗證 → 驗收紀錄。
