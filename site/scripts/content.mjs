import path from "node:path";
import { createHash } from "node:crypto";
import { unified } from "unified";
import remarkParse from "remark-parse";
import remarkGfm from "remark-gfm";
import remarkMath from "remark-math";
import remarkRehype from "remark-rehype";
import rehypeKatex from "rehype-katex";
import rehypeStringify from "rehype-stringify";
import { visit } from "unist-util-visit";
import GithubSlugger from "github-slugger";

export const escapeHtml = (value = "") =>
  String(value).replace(
    /[&<>"']/g,
    (c) =>
      ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" })[
        c
      ],
  );
export const encodePath = (value) =>
  value.split("/").map(encodeURIComponent).join("/");
export const resourceId = (source) =>
  createHash("sha256")
    .update(source.normalize("NFC"))
    .digest("hex")
    .slice(0, 12);
export const sizeLabel = (size) =>
  size < 1024
    ? `${size} B`
    : size < 1048576
      ? `${(size / 1024).toFixed(1)} KB`
      : `${(size / 1048576).toFixed(1)} MB`;
export const normalizeSearch = (value) =>
  value.normalize("NFKC").toLocaleLowerCase().replace(/\s+/g, " ").trim();
const nodeText = (node) =>
  node.value || (node.children || []).map(nodeText).join("");

