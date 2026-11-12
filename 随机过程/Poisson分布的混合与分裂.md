# Poisson 分布的混合与分裂

> **课程**：随机过程（Shanshan Guo, Fall 2026）
> **定位**：Chap.3 条件期望里的 Poisson 招式；Chap.5 染色 / 叠加的随机变量预演
> **配套**：[[随机过程导论与概率论复习——Chap3 Introduction]] · [[条件概率与条件期望——训练题]] · [[concepts/泊松过程]]
> **Ross**：§3.3–3.5、§3.7；过程版见 Chap.5

Poisson 有两套「把随机性叠上去」的标准操作，方向相反：

|     | 分裂（thinning / 染色）                                    | 混合（mixing）                                                         |
| --- | ---------------------------------------------------- | ------------------------------------------------------------------ |
| 谁随机 | 个数 $N\sim\mathrm{Poisson}(\lambda)$ **固定参数**；每个点独立分类 | **参数** $\Lambda$ 先随机，再 $N\mid\Lambda\sim\mathrm{Poisson}(\Lambda)$ |
| 结果  | 各类仍是 Poisson，而且**相互独立**                              | 无条件一般**不再是** Poisson；方差被撑大                                         |
| 典型题 | 瑜伽馆男女客、染色定理                                          | 雨天/晴天事故率、伽马–Poisson = 负二项                                          |

复合 Poisson（随机个 i.i.d. 之和）是第三条线，别和混合搅在一起。见文末对照表。

---

## 目录

