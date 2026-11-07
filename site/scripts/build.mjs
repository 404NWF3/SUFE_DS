import { execFileSync } from "node:child_process";
import {
  readFile,
  writeFile,
  mkdir,
  rm,
  copyFile,
  cp,
  stat,
} from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";
import {
  repository,
  base,
  siteUrl,
  groups,
  courseDefinitions,
  featuredPaths,
  featuredCourses,
} from "../src/config.mjs";
import {
  escapeHtml as e,
  encodePath,
  resourceId,
  sizeLabel,
  normalizeSearch,
  textSummary,
  markdownTitle,
  createResolver,
  renderMarkdown,
} from "./content.mjs";

const site = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const root = path.dirname(site);
const dist = path.join(site, "dist");
const git = (args) =>
  execFileSync("git", args, {
    cwd: root,
    encoding: "utf8",
    maxBuffer: 16 * 1024 * 1024,
  }).trim();
const ref = process.env.GITHUB_SHA || git(["rev-parse", "HEAD"]);
const repoUrl = `https://github.com/${repository}`;
const files = git(["ls-files", "-z"]).split("\0").filter(Boolean);
const allowed = new Set([
  "md",
  "pdf",
  "doc",
  "docx",
  "ppt",
  "pptx",
  "xls",
  "xlsx",
  "zip",
  "7z",
  "rar",
  "mp3",
  "m4a",
  "wav",
  "mp4",
  "ipynb",
  "cpp",
  "c",
  "py",
  "h",
  "txt",
  "tex",
  "typ",
  "csv",
  "tsv",
  "url",
  "accdb",
  "mdb",
  "lrc",
]);
const courses = courseDefinitions.map(([folder, id, group, description]) => ({
  folder,
  id,
  group,
  description,
  title: folder === "for fun" ? "课外探索" : folder,
  resources: [],
}));
const extras = {
  folder: "",
  id: "more-resources",
  group: "exam",
  title: "其他学习资料",
  description: "更多值得收藏的学习参考。",
  resources: [],
};
const byFolder = new Map(courses.map((c) => [c.folder, c]));
const resources = [];
for (const file of files) {
  if (
    file.split("/").some((segment) => segment.startsWith(".")) ||
    /(?:^|\/)~\$/.test(file)
  )
    continue;
  const format = path.posix.extname(file).slice(1).toLowerCase();
  if (
    !allowed.has(format) ||
    /^readme(?:\.[a-z]+)?\.md$/i.test(path.posix.basename(file))
  )
    continue;
  let course = byFolder.get(file.split("/")[0]);
  if (!course && !file.includes("/") && format !== "md") course = extras;
  if (!course) continue;
  let size = null;
  try {
    size = (await stat(path.join(root, file))).size;
  } catch {
    /* Binary files need not be checked out in CI. */
  }
  const resource = {
    id: resourceId(file),
    path: file,
    course,
    format,
    size,
    title: path.posix.basename(file, `.${format}`),
    summary: "",
  };
  if (format === "md") {
    resource.markdown = await readFile(path.join(root, file), "utf8");
    if (!resource.markdown.trim()) continue;
    resource.title = markdownTitle(resource.markdown, file);
    resource.summary = textSummary(resource.markdown)
      .replace(resource.title, "")
      .trim()
      .slice(0, 115);
  } else if (format === "url") {
    const shortcut = await readFile(path.join(root, file), "utf8");
    const target = shortcut.match(/^URL=(https?:\/\/[^\r\n]+)/m)?.[1];
    if (target) resource.externalUrl = target;
  }
  resources.push(resource);
  course.resources.push(resource);
}
if (extras.resources.length) courses.push(extras);
for (const c of courses) {
  c.resources.sort(
    (a, b) =>
      (b.format === "md") - (a.format === "md") ||
      a.path.localeCompare(b.path, "zh-CN", { numeric: true }),
  );
  c.notes = c.resources.filter((r) => r.format === "md");
}
const ids = resources.map((r) => r.id);
if (new Set(ids).size !== ids.length) throw new Error("Resource ID collision");
const notes = resources.filter((r) => r.format === "md");
const downloads = resources.filter((r) => r.format !== "md" && !r.externalUrl);
const resolver = createResolver({
  files,
  resources,
  repo: repository,
  ref,
  base,
});
const href = (resource) =>
  resource.format === "md"
    ? `${base}notes/${resource.id}/`
    : resource.externalUrl || resolver.downloadUrl(resource.path);
