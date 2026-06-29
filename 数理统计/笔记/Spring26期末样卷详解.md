# Spring 2026 数理统计期末样卷 — 完整解答

> Source: `source/数理统计/数理统计_Spring26_期末样卷.docx`
> 抽取说明：该 docx 公式以 OMML（`<m:oMath>`）存储，`raw/数理统计/数理统计_Spring26_期末样卷.md` 与工作区临时文件均丢公式。本篇从 `document.xml` 的 OMML 节点还原全文后作答，公式逐条经独立推导核对。
> 覆盖：充分统计量唯一性 / 有效性 / LRT 与正态 z 检验 / 正则指数族与完备充分统计量 / MVUE（Lehmann-Scheffé + Rao-Blackwell）/ NP 最优检验 / Beta(θ,1) 拒绝域

> ⚠️ **作答前提醒**：原卷答案在**第三大题第 3 题**有一处笔误——完备充分统计量是 $\sum\log X_i$（或 $\prod X_i$），原答案误写成 $\sum X_i$。下文给出正确推导并标注。其余各题答案均经独立核对，与原卷一致。

---

## 一、判断题（每小题 2 分，共计 10 分）

### 1. 一个参数的充分统计量必然唯一存在。 **(F)**

**解析**：充分统计量若存在也**不唯一**——任何一一变换仍是充分的。例如 $N(\theta,1)$ 的 $\sum X_i$ 与 $\bar X$ 都是充分的。且并非所有分布都有低维充分统计量（如位置 Cauchy）。关键词"必然唯一存在"两处都错。

**参考**：[12 充分统计量](12%20充分统计量.md)

### 2. 估计量的有效性一定在区间 $[0,1]$ 之内。 **(T)**

**解析**：有效性 $\text{Eff}(\hat\theta)=\dfrac{\text{RCB}}{\text{Var}(\hat\theta)}$。由 Cramér-Rao 不等式 $\text{Var}(\hat\theta)\ge\text{RCB}$（正则条件下），故 $\text{Eff}\in[0,1]$，等号成立即有效估计量。

**参考**：[09 Rao-Cramer下界与有效性](09%20Rao-Cramer下界与有效性.md)

### 3. 假设样本 $X_1,\ldots,X_n$ 取自正态分布 $N(\mu_0,\theta)$，其中 $\mu_0$ 已知。考虑假设 $H_0:\theta=\theta_0$ vs $H_1:\theta\ne\theta_0$ 的似然比检验，则得到的拒绝域是一个依赖于统计量 $\bar X$ 的拒绝域。 **(F)**

**解析**：这里 $\theta$ 是**方差**参数、$\mu_0$ 已知。由 Neyman 分解，充分统计量是 $\sum(X_i-\mu_0)^2$（不是 $\bar X$）。LRT 统计量
$$-2\log\Lambda=2\{l(\hat\theta)-l(\theta_0)\},\qquad \hat\theta=\tfrac1n\sum(X_i-\mu_0)^2$$
化简后只含 $\sum(X_i-\mu_0)^2$，拒绝域为 $\{\sum(X_i-\mu_0)^2\le c_1\}\cup\{\sum(X_i-\mu_0)^2\ge c_2\}$，**不依赖 $\bar X$**。故判 F。

> 💡 对照记：均值未知估均值时拒绝域才依赖 $\bar X$（z/t 检验）；这里均值已知估方差，依赖的是离差平方和。

**参考**：[07 正态总体假设检验与拟合优度检验](07%20正态总体假设检验与拟合优度检验.md)、[常见分布信息汇总](常见分布信息汇总.md)（第 7 条 $N(\mu_0,\theta)$）

### 4. 对于单参数的正则指数分布类，完备充分统计量一定存在。 **(T)**

**解析**：单参数正则指数族 $f(x;\theta)=\exp\{p(\theta)K(x)+H(x)+q(\theta)\}$，自然参数 $p(\theta)$ 取值含一开区间，由指数族完备性定理，$T=\sum K(X_i)$ 为**完备充分**统计量。故"一定存在"成立。

