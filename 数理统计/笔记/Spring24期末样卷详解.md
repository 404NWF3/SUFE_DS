# Spring 2024 数理统计期末样卷 — 完整解答

> Source: `source/数理统计/数理统计_Spring24_期末样卷(1).docx`
> 覆盖：MLE、Fisher 信息量、有效性、RCB、LRT、指数分布族、完备充分统计量、Neyman-Pearson 最优检验、MVUE（Rao-Blackwell 与直接构造）

---

## 一、判断题（每小题 2 分，共计 10 分）

### 1. 无偏估计量的有效性一定在区间 $[0,1]$ 之中。 **(T)**

**解析**：设 $\widehat\theta$ 为 $\theta$ 的无偏估计量，其有效性定义为
$$
\text{Eff}(\widehat\theta) = \frac{\text{RCB}}{\text{Var}(\widehat\theta)},\quad \text{RCB} = \frac{1}{nI(\theta)}
$$
由 Cramér-Rao 不等式，$\text{Var}(\widehat\theta) \ge \text{RCB}$，故 $\text{Eff}(\widehat\theta) \in [0,1]$。等号成立时称 $\widehat\theta$ 为**有效估计量**。

### 2. 假设随机变量 $Y$ 的分布中含有参数 $\theta$，且属于一个完备族。如果 $E\{u(Y)\}=0$ 对于**某个** $\theta$ 成立，则 $u(Y)=0$ 几乎必然成立。 **(F)**

**解析**：完备族的定义要求：若 $E_\theta[u(Y)]=0$ 对**所有** $\theta\in\Theta$ 成立，才能推出 $u(Y)=0$ a.s.。题目说"对于某个 $\theta$ 成立"即可推出结论，是错误的。例如 $Y\sim N(\mu,1)$，取 $u(Y)=Y-\mu_0$，则当 $\theta=\mu_0$ 时 $E(u(Y))=0$ 但 $Y-\mu_0\not\equiv 0$。

### 3. 若总体分布中只含有一个参数 $\theta$，则可以找到一个 1 维的充分统计量。 **(F)**

**解析**：充分统计量的维度与参数维度无必然对应。反例：**Cauchy 分布** $C(\theta,1)$ 只有位置参数，但不存在低于样本容量的充分统计量。均匀分布 $U(\theta-1/2,\theta+1/2)$ 亦然。

### 4. 假设总体分布中有未知参数 $\theta$，$\theta$ 的 MLE 为 $\widehat\theta$。对于双侧检验 $H_0:\theta=\theta_0\ \text{vs}\ H_1:\theta\neq\theta_0$ 使用似然比检验，拒绝域可以取为 $\{l(\widehat\theta)-l(\theta_0)\le c\}$。**(F)**

**解析**：似然比检验统计量为 $\Lambda = L(\theta_0)/L(\widehat\theta)$ 或等价的 $-2\log\Lambda = 2[l(\widehat\theta)-l(\theta_0)]$。拒绝域应为 $\{-2\log\Lambda \ge c\}$，即 $l(\widehat\theta)-l(\theta_0)$ **足够大**时拒绝。题目取 $\le c$ 方向反了。

### 5. 假设样本 $X_1,\ldots,X_n$ 取自正态分布 $N(0,\theta)$。对于 $\theta'<\theta''$，检验 $H_0:\theta=\theta'\ \text{vs}\ H_1:\theta=\theta''$ 的最优拒绝域形如 $\{\sum X_i^2 \ge c\}$。**(T)**