const courseHref = (course) => `${base}courses/${course.id}/`;
const groupFor = (course) => groups.find((group) => group.id === course.group);
const iconPaths = {
  arrow: '<path d="M4 12h15m-6-6 6 6-6 6"/>',
  diagonal: '<path d="M6 18 18 6M6 6h12v12"/>',
  search: '<circle cx="10.5" cy="10.5" r="6.5"/><path d="m16 16 5 5"/>',
  download: '<path d="M12 3v12m-5-5 5 5 5-5M5 16v5h14v-5"/>',
  book: '<path d="M12 5C8 2 4 3 2 4v15c4-2 7-1 10 1 3-2 6-3 10-1V4c-4-2-7-1-10 1Zm0 0v15"/>',
  file: '<path d="M14 2H5v20h14V7l-5-5Zm0 0v6h5M8 12h8m-8 4h6"/>',
  github:
    '<path d="M9 19c-4 1-4-2-6-2m12 5v-4c0-1-.3-2-1-2 3-.4 6-1.5 6-6a4 4 0 0 0-1-3c.1-1 .1-2-.4-3-2 0-3 1-4 1a12 12 0 0 0-6 0c-1 0-2-1-4-1-.5 1-.5 2-.4 3a4 4 0 0 0-1 3c0 4.5 3 5.6 6 6-.7.7-1 1.5-1 2v4"/>',
  menu: '<path d="M4 7h16M4 12h16M4 17h16"/>',
  copy: '<rect x="8" y="8" width="12" height="13" rx="2"/><path d="M16 8V3H3v13h5"/>',
  check: '<path d="m5 12 4 4L19 6"/>',
};
const icon = (name, cls = "") =>
  `<svg class="icon ${cls}" width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.65" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true">${iconPaths[name] || iconPaths.file}</svg>`;
const badge = (text, cls = "") =>
  `<span class="badge ${cls}">${e(text)}</span>`;