- [0. 先记住的三件事实](#0-先记住的三件事实)
- [1. 分裂](#1-分裂)
- [2. 叠加：分裂的逆](#2-叠加分裂的逆)
- [3. 和固定时：分裂的条件版](#3-和固定时分裂的条件版)
- [4. 混合](#4-混合)
- [5. 伽马混合 = 负二项](#5-伽马混合--负二项)
- [6. 复合 Poisson：不是混合](#6-复合-poisson不是混合)
- [7. 一张对照表](#7-一张对照表)
- [8. 易错点](#8-易错点)
- [9. 练哪些题](#9-练哪些题)

---

## 0. 先记住的三件事实

$N\sim\mathrm{Poisson}(\lambda)$ 表示

$$P(N=n)=e^{-\lambda}\frac{\lambda^n}{n!},\qquad E[N]=\mathrm{Var}(N)=\lambda.$$

后面所有推导只用全期望 / 全概率，加上 Poisson 的 pgf $E[s^N]=\exp(\lambda(s-1))$。

1. **独立 Poisson 可加**：独立 $N_i\sim\mathrm{Poisson}(\lambda_i)$ 则 $\sum N_i\sim\mathrm{Poisson}(\sum\lambda_i)$。
2. **分裂保持 Poisson 且独立**（下文 §1）。
3. **和固定则二项**：独立时 $N_1\mid(N_1+N_2=n)\sim\mathrm{Binomial}\bigl(n,\lambda_1/(\lambda_1+\lambda_2)\bigr)$。这是 2 的条件逆，也是讲义 Example 3.3。

---

## 1. 分裂

### 1.1 随机变量版（瑜伽馆）

**例题背景（讲义 Example 3.24）。** 瑜伽馆一天的到访总人数服从均值为 $\lambda$ 的泊松分布。每位到访者独立地以概率 $p$ 为女、以概率 $1-p$ 为男，分类独立于总人数。令 $N_1,N_2$ 为当天女客数和男客数，求恰有 $n$ 位女客、$m$ 位男客的联合概率，并判断两类人数是否独立。这里 $\lambda$ 是一天的平均总人数，不是某个已知的实际总人数。

先写成 $r$ 类的通用模型，再代回两类：

$N\sim\mathrm{Poisson}(\lambda)$。给定 $N=n$，把 $n$ 个点独立地标成 $r$ 类，第 $i$ 类概率 $p_i$（$\sum p_i=1$）。令 $N_i$ 为第 $i$ 类个数，则

$$(N_1,\dots,N_r)\mid N=n \;\sim\; \mathrm{Multinomial}(n;p_1,\dots,p_r),$$

且 $N_1+\cdots+N_r=N$。

**结论**：$N_1,\dots,N_r$ **独立**，$N_i\sim\mathrm{Poisson}(\lambda p_i)$。

两类时就是讲义 Example 3.24：每人独立以 $p$ 为女，

$$
\begin{aligned}
P(N_1=n,N_2=m)
&= P(N=n+m)\,P(N_1=n\mid N=n+m)\\
&= e^{-\lambda}\frac{\lambda^{n+m}}{(n+m)!}\cdot\binom{n+m}{n}p^n(1-p)^m\\
&= e^{-\lambda p}\frac{(\lambda p)^n}{n!}\cdot e^{-\lambda(1-p)}\frac{(\lambda(1-p))^m}{m!}.
\end{aligned}
$$

联合 PMF 裂成两个 Poisson PMF 的乘积，所以独立。

$r$ 类同理：多项系数把 $(n_1+\cdots+n_r)!$ 拆开，指数 $e^{-\lambda}=e^{-\lambda\sum p_i}$ 也拆开。

### 1.2 用 pgf 一眼看出独立

$$E\bigl[s_1^{N_1}\cdots s_r^{N_r}\bigr]
= E\Bigl[E\bigl[s_1^{N_1}\cdots s_r^{N_r}\bigm| N\bigr]\Bigr]
= E\bigl[(p_1 s_1+\cdots+p_r s_r)^N\bigr]
= \exp\bigl(\lambda(\textstyle\sum p_i s_i-1)\bigr)
= \prod_i \exp(\lambda p_i(s_i-1)).$$

乘积 pgf $\iff$ 独立 Poisson。

### 1.3 过程版（Chap.5 染色）

速率 $\lambda$ 的 Poisson 过程，每次到达独立以 $p_i$ 染成第 $i$ 色。则各色是独立的 $PP(\lambda p_i)$。固定时刻 $t$ 看 $N_i(t)$，就是上面的随机变量版（$\lambda$ 换成 $\lambda t$）。

分类必须**彼此独立、且与到达时刻独立**。若「第 $k$ 个点的颜色依赖第 $k-1$ 个」，分裂一般失败。

### 1.4 均值方差（不需要先证独立）

$N_1\mid N\sim\mathrm{Binomial}(N,p)$，故

$$E[N_1\mid N]=Np,\qquad \mathrm{Var}(N_1\mid N)=Np(1-p).$$

$$E[N_1]=\lambda p,$$

$$
\mathrm{Var}(N_1)
= E[Np(1-p)]+\mathrm{Var}(Np)
= \lambda p(1-p)+\lambda p^2
= \lambda p.
$$

均值方差已经是 Poisson 的；独立性要靠联合 PMF / pgf，单看边缘不够。

---

## 2. 叠加：分裂的逆

独立 $N_i\sim\mathrm{Poisson}(\lambda_i)$，令 $N=\sum N_i$。则 $N\sim\mathrm{Poisson}(\sum\lambda_i)$，并且

$$\text{给定 }N=n\text{ 时，}(N_1,\dots,N_r)\sim\mathrm{Multinomial}\Bigl(n;\;\frac{\lambda_1}{\lambda},\dots,\frac{\lambda_r}{\lambda}\Bigr),\quad \lambda=\sum\lambda_i.$$

两类：$X\sim\mathrm{Poisson}(\lambda_1)$、$Y\sim\mathrm{Poisson}(\lambda_2)$ 独立 $\implies$ $X+Y\sim\mathrm{Poisson}(\lambda_1+\lambda_2)$，且

$$X\mid(X+Y=n)\sim\mathrm{Binomial}\Bigl(n,\frac{\lambda_1}{\lambda_1+\lambda_2}\Bigr).$$

这就是讲义 Example 3.3：

$$E[X\mid X+Y=n]=n\cdot\frac{\lambda_1}{\lambda_1+\lambda_2}.$$

> **配对记忆**：先独立叠加再看和，等价于「一个大 Poisson 再按比例 $p_i=\lambda_i/\lambda$ 独立染色」。分裂 $\leftrightarrow$ 叠加是同一件事的两个方向。

---

## 3. 和固定时：分裂的条件版

已经独立的两条 Poisson，**再**条件化在和上，它们当然不再独立：和被钉死了。条件分布是二项，不是「两条更小的独立 Poisson」。

**条件例题。** 一天总到访人数 $N\sim\operatorname{Poisson}(\lambda)$，每人独立地以概率 $p$ 为女。$N_1$ 为女客数、$N_2$ 为男客数。已知今天有 $m$ 位男客，求女客数的条件期望。由于未固定总人数，两类人数在无条件模型下独立，所以

$$E[N_1\mid N_2=m]=E[N_1]=\lambda p$$

与 $m$ 无关。若题目给的是「先有两个独立 Poisson 再看 $N_1+N_2$」，条件期望就依赖和，走 §2。

两种条件不要混：

| 给定 | 得到 |
|---|---|
| $N=n$（总数） | $(N_1,\dots)\sim$ 多项 / 二项 |
| $N_2=m$（其中一类） | 若来自分裂，则 $N_1$ 与 $N_2$ 独立，条件期望不依赖 $m$ |

---

## 4. 混合

### 4.1 定义

先抽 $\Lambda$（随机强度），再

$$N\mid \Lambda=\lambda \;\sim\; \mathrm{Poisson}(\lambda).$$

无条件分布

$$P(N=n)=E\bigl[P(N=n\mid\Lambda)\bigr]=E\Bigl[e^{-\Lambda}\frac{\Lambda^n}{n!}\Bigr].$$

这叫 **混合 Poisson**（mixed Poisson）。$\Lambda$ 退化成常数时才回到普通 Poisson。

### 4.2 均值被撑大的方差

$$E[N\mid\Lambda]=\Lambda=\mathrm{Var}(N\mid\Lambda),$$

$$E[N]=E[\Lambda],$$

$$
\mathrm{Var}(N)
= E[\Lambda]+\mathrm{Var}(\Lambda)
= E[N]+\mathrm{Var}(\Lambda)
\ge E[N].
$$

等号当且仅当 $\Lambda$ 几乎必然为常数。混合 Poisson **过度离散**（overdispersed）：方差大于均值。这是现场识别「该用混合而不是普通 Poisson」的信号。

### 4.3 两个标准例子

**两点混合（雨天/晴天，说明性模型）。** 观察某一天的事故总数 $N$。这一天以概率 $\alpha$ 下雨；给定下雨，事故数服从 $\operatorname{Poisson}(\lambda_1)$；给定不下雨，事故数服从 $\operatorname{Poisson}(\lambda_2)$。在尚不知道天气时，求这一天事故数的分布、期望与方差。两种天气互斥，是先确定当天环境再生成当天的事故数，并非把同一天两类事故相加。

令随机参数 $\Lambda$ 在下雨时取 $\lambda_1$，不下雨时取 $\lambda_2$。对天气用全概率公式：

$$P(N=n)=\alpha e^{-\lambda_1}\frac{\lambda_1^n}{n!}+(1-\alpha)e^{-\lambda_2}\frac{\lambda_2^n}{n!}.$$

这是两个 Poisson 的凸组合，一般不是 Poisson。$E[N]=\alpha\lambda_1+(1-\alpha)\lambda_2$，方差多出 $\alpha(1-\alpha)(\lambda_1-\lambda_2)^2$。

**均匀混合**  
$\Lambda\sim\mathrm{Unif}(0,a)$ 时，

$$P(N=n)=\frac1a\int_0^a e^{-\lambda}\frac{\lambda^n}{n!}\,d\lambda,$$

尾概率用不完全伽马写（Ross 3.57）。

---

## 5. 伽马混合 = 负二项

这是混合里最常用的共轭。取 $\Lambda\sim\mathrm{Gamma}(\alpha,\beta)$，密度按「形状–速率」约定：

$$f(\lambda)=\frac{\beta^\alpha}{\Gamma(\alpha)}\lambda^{\alpha-1}e^{-\beta\lambda},\qquad E[\Lambda]=\frac{\alpha}{\beta},\;\mathrm{Var}(\Lambda)=\frac{\alpha}{\beta^2}.$$

则

$$
\begin{aligned}
P(N=n)
&= \int_0^\infty e^{-\lambda}\frac{\lambda^n}{n!}\cdot\frac{\beta^\alpha}{\Gamma(\alpha)}\lambda^{\alpha-1}e^{-\beta\lambda}\,d\lambda\\
&= \frac{\Gamma(n+\alpha)}{n!\,\Gamma(\alpha)}\Bigl(\frac{\beta}{\beta+1}\Bigr)^\alpha\Bigl(\frac{1}{\beta+1}\Bigr)^n.
\end{aligned}
$$

这是负二项（失败次数版：成功概率 $\beta/(\beta+1)$，成功次数 $\alpha$；$\alpha$ 不必是整数）。

$$E[N]=\frac{\alpha}{\beta},\qquad \mathrm{Var}(N)=\frac{\alpha}{\beta}+\frac{\alpha}{\beta^2}.$$

Bayes 视角：$N=n$ 后，$\Lambda\mid N=n\sim\mathrm{Gamma}(\alpha+n,\beta+1)$。Poisson–伽马共轭，Ross 3.17、3.58。

---

## 6. 复合 Poisson：不是混合

$$S=\sum_{i=1}^N X_i,\qquad N\sim\mathrm{Poisson}(\lambda),\quad X_i\text{ i.i.d. 与 }N\text{ 独立}$$

（$N=0$ 时 $S=0$）。这是**随机个加数**，参数 $\lambda$ 仍是常数。

$$E[S]=\lambda E[X],\qquad \mathrm{Var}(S)=\lambda E[X^2].$$

过程版 $S(t)=\sum_{i=1}^{N(t)} X_i$，$E[S(t)]=\lambda t E[X]$，$\mathrm{Var}(S(t))=\lambda t E[X^2]$。见 [[concepts/泊松过程]]。

混合 Poisson 的随机性在**强度**；复合 Poisson 的随机性在**每个事件的标值**。可以两个都做：强度随机且每次有标值，那是复合混合，考试先分清问的是 $N$ 还是 $S$。

若 $X_i\in\{0,1\}$ 且 $P(X=1)=p$，则 $S\mid N\sim\mathrm{Binomial}(N,p)$，复合退化为分裂，$S\sim\mathrm{Poisson}(\lambda p)$。分裂是复合的 0-1 特例。

---

## 7. 一张对照表

| | 分裂 | 叠加 | 混合 | 复合 |
|---|---|---|---|---|
| 输入 | 一个 $\mathrm{Poisson}(\lambda)$ + 独立分类 | 独立 $\mathrm{Poisson}(\lambda_i)$ | 随机 $\Lambda$，再 $\mathrm{Poisson}(\Lambda)$ | $\mathrm{Poisson}(\lambda)$ 个 i.i.d. $X_i$ |
| 输出 | 独立 $\mathrm{Poisson}(\lambda p_i)$ | $\mathrm{Poisson}(\sum\lambda_i)$ | 一般非 Poisson，方差 $> $ 均值 | $S$ 的分布由 $X$ 决定 |
| $E$ | $\lambda p_i$ | $\sum\lambda_i$ | $E[\Lambda]$ | $\lambda E[X]$ |
| $\mathrm{Var}$ | $\lambda p_i$ | $\sum\lambda_i$ | $E[\Lambda]+\mathrm{Var}(\Lambda)$ | $\lambda E[X^2]$ |
| 条件化 | 给定总数 → 多项 | 给定总和 → 多项 | 给定 $\Lambda$ → Poisson | 给定 $N$ → $X$ 的 $n$ 重卷积 |

---

## 8. 易错点

1. **分裂后各类独立**。不要因为 $N_1+N_2=N$ 就说它们负相关——$N$ 自己也随机，正好把相关性抵消掉。固定 $N=n$ 之后才是多项，那时负相关。
2. **混合之后一般不是 Poisson**。两点混合、均匀混合都不是。只有 $\Lambda$ 退化，或你另证 pgf 仍是 $\exp(\mu(s-1))$。
3. **$\mathrm{Var}>\mathrm{E}$ 不是 Poisson**。普通 Poisson 等号；看见事故数方差明显大于均值，优先想混合强度。
4. **条件二项的 $p$ 是强度比** $\lambda_1/(\lambda_1+\lambda_2)$，不是「题目里随便一个比例」。
5. **复合 $\neq$ 混合**。复合保持「次数是 Poisson」；混合改的是次数的分布。
6. 连续时间染色：颜色必须 i.i.d.、与到达独立。按时间段用不同 $p(t)$ 是非齐次染色，边缘仍可 Poisson，独立要重新证。

---

## 9. 练哪些题

本仓库短题：[[条件概率与条件期望——训练题]] 的 A3、F1、G1、G2、C1。

Ross 12e 第 3 章（[[课后习题/第03章-条件概率与条件期望/03-原题]]）：

| 题 | 点 |
|---|---|
| Example 3.3 / 3.24（讲义） | 条件二项；瑜伽馆分裂 |
| 3.17 | Poisson–伽马共轭 |
| 3.37, 3.56 | 混合 Poisson 的均值方差 |
| 3.53*, 3.57, 3.58* | 指数 / 均匀 / 伽马混合的边际 |
| 3.44, 3.92 | 复合 Poisson |
| 3.96 | 随机抽取后仍是 Poisson（分裂味道） |

Chap.5 把 §1–§2 升级成过程：独立增量 + 染色 + 叠加，见 [[concepts/泊松过程]] 与笔记整理（5）（6）。
