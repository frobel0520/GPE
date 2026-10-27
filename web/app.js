'use strict';

const $ = (selector) => document.querySelector(selector);
let problems = [];
let previousRoute = '';
const controls = { q: $('#query'), language: $('#language'), tag: $('#tag') };

function element(tag, className, text) {
  const node = document.createElement(tag);
  if (className) node.className = className;
  if (text !== undefined) node.textContent = text;
  return node;
}

function filters() {
  return new URLSearchParams(location.search);
}

function listUrl() {
  return location.pathname + location.search + '#/';
}

function syncControls() {
  const params = filters();
  for (const [key, control] of Object.entries(controls)) {
    control.value = params.get(key) || '';
  }
}

function updateFilters() {
  const params = new URLSearchParams();
  for (const [key, control] of Object.entries(controls)) {
    if (control.value.trim()) params.set(key, control.value.trim());
  }
  history.replaceState(null, '', location.pathname + (params.size ? '?' + params : '') + '#/');
  renderList();
}

function reset() {
  for (const control of Object.values(controls)) control.value = '';
  updateFilters();
  controls.q.focus();
}

function renderList() {
  const params = filters();
  const terms = (params.get('q') || '').normalize('NFKC').toLocaleLowerCase().trim().split(/\s+/).filter(Boolean);
  const language = params.get('language') || '';
  const tag = params.get('tag') || '';
  const visible = problems.filter((p) => {
    const haystack = [p.number, p.title, p.titleZh, p.summary, p.language, ...p.tags].join(' ').normalize('NFKC').toLocaleLowerCase();
    return (!language || p.language === language) && (!tag || p.tags.includes(tag)) && terms.every((term) => haystack.includes(term));
  });
  $('#result-count').textContent = `${visible.length} / ${problems.length} 道題目`;
  $('#empty').hidden = visible.length > 0;
  const fragment = document.createDocumentFragment();
  for (const p of visible) {
    const link = element('a', 'problem-row');
    link.href = '#/problem/' + p.id;
    const number = element('span', 'problem-number', p.number || '—');
    const body = element('div', 'problem-row-body');
    body.append(element('h2', '', p.title), element('p', 'problem-zh', p.titleZh));
    const tags = element('div', 'tags');
    for (const tag of p.tags) tags.append(element('span', 'tag', tag));
    body.append(tags);
    const meta = element('div', 'problem-meta');
    meta.append(element('span', 'language-chip', p.language), element('span', 'source-label', p.source === 'UVa' ? (p.originalStatus === 'verified' ? 'UVa · 原文已核對' : 'UVa · 原文待核對') : '來源待確認'));
    const arrow = element('span', 'row-arrow', '↗');
    arrow.setAttribute('aria-hidden', 'true');
    link.append(number, body, meta, arrow);
    fragment.append(link);
  }
  $('#problem-list').replaceChildren(fragment);
}

function section(number, heading, id) {
  const node = element('section', 'reading-section');
  node.id = id;
  const header = element('div', 'section-heading');
  header.append(element('span', 'section-number', number), element('h2', '', heading));
  node.append(header);
  return node;
}

function sourceSection(p) {
  const node = section('01', '題目原文', 'original');
  if (!p.originalUrl) {
    node.append(element('p', 'muted', '這份歷史解答尚未確認原題來源。以下中文說明依現有程式整理，完整限制與輸入輸出格式仍需核對。'));
    return node;
  }
  node.append(element('p', 'muted', p.originalStatus === 'verified'
    ? '題意與來源已核對，請以官方原文的限制與輸出格式為準。'
    : '依題號與名稱整理的 UVa 官方 PDF 連結，尚未核對原文。中文摘要依現有程式整理；完整限制、圖例與格式請以核對後的原文為準。'));
  const actions = element('div', 'source-actions');
  const link = element('a', 'primary-button', '前往官方原文 ↗');
  link.href = p.originalUrl;
  link.target = '_blank';
  link.rel = 'noopener noreferrer';
  const preview = element('button', 'secondary-button', '在此閱讀 PDF');
  preview.type = 'button';
  preview.setAttribute('aria-expanded', 'false');
  preview.setAttribute('aria-controls', 'pdf-reader');
  const reader = element('div', 'pdf-reader');
  reader.id = 'pdf-reader';
  reader.hidden = true;
  preview.addEventListener('click', () => {
    reader.hidden = !reader.hidden;
    preview.setAttribute('aria-expanded', String(!reader.hidden));
    preview.textContent = reader.hidden ? '在此閱讀 PDF' : '收起 PDF';
    if (!reader.childElementCount) {
      const frame = element('iframe');
      frame.src = p.originalUrl;
      frame.title = `${p.title} 官方題目 PDF`;
      frame.referrerPolicy = 'no-referrer';
      reader.append(frame, element('p', 'muted', '若瀏覽器或來源網站無法顯示 PDF，請使用上方的官方原文連結。'));
    }
  });
  actions.append(link, preview);
  node.append(actions, reader);
  return node;
}