**参考**：[13 完备性与指数分布类](13%20完备性与指数分布类.md)

### 5. 若有 $\theta$ 的完备充分统计量 $Y$ 的函数 $\varphi(Y)$，它是参数的函数 $g(\theta)$ 的无偏估计量，则 $\varphi(Y)$ 为 $g(\theta)$ 的 MVUE。 **(T)**

**解析**：这正是 **Lehmann-Scheffé 定理**——完备充分统计量的无偏函数即 MVUE（唯一）。完备性保证唯一性，充分性 + Rao-Blackwell 保证方差最小。

**参考**：[13 完备性与指数分布类](13%20完备性与指数分布类.md)、[14 最小充分性与从属统计量](14%20最小充分性与从属统计量.md)

---

## 二、单选题（每小题 3 分，共计 15 分）

### 1. 下面哪种情况中，统计量 $Y$ 不是 $\theta$ 的充分统计量？ **(B)**

A. $X_1,\ldots,X_n\sim N(\theta,1)$，$Y=\sum X_i$ → 充分（因子分解，$K(x)=x$）✓
B. **$X_1,\ldots,X_n\sim N(0,\theta)$，$Y=(\sum X_i)^2$ → 不充分** ❌
   - $N(0,\theta)$ 均值 0 已知、方差 $\theta$ 未知，充分统计量是 $\sum X_i^2$。而 $(\sum X_i)^2\ne\sum X_i^2$，丢失了平方和的信息，不充分。
C. $X_1,\ldots,X_n\sim U[0,\theta]$，$Y=1/\max X_i$ → 充分（与 $X_{(n)}$ 一一对应）✓
D. $X_1\sim Bin(5,\theta)$，$Y=X_1$ → 充分（单样本自身即充分）✓

### 2. 假设 $X_1,\ldots,X_n$ 为取自总体的样本。下列哪种情况中，给出的统计量 $Y$ 不是未知参数 $\theta$ 的充分统计量？ **(B)**

A. $N(\mu_0,\theta)$，$\mu_0$ 已知，$Y=\sum(X_i-\mu_0)^2$ → 充分 ✓
B. **$N(\theta,\sigma_0^2)$，$\sigma_0$ 已知，$Y=\sum X_i^2$ → 不充分** ❌
   - 均值 $\theta$ 未知、方差已知，充分统计量是 $\sum X_i$（或 $\bar X$）。$\sum X_i^2$ 不能替代 $\sum X_i$（除非 $\theta=0$），不充分。
C. $Bin(m,\theta)$，$m$ 已知，$Y=\sum X_i$ → 充分 ✓
D. 平移指数 $f(x;\theta)=e^{-(x-\theta)},\,x>\theta$，$Y=\min X_i$ → 充分（$X_{(1)}$）✓

> 💡 第 1、2 题是同一考点的正反两问：**均值未知估均值**用 $\sum X_i$；**方差未知估方差（均值已知）**用 $\sum(X_i-\mu_0)^2$。把平方和/和的平方混了就错。

### 3. 下列分布中，属于正则指数分布类的是 **(B)**

A. 均匀分布 $U[0,\theta]$ → 支撑 $[0,\theta]$ 依赖 $\theta$，非正则 ❌
B. **拉普拉斯 $f(x;\theta)=\frac1{2\theta}\exp(-|x|/\theta),\,-\infty<x<\infty$** → 正则 ✓
   - $f=\exp\{-\frac1\theta|x|-\ln(2\theta)\}$，$p(\theta)=-1/\theta$，$K(x)=|x|$，$q(\theta)=-\ln(2\theta)$，支撑 $\mathbb R$ 不依赖 $\theta$。
C. 平移指数 $f(x;\theta)=e^{-(x-\theta)},\,x>\theta$ → 支撑依赖 $\theta$，非正则 ❌
D. 正态 $N(\theta,\theta^2)$ → 均值方差耦合含 $\theta$，无法写成 $p(\theta)K(x)+H(x)+q(\theta)$ 的可加分离形式，非（单参数）正则指数族 ❌