const external = 'target="_blank" rel="noopener noreferrer"';
const brand = `<span class="brand-mark" aria-hidden="true">s<span>.</span></span><span class="brand-type">SUFE <strong>DS</strong><small>上财学习资料库</small></span>`;
function layout({
  title,
  description = "上财学生共建的课程资料库。在线阅读学习笔记，查找课程资料，下载所需文件。",
  body,
  active = "",
  pathname = "",
  isNote = false,
}) {
  return `<!doctype html><html lang="zh-CN"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>${e(title)} · SUFE DS</title><meta name="description" content="${e(description)}"><meta name="theme-color" content="#f7f8f2"><link rel="icon" href="${base}assets/favicon.svg" type="image/svg+xml"><link rel="canonical" href="${siteUrl}${base}${pathname}"><meta property="og:title" content="${e(title)} · SUFE DS"><meta property="og:description" content="${e(description)}"><meta property="og:type" content="${isNote ? "article" : "website"}"><meta property="og:url" content="${siteUrl}${base}${pathname}"><link rel="stylesheet" href="${base}assets/style.css">${isNote ? `<link rel="stylesheet" href="${base}assets/katex/katex.min.css">` : ""}<script src="${base}assets/app.js" defer></script></head><body class="${isNote ? "reading-page" : ""}"><a class="skip-link" href="#main">跳到主要内容</a><header class="header"><div class="header-inner"><a class="brand" href="${base}" aria-label="SUFE DS 首页">${brand}</a><nav class="nav" aria-label="主导航"><a ${active === "home" ? 'aria-current="page"' : ""} href="${base}">首页</a><a ${active === "courses" ? 'aria-current="page"' : ""} href="${base}courses/">课程目录</a><a ${active === "resources" ? 'aria-current="page"' : ""} href="${base}resources/">全部资料</a><a ${active === "about" ? 'aria-current="page"' : ""} href="${base}about/">关于</a></nav><a class="github-link" href="${repoUrl}" ${external}>${icon("github")}<span>GitHub</span>${icon("diagonal")}</a><button class="mobile-menu" aria-label="展开导航" aria-expanded="false">${icon("menu")}</button></div></header><main id="main">${body}</main><footer class="footer"><div class="container footer-inner"><div><a class="brand footer-brand" href="${base}">${brand}</a><p>让整理过的知识，走得更远一点。</p></div><div class="footer-links"><a href="${base}courses/">浏览课程</a><a href="${base}about/">关于与贡献</a><a href="${repoUrl}" ${external}>GitHub ${icon("diagonal")}</a><span>学生自发共建 · 非学校官方网站</span></div></div><div class="container footer-bottom"><span>资料仅供学习交流，版权归原作者所有。</span><span>Made for learning, shared with everyone.</span></div></footer><div class="toast" role="status" aria-live="polite"></div></body></html>`;
}
function sectionTitle(kicker, title, aside = "") {
  return `<div class="section-heading"><div><p class="eyebrow">${kicker}</p><h2>${title}</h2></div>${aside}</div>`;
}
function courseCard(c, number) {
  const group = groupFor(c);
  return `<a class="course-card" href="${courseHref(c)}" data-group="${c.group}" data-search="${e(normalizeSearch(c.title + " " + group.title + " " + c.description))}"><div class="course-top"><span class="subject-symbol ${group.color}">${group.symbol}</span><span class="course-number">${String(number + 1).padStart(2, "0")}</span></div><h3>${e(c.title)}</h3><p>${e(c.description)}</p><div class="course-bottom"><span>${c.resources.length} 份资料${c.notes.length ? ` <b>·</b> ${c.notes.length} 篇笔记` : ""}</span>${icon("arrow")}</div></a>`;
}
function noteCard(resource, index) {
  const styles = ["sage", "sand", "blue"];
  const coverText = [
    "STATISTICAL<br>THINKING.",
    "THINK IN<br>ALGORITHMS.",
    "FIND THE<br>OPTIMUM.",
  ];
  return `<article class="note-card"><a href="${href(resource)}" class="note-cover ${styles[index]}"><span class="cover-course">${e(resource.course.title)}<span>NO. 0${index + 1}</span></span><span class="cover-word">${coverText[index]}</span><span class="cover-line"><span>学习笔记 / READING NOTES</span>${icon("diagonal")}</span></a><div class="note-card-body">${badge("在线阅读", "green")}<h3><a href="${href(resource)}">${e(resource.title)}</a></h3><p>${e(resource.summary)}</p><div class="note-card-bottom"><span>Markdown <b>·</b> ${Math.max(1, Math.round(resource.markdown.length / 600))} 分钟阅读</span><a href="${href(resource)}" aria-label="阅读${e(resource.title)}">${icon("arrow")}</a></div></div></article>`;
}
function searchForm(placeholder = "搜索课程、笔记或文件名", value = "") {
  return `<form class="search-form" action="${base}resources/" role="search"><label class="sr-only" for="search-input">搜索资料</label>${icon("search")}<input id="search-input" name="q" type="search" placeholder="${placeholder}" value="${e(value)}" autocomplete="off"><kbd aria-hidden="true">/</kbd><button type="submit" aria-label="搜索">${icon("arrow")}</button></form>`;
}
function fileRow(r, index) {
  const readable = r.format === "md";
  return `<article class="file-row" data-search="${e(normalizeSearch(`${r.title} ${r.path} ${r.summary} ${r.course.title}`))}" data-format="${r.format}" data-kind="${readable ? "note" : "file"}" data-order="${index}" ${index >= 24 ? "hidden" : ""}><span class="file-type ${readable ? "md" : ""}" aria-hidden="true">${readable ? icon("book") : icon("file")}<small>${r.externalUrl ? "LINK" : e(r.format.toUpperCase())}</small></span><div class="file-info"><h3><a href="${href(r)}" ${readable ? "" : external}>${e(r.title)}</a></h3><p><a href="${courseHref(r.course)}">${e(r.course.title)}</a><span class="file-path">${e(path.posix.dirname(r.path).split("/").slice(1).join(" / "))}</span></p></div><span class="file-size">${r.size === null ? r.format.toUpperCase() : sizeLabel(r.size)}</span><div class="file-actions">${readable ? `<a class="text-link read-link" href="${href(r)}">阅读 ${icon("arrow")}</a>` : ""}<a class="download-link" href="${r.externalUrl || resolver.downloadUrl(r.path)}" ${readable ? `data-download-md="${resolver.rawUrl(r.path)}" data-filename="${e(path.posix.basename(r.path))}"` : ""} ${external} aria-label="${r.externalUrl ? "打开原站" : "下载"} ${e(r.title)}">${icon(r.externalUrl ? "diagonal" : "download")}<span>${r.externalUrl ? "原站" : "下载"}</span></a></div></article>`;
}
function library(items, title = "全部资料", course = null) {
  const formats = [...new Set(items.map((r) => r.format))].sort();
  return `<section class="library" data-library><div class="library-toolbar"><div class="filter-tabs" role="group" aria-label="资料类型"><button class="active" data-kind-filter="all" aria-pressed="true">全部 <span>${items.length}</span></button><button data-kind-filter="note" aria-pressed="false">在线笔记 <span>${items.filter((r) => r.format === "md").length}</span></button><button data-kind-filter="file" aria-pressed="false">下载资料 <span>${items.filter((r) => r.format !== "md").length}</span></button></div><div class="format-filter"><label class="sr-only" for="format-filter">文件格式</label><select id="format-filter"><option value="all">所有格式</option>${formats.map((f) => `<option value="${f}">${f.toUpperCase()}</option>`).join("")}</select></div></div><div class="results-meta"><span id="result-count" aria-live="polite">共 ${items.length} 份资料</span><span>Markdown 在线阅读 · 其他文件直接下载</span></div><div class="file-list">${items.map(fileRow).join("")}</div><div class="empty-state" hidden><span class="empty-icon">${icon("search")}</span><h3>还没有找到匹配的资料</h3><p>试试课程名或更短的关键词，也可以清除筛选重新查找。</p><button class="button secondary" data-clear>清除搜索与筛选</button></div><div class="pagination"><span data-page-label>第 1 页</span><div><button data-prev aria-label="上一页">← 上一页</button><button data-next aria-label="下一页">下一页 →</button></div></div><noscript><style>.file-list .file-row[hidden]{display:grid}.pagination,.library-toolbar{display:none}</style><p>搜索与筛选需要 JavaScript。所有资料已在下方列出，也可以按课程浏览。</p></noscript></section>`;
}