export function textSummary(markdown) {
  return markdown
    .replace(/```[\s\S]*?```/g, "")
    .replace(/!\[\[[^\]]*\]\]/g, "")
    .replace(/!\[[^\]]*\]\([^)]*\)/g, "")
    .replace(/\[([^\]]+)\]\([^)]*\)/g, "$1")
    .replace(/\$\$[\s\S]*?\$\$/g, "")
    .replace(/\$[^$\n]+\$/g, "")
    .replace(/[#>*_`|\[\]]/g, "")
    .replace(/\s+/g, " ")
    .trim();
}

export function markdownTitle(markdown, file) {
  const match = markdown.match(/^#\s+(.+)$/m);
  const heading = match?.[1]?.trim();
  return heading &&
    !["重点", "目录", "笔记", "知识点", "总结"].includes(heading)
    ? heading.replace(/[*`]/g, "")
    : path.posix.basename(file, ".md");
}

export function normalizeMath(markdown) {
  let fence = null;
  const normalized = markdown
    .split("\n")
    .map((line) => {
      const marker = line.match(/^\s*(`{3,}|~{3,})/);
      if (marker) {
        if (!fence) fence = marker[1];
        else if (marker[1][0] === fence[0] && marker[1].length >= fence.length)
          fence = null;
        return line;
      }
      if (fence || /^(?: {4}|\t)/.test(line)) return line;
      return line
        .split(/(`+[^`]*`+)/g)
        .map((part, i) =>
          i % 2
            ? part
            : part
                .replace(/(?<!\\)\\\(/g, "$")
                .replace(/(?<!\\)\\\)/g, "$")
                .replace(/(?<!\\)\\\[/g, "$$$$")
                .replace(/(?<!\\)\\\]/g, "$$$$"),
        )
        .join("");
    })
    .join("\n");
  // Obsidian accepts $$ formulas with the closing delimiter on the content line.
  // Give CommonMark a consistent block boundary, preserving code and TeX row spacing.
  return normalized.replace(
    /```[\s\S]*?```|~~~[\s\S]*?~~~|`[^`\n]*`|(?<!\\)\$\$([\s\S]*?)(?<!\\)\$\$/g,
    (match, formula, offset) => {
      if (formula === undefined) return match;
      const before = normalized.slice(
        normalized.lastIndexOf("\n", offset - 1) + 1,
        offset,
      );
      let prefix = before.match(/^[ \t]*(?:>[ \t]*)*/)?.[0] || "";
      if (/^[ \t]*(?:[-*+]|\d+\.)\s+$/.test(before))
        prefix = " ".repeat(before.length);
      const body = formula
        .trim()
        .split("\n")
        .map((line) => prefix + line.replace(/^[ \t]*(?:>[ \t]*)+/, "").trim())
        .join("\n");
      return `\n${prefix}$$\n${body}\n${prefix}$$\n${prefix}`;
    },
  );
}

export function createResolver({ files, resources, repo, ref, base }) {
  const fileSet = new Set(files);
  const names = new Map();
  for (const file of files) {
    const name = path.posix.basename(file);
    names.set(name, [...(names.get(name) || []), file]);
  }
  const byPath = new Map(resources.map((item) => [item.path, item]));
  const sourceUrl = (file) =>
    `https://github.com/${repo}/blob/${ref}/${encodePath(file)}`;
  const rawUrl = (file) =>
    `https://raw.githubusercontent.com/${repo}/${ref}/${encodePath(file)}`;
  const downloadUrl = (file) =>
    `https://github.com/${repo}/raw/${ref}/${encodePath(file)}`;
  function resolve(target, from) {
    let decoded;
    try {
      decoded = decodeURIComponent(target);
    } catch {
      decoded = target;
    }
    const relative = path.posix.normalize(
      path.posix.join(path.posix.dirname(from), decoded),
    );
    const candidates = [relative, decoded.replace(/^\//, "")];
    for (const candidate of candidates) {
      if (fileSet.has(candidate)) return candidate;
      if (!path.posix.extname(candidate) && fileSet.has(`${candidate}.md`))
        return `${candidate}.md`;
    }
    const basename = path.posix.basename(decoded);
    const matches = names.get(basename) || names.get(`${basename}.md`) || [];
    const sameCourse = matches.filter(
      (file) => file.split("/")[0] === from.split("/")[0],
    );
    return sameCourse.length === 1
      ? sameCourse[0]
      : matches.length === 1
        ? matches[0]
        : null;
  }
  function href(file) {
    const resource = byPath.get(file);
    return resource?.format === "md"
      ? `${base}notes/${resource.id}/`
      : downloadUrl(file);
  }
  return { resolve, href, rawUrl, sourceUrl, downloadUrl };
}

export async function renderMarkdown(markdown, source, resolver) {
  const toc = [],
    warnings = [];
  const slugger = new GithubSlugger();
  function transform() {
    return (tree) => {
      visit(tree, "text", (node, index, parent) => {
        if (!parent || parent.type === "link") return;
        const pattern = /(!?)\[\[([^\]]+)\]\]/g;
        let match,
          last = 0;
        const nodes = [];
        while ((match = pattern.exec(node.value))) {
          if (match.index > last)
            nodes.push({
              type: "text",
              value: node.value.slice(last, match.index),
            });
          const [target, label] = match[2].split("|");
          const fullTarget = resolver.resolve(target, source);
          const [fileName] = fullTarget ? [target] : target.split("#");
          const file = fullTarget || resolver.resolve(fileName, source);
          if (file) {
            const isImage =
              match[1] && /\.(png|jpe?g|gif|webp|svg)$/i.test(file);
            nodes.push(
              isImage
                ? {
                    type: "image",
                    url: resolver.rawUrl(file),
                    alt: label || path.posix.basename(file),
                  }
                : {
                    type: "link",
                    url: `${resolver.href(file)}${!fullTarget && target.includes("#") ? `#h-${new GithubSlugger().slug(target.split("#")[1])}` : ""}`,
                    children: [{ type: "text", value: label || target }],
                  },
            );
          } else {
            warnings.push({ kind: "missing-wikilink", target: fileName });
            nodes.push({
              type: "text",
              value: match[1]
                ? `[原笔记图片未收录：${fileName}]`
                : label || target,
            });
          }
          last = pattern.lastIndex;
        }
        if (last) {
          if (last < node.value.length)
            nodes.push({ type: "text", value: node.value.slice(last) });
          parent.children.splice(index, 1, ...nodes);
          return index + nodes.length;
        }
      });
      visit(tree, "heading", (node) => {
        const text = nodeText(node);
        const id = `h-${slugger.slug(text)}`;
        node.data = { ...node.data, hProperties: { id } };
        toc.push({ text, id, depth: node.depth });
      });
      visit(
        tree,
        (node) => node.type === "link" || node.type === "image",
        (node) => {
          const url = node.url || "";
          if (/^https?:\/\//i.test(url)) {
            if (node.type === "link")
              node.data = {
                ...node.data,
                hProperties: { target: "_blank", rel: "noopener noreferrer" },
              };
            else
              node.data = {
                ...node.data,
                hProperties: { loading: "lazy", decoding: "async" },
              };
            return;
          }
          if (url.startsWith("/SUFE_DS/")) return;
          if (url.startsWith("#")) {
            let fragment;
            try {
              fragment = decodeURIComponent(url.slice(1));
            } catch {
              fragment = url.slice(1);
            }
            node.url = fragment.startsWith("h-") ? url : `#h-${fragment}`;
            return;
          }
          if (/^[a-z][a-z\d+.-]*:/i.test(url) || url.startsWith("//")) {
            if (!url.startsWith("mailto:")) {
              node.url = "";
              warnings.push({ kind: "blocked-url", target: url });
            }
            return;
          }
          const [target, hash] = url.split("#");
          const file = resolver.resolve(target, source);
          if (file) {
            node.url =
              node.type === "image"
                ? resolver.rawUrl(file)
                : resolver.href(file);
            if (hash && file.endsWith(".md")) node.url += `#h-${hash}`;
            if (node.type === "image")
              node.data = {
                hProperties: { loading: "lazy", decoding: "async" },
              };
          } else {
            warnings.push({ kind: "missing-local-link", target: url });
            if (node.type === "image") {
              node.type = "text";
              node.value = `[原笔记图片未收录：${target}]`;
            } else {
              node.url = resolver.sourceUrl(source);
              node.data = {
                hProperties: {
                  title: "原笔记中的链接尚未收录；查看原文",
                  target: "_blank",
                  rel: "noopener noreferrer",
                },
              };
            }
          }
        },
      );
      visit(tree, "blockquote", (node) => {
        const first = node.children?.[0]?.children?.[0];
        const match =
          first?.type === "text" &&
          first.value.match(
            /^\[!(NOTE|TIP|IMPORTANT|WARNING|CAUTION)\][+-]?\s*/i,
          );
        if (match) {
          first.value = first.value.slice(match[0].length);
          node.data = {
            hProperties: {
              className: ["callout", `callout-${match[1].toLowerCase()}`],
            },
          };
        }
      });
    };
  }
  const file = await unified()
    .use(remarkParse)
    .use(remarkGfm)
    .use(remarkMath)
    .use(transform)
    .use(remarkRehype)
    .use(rehypeKatex, {
      strict: "ignore",
      trust: false,
      macros: {
        "\\*": "*",
        "\\arsinh": "\\operatorname{arsinh}",
        "\\arcosh": "\\operatorname{arcosh}",
        "\\artanh": "\\operatorname{artanh}",
        "\\arcoth": "\\operatorname{arcoth}",
      },
    })
    .use(rehypeStringify)
    .process(normalizeMath(markdown));
  for (const message of file.messages)
    warnings.push({
      kind: "math",
      message: message.cause?.message || message.reason,
      line: message.line,
    });
  return { html: String(file), toc, warnings };
}