**参考**：[13 完备性与指数分布类](13%20完备性与指数分布类.md)、[常见分布信息汇总](常见分布信息汇总.md)（拉普拉斯 $a$ 已知估 $b$ 一条）

### 4. 下面 $\theta$ 的估计量中，不为 $\theta$ 的 MVUE 的是 **(A)**

A. **$U[0,\theta]$，$\hat\theta=\max X_i$ → 不是 MVUE** ❌
   - $E[X_{(n)}]=\frac n{n+1}\theta$ **有偏**；MVUE 是 $\frac{n+1}{n}X_{(n)}$。
B. $N(\theta,\sigma_0^2)$（$\sigma_0^2$ 已知），$\hat\theta=\bar X$ → 无偏有效，MVUE ✓
C. $Po(\theta)$，$\hat\theta=\bar X$ → 无偏有效，MVUE ✓
D. $Exp(1/\theta)$，$\hat\theta=\bar X$ → mean 参数化 $E[X]=\theta$，$\bar X$ 无偏有效，MVUE ✓

> ⚠️ $U[0,\theta]$ 是"非正则但有 CSS"的反例：$X_{(n)}$ 完备充分，但 MLE 本身有偏，需乘 $\frac{n+1}{n}$ 纠偏才是 MVUE，且其方差不达任何 C-R 下界（RCB 不适用）。

### 5. 若 $\hat\theta$ 为 $\theta$ 的 MVUE，下列说法正确的是 **(B)**

A. $\hat\theta$ 的方差一定能达到 Rao-Cramer 下界 → 错。MVUE 未必有效，如 $U[0,\theta]$ 的 $\frac{n+1}{n}X_{(n)}$ 根本不受 RCB 约束。❌
B. **若 $\hat\theta$ 为 $\theta$ 的 MVUE，且 $g(\theta)=a+b\theta$，$a,b$ 已知常数 $b\ne0$，则 $g(\hat\theta)$ 一定为 $g(\theta)$ 的 MVUE** → 正确 ✓
   - MVUE 对**仿射变换**保持：$g(\hat\theta)=a+b\hat\theta$ 无偏（$E=a+b\theta$），且仿射不改变"方差最小"的排序。$b\ne0$ 保证非退化。
C. 若 $\hat\theta'$ 为另一个估计量，则必有 $\text{Var}(\hat\theta)\le\text{Var}(\hat\theta')$ → 错。MVUE 只在**无偏估计**类中最小，对有偏估计不成立；且可有方差相等的另一无偏估计。❌
D. $\hat\theta$ 一定为 $\theta$ 的 MLE → 错。MVUE 不必是 MLE，如 $U[0,\theta]$ 的 MVUE $\frac{n+1}{n}X_{(n)}$ ≠ MLE $X_{(n)}$。❌

**参考**：[14 最小充分性与从属统计量](14%20最小充分性与从属统计量.md)、[常见分布信息汇总](常见分布信息汇总.md)（坑 10）

---

## 三、计算题（共计 75 分）

### 1.（15 分）正态总体 LRT 等价于 z 检验

**已知**：$X_1,\ldots,X_n\sim N(\mu,\sigma_0^2)$，$\sigma_0^2$ 已知。检验 $H_0:\mu=\mu_0$ vs $H_1:\mu\ne\mu_0$。证明 LRT 等价于 z 检验。

**解**：

① $\mu$ 的 MLE 为 $\hat\mu=\bar X$。似然函数
$$L(\mu)=\Big(\frac1{\sigma_0\sqrt{2\pi}}\Big)^{\!n}\exp\!\Big\{-\frac1{2\sigma_0^2}\sum_{i=1}^n(X_i-\mu)^2\Big\}.$$