await rm(dist, { recursive: true, force: true });
await mkdir(path.join(dist, "assets"), { recursive: true });
const writePage = async (pathname, html) => {
  const file = path.join(dist, pathname, "index.html");
  await mkdir(path.dirname(file), { recursive: true });
  await writeFile(file, html);
};
const pickedNotes = featuredPaths
  .map((p) => resources.find((r) => r.path === p))
  .filter(Boolean);
const heroNote = pickedNotes[0] || notes[0];
const home = `<div class="container"><section class="hero"><div class="hero-copy"><p class="eyebrow"><span class="live-dot"></span> THE STUDENT-CURATED KNOWLEDGE LIBRARY</p><h1>SUFE数据科学<br>与大数据技术<br><span class="title-accent">资料分享计划<svg viewBox="0 0 320 18" aria-hidden="true"><path d="M3 13C90 1 231 1 315 10"/></svg></span></h1><p class="hero-description">由24大数据2班开发并维护，<br>SIME同学共享的知识书架。</p>${searchForm()}<div class="quick-search"><span>从这里开始</span><a href="${base}courses/statistics/">数理统计</a><a href="${base}courses/algorithms/">算法设计</a><a href="${base}resources/?q=期末">期末复习 ${icon("diagonal")}</a></div></div><div class="hero-visual" aria-label="精选数理统计笔记"><div class="orbit orbit-one"></div><div class="orbit orbit-two"></div><span class="visual-label">A LITTLE KNOWLEDGE,<br>SHARED GOES A LONG WAY.</span><div class="paper-back"></div><a class="hero-paper" href="${href(heroNote)}"><div class="paper-top"><span>SUFE DS / 学习笔记</span>${icon("diagonal")}</div><span class="paper-index">01 — STATISTICS</span><h2>数理统计<br>期末知识点总结<span>.</span></h2><div class="paper-formula" aria-hidden="true">χ² <span>·</span> t <span>·</span> F</div><div class="paper-rule"></div><ol><li><span>01</span> 抽样分布与基础回顾</li><li><span>02</span> 参数估计与充分统计量</li><li><span>03</span> 假设检验与典型例题</li></ol><div class="paper-bottom">翻开笔记 ${icon("arrow")}</div></a><span class="visual-stamp">知识<br>共享<span>OPEN NOTES</span></span></div></section><section class="stats-strip" aria-label="资料库概览"><div><strong>${courses.length}<span>个</span></strong><p>课程与专题</p></div><div><strong>${notes.length}<span>篇</span></strong><p>可在线阅读的笔记</p></div><div><strong>${downloads.length.toLocaleString("en-US")}<span>份</span></strong><p>可下载的学习资料</p></div><div class="stats-note">${icon("book")}<span>学生整理，持续共建。<br><strong>从一份笔记，到一座资料库。</strong></span></div></section><section class="home-section" id="courses">${sectionTitle("01 / EXPLORE BY COURSE", "从一门课程开始", `<a class="section-link" href="${base}courses/">查看全部课程 ${icon("arrow")}</a>`)}<div class="course-grid">${featuredCourses
  .map((id) => courses.find((c) => c.id === id))
  .filter(Boolean)
  .map(courseCard)
  .join(
    "",
  )}</div></section><section class="home-section">${sectionTitle("02 / WORTH A READ", "翻开这些笔记", `<a class="section-link" href="${base}resources/?kind=note">浏览所有笔记 ${icon("arrow")}</a>`)}<div class="note-grid">${pickedNotes.map(noteCard).join("")}</div></section><section class="study-banner"><div><p class="eyebrow">BEYOND THE CLASSROOM</p><h2>课堂之外，也有好资料。</h2><p>四六级真题、数学竞赛与课外阅读，接着往下探索。</p></div><div class="study-links"><a href="${base}courses/cet-4/">英语四级 ${icon("diagonal")}</a><a href="${base}courses/cet-6/">英语六级 ${icon("diagonal")}</a><a href="${base}courses/math-competition/">数学竞赛 ${icon("diagonal")}</a></div></section><section class="contribute-strip"><div><span class="contribute-mark">＋</span><div><h2>你的笔记，也可以帮到下一个人。</h2><p>一份整理、一处勘误，都是这个资料库继续生长的理由。</p></div></div><a class="button primary" href="${base}about/#contribute">一起完善资料库 ${icon("arrow")}</a></section></div>`;
