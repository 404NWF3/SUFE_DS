(() => {
  const $ = (selector, parent = document) => parent.querySelector(selector);
  const $$ = (selector, parent = document) => [
    ...parent.querySelectorAll(selector),
  ];
  const normalize = (value) =>
    value.normalize("NFKC").toLocaleLowerCase().replace(/\s+/g, " ").trim();
  const header = $(".header");
  const menu = $(".mobile-menu");
  menu?.addEventListener("click", () => {
    const expanded = menu.getAttribute("aria-expanded") !== "true";
    menu.setAttribute("aria-expanded", String(expanded));
    menu.setAttribute("aria-label", expanded ? "收起导航" : "展开导航");
    header.classList.toggle("menu-open", expanded);
  });
  document.addEventListener("keydown", (event) => {
    if (
      event.key === "Escape" &&
      menu?.getAttribute("aria-expanded") === "true"
    ) {
      menu.click();
      menu.focus();
    }
    if (
      event.key === "/" &&
      !event.metaKey &&
      !event.ctrlKey &&
      !event.altKey &&
      !/INPUT|TEXTAREA|SELECT/.test(event.target.tagName) &&
      !event.target.isContentEditable
    ) {
      const field = $("#search-input") || $("[data-course-search]");
      if (field) {
        event.preventDefault();
        field.focus();
      }
    }
  });
  let toastTimer;
  function toast(text) {
    const el = $(".toast");
    if (!el) return;
    el.textContent = text;
    el.classList.add("visible");
    clearTimeout(toastTimer);
    toastTimer = setTimeout(() => el.classList.remove("visible"), 2800);
  }
  $("[data-copy]")?.addEventListener("click", async () => {
    try {
      await navigator.clipboard.writeText(location.href);
      toast("链接已复制，可以分享给同学了。");
    } catch {
      toast("暂时无法自动复制，请复制浏览器地址栏中的链接。");
    }
  });
  $$("[data-download-md]").forEach((link) =>
    link.addEventListener("click", async (event) => {
      if (
        link.dataset.downloadFallback ||
        event.metaKey ||
        event.ctrlKey ||
        event.shiftKey
      )
        return;
      event.preventDefault();
      if (link.getAttribute("aria-busy") === "true") return;
      link.setAttribute("aria-busy", "true");
      try {
        const response = await fetch(link.dataset.downloadMd, {
          credentials: "omit",
          signal: AbortSignal.timeout(15000),
        });
        if (!response.ok) throw new Error("Download failed");
        const objectUrl = URL.createObjectURL(await response.blob());
        const anchor = document.createElement("a");
        anchor.href = objectUrl;
        anchor.download = link.dataset.filename;
        document.body.append(anchor);
        anchor.click();
        anchor.remove();
        setTimeout(() => URL.revokeObjectURL(objectUrl), 30000);
        toast("已发起 Markdown 下载。");
      } catch {
        link.dataset.downloadFallback = "true";
        toast("下载暂时失败，再次点击可打开 GitHub 原文件。");
      } finally {
        link.removeAttribute("aria-busy");
      }
    }),
  );

  const library = $("[data-library]");
  if (library) {
    const input = $("#search-input");
    const rows = $$(".file-row", library);
    const format = $("#format-filter");
    const tabs = $$("[data-kind-filter]");
    const pagination = $(".pagination", library);
    let state = { q: "", kind: "all", format: "all", page: 1 };
    let debounce,
      composing = false;
    const readState = () => {
      const query = new URLSearchParams(location.search);
      state = {
        q: query.get("q") || "",
        kind: ["all", "note", "file"].includes(query.get("kind"))
          ? query.get("kind")
          : "all",
        format: [...format.options].some((o) => o.value === query.get("format"))
          ? query.get("format")
          : "all",
        page: Math.max(1, Number.parseInt(query.get("page"), 10) || 1),
      };
      input.value = state.q;
      format.value = state.format;
    };
    function apply(updateUrl = true) {
      const terms = normalize(state.q).split(" ").filter(Boolean);
      const found = rows.filter(
        (row) =>
          (state.kind === "all" || row.dataset.kind === state.kind) &&
          (state.format === "all" || row.dataset.format === state.format) &&
          terms.every((term) => row.dataset.search.includes(term)),
      );
      const pages = Math.max(1, Math.ceil(found.length / 24));
      state.page = Math.min(state.page, pages);
      const visible = new Set(
        found.slice((state.page - 1) * 24, state.page * 24),
      );
      rows.forEach((row) => {
        row.hidden = !visible.has(row);
      });
      tabs.forEach((tab) => {
        const active = tab.dataset.kindFilter === state.kind;
        tab.classList.toggle("active", active);
        tab.setAttribute("aria-pressed", String(active));
      });
      $("#result-count").textContent =
        state.q || state.kind !== "all" || state.format !== "all"
          ? `找到 ${found.length} 份资料`
          : `共 ${found.length} 份资料`;
      $(".empty-state", library).hidden = found.length > 0;
      pagination.hidden = found.length === 0;
      $("[data-page-label]", library).textContent =
        `第 ${state.page} / ${pages} 页`;
      $("[data-prev]", library).disabled = state.page <= 1;
      $("[data-next]", library).disabled = state.page >= pages;
      if (updateUrl) {
        const url = new URL(location.href);
        for (const [key, value] of Object.entries(state)) {
          if (!value || value === "all" || (key === "page" && value === 1))
            url.searchParams.delete(key);
          else url.searchParams.set(key, String(value));
        }
        history.replaceState(null, "", url);
      }
    }
    function search() {
      state.q = input.value;
      state.page = 1;
      apply();
    }
    input.addEventListener("compositionstart", () => {
      composing = true;
      clearTimeout(debounce);
    });
    input.addEventListener("compositionend", () => {
      composing = false;
      search();
    });
    input.addEventListener("input", () => {
      if (!composing) {
        clearTimeout(debounce);
        debounce = setTimeout(search, 150);
      }
    });
    input.closest("form").addEventListener("submit", (event) => {
      event.preventDefault();
      clearTimeout(debounce);
      search();
    });
    tabs.forEach((tab) =>
      tab.addEventListener("click", () => {
        state.kind = tab.dataset.kindFilter;
        state.page = 1;
        apply();
      }),
    );
    format.addEventListener("change", () => {
      state.format = format.value;
      state.page = 1;
      apply();
    });
    $("[data-clear]", library).addEventListener("click", () => {
      clearTimeout(debounce);
      state = { q: "", kind: "all", format: "all", page: 1 };
      input.value = "";
      format.value = "all";
      apply();
      input.focus();
    });
    for (const [selector, delta] of [
      ["[data-prev]", -1],
      ["[data-next]", 1],
    ]) {
      $(selector, library).addEventListener("click", () => {
        state.page += delta;
        apply();
        library.scrollIntoView({ block: "start" });
      });
    }
    window.addEventListener("popstate", () => {
      readState();
      apply(false);
    });
    readState();
    apply(false);
  }

  const courseSearch = $("[data-course-search]");
  if (courseSearch) {
    const cards = $$(".directory-grid .course-card");
    const tabs = $$("[data-group-filter]");
    let group = "all";
    const apply = () => {
      const query = normalize(courseSearch.value);
      let count = 0;
      cards.forEach((card) => {
        card.hidden = !(
          (group === "all" || card.dataset.group === group) &&
          card.dataset.search.includes(query)
        );
        if (!card.hidden) count++;
      });
      $(".course-empty").hidden = count !== 0;
    };
    courseSearch.addEventListener("input", apply);
    tabs.forEach((tab) =>
      tab.addEventListener("click", () => {
        group = tab.dataset.groupFilter;
        tabs.forEach((t) => {
          const active = t === tab;
          t.classList.toggle("active", active);
          t.setAttribute("aria-pressed", String(active));
        });
        apply();
      }),
    );
  }
  const tocLinks = $$(".toc nav a");
  if (tocLinks.length && "IntersectionObserver" in window) {
    const observer = new IntersectionObserver(
      (entries) => {
        const visible = entries
          .filter((entry) => entry.isIntersecting)
          .sort(
            (a, b) => a.boundingClientRect.top - b.boundingClientRect.top,
          )[0];
        if (!visible) return;
        tocLinks.forEach((link) =>
          link.classList.toggle(
            "active",
            link.getAttribute("href") === `#${visible.target.id}`,
          ),
        );
      },
      { rootMargin: "-110px 0px -60% 0px" },
    );
    tocLinks.forEach((link) => {
      const heading = document.getElementById(
        link.getAttribute("href").slice(1),
      );
      if (heading) observer.observe(heading);
    });
  }
})();