② 代入 $\hat\mu=\bar X$ 与 $\mu_0$，利用 $\sum(X_i-\bar X)^2=\sum X_i^2-n\bar X^2$、$\sum(X_i-\mu_0)^2=\sum(X_i-\bar X)^2+n(\bar X-\mu_0)^2$，得
$$\Lambda=\frac{L(\mu_0)}{L(\hat\mu)}=\exp\!\Big\{-\frac{n}{2\sigma_0^2}(\bar X-\mu_0)^2\Big\}.$$

③ 拒绝域 $\{\Lambda\le c\}$ 等价于 $\{(\bar X-\mu_0)^2\ge c_1\}$，即
$$\Big\{\frac{|\bar X-\mu_0|}{\sigma_0/\sqrt n}\ge z_{\alpha/2}\Big\}.$$

在 $H_0$ 下 $\frac{\bar X-\mu_0}{\sigma_0/\sqrt n}\sim N(0,1)$，这正是 **z 检验**。$\square$

> ⭐ **套路**：方差已知估均值 → LRT 化为 $\bar X$ 的双侧 z 检验；方差未知时则化为 t 检验（$\sigma_0$ 换成 $S$，分位数换 $t_{\alpha/2}(n-1)$）。

**参考**：[10 极大似然检验](10%20极大似然检验.md)

---

### 2.（15 分）$Exp(1/\theta^2)$ 估计 $\theta$：MLE / RCB / 有效性

**已知**：$X_1,\ldots,X_n\sim Exp(1/\theta^2)$，$\theta>0$。即 $f(x;\theta)=\frac1{\theta^2}e^{-x/\theta^2}$，$E[X]=\theta^2$，$\text{Var}(X)=\theta^4$。目标估 $\theta$。又已知 $E(\sqrt{\bar X})=c\theta$，$0<c<\sqrt{\frac{4n}{4n+1}}$。

#### 1)（5 分）$\theta$ 的 MLE

$\theta^2$ 是 mean-参数化指数分布的均值，MLE 为 $\widehat{\theta^2}=\bar X$。由 MLE 不变性，
$$\boxed{\hat\theta=\sqrt{\bar X}.}$$

#### 2)（5 分）$\theta$ 的无偏估计的 RCB

单观测对数密度 $\log f(X;\theta)=-2\log\theta-\frac{X}{\theta^2}$。
$$\frac{\partial\log f}{\partial\theta}=-\frac2\theta+\frac{2X}{\theta^3},\qquad
\frac{\partial^2\log f}{\partial\theta^2}=\frac2{\theta^2}-\frac{6X}{\theta^4}.$$
取期望（$E[X]=\theta^2$）：
$$I(\theta)=-E\!\Big[\frac{\partial^2\log f}{\partial\theta^2}\Big]=-\Big(\frac2{\theta^2}-\frac{6\theta^2}{\theta^4}\Big)=\frac4{\theta^2}.$$
故
$$\boxed{\text{RCB}=\frac1{nI(\theta)}=\frac{\theta^2}{4n}.}$$

#### 3)（5 分）由 $E(\sqrt{\bar X})=c\theta$ 构造无偏估计并算有效性

由 $E(\sqrt{\bar X})=c\theta$，取
$$\hat\theta=\frac1c\sqrt{\bar X}\quad\Rightarrow\quad E[\hat\theta]=\theta\ \text{（无偏）}.$$

算方差。先算 $\text{Var}(\sqrt{\bar X})$：
$$\text{Var}(\sqrt{\bar X})=E[\bar X]-\big(E[\sqrt{\bar X}]\big)^2=\theta^2-c^2\theta^2=(1-c^2)\theta^2.$$
（这里 $E[\bar X]=\theta^2$。）于是
$$\text{Var}(\hat\theta)=\frac1{c^2}\text{Var}(\sqrt{\bar X})=\frac{1-c^2}{c^2}\theta^2.$$

有效性：
$$\boxed{\text{Eff}(\hat\theta)=\frac{\text{RCB}}{\text{Var}(\hat\theta)}=\frac{\theta^2/(4n)}{(1-c^2)\theta^2/c^2}=\frac{c^2}{4n(1-c^2)}.}$$