await writePage(
  "",
  layout({ title: "上财学习资料库", active: "home", body: home }),
);

await writePage(
  "courses",
  layout({
    title: "课程目录",
    active: "courses",
    pathname: "courses/",
    body: `<div class="container directory-page"><div class="page-intro"><p class="eyebrow">THE COURSE INDEX</p><h1>找到你的下一页。</h1><p>按学科浏览 ${courses.length} 个课程与专题，找到需要的笔记与资料。</p></div><div class="course-controls"><div class="filter-tabs category-tabs" aria-label="学科分类" role="group"><button class="active" data-group-filter="all" aria-pressed="true">全部</button>${groups.map((g) => `<button data-group-filter="${g.id}" aria-pressed="false">${g.title}</button>`).join("")}</div><label class="course-search">${icon("search")}<span class="sr-only">查找课程</span><input type="search" placeholder="查找课程" data-course-search></label></div><div class="course-grid directory-grid">${courses.map(courseCard).join("")}</div><p class="course-empty empty-state" hidden>没有找到这门课程，试试其他关键词。</p></div>`,
  }),
);

await writePage(
  "resources",
  layout({
    title: "全部资料",
    active: "resources",
    pathname: "resources/",
    body: `<div class="container resources-page"><div class="page-intro"><p class="eyebrow">FIND SOMETHING USEFUL</p><h1>你需要的，可能就在这里。</h1><p>搜索笔记、课程或文件名。读一篇笔记，也带走一份资料。</p></div>${searchForm()}${library(resources)}</div>`,
  }),
);

const report = {
  sourceRef: ref,
  courses: courses.length,
  notes: notes.length,
  resources: resources.length,
  downloads: downloads.length,
  warnings: [],
};
for (const course of courses) {
  let intro = "";
  if (course.folder && files.includes(`${course.folder}/README.md`)) {
    const markdown = await readFile(
      path.join(root, course.folder, "README.md"),
      "utf8",
    );
    if (markdown.trim()) {
      const rendered = await renderMarkdown(
        markdown,
        `${course.folder}/README.md`,
        resolver,
      );
      intro = `<details class="course-intro"><summary>课程说明与补充链接 ${icon("arrow")}</summary><div class="prose">${rendered.html}</div></details>`;
    }
  }
  await writePage(
    `courses/${course.id}`,
    layout({
      title: course.title,
      active: "courses",
      pathname: `courses/${course.id}/`,
      body: `<div class="container resources-page"><a class="back-link" href="${base}courses/">← 课程目录</a><div class="course-page-intro"><div><p class="eyebrow">${groupFor(course).title} / COURSE MATERIALS</p><h1>${e(course.title)}</h1><p>${e(course.description)}</p></div><span class="subject-symbol large ${groupFor(course).color}">${groupFor(course).symbol}</span></div>${intro}${searchForm(`在${course.title}中查找资料`)}${library(course.resources, course.title, course)}</div>`,
    }),
  );
}