function showProblem(p) {
  const article = $('#detail');
  const back = element('a', 'back-link', '← 返回全部題目');
  back.href = listUrl();
  const header = element('header', 'detail-header');
  header.append(element('p', 'eyebrow', `${p.number || 'PRACTICE'} / ${p.language}`), element('h1', '', p.title));
  header.querySelector('h1').id = 'detail-title';
  header.querySelector('h1').tabIndex = -1;
  header.append(element('p', 'detail-subtitle', p.titleZh));
  const tags = element('div', 'tags');
  for (const tag of p.tags) tags.append(element('span', 'tag', tag));
  header.append(tags);
  const nav = element('nav', 'reading-nav');
  nav.setAttribute('aria-label', '題解段落');
  for (const [id, label] of [['original', '題目原文'], ['summary', '白話題意'], ['steps', '解題步驟'], ['code', '程式碼']]) {
    const button = element('button', 'text-button', label);
    button.type = 'button';
    button.addEventListener('click', () => document.getElementById(id).scrollIntoView({ behavior: matchMedia('(prefers-reduced-motion: reduce)').matches ? 'instant' : 'smooth' }));
    nav.append(button);
  }
  const summary = section('02', '這題要做什麼？', 'summary');
  summary.append(element('p', 'summary-text', p.summary), element('p', 'editorial-note', '白話摘要 · 依歷史解答整理，非原題逐字翻譯。'));
  const steps = section('03', '把思路拆開來看', 'steps');
  const list = element('ol', 'steps');
  for (const step of p.steps) list.append(element('li', '', step));
  const complexity = element('div', 'complexity-box');
  complexity.append(element('h3', '', '時間與空間'), element('p', '', p.complexity));
  const pitfalls = element('div', 'pitfalls');
  pitfalls.append(element('h3', '', '留意這裡'));
  for (const pitfall of p.pitfalls) pitfalls.append(element('p', '', pitfall));
  steps.append(list, complexity, pitfalls);
  const code = section('04', '回到程式碼', 'code');
  const codeNote = p.codeStatus === 'compile-error'
    ? '這份歷史解答目前無法編譯，原因請參考上方提醒。以下保留當時的原始碼。'
    : p.codeStatus === 'syntax-passed'
      ? '保留當時的原始解答；已通過 C++17 語法編譯檢查，尚未逐題通過評測驗證。'
      : '保留當時的原始解答，尚未逐題通過評測驗證；已知問題請參考上方提醒。';
  code.append(element('p', 'muted', codeNote));
  const toolbar = element('div', 'code-toolbar');
  toolbar.append(element('span', 'code-filename', p.file));
  const actions = element('div', 'code-actions');
  const copy = element('button', 'code-button', '複製');
  copy.type = 'button';
  const status = element('span', 'copy-status');
  status.setAttribute('role', 'status');
  copy.addEventListener('click', async () => {
    try {
      await navigator.clipboard.writeText(p.code);
      status.textContent = '已複製程式碼';
    } catch {
      status.textContent = '無法自動複製，請選取下方程式碼複製。';
    }
  });
  const download = element('button', 'code-button', '下載');
  download.type = 'button';
  download.addEventListener('click', () => {
    const url = URL.createObjectURL(new Blob([p.code], { type: 'text/plain;charset=utf-8' }));
    const anchor = element('a');
    anchor.href = url;
    anchor.download = p.file;
    document.body.append(anchor);
    anchor.click();
    anchor.remove();
    setTimeout(() => URL.revokeObjectURL(url), 1000);
  });
  actions.append(copy, download);
  toolbar.append(actions);
  const pre = element('pre', 'source-code');
  pre.tabIndex = 0;
  pre.setAttribute('aria-label', `${p.language} 原始程式碼`);
  pre.append(element('code', '', p.code));
  code.append(toolbar, status, pre);
  article.replaceChildren(back, header, nav, sourceSection(p), summary, steps, code);
  document.title = `${p.number ? p.number + ' · ' : ''}${p.title} — GPE`;
}

function renderRoute() {
  let hash;
  try { hash = decodeURIComponent(location.hash || '#/'); } catch { hash = '#invalid'; }
  const catalog = hash === '#/' || hash === '#main';
  $('#catalog').hidden = !catalog;
  $('#detail').hidden = catalog;
  if (catalog) {
    document.title = 'GPE — 解題筆記';
    syncControls();
    renderList();
  } else {
    const match = /^#\/problem\/([a-z0-9-]+)$/.exec(hash);
    const p = match && problems.find((p) => p.id === match[1]);
    if (p) showProblem(p);
    else {
      const h1 = element('h1', '', '找不到這道題');
      h1.id = 'detail-title';
      const back = element('a', 'back-link', '← 返回全部題目');
      back.href = listUrl();
      $('#detail').replaceChildren(h1, element('p', 'muted', '題目網址可能有誤，請返回題庫重新尋找。'), back);
      document.title = '找不到題目 — GPE';
    }
  }
  if (previousRoute !== hash) {
    window.scrollTo(0, 0);
    if (!catalog) $('#detail-title').focus?.();
    else if (previousRoute) $('#catalog-heading').focus?.();
  }
  previousRoute = hash;
}

async function init() {
  try {
    const embedded = $('#problem-data');
    if (embedded) {
      problems = JSON.parse(embedded.textContent);
    } else {
      const response = await fetch('./problems.json');
      if (!response.ok) throw new Error('Problem data unavailable');
      problems = await response.json();
    }
    $('#total-count').textContent = problems.length;
    const tags = [...new Set(problems.flatMap((p) => p.tags))].sort((a, b) => a.localeCompare(b, 'zh-Hant'));
    for (const tag of tags) {
      const option = element('option', '', tag);
      option.value = tag;
      controls.tag.append(option);
    }
    $('#load-error').hidden = true;
    renderRoute();
  } catch {
    $('#catalog').hidden = false;
    $('#detail').hidden = true;
    $('#load-error').hidden = false;
    $('#result-count').textContent = '無法載入題庫';
  }
}

for (const control of Object.values(controls)) control.addEventListener(control === controls.q ? 'input' : 'change', updateFilters);
$('#reset').addEventListener('click', reset);
$('#empty-reset').addEventListener('click', reset);
$('#retry').addEventListener('click', () => location.reload());
window.addEventListener('hashchange', renderRoute);
window.addEventListener('popstate', renderRoute);
init();