> 💡 **关于常数 $c$ 的范围**：$0<c<\sqrt{\tfrac{4n}{4n+1}}$ 保证了 $\text{Eff}<1$（即 $\hat\theta$ 非有效）。代入上界 $c^2=\frac{4n}{4n+1}$ 时 $\text{Eff}=\frac{4n/(4n+1)}{4n\cdot 1/(4n+1)}=1$；$c$ 更小则 $\text{Eff}<1$。这也说明 $\sqrt{\bar X}$ 的纠偏估计量一般达不到 RCB。

**参考**：[09 Rao-Cramer下界与有效性](09%20Rao-Cramer下界与有效性.md)、[常见分布信息汇总](常见分布信息汇总.md)（第 9 条 mean-Exp）

---

### 3.（15 分）Beta(θ,1)：指数族 / 完备充分统计量 / NP 最优拒绝域

**已知**：$f(x,\theta)=\theta x^{\theta-1},\,0<x<1$（即 $\text{Beta}(\theta,1)$），$\theta>0$。样本 $X_1,\ldots,X_n$。

#### 1)（5 分）判断是否正则指数族

$$f(x;\theta)=\theta x^{\theta-1}=\exp\{(\theta-1)\log x+\log\theta\}=\exp\{\underbrace{(\theta-1)}_{p(\theta)}\underbrace{\log x}_{K(x)}+\underbrace{0}_{H(x)}+\underbrace{\log\theta}_{q(\theta)}\}.$$
支撑 $(0,1)$ 与 $\theta$ 无关，$p(\theta)=\theta-1$ 非平凡连续。✅ **属于正则指数分布类**。

#### 2)（5 分）完备充分统计量

由 $K(x)=\log x$，完备充分统计量为
$$\boxed{Y=\sum_{i=1}^n \log X_i\ \ (\text{等价于 }\prod X_i).}$$

#### 3)（5 分）$H_0:\theta=1$ vs $H_1:\theta=2$，证明最优拒绝域形如 $\{\sum\log X_i\ge c\}$

> ⚠️ **原卷答案此处有笔误**：原文写似然比 $\Lambda=(1/2)^n(\sum X_i)^{-1}$、拒绝域 $\{\sum X_i\ge c\}$。正确的统计量是 $\sum\log X_i$（或 $\prod X_i$），不是 $\sum X_i$。下面给出正确推导。

似然函数 $L(\theta)=\theta^n\big(\prod x_i\big)^{\theta-1}$。由 Neyman-Pearson 引理，MP 检验拒绝 $H_0$ 当 $\frac{L(2)}{L(1)}\ge k$：
$$\frac{L(2)}{L(1)}=\frac{2^n(\prod x_i)^{2-1}}{1^n(\prod x_i)^{1-1}}=2^n\prod x_i=2^n\exp\!\Big(\sum_{i=1}^n\log x_i\Big).$$