for (const note of notes) {
  const rendered = await renderMarkdown(note.markdown, note.path, resolver);
  for (const warning of rendered.warnings)
    report.warnings.push({ source: note.path, ...warning });
  const firstHeading = rendered.toc[0];
  const repeatsTitle =
    firstHeading?.depth === 1 &&
    firstHeading.text === note.title &&
    /^\s*<h1\b/.test(rendered.html);
  const noteTitleId = repeatsTitle ? firstHeading.id : "note-title";
  const noteBody = repeatsTitle
    ? rendered.html.replace(/^\s*<h1\b[^>]*>[\s\S]*?<\/h1>\n?/, "")
    : rendered.html;
  const headings = rendered.toc.filter((h) => h.depth <= 3);
  const siblingNotes = note.course.notes
    .filter((n) => n.id !== note.id)
    .slice(0, 5);
  const body = `<div class="container note-layout"><aside class="note-sidebar"><a class="back-link" href="${courseHref(note.course)}">← ${e(note.course.title)}</a><p class="eyebrow">同课程笔记</p><nav aria-label="同课程笔记"><a class="current" href="${href(note)}">${e(note.title)}</a>${siblingNotes.map((n) => `<a href="${href(n)}">${e(n.title)}</a>`).join("")}</nav><a class="sidebar-all" href="${courseHref(note.course)}">全部课程资料 ${icon("arrow")}</a></aside><article class="note-main"><div class="note-heading"><div class="breadcrumbs"><a href="${base}courses/">课程</a><span>/</span><a href="${courseHref(note.course)}">${e(note.course.title)}</a><span>/</span>学习笔记</div><h1 id="${e(noteTitleId)}">${e(note.title)}</h1><div class="note-meta">${badge("Markdown", "green")}<span>约 ${Math.max(1, Math.round(note.markdown.length / 600))} 分钟阅读</span><a href="${resolver.sourceUrl(note.path)}" ${external}>查看原文 ${icon("diagonal")}</a></div><div class="reader-actions"><a class="button primary" href="${resolver.downloadUrl(note.path)}" data-download-md="${resolver.rawUrl(note.path)}" data-filename="${e(path.posix.basename(note.path))}" ${external}>${icon("download")}下载 Markdown</a><button class="button secondary" data-copy>${icon("copy")}复制链接</button></div></div><details class="mobile-toc"><summary>本文目录</summary><nav>${headings.map((h) => `<a href="#${e(h.id)}">${e(h.text)}</a>`).join("")}</nav></details><div class="prose note-prose">${noteBody}</div><div class="note-end"><span>读到这里，辛苦了。</span><a href="${courseHref(note.course)}">继续探索这门课程 ${icon("arrow")}</a></div></article><aside class="toc"><p class="eyebrow">ON THIS PAGE</p><nav aria-label="本文目录">${headings.map((h) => `<a class="depth-${h.depth}" href="#${e(h.id)}">${e(h.text)}</a>`).join("")}</nav><a class="toc-top" href="#main">↑ 回到顶部</a></aside></div>`;
  await writePage(
    `notes/${note.id}`,
    layout({
      title: note.title,
      description: note.summary,
      pathname: `notes/${note.id}/`,
      body,
      isNote: true,
      active: "resources",
    }),
  );
}

