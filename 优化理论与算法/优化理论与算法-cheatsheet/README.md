# 优化理论与算法 · Cheat Sheet

用 [simple-cheatsheet](https://typst.app/universe/package/simple-cheatsheet/) 模板制作的中文版「优化理论与算法」课程速查表，浓缩自 `wiki/优化理论与算法/` 全部讲义笔记（00–14 讲）。

## 内容

9 个色块章节，横向 A4 双栏多列排版：

0. 建模 & LP 标准型 — 三要素、标准型转换、可线性化结构
1. 单纯形法 — BFS、检验数、换基、人工变量、退化
2. LP 对偶 & 灵敏度 — 强弱对偶、互补松弛、影子价格、对偶单纯形
3. 凸集 · 凸函数 · 凸优化 — 保凸运算、一阶/二阶判别、锥优化谱系
4. KKT & 拉格朗日对偶 — 四件套、约束资格、强对偶
5. 梯度下降 · 动量 · Newton — GD/HB/NAG/Newton/BFGS/L-BFGS
6. 投影 · 近端 · SGD · Adam — PGD、prox、ISTA/FISTA、SGD、Adam
7. 整数规划 — 集合模型、Big-M、分支定界、割平面
8. 列生成 · 网络流 — DW 分解、列生成、最大流最小割、时空网络

## 编译

需安装 typst（已在仓库环境中用 `winget install Typst.Typst` 装好 0.15.0）。

```bash
typst compile cheatsheet.typ
```

输出 `cheatsheet.pdf`（A4 横向，4 列，约 2 页）。

## 字体说明

中文字体回退链：Microsoft YaHei → SimSun → Noto Sans CJK SC → Source Han Sans SC。
编译时会有 `unknown font family: roboto/helvetica/...` 警告——这是模板内置的西文字体在本机不存在，会自动回退到 Arial/系统默认，不影响中文渲染，可忽略。