该似然比关于 $Y=\sum\log X_i$ **单调递增**（$\prod x_i$ 关于每个 $x_i$ 递增，故 $Y$ 越大似然比越大）。因此 $\frac{L(2)}{L(1)}\ge k\iff Y\ge c$，最优拒绝域为
$$\boxed{\Big\{\sum_{i=1}^n\log X_i\ge c\Big\}\ \ \text{（等价 }\{\prod X_i\ge c'\}\text{）}.}$$

> 💡 **直觉核对**：$H_0:\theta=1$ 即 $X\sim U(0,1)$，均值 $1/2$；$H_1:\theta=2$ 即 $X\sim\text{Beta}(2,1)$，密度 $2x$，均值 $2/3$。$H_1$ 下 $X$ 偏大，故 $\prod X_i$（或 $\sum\log X_i$）偏大时拒绝 $H_0$，方向一致。⚠️ 注意 $\sum\log X_i\ge c$ 与 $\sum X_i\ge c$ **不是同一条件**——$\sum X_i$ 不是充分统计量，NP 给出的是充分统计量 $\sum\log X_i$ 的拒绝域。

**参考**：[15 最优假设检验](15%20最优假设检验.md)、[常见分布信息汇总](常见分布信息汇总.md)（第 12 条 Beta(θ,1)）

---

### 4.（15 分）Bernoulli(θ)：$g(\theta)=a\theta^2+b\theta+c$ 的 MVUE

**已知**：$X_1,\ldots,X_n\sim\text{Bernoulli}(\theta)$。完备充分统计量 $Y=\bar X$（等价 $\sum X_i\sim\text{Bin}(n,\theta)$）。

**矩**：
$$E[\bar X]=\theta,\qquad E[\bar X^2]=(E[\bar X])^2+\text{Var}(\bar X)=\theta^2+\frac{\theta(1-\theta)}{n}=\frac{n-1}{n}\theta^2+\frac1n\theta.$$

由此：
- $\bar X$ 是 $\theta$ 的无偏估计；
- $E\!\big[\bar X^2-\tfrac{\bar X}{n}\big]=\theta^2+\frac{\theta(1-\theta)}{n}-\frac\theta n=\theta^2-\frac{\theta^2}{n}=\frac{n-1}{n}\theta^2$，故 $\dfrac{n}{n-1}\Big(\bar X^2-\dfrac{\bar X}{n}\Big)$ 是 $\theta^2$ 的无偏估计。

组合得 $g(\theta)=a\theta^2+b\theta+c$ 的无偏估计：
$$\boxed{\widehat{g(\theta)}=a\cdot\frac{n}{n-1}\Big(\bar X^2-\frac{\bar X}{n}\Big)+b\bar X+c.}$$

它是完备充分统计量 $\bar X$ 的函数，由 **Lehmann-Scheffé 定理**，必为 MVUE。

> 💡 这题与 [Spring24 期末样卷详解 第5题](Spring24期末样卷详解.md)（$Bin(2,\theta)$ 估 $\theta(1+\theta)$）同构，只是参数函数换成了二次式。套路一致：用 $\bar X$ 与 $\bar X^2-\bar X/n$ 分别纠偏出 $\theta$、$\theta^2$，再线性组合。

**参考**：[14 最小充分性与从属统计量](14%20最小充分性与从属统计量.md)、[常见分布信息汇总](常见分布信息汇总.md)（第 1 条 Bernoulli）

---

### 5.（15 分）Poisson(θ)：$g(\theta)=e^{-\theta}+\theta^2 e^{-\theta}$ 的 MLE 与 MVUE

**已知**：$X_1,\ldots,X_n\sim\text{Po}(\theta)$，$P(X=k)=\frac{\theta^k}{k!}e^{-\theta}$。完备充分统计量 $Y=\sum X_i\sim\text{Po}(n\theta)$。估 $g(\theta)=e^{-\theta}(1+\theta^2)$。

#### 1)（5 分）$g(\theta)$ 的 MLE

$\theta$ 的 MLE 为 $\hat\theta=\bar X$。由 MLE 不变性，
$$\boxed{\widehat{g(\theta)}_{\text{MLE}}=g(\hat\theta)=e^{-\bar X}(1+\bar X^2).}$$

#### 2)（10 分）$g(\theta)$ 的 MVUE（Rao-Blackwell）

**① 找无偏估计 $u(X_1)$。** 注意
$$g(\theta)=e^{-\theta}+\theta^2 e^{-\theta}=P(X_1=0)+2P(X_1=2),$$
（因 $P(X_1=2)=\frac{\theta^2}{2}e^{-\theta}$，$2P(X_1=2)=\theta^2 e^{-\theta}$）。故取
$$u(X_1)=I_{\{X_1=0\}}+2I_{\{X_1=2\}},\qquad E[u(X_1)]=g(\theta).$$

**② Rao-Blackwell：算 $E[u(X_1)\mid Y=y]$。** 由 $X_1\mid Y=y\sim\text{Bin}(y,1/n)$（标准结论，见下）：
$$E[u(X_1)\mid Y=y]=P(X_1=0\mid Y=y)+2P(X_1=2\mid Y=y).$$

用条件概率公式（$\sum_{i=2}^n X_i\sim\text{Po}((n-1)\theta)$）：
$$P(X_1=0\mid Y=y)=\frac{P(X_1=0)P(\sum_{i=2}^n X_i=y)}{P(Y=y)}=\frac{e^{-\theta}\cdot\frac{((n-1)\theta)^y e^{-(n-1)\theta}}{y!}}{\frac{(n\theta)^y e^{-n\theta}}{y!}}=\Big(\frac{n-1}{n}\Big)^{\!y}.$$
$$P(X_1=2\mid Y=y)=\frac{P(X_1=2)P(\sum_{i=2}^n X_i=y-2)}{P(Y=y)}=\frac{\frac{\theta^2 e^{-\theta}}{2}\cdot\frac{((n-1)\theta)^{y-2}e^{-(n-1)\theta}}{(y-2)!}}{\frac{(n\theta)^y e^{-n\theta}}{y!}}=\frac{y(y-1)}{2n^2}\Big(\frac{n-1}{n}\Big)^{\!y-2}.$$

（最后一步用了 $\frac{y!}{(y-2)!}=y(y-1)$ 与 $\theta$ 的幂次相消。）代入：
$$E[u(X_1)\mid Y=y]=\Big(\frac{n-1}{n}\Big)^{\!y}+2\cdot\frac{y(y-1)}{2n^2}\Big(\frac{n-1}{n}\Big)^{\!y-2}=\Big(\frac{n-1}{n}\Big)^{\!y}+\frac{y(y-1)}{n^2}\Big(\frac{n-1}{n}\Big)^{\!y-2}.$$

它是完备充分统计量 $Y$ 的函数且无偏，由 Lehmann-Scheffé 定理即 MVUE：
$$\boxed{\widehat{g(\theta)}_{\text{MVUE}}=\Big(\frac{n-1}{n}\Big)^{\!Y}+\frac{Y(Y-1)}{n^2}\Big(\frac{n-1}{n}\Big)^{\!Y-2},\quad Y=\sum_{i=1}^n X_i.}$$

> ⭐ **两项的来源可分开看**：第一项 $\big(\frac{n-1}{n}\big)^Y$ 是 $e^{-\theta}$ 的 MVUE（即 $P(X_1=0)$ 的 MVUE，见 [常见分布信息汇总](常见分布信息汇总.md) Poisson 条）；第二项 $\frac{Y(Y-1)}{n^2}\big(\frac{n-1}{n}\big)^{Y-2}$ 是 $\theta^2 e^{-\theta}=2P(X_1=2)$ 的 MVUE。两者相加即得。
>
> 💡 **条件分布 $X_1\mid Y=y\sim\text{Bin}(y,1/n)$ 的速记**：给定总和 $y$ 个事件，每个事件独立等概率落在 $n$ 个样本之一，故 $X_1\sim\text{Bin}(y,1/n)$。这能让你跳过逐项写条件概率的代数。

**参考**：[13 完备性与指数分布类](13%20完备性与指数分布类.md)、[常见分布信息汇总](常见分布信息汇总.md)（第 5 条 Poisson 的 MVUE 套路）、[Spring25 期末样卷详解 第5题](Spring25期末样卷详解.md)（同型 Rao-Blackwell）

---

## 总览与考点分布

| 考点 | 题型 | 分值 | 对应讲义 |
|------|------|------|----------|
| 充分统计量唯一性 | 判断 | 2 | 第 12 讲 |
| 有效性 ∈[0,1] | 判断 | 2 | 第 9 讲 |
| $N(\mu_0,\theta)$ LRT 拒绝域依赖谁 | 判断 | 2 | 第 10 讲 |
| 正则指数族⇒完备充分存在 | 判断 | 2 | 第 13 讲 |
| Lehmann-Scheffé | 判断 | 2 | 第 13 讲 |
| 充分统计量判定（和 vs 平方和） | 单选×2 | 6 | 第 12 讲 |
| 正则指数族识别 | 单选 | 3 | 第 13 讲 |
| MVUE 识别（$U[0,\theta]$ 有偏） | 单选 | 3 | 第 14 讲 |
| MVUE 的仿射保持 | 单选 | 3 | 第 14 讲 |
| LRT⇔z 检验 | 计算 | 15 | 第 10 讲 |
| MLE/RCB/有效性（mean-Exp） | 计算 | 15 | 第 9 讲 |
| 指数族+CSS+NP 拒绝域（Beta） | 计算 | 15 | 第 13/15 讲 |
| Bernoulli 二次式 MVUE | 计算 | 15 | 第 14 讲 |
| Poisson $e^{-\theta}(1+\theta^2)$ MLE+MVUE | 计算 | 15 | 第 14 讲 |

---

## 易错点

> ⚠️ **1. 第三大题第 3 题的笔误（最高优先级）**
> 原卷答案把 Beta(θ,1) 的完备充分统计量 $\sum\log X_i$ 误写成 $\sum X_i$。NP 拒绝域也应以 $\sum\log X_i$（或 $\prod X_i$）为统计量。$\sum X_i$ 不是充分统计量，照原答案写会被扣分。

> ⚠️ **2. 均值未知估均值 vs 方差未知估方差（均值已知）**
> 充分统计量分别是 $\sum X_i$ 与 $\sum(X_i-\mu_0)^2$。判断题 3、单选 1/2 都考这点。注意 $(\sum X_i)^2\ne\sum X_i^2$。

> ⚠️ **3. $U[0,\theta]$ 的 MLE 不是 MVUE**
> $X_{(n)}$ 有偏（$E=\frac n{n+1}\theta$），MVUE 是 $\frac{n+1}{n}X_{(n)}$。且该分布非正则，RCB 不适用——别用"达 RCB"去判它的有效性。

> ⚠️ **4. MVUE 的保持性只对仿射变换成立**
> 单选 5 的 B 选项：$g(\theta)=a+b\theta$（$b\ne0$）才保 MVUE；非线性变换不保（如 $\hat\theta$ 是 $\theta$ 的 MVUE，$\hat\theta^2$ 未必是 $\theta^2$ 的 MVUE，需另纠偏）。

> ⚠️ **5. Exp 的参数化**
> $Exp(1/\theta^2)$ 是 mean 参数化（$E[X]=\theta^2$），MLE $\bar X$ 无偏。若题目写 $Exp(\theta)$（rate），则 $E[X]=1/\theta$，MLE $1/\bar X$ 有偏。算前先确认参数化。

> ⚠️ **6. Poisson MVUE 的"拼装"思路**
> $e^{-\theta}=P(X_1=0)$、$\theta^2 e^{-\theta}=2P(X_1=2)$，把待估函数拆成若干 $P(X_1=k)$ 的线性组合，每个用 $I_{\{X_1=k\}}$ 做无偏估计，再 Rao-Blackwell 对 $\sum X_i$ 取条件期望。条件分布 $X_1\mid Y=y\sim\text{Bin}(y,1/n)$ 是速算关键。

---

## See Also

- [数理统计期末总结](数理统计期末总结.md) — 全部知识点汇总
- [常见分布信息汇总](常见分布信息汇总.md) — 各分布 MLE/Fisher/CSS/MVUE 速查
- [Spring24 期末样卷详解](Spring24期末样卷详解.md) / [Spring25 期末样卷详解](Spring25期末样卷详解.md) — 同型实战题型
- [09 Rao-Cramer下界与有效性](09%20Rao-Cramer下界与有效性.md)
- [10 极大似然检验](10%20极大似然检验.md)
- [12 充分统计量](12%20充分统计量.md)
- [13 完备性与指数分布类](13%20完备性与指数分布类.md)
- [14 最小充分性与从属统计量](14%20最小充分性与从属统计量.md)
- [15 最优假设检验](15%20最优假设检验.md)