await writePage(
  "about",
  layout({
    title: "关于与贡献",
    active: "about",
    pathname: "about/",
    body: `<div class="container about-page"><div class="page-intro"><p class="eyebrow">KNOWLEDGE IS BETTER WHEN SHARED</p><h1>学习这件事，<br>我们可以互相帮一点。</h1><p>从一个学生的资料文件夹，慢慢成为更多人的共享书架。</p></div><div class="about-content"><section><h2>关于这个资料库</h2><p>「上财学生资料共享计划」主要整理上海财经大学数据科学与大数据技术专业的学习资料，也收录通识课程、英语考试和数学竞赛等内容。</p><p>项目受到浙江大学 <a href="https://github.com/QSCTech/zju-icicles" ${external}>zju-icicles</a> 的启发，希望把学习中获得的帮助继续传递下去。这是学生自发维护的共享项目，并非学校官方网站。</p></section><section><h2>怎么使用</h2><div class="how-grid"><div><span>01</span><h3>找到课程</h3><p>从课程目录进入，或直接搜索资料名称。</p></div><div><span>02</span><h3>翻开笔记</h3><p>Markdown 笔记可以直接在线阅读，支持公式与章节目录。</p></div><div><span>03</span><h3>带走资料</h3><p>其他格式提供原文件下载，按自己的学习习惯使用。</p></div></div></section><section id="contribute"><h2>一起完善资料库</h2><p>欢迎分享笔记、补充资料，也欢迎指出错别字、失效链接或内容错误。可以在 GitHub 上提交 Issue，或 Fork 仓库后通过 Pull Request 贡献资料。</p><div class="about-actions"><a class="button primary" href="${repoUrl}/blob/main/CONTRIBUTING.md" ${external}>查看贡献指南 ${icon("arrow")}</a><a class="button secondary" href="${repoUrl}/issues" ${external}>反馈问题 ${icon("diagonal")}</a></div></section><section><h2>更多学习入口</h2><ul class="external-resources"><li><a href="https://pan.baidu.com/s/10kGrBMz4QOpumUfRbLF8Xw?pwd=t5dr" ${external}>项目补充网盘 ${icon("diagonal")}</a><span>提取码：t5dr</span></li><li><a href="https://aureliano37.notion.site/" ${external}>Notion 课程笔记 ${icon("diagonal")}</a></li><li><a href="https://github.com/jayjiaowhy/JAYJIAOlearning" ${external}>学长的学习笔记 ${icon("diagonal")}</a></li></ul></section><section class="about-rights"><h2>关于资料</h2><p>资料仅用于学习交流，版权归原作者所有。课程内容与要求可能调整，请结合实际教学安排使用。如需勘误或移除资料，请通过 GitHub Issue 联系维护者。</p></section></div></div>`,
  }),
);

await writeFile(
  path.join(dist, "404.html"),
  layout({
    title: "没有找到这一页",
    body: `<div class="container not-found"><p class="eyebrow">404 / PAGE NOT FOUND</p><h1>这一页，暂时翻不到。</h1><p>也许链接已经变动，试试从课程目录重新出发。</p><a class="button primary" href="${base}courses/">浏览课程 ${icon("arrow")}</a></div>`,
  }),
);
for (const name of ["style.css", "app.js", "favicon.svg"])
  await copyFile(path.join(site, "src", name), path.join(dist, "assets", name));
await mkdir(path.join(dist, "assets/katex"), { recursive: true });
await copyFile(
  path.join(site, "node_modules/katex/dist/katex.min.css"),
  path.join(dist, "assets/katex/katex.min.css"),
);
await cp(
  path.join(site, "node_modules/katex/dist/fonts"),
  path.join(dist, "assets/katex/fonts"),
  { recursive: true },
);
await writeFile(path.join(dist, ".nojekyll"), "");
const urls = [
  "",
  "courses/",
  "resources/",
  "about/",
  ...courses.map((c) => `courses/${c.id}/`),
  ...notes.map((n) => `notes/${n.id}/`),
];
await writeFile(
  path.join(dist, "sitemap.xml"),
  `<?xml version="1.0" encoding="UTF-8"?><urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">${urls.map((url) => `<url><loc>${siteUrl}${base}${url}</loc></url>`).join("")}</urlset>`,
);
await mkdir(path.join(site, ".cache"), { recursive: true });
await writeFile(
  path.join(site, ".cache/build-report.json"),
  JSON.stringify(report, null, 2),
);
await writeFile(
  path.join(site, ".cache/manifest.json"),
  JSON.stringify(
    resources.map((r) => ({
      id: r.id,
      path: r.path,
      format: r.format,
      url: href(r),
      download: resolver.downloadUrl(r.path),
    })),
    null,
    2,
  ),
);
console.log(
  `Built ${urls.length} pages: ${courses.length} courses/topics, ${notes.length} Markdown notes, ${downloads.length} downloads.`,
);
console.log(
  `${report.warnings.length} existing-content notices recorded in .cache/build-report.json. Original materials were not copied.`,
);