**解析**：由 Neyman-Pearson 引理，MP 检验拒绝域为 $\{L(\theta'')/L(\theta') \ge k\}$。
$$
\frac{L(\theta'')}{L(\theta')} = \left(\frac{\theta'}{\theta''}\right)^{\!n/2}\!\exp\!\left\{\frac{\sum X_i^2}{2}\!\left(\frac{1}{\theta'}-\frac{1}{\theta''}\right)\right\}
$$
因 $\theta''>\theta'$ 有 $1/\theta'-1/\theta''>0$，似然比关于 $\sum X_i^2$ 单调递增，等价于 $\{\sum X_i^2 \ge c\}$。✅

> ⚠️ 第 4 题易混淆 LRT 拒绝域的方向。$\{-2\log\Lambda\ge c\}$ 意味着 $l(\widehat\theta)-l(\theta_0)$ 足够大才拒绝，不是足够小。

---

## 二、单选题（每小题 3 分，共计 15 分）

### 1. 下列说法正确的是 **(A)**

A. **Fisher 信息量 $I(\theta)$ 总是非负的** ✅
   - $I(\theta)=E[(\partial\log f/\partial\theta)^2]\ge 0$，取零当且仅当得分函数几乎处处为零（即分布与 $\theta$ 无关）。

B. 参数 $\theta$ 的函数 $g(\theta)$ 的无偏估计量的 Rao-Cramer 下界为 $1/[nI(\theta)]$ ❌
   - 正确 RCB 为 $[g'(\theta)]^2/[nI(\theta)]$。

C. 任何 $\theta$ 的估计量的方差都不会低于 Rao-Cramer 下界 ❌
   - 正则条件不满足时，方差可以低于 RCB（如 $U[0,\theta]$ 的 MLE）。

D. $\theta$ 的有效估计量一定存在 ❌
   - 有效估计量存在是有条件的（RCB 可达），许多分布不存在有效估计。

### 2. 关于充分统计量，下列说法正确的是 **(C)**

A. 充分统计量唯一存在 ❌（如正态分布 $N(\mu,1)$ 的 $\sum X_i$ 和 $\overline X$ 都是充分的）
B. 最小充分统计量唯一存在 ❌（不一定唯一）
C. **若 $Y$ 为充分统计量，则 $e^Y$ 也是充分统计量** ✅（一一变换保充分性）
D. 若 $Y_1,Y_2$ 均为充分统计量，则 $Y_1+Y_2$ 也是充分统计量 ❌（无反例；但和的充分性不自动成立，需验证，且直觉上 C 更符合定义）

### 3. 统计量 $Y$ **不是** $\theta$ 的充分统计量的是 **(B)**

A. $X_i\sim N(\theta,1)$，$Y=\sum X_i$ → 充分 ✅
B. **$X_i\sim N(1,\theta)$，$Y=\sum X_i^2$ → 不充分** ❌
   - $f(x;\theta)=(2\pi\theta)^{-1/2}\exp\{-(x-1)^2/(2\theta)\}$：充分统计量应包含 $\sum X_i$ 和 $\sum X_i^2$。单靠 $\sum X_i^2$ 丢失了 $\sum X_i$ 的信息，不充分。
C. $X_i\sim U[0,\theta]$，$Y=1/\max(X_i)$ → 充分 ✅（与 $\max X_i$ 一一对应）
D. $X_1\sim Bin(5,\theta)$，$Y=X_1$ → 充分 ✅

### 4. 下列说法正确的是 **(D)**

A. $\theta$ 的无偏估计量一定是充分统计量的函数 ❌
B. 若一个 $\theta$ 的无偏估计量是充分统计量的函数，则它必然是 MVUE ❌（还需完备性）
C. 若 $\widehat\theta$ 为 $\theta$ 的 MVUE，则 $g(\widehat\theta)$ 一定是 $g(\theta)$ 的 MVUE ❌（非线性变换不保 MVUE）
D. **若两个不同的统计量均为 $\theta$ 的无偏估计量，则它们不可能都是 MVUE** ✅
   - MVUE 在平方损失下唯一。若存在两个不同的无偏估计，可通过 convex combination 构造方差更小的估计。

### 5. 不为 $\theta$ 的 MVUE 的是 **(D)**

A. $Bernoulli(\theta)$：$\widehat\theta=\overline X$ 是 MVUE ✅
B. $N(\theta,\sigma_0^2)$ 已知方差：$\widehat\theta=\overline X$ 是 MVUE ✅
C. $Po(\theta)$：$\widehat\theta=\overline X$ 是 MVUE ✅
D. **$Exp(\theta)$：$\widehat\theta=\overline X$ 不是 MVUE** ❌
   - 这里 $Exp(\theta)$ 是**速率参数化**：$f(x)=\theta e^{-\theta x}$，$E(X)=1/\theta$。$\overline X$ 不是 $\theta$ 的无偏估计，更谈不上 MVUE。

---

## 三、计算题（共计 75 分）

---

### 1.（15 分）几何分布的参数估计

**已知**：$X\sim Geom(1/\theta)$，p.m.f.
$$
f(x;\theta) = \frac{1}{\theta}\left(1-\frac{1}{\theta}\right)^{x-1},\quad x=1,2,\ldots,\ \theta>1
$$
$E(X)=\theta,\ Var(X)=\theta(\theta-1)$，样本 $X_1,\ldots,X_n$。

---

#### 1)（5 分）MLE

$$
\begin{aligned}
L(\theta) &= \prod_{i=1}^n f(x_i;\theta) = \theta^{-n}\left(\frac{\theta-1}{\theta}\right)^{\sum(x_i-1)} \\
l(\theta) &= -n\log\theta + n(\bar x-1)\bigl[\log(\theta-1)-\log\theta\bigr] \\
l'(\theta) &= -\frac{n}{\theta} + n(\bar x-1)\left(\frac{1}{\theta-1} - \frac{1}{\theta}\right) = -\frac{n}{\theta} + \frac{n(\bar x-1)}{\theta(\theta-1)}
\end{aligned}
$$

令 $l'(\theta)=0$：
$$
\frac{n(\bar x-1)}{\theta(\theta-1)} = \frac{n}{\theta}\ \Longrightarrow\ \frac{\bar x-1}{\theta-1}=1
$$

$$
\boxed{\widehat\theta = \overline X}
$$

---

#### 2)（5 分）Fisher 信息量 $I(\theta)$

**方法一（二阶导期望法）**：
$$
\frac{\partial\log f}{\partial\theta} = \frac{x-1}{\theta(\theta-1)} - \frac{1}{\theta}
$$
$$
\frac{\partial^2\log f}{\partial\theta^2} = -\frac{(x-1)(2\theta-1)}{\theta^2(\theta-1)^2} + \frac{1}{\theta^2}
$$
$$
E\!\left(\frac{\partial^2\log f}{\partial\theta^2}\right) = -\frac{(\theta-1)(2\theta-1)}{\theta^2(\theta-1)^2} + \frac{1}{\theta^2}
= -\frac{1}{\theta(\theta-1)}
$$

$$
\boxed{I(\theta) = -E\!\left(\frac{\partial^2\log f}{\partial\theta^2}\right) = \frac{1}{\theta(\theta-1)}}
$$

**方法二（得分函数方差法）**：
$$
I(\theta) = \text{Var}\!\left(\frac{\partial\log f}{\partial\theta}\right)
= \frac{\text{Var}(X)}{\theta^2(\theta-1)^2}
= \frac{\theta(\theta-1)}{\theta^2(\theta-1)^2} = \frac{1}{\theta(\theta-1)}
$$
两种方法结果一致。

---

#### 3)（5 分）MLE 的有效性

**Rao-Cramer 下界**：
$$
\text{RCB} = \frac{1}{nI(\theta)} = \frac{\theta(\theta-1)}{n}
$$

**MLE 的方差**：
$$
\text{Var}(\widehat\theta) = \text{Var}(\overline X) = \frac{\text{Var}(X)}{n} = \frac{\theta(\theta-1)}{n}
$$

**有效性**：
$$
\boxed{\text{Eff}(\widehat\theta) = \frac{\text{RCB}}{\text{Var}(\widehat\theta)} = 1}
$$

$\widehat\theta$ 达到 Cramér-Rao 下界，是**有效估计量**。

> ⭐ MLE 有效性的判断步骤​：①计算 Fisher 信息量 ②计算 RCB ③计算 MLE 方差 ④比较是否相等。本题中几何分布恰好达到下界。

---

### 2.（14 分）Gamma 分布似然比检验

**已知**：$X_i \sim \Gamma(c,\theta)$，p.d.f.
$$
f(x;\theta) = \frac{1}{\Gamma(c)\theta^c}x^{c-1}e^{-x/\theta},\quad x>0
$$
$c$ **已知**，$\theta$ **未知**。检验 $H_0:\theta=\theta_0\ \text{vs}\ H_1:\theta\neq\theta_0$。

---

#### 1)（7 分）似然比检验统计量

$$
\begin{aligned}
L(\theta) &= \frac{1}{\Gamma(c)^n\theta^{nc}}\left(\prod x_i\right)^{c-1}\exp\!\left(-\frac{\sum x_i}{\theta}\right) \\
l(\theta) &= -n\log\Gamma(c) - nc\log\theta + (c-1)\sum\log x_i - \frac{\sum x_i}{\theta} \\
l'(\theta) &= -\frac{nc}{\theta} + \frac{\sum x_i}{\theta^2}
\end{aligned}
$$

令 $l'(\theta)=0$ 得 MLE：
$$
\widehat\theta = \frac{\sum_{i=1}^n X_i}{nc}
$$

**似然比检验统计量**（取 $L(\theta_0)/L(\widehat\theta)$ 形式）：
$$
\Lambda = \frac{L(\theta_0)}{L(\widehat\theta)} = \frac{\theta_0^{-nc}\exp\!\left(-\dfrac{Y}{\theta_0}\right)}{\widehat\theta^{-nc}\exp\!\left(-\dfrac{Y}{\widehat\theta}\right)},\qquad Y = \sum_{i=1}^n X_i
$$

其等价形式（常用）为：
$$
\boxed{-2\log\Lambda = 2\bigl[l(\widehat\theta) - l(\theta_0)\bigr]}
$$

展开计算：
$$
\begin{aligned}
l(\widehat\theta) - l(\theta_0) &= -nc\log\!\left(\frac{Y}{nc}\right) - nc - \left[-nc\log\theta_0 - \frac{Y}{\theta_0}\right] \\
&= -nc\log\!\left(\frac{Y}{nc\theta_0}\right) - nc + \frac{Y}{\theta_0}
\end{aligned}
$$

---

#### 2)（7 分）转化为关于 $Y$ 的拒绝域

**单调性分析**：
$$
\frac{d(-2\log\Lambda)}{dY} = 2\!\left(-\frac{nc}{Y} + \frac{1}{\theta_0}\right)
$$
- $Y < nc\theta_0$：导数负 → 递减
- $Y = nc\theta_0$：导数为零 → 极小值（即 $E_{H_0}(Y)$）
- $Y > nc\theta_0$：导数正 → 递增

故 $-2\log\Lambda$ 关于 $Y$ **先减后增**，拒绝域 $\{-2\log\Lambda\ge c\}$ 等价于两端：
$$
\{Y \le c_1\} \cup \{Y \ge c_2\}
$$

在 $H_0$ 下，$Y\sim\Gamma(nc,\theta_0)$。显著性水平 $\alpha$ 的拒绝域：
$$
\boxed{\bigl\{Y \le \Gamma_{1-\alpha/2}(nc,\theta_0)\bigr\}\ \cup\ \bigl\{Y \ge \Gamma_{\alpha/2}(nc,\theta_0)\bigr\}}
$$

其中 $\Gamma_{\alpha/2}$ 和 $\Gamma_{1-\alpha/2}$ 分别为 $\Gamma(nc,\theta_0)$ 的上 $\alpha/2$ 和上 $1-\alpha/2$ 分位数。

> ⭐ LRT 得到精确拒绝域（非渐进）的关键在于：①写出似然比 → ②代入 MLE 化简 → ③判断似然比关于充分统计量的单调性 → ④转化为充分统计量的拒绝域形式（单侧或双侧）。

---

### 3.（12 分）指数分布族与最优检验

**已知**：总体 p.d.f.
$$
f(x) = \frac{1}{\theta}\exp\!\left(x - \frac{e^x}{\theta}\right),\quad x\in\mathbb{R},\ \theta>0
$$
样本 $X_1,\ldots,X_n$。

---

#### 1)（5 分）指数分布族与完备充分统计量

将 p.d.f. 改写为指数族标准形式：
$$
f(x;\theta) = \exp\!\left(x - \frac{e^x}{\theta} - \log\theta\right) = e^x\cdot\exp\!\left(-\frac{e^x}{\theta} - \log\theta\right)
$$

对照 $f(x;\theta)=h(x)\exp\{\eta(\theta)T(x)-A(\theta)\}$：
| 成分 | 对应 |
|------|------|
| $h(x)$ | $e^x$ |
| $T(x)$ | $e^x$ |
| $\eta(\theta)$ | $-1/\theta$ |
| $A(\theta)$ | $\log\theta$ |

✅ 属于指数分布族。参数空间 $\Theta=(0,\infty)$ 为开区间，自然参数 $\eta(\theta)=-1/\theta$ 的值域也含开区间，故充分统计量也是完备的。

**完备充分统计量**：
$$
\boxed{Y = \sum_{i=1}^n e^{X_i}}
$$

---

#### 2)（7 分）最优拒绝域

**问题**：$H_0:\theta=\theta_0\ \text{vs}\ H_1:\theta=\theta_1$，$\theta_0<\theta_1$。

**Neyman-Pearson 引理**：MP 检验拒绝域形如 $\{L(\theta_1;x)/L(\theta_0;x)\ge k\}$。

计算似然比：
$$
\begin{aligned}
\frac{L(\theta_1)}{L(\theta_0)} &=
\frac{\exp\!\bigl(\sum x_i - \frac{Y}{\theta_1} - n\log\theta_1\bigr)}
{\exp\!\bigl(\sum x_i - \frac{Y}{\theta_0} - n\log\theta_0\bigr)} \\[3pt]
&= \exp\!\left\{\left(\frac{1}{\theta_0} - \frac{1}{\theta_1}\right)Y + n(\log\theta_0 - \log\theta_1)\right\}
\end{aligned}
$$

由于 $\theta_0<\theta_1$ 有 $1/\theta_0 - 1/\theta_1 > 0$，似然比关于 $Y$ **单调递增**。

故 $L(\theta_1)/L(\theta_0)\ge k \iff Y\ge c$，最优拒绝域为：
$$
\boxed{\{Y \ge c\}}
$$

> ⚠️ **注意递增/递减的判断**：先确定似然比中 $Y$ 的系数符号。若 $1/\theta_0 - 1/\theta_1 >0$，$Y$ 越大似然比越大 → 拒绝域取 $Y\ge c$；若系数为负则方向反转。

---

### 4.（14 分）Weibull 分布参数 $\theta^c$ 的估计

**已知**：p.d.f.
$$
f(x;\theta) = \begin{cases}
c\theta^{-c}x^{c-1}\exp\!\left\{-\left(\dfrac{x}{\theta}\right)^c\right\}, & x>0 \\[5pt]
0, & \text{其它}
\end{cases}
$$
$c>0$ **已知**，$\theta>0$ **未知**。目标：估计 $\theta^c$。

---

#### 1)（7 分）$\theta^c$ 的 MLE

设 $\phi = \theta^c$，则 $\theta = \phi^{1/c}$，$\log\theta = \frac1c\log\phi$。

$$
\begin{aligned}
L(\phi) &= c^n\phi^{-n}\left(\prod x_i\right)^{c-1}\exp\!\left(-\frac{\sum x_i^c}{\phi}\right) \\[3pt]
l(\phi) &= n\log c - n\log\phi + (c-1)\sum\log x_i - \frac{\sum x_i^c}{\phi} \\[3pt]
\frac{\partial l}{\partial\phi} &= -\frac{n}{\phi} + \frac{\sum x_i^c}{\phi^2}
\end{aligned}
$$

令 $\partial l/\partial\phi = 0$：
$$
\frac{\sum x_i^c}{\phi^2} = \frac{n}{\phi}\ \Longrightarrow\ \phi = \frac{\sum x_i^c}{n}
$$

故 $\theta^c$ 的 MLE 为：
$$
\boxed{\widehat{\theta^c} = \frac{1}{n}\sum_{i=1}^n X_i^c}
$$

---

#### 2)（7 分）$\theta^c$ 的 MVUE

**Step 1：$X^c$ 的分布**
$$
\begin{aligned}
P(X^c\le z) &= P(X\le z^{1/c}) = \int_0^{z^{1/c}} c\theta^{-c}x^{c-1}\exp\!\left\{-\left(\frac{x}{\theta}\right)^c\right\}dx
\end{aligned}
$$
令 $t=(x/\theta)^c$，$dx=(\theta/c)t^{1/c-1}dt$：
$$
P(X^c\le z) = \int_0^{z/\theta^c} e^{-t}dt = 1 - \exp\!\left(-\frac{z}{\theta^c}\right)
$$
即 $X^c\sim Exp(\theta^c)$，均值 $\theta^c$。

**Step 2：充分完备统计量**
$Y=\sum_{i=1}^n X_i^c$：
- Neyman 分解定理 → $Y$ 充分
- 指数族 → $Y$ **完备**

**Step 3：无偏构造**
$E(Y) = n\cdot\theta^c$，故 $Y/n$ 是 $\theta^c$ 的无偏估计。

**Step 4：Lehmann-Scheffé 定理**
$Y/n$ 是完备充分统计量的函数 → **MVUE**：
$$
\boxed{\widehat{\theta^c}_{\text{MVUE}} = \frac{1}{n}\sum_{i=1}^n X_i^c}
$$

> ⭐ MLE 与 MVUE 恰好相同。这是因为 $X^c\sim Exp(\theta^c)$ 中样本均值既是 MLE 也是 UMVUE。

---

### 5.（20 分）$g(\theta)=\theta(1+\theta)$ 的 MVUE

**已知**：$X_1,\ldots,X_n\stackrel{i.i.d.}{\sim} Bin(2,\theta)$
$$
P(X=k) = \binom{2}{k}\theta^k(1-\theta)^{2-k},\quad k=0,1,2
$$
$$
g(\theta) = \theta(1+\theta) = \theta + \theta^2
$$

---

#### 1)（10 分）Rao-Blackwell 方法

**① 基于 $X_1$ 的无偏估计**

设 $Y_2=\phi(X_1)$ 满足 $E[\phi(X_1)] = g(\theta)$：
$$
\begin{aligned}
E[\phi(X_1)] &= \phi(0)(1-\theta)^2 + \phi(1)\!\cdot\!2\theta(1-\theta) + \phi(2)\theta^2 \\
&= \phi(0) + [-2\phi(0) + 2\phi(1)]\theta + [\phi(0) - 2\phi(1) + \phi(2)]\theta^2
\end{aligned}
$$

令等于 $\theta + \theta^2$，比较系数：
$$
\begin{cases}
\phi(0) = 0 \\
-2\phi(0) + 2\phi(1) = 1 \ \Rightarrow\ \phi(1) = 1/2 \\
\phi(0) - 2\phi(1) + \phi(2) = 1 \ \Rightarrow\ \phi(2) = 2
\end{cases}
$$

故：
$$
\boxed{Y_2 = \frac12 I_{\{X_1=1\}} + 2I_{\{X_1=2\}}}
$$

验证：$E(Y_2) = \frac12\cdot2\theta(1-\theta) + 2\cdot\theta^2 = \theta(1-\theta) + 2\theta^2 = \theta + \theta^2$ ✅

**② 完备充分统计量**

$Y_1 = \sum_{i=1}^n X_i \sim Bin(2n,\theta)$
- 属于指数族 → $Y_1$ 是**完备充分统计量**

**③ Rao-Blackwell 改进**

$$
\begin{aligned}
\text{MVUE} &= E[Y_2\mid Y_1=y_1] \\
&= \frac12 P(X_1=1\mid Y_1=y_1) + 2P(X_1=2\mid Y_1=y_1)
\end{aligned}
$$

计算条件概率：
$$
\begin{aligned}
P(X_1=1\mid Y_1=y_1) &= \frac{P(X_1=1)P\!\left(\sum_{i=2}^n X_i = y_1-1\right)}{P(Y_1=y_1)} \\
&= \frac{2\theta(1-\theta)\binom{2n-2}{y_1-1}\theta^{y_1-1}(1-\theta)^{2n-y_1-1}}{\binom{2n}{y_1}\theta^{y_1}(1-\theta)^{2n-y_1}}
= \frac{2\binom{2n-2}{y_1-1}}{\binom{2n}{y_1}}
\end{aligned}
$$

$$
\begin{aligned}
P(X_1=2\mid Y_1=y_1) &= \frac{P(X_1=2)P\!\left(\sum_{i=2}^n X_i = y_1-2\right)}{P(Y_1=y_1)} \\
&= \frac{\theta^2\binom{2n-2}{y_1-2}\theta^{y_1-2}(1-\theta)^{2n-y_1}}{\binom{2n}{y_1}\theta^{y_1}(1-\theta)^{2n-y_1}}
= \frac{\binom{2n-2}{y_1-2}}{\binom{2n}{y_1}}
\end{aligned}
$$

简化组合数：
$$
\frac{\binom{2n-2}{y_1-1}}{\binom{2n}{y_1}}
= \frac{y_1(2n-y_1)}{2n(2n-1)},\qquad
\frac{\binom{2n-2}{y_1-2}}{\binom{2n}{y_1}}
= \frac{y_1(y_1-1)}{2n(2n-1)}
$$

代入得：
$$
\begin{aligned}
\text{MVUE} &= \frac12\cdot\frac{2y_1(2n-y_1)}{2n(2n-1)} + 2\cdot\frac{y_1(y_1-1)}{2n(2n-1)} \\[3pt]
&= \frac{y_1(2n-y_1) + 2y_1(y_1-1)}{2n(2n-1)} \\[3pt]
&= \boxed{\frac{Y_1^2 + 2(n-1)Y_1}{2n(2n-1)}}
\end{aligned}
$$

---

#### 2)（10 分）直接构造法

**① 计算 $Y_1$ 的矩**
$$
E(Y_1) = 2n\theta
$$
$$
E(Y_1^2) = \text{Var}(Y_1) + [E(Y_1)]^2 = 2n\theta(1-\theta) + (2n\theta)^2 = 2n\theta + 2n(2n-1)\theta^2
$$

**② 反解无偏估计**
$$
\widehat\theta = \frac{Y_1}{2n} \quad(\text{$\theta$ 的无偏估计})
$$

$$
E(Y_1^2 - Y_1) = \cancel{2n\theta} + 2n(2n-1)\theta^2 - \cancel{2n\theta} = 2n(2n-1)\theta^2
\ \Longrightarrow\ \widehat{\theta^2} = \frac{Y_1^2 - Y_1}{2n(2n-1)}
$$

**③ 组合**
$$
\begin{aligned}
\widehat{g(\theta)} &= \frac{Y_1}{2n} + \frac{Y_1^2 - Y_1}{2n(2n-1)} \\[3pt]
&= \frac{Y_1(2n-1)}{2n(2n-1)} + \frac{Y_1^2 - Y_1}{2n(2n-1)} \\[3pt]
&= \boxed{\frac{Y_1^2 + 2(n-1)Y_1}{2n(2n-1)}}
\end{aligned}
$$

由于它是完备充分统计量 $Y_1$ 的函数，由 Lehmann-Scheffé 定理，必为 MVUE。与 1) 结果一致 ✅。

> 💡 **两条路线对比**：
> - **Rao-Blackwell**：先找任意无偏估计（粗糙但容易构造），再对完备充分统计量取条件期望改进 → 通用，但计算条件期望可能繁琐。
> - **直接构造**：先求完备充分统计量的矩，反解待估参数的函数 → 计算简洁，但要能解出矩的方程。
>
> 两条路线最终得到相同的 MVUE，可相互验证。

---

> **总览**：本样卷覆盖数理统计核心内容——MLE 与 Fisher 信息量（题 1）、似然比检验与精确拒绝域（题 2）、指数分布族与 NP 最优检验（题 3）、Weibull 分布的 MLE 与 MVUE（题 4）、二项分布的 Rao-Blackwell 与直接构造 MVUE（题 5）。涵盖点估计、区间估计与假设检验三大支柱。
