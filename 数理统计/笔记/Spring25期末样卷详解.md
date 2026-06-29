# Spring 2025 数理统计期末样卷 — 详解

> Source: `source/数理统计/数理统计_Spring25_期末样卷.docx`
> 无答案 LaTeX 试卷: `assets/数理统计-期末样卷Spring25/数理统计-期末样卷Spring25.tex`
> 覆盖：充分统计量、完备性、正则指数分布类、MVUE、RCB、Fisher 信息量、LRT/Wald/Score、Neyman-Pearson 最优检验

---

## 一、判断题（每小题 2 分，共计 10 分）

### 1. 有效估计量一定是 MVUE，反之则不一定。 (T)

> ⭐ **正确**。

- 有效估计量 = 方差达到 RCB 的无偏估计量。由 RCB 理论，任何无偏估计量的方差下界就是 RCB，达到下界的自然是方差最小的无偏估计量（即 MVUE）。
- 反过来的反例：某些 MVUE 的方差并不达到 RCB（如 $U[0,\theta]$ 中 $\frac{n+1}{n}X_{(n)}$ 是 $\theta$ 的 MVUE，但其方差未达到 RCB，因为该分布不满足 RCB 的正则条件）。

**参考**：[Rao-Cramer下界与有效性](09%20Rao-Cramer下界与有效性.md)

---

### 2. 一个参数的完备充分统计量必然唯一存在。 (F)

> ⚠️ **错误**。

- 完备充分统计量如果存在，它并不是"唯一"的——任何一对一变换仍然是完备充分的。例如若 $T$ 是完备充分统计量，则 $2T$、$T+1$ 也是。
- 更关键的是，并非所有分布族都存在完备充分统计量。例如 $U[\theta-1, \theta+1]$，$(\min X_i, \max X_i)$ 是充分但不完备的。

**参考**：[完备性与指数分布类](13%20完备性与指数分布类.md)

---

### 3. 若存在 $\theta$ 的完备充分统计量 $Y_1$，则对于 $\theta$ 的某个函数 $g(\theta)$，其 MVUE 一定是 $Y_1$ 的函数。 (T)

> ⭐ **正确**。

- 这是 Lehmann-Scheffe 定理的核心推论：若 $T$ 完备充分，则任何参数函数的 MVUE（若存在）必为 $T$ 的函数。
- 证明思路：若存在某 MVUE $U$，对 $U$ 做 Rao-Blackwell 改进得 $\varphi(T) = E[U|T]$，其方差 $\leq \text{Var}(U)$，且由完备性 $\varphi(T)$ 是唯一的 MVUE。

**参考**：[完备性与指数分布类](13%20完备性与指数分布类.md), [参数的函数与最小充分性](14%20最小充分性与从属统计量.md)

---

### 4. 样本 $X_1,\ldots,X_n \sim N(\theta,\sigma_0^2)$，$\sigma_0$ 已知。$H_0:\theta=\theta_0$ vs $H_1:\theta\neq\theta_0$ 的似然比检验，拒绝域依赖于 $\overline{X}$。 (T)

> ⭐ **正确**。

- $\theta$ 的 MLE 是 $\hat{\theta} = \overline{X}$。
- 似然比统计量：
  $$\Lambda = \frac{L(\theta_0)}{L(\hat{\theta})} = \frac{\exp\left(-\frac{1}{2\sigma_0^2}\sum(X_i-\theta_0)^2\right)}{\exp\left(-\frac{1}{2\sigma_0^2}\sum(X_i-\overline{X})^2\right)} = \exp\left(-\frac{n(\overline{X}-\theta_0)^2}{2\sigma_0^2}\right)$$
- $-2\log\Lambda = \frac{n(\overline{X}-\theta_0)^2}{\sigma_0^2} = Z^2$，它完全由 $\overline{X}$ 决定。拒绝域为 $|\overline{X}-\theta_0|$ 过大，即经典的 $z$-检验。

**参考**：[极大似然检验](10%20极大似然检验.md)

---

### 5. $X_1,\ldots,X_n \sim N(\mu_0, \theta)$，$\mu_0$ 已知，则 $Y=\sum X_i^2$ 为 $\theta$ 的完备充分统计量。 (F)

> ⚠️ **错误**。

- 对于 $N(\mu_0, \theta)$（均值已知、方差未知），应先将数据中心化。令 $Z_i = X_i - \mu_0 \sim N(0, \theta)$。
- 由 Neyman 分解定理，充分统计量是 $\sum (X_i - \mu_0)^2$，**不是** $\sum X_i^2$。
- 当 $\mu_0 \neq 0$ 时，$\sum X_i^2$ 混入了 $\mu_0$ 的信息，它确实包含了 $\sum (X_i-\mu_0)^2$ 但没有分离出 $\mu_0$ 的影响——实际上它仍然是充分的（因为 $\sum X_i^2 = \sum (X_i-\mu_0)^2 + 2\mu_0\sum X_i - n\mu_0^2$ 且 $\sum X_i$ 也是充分的）。但关键是：**对于 $(\mu_0, \theta)$ 这个参数空间，$\sum X_i^2$ 不是完备的**（完备性要求在子参数空间上考察）。
- 此处只有 $\theta$ 一个未知参数（$\mu_0$ 已知），完备充分统计量应该是 $\sum (X_i-\mu_0)^2$。

**参考**：[统计量与三大抽样分布](02%20统计量与三大抽样分布.md), [完备性与指数分布类](13%20完备性与指数分布类.md)

---

## 二、单选题（每小题 3 分，共计 15 分）

### 1. $N(\theta,\sigma_0^2)$ 样本（$\sigma_0$ 已知），哪个不是 $\theta$ 的充分统计量？答案：C

> 📐 **C. $\sum X_i^2$**

- 由 Neyman 分解定理，$f(x;\theta) \propto \exp\left(-\frac{(x-\theta)^2}{2\sigma_0^2}\right) = \exp\left(-\frac{x^2}{2\sigma_0^2} + \frac{\theta x}{\sigma_0^2} - \frac{\theta^2}{2\sigma_0^2}\right)$
- 联合密度 $\propto \exp\left(\frac{\theta}{\sigma_0^2}\sum X_i - \frac{n\theta^2}{2\sigma_0^2}\right) \cdot \exp\left(-\frac{\sum X_i^2}{2\sigma_0^2}\right)$
- 由因子分解，$T = \sum X_i$（或其一对一变换 $\overline{X}$）是充分统计量。$\sum X_i^2$ 不是。

各选项分析：
- A: $\overline{X}$ 是充分统计量的函数 ✓
- B: $X_3$ 虽然单独一个观测，但**仍然是充分的**（因为 $n=1$ 时单个观测就是充分的；而 $n>1$ 时 $X_3$ 不是充分的——但这里选项没有限定 $n>1$，且较真的话 $X_3$ 确实不是充分统计量... 实际上严格来说 B 也应该不算充分，但题目问的是"不是的"，C 更明显不充分）

> 💡 **修正理解**：B 也不是充分统计量（除非 $n=1$），但教材答案选 C，因为 $\sum X_i^2$ 在标准形式中直接出现在与 $\theta$ 无关的部分 $H(x)$ 中。实际考试中以 C 为正确答案。

---

### 2. 属于正则指数分布类的是？答案：B

> 📐 **B. 拉普拉斯分布 $f(x;\theta)=\frac{1}{2\theta}\exp(-|x|/\theta)$**

正则指数分布类的三个条件：
1. 支撑集 $S$ 不依赖于 $\theta$
2. 可写成 $\exp\{p(\theta)K(x)+H(x)+q(\theta)\}$ 形式
3. $p(\theta)$ 非平凡连续

各选项分析：
- **A. $U[0,\theta]$**：支撑集 $[0,\theta]$ 依赖 $\theta$，不是 ❌
- **B. Laplace**：$f(x;\theta) = \exp\left(-\frac{|x|}{\theta} - \ln(2\theta)\right) = \exp\{p(\theta)K(x)+H(x)+q(\theta)\}$，其中 $p(\theta)=-\frac{1}{\theta}$, $K(x)=|x|$, $q(\theta)=-\ln(2\theta)$，$S=\mathbb{R}$ 不依赖于 $\theta$ ✓
- **C. 平移指数 $f(x;\theta)=e^{-(x-\theta)}, x>\theta$**：支撑集 $(\theta, \infty)$ 依赖 $\theta$，不是 ❌
- **D. $N(\theta,\theta^2)$**：方差依赖 $\theta$，但参数空间使得支撑 $S=\mathbb{R}$ 不变，**但无法写成 $\exp\{p(\theta)K(x)+H(x)+q(\theta)\}$ 的形式**（方差含 $\theta$ 导致交叉项出现） ❌

**参考**：[完备性与指数分布类](13%20完备性与指数分布类.md)

---

### 3. $\widehat{\theta}$ 为 $\theta$ 的无偏估计量，正确的是？答案：B

> 📐 **B. $\widehat{\theta}$ 的有效性一定不超过 1**

- **有效性** $e(\widehat{\theta}) = \frac{\text{RCB}}{\text{Var}(\widehat{\theta})}$，由 RCB 定理 $\text{Var}(\widehat{\theta}) \geq \text{RCB}$，故 $e(\widehat{\theta}) \leq 1$。✓

各选项分析：
- **A**：$g(\widehat{\theta})$ 一般不无偏，除非 $g$ 是线性的（如 $g(\theta)=a\theta+b$） ❌
- **C**：即使 $\widehat{\theta}$ 是充分统计量的函数，还必须是无偏的 + 充分统计量完备，才能得出 MVUE。缺少完备性条件 ❌
- **D**：$E[\widehat{\theta}-\widehat{\theta}']=0$ 恒为零，这意味着 $\widehat{\theta}-\widehat{\theta}'$ 是 $0$ 的无偏估计（平凡），但题目不是说"是 $0$ 的无偏估计"而是说"是 $\theta$ 的无偏估计"——显然 $\widehat{\theta}-\widehat{\theta}'$ 的期望是 $0$ 不是 $\theta$ ❌

**参考**：[Rao-Cramer下界与有效性](09%20Rao-Cramer下界与有效性.md)

---

### 4. 是 $\theta$ 的 MVUE 的是？答案：C

> 📐 **C. $\mathrm{Po}(\theta)$ 样本，$\widehat{\theta} = \overline{X}$**

各选项分析：
- **A. Bernoulli $X_1$**：$X_1$ 是无偏但 $\overline{X}$ 方差更小。$X_1$ 不是 MVUE ❌
- **B. $U[0,\theta]$ $\max X_i$**：$E[X_{(n)}] = \frac{n}{n+1}\theta$，有偏。MVUE 是 $\frac{n+1}{n}X_{(n)}$ ❌
- **C. Poisson $\overline{X}$**：$E[\overline{X}]=\theta$ 无偏，$\overline{X}$ 是完备充分统计量 $\sum X_i$ 的无偏函数，由 Lehmann-Scheffe 定理，它是 MVUE ✓
- **D. Exp$(\theta)$ $\overline{X}$**：取决于 Exp 的参数化。若 $f(x;\theta)=\frac{1}{\theta}e^{-x/\theta}$（如讲义约定），则 $E[X]=\theta$，$\overline{X}$ 是 $\theta$ 的 MVUE。若 $f(x;\theta)=\theta e^{-\theta x}$（rate），则 $E[X]=1/\theta$，$\overline{X}$ 是 $1/\theta$ 的 MVUE 而非 $\theta$ 的 MVUE。根据讲义中 Exp 的约定（见选项 5 中 Exp$(\theta)$ 的检验），此处的答案为 C，说明 D 中 Exp 的参数化使其不是 $\theta$ 的 MVUE。实际上，Exp$(\theta)$ 按照部分教材的 rate 参数化，$E[X]=1/\theta$，$\overline{X}$ 是 $1/\theta$ 的 MVUE，而非 $\theta$ 的 MVUE。

**参考**：[极大似然估计与估计量评价准则](04%20极大似然估计与估计量评价准则.md), [完备性与指数分布类](13%20完备性与指数分布类.md)

---

### 5. Exp$(\theta)$ 样本，$H_0:\theta=1$ vs $H_1:\theta=2$，最优拒绝域形如？答案：A

> 📐 **A. $\sum X_i \leq c$（$c>0$）**

对于 Exp$(\theta)$，p.d.f. 为 $f(x;\theta)=\frac{1}{\theta}e^{-x/\theta}$（或 rate 参数化 $f(x;\theta)=\theta e^{-\theta x}$——需根据上下文判断。此处 Exp$(\theta)$ 按均值参数化，即 $E[X]=\theta$）。

似然比：
$$\frac{L(1; \mathbf{X})}{L(2; \mathbf{X})} = \frac{\exp(-\sum X_i)}{2^{-n}\exp(-\sum X_i/2)} = 2^n \exp\!\left(-\frac{1}{2}\sum X_i\right)$$

该似然比关于 $Y = \sum X_i$ **单调递减**。当 $Y$ 较小时（即 $\sum X_i \leq c$），似然比 $\geq k$，此时 $H_1$ 相对 $H_0$ 更受支持，拒绝 $H_0$。

由 Neyman-Pearson 引理，最优拒绝域形如 $\{\sum X_i \leq c\}$。

> 💡 **直觉**：$H_0:\theta=1$ vs $H_1:\theta=2$。$\theta$ 越大，Exp$(\theta)$ 的均值越大，样本应该越大。若 $\theta=2$ 为真，均值应为 2；若 $\theta=1$ 为真，均值应为 1。所以当样本总和**偏小**时，更倾向于 $H_0$？不对——等等。
>
> 实际上，若 $\theta=2$，$E[X]=2$；若 $\theta=1$，$E[X]=1$。样本总和偏大时支持 $H_1$。但似然比的计算表明 $L(1)/L(2) = 2^n e^{-\frac{1}{2}\sum X_i}$ 随 $\sum X_i$ 递减。当 $\sum X_i$ 小，$L(1)/L(2)$ 大，倾向于 $H_0$；当 $\sum X_i$ 大，$L(1)/L(2)$ 小，倾向于 $H_1$。所以拒绝域应是 $\sum X_i \geq c$？
>
> 等一下，让我重新验证：NP 引理说，拒绝 $H_0$ 当 $L(\theta_1)/L(\theta_0) \geq k$（$H_1$ 下的似然相对更大）。这里 $L(2)/L(1) = \frac{1}{2^n}e^{\frac{1}{2}\sum X_i}$，随 $\sum X_i$ 递增，所以 $\sum X_i$ 大时拒绝 $H_0$。
>
> 但官方答案是 **A ($\sum X_i \leq c$)**。让我重新检查参数化...
>
> 若 Exp$(\theta)$ 按 rate 参数化 $f(x;\theta)=\theta e^{-\theta x}$：则 $L(1)/L(2) = \frac{e^{-\sum X_i}}{2^n e^{-2\sum X_i}} = 2^{-n} e^{\sum X_i}$。该比值随 $\sum X_i$ 递增。NP 引理：当 $L(1)/L(2) \leq k$（即 $\sum X_i$ 小）时拒绝 $H_0$。所以 $\sum X_i \leq c$ ✓！
>
> 所以本题采用 rate 参数化 $f(x;\theta)=\theta e^{-\theta x}, E[X]=1/\theta$。这与国内教材常见约定一致。

**参考**：[最优假设检验](15%20最优假设检验.md)

---

## 三、计算题（共计 75 分）

---

### 第 1 题（15 分）$\Gamma(\alpha_0, \beta)$ 分布中 $\beta$ 的 MLE、RCB 与有效性

> $\Gamma(\alpha_0, \beta)$ 的 p.d.f.：$f(x) = \frac{1}{\Gamma(\alpha_0)\beta^{\alpha_0}}x^{\alpha_0-1}e^{-x/\beta}, x>0$，$\alpha_0$ 已知，$E[X]=\alpha_0\beta$，$\text{Var}(X)=\alpha_0\beta^2$

#### (1) 求 $\beta$ 的 MLE

对数似然函数：
$$\ell(\beta) = -n\ln\Gamma(\alpha_0) - n\alpha_0\ln\beta + (\alpha_0-1)\sum\ln X_i - \frac{1}{\beta}\sum X_i$$

Score 函数：
$$\ell'(\beta) = -\frac{n\alpha_0}{\beta} + \frac{\sum X_i}{\beta^2}$$

令 $\ell'(\beta)=0$：
$$\frac{\sum X_i}{\beta^2} = \frac{n\alpha_0}{\beta} \quad\Rightarrow\quad \boxed{\widehat{\beta} = \frac{\sum X_i}{n\alpha_0} = \frac{\overline{X}}{\alpha_0}}$$

---

#### (2) 计算 $\beta$ 的 RCB

先求单个观测的 Fisher 信息量。对 $f(x;\beta) = -\ln\Gamma(\alpha_0) - \alpha_0\ln\beta + (\alpha_0-1)\ln x - x/\beta$：

$$\frac{\partial \log f}{\partial\beta} = -\frac{\alpha_0}{\beta} + \frac{x}{\beta^2}$$
$$\frac{\partial^2 \log f}{\partial\beta^2} = \frac{\alpha_0}{\beta^2} - \frac{2x}{\beta^3}$$

$$I(\beta) = -E\left[\frac{\partial^2 \log f}{\partial\beta^2}\right] = -\left(\frac{\alpha_0}{\beta^2} - \frac{2E[X]}{\beta^3}\right) = -\left(\frac{\alpha_0}{\beta^2} - \frac{2\alpha_0\beta}{\beta^3}\right) = \frac{\alpha_0}{\beta^2}$$

$$\boxed{\text{RCB} = \frac{1}{nI(\beta)} = \frac{\beta^2}{n\alpha_0}}$$

---

#### (3) 判断无偏性与有效性

$$E[\widehat{\beta}] = E\left[\frac{\sum X_i}{n\alpha_0}\right] = \frac{n\alpha_0\beta}{n\alpha_0} = \beta$$

$\widehat{\beta}$ **是无偏的**。

$$\text{Var}(\widehat{\beta}) = \text{Var}\!\left(\frac{\sum X_i}{n\alpha_0}\right) = \frac{n\alpha_0\beta^2}{n^2\alpha_0^2} = \frac{\beta^2}{n\alpha_0} = \text{RCB}$$

> ⭐ $\widehat{\beta}$ 的方差达到 RCB，故 $\widehat{\beta}$ 是**有效估计量**。

**参考**：[Rao-Cramer下界与有效性](09%20Rao-Cramer下界与有效性.md), [极大似然估计](04%20极大似然估计与估计量评价准则.md)

---

### 第 2 题（16 分）参数函数 $g(\theta)=a\theta^2+b\theta+c$ 的 MVUE

#### (1) Exp$(1/\theta)$ 样本（8 分）

> 此处 Exp$(1/\theta)$ 的含义：$f(x;\theta) = \theta e^{-\theta x}$（rate 参数化），$E[X]=1/\theta$。注意参数记为 $\theta$。

> 💡 等价的写法：$f(x;\theta)=\frac{1}{(1/\theta)}e^{-x/(1/\theta)}$，均值 $=1/\theta$。

$\overline{X}$ 是完备充分统计量 $\sum X_i$ 的函数。

目标：找 $g(\theta) = a\theta^2 + b\theta + c$ 的 MVUE。

**Step 1**：$\theta$ 的 MVUE。$E[\overline{X}] = 1/\theta$，所以 $\overline{X}$ 不是 $\theta$ 的无偏估计。需要先求 $\theta$ 的 MVUE。

事实上对于 Exp$(1/\theta)$（rate=$\theta$），$E[X]=1/\theta$，要估计 $\theta$ 较困难。但从标准做法：
- $\sum X_i \sim \Gamma(n, 1/\theta)$，$E[1/\overline{X}]$ 需要修正。
- 已知 $E[1/\sum X_i] \neq \theta$。但对于本题，我们可以用**方法一**：直接利用已知结论。

**简化理解**：注意到选项答案中使用了 $\overline{X}$ 作为 $\theta$ 的 MVUE。这意味着在此参数化中，$E[X]=\theta$（均值参数化而非 rate 参数化）。实际上 Exp$(1/\theta)$ 这里的记号表示 $f(x;\theta)=\frac{1}{1/\theta}e^{-x/(1/\theta)}=\theta e^{-\theta x}$，$E[X]=1/\theta$...

让我换一个思路。官方答案显示用 $\overline{X}$ 估计 $\theta$，且纠偏时 $E[\overline{X}^2]=\frac{n+1}{n}\theta^2$。这说明在此参数化中 $E[X]=\theta$ 且 $\text{Var}(X)=\theta^2$。因此 $f(x;\theta)=\frac{1}{\theta}e^{-x/\theta}$（scale 参数化），其中 $1/\theta$ 是 rate。

> 所以"Exp$(1/\theta)$"应理解为**指数分布，均值为 $\theta$**，即 $f(x;\theta)=\frac{1}{\theta}e^{-x/\theta}$，$E[X]=\theta$，$\text{Var}(X)=\theta^2$。

在此参数化下：
- $\overline{X}$ 是 $\theta$ 的 MVUE（完备充分统计量的无偏函数） ✓

$$E[\overline{X}^2] = (E[\overline{X}])^2 + \text{Var}(\overline{X}) = \theta^2 + \frac{\theta^2}{n} = \frac{n+1}{n}\theta^2$$

因此 $\frac{n}{n+1}\overline{X}^2$ 是 $\theta^2$ 的 MVUE。

> ⭐ **答案**：$g(\theta)$ 的 MVUE = $\boxed{a\cdot\frac{n}{n+1}\overline{X}^2 + b\overline{X} + c}$

---

#### (2) $U[0,\theta]$ 样本（8 分）

已知完备充分统计量 $Y_1 = X_{(n)}$，其 p.d.f.：$f_{Y_1}(y;\theta) = \frac{ny^{n-1}}{\theta^n}$, $0 \leq y \leq \theta$。

计算期望：
$$E[Y_1] = \int_0^\theta y \cdot \frac{ny^{n-1}}{\theta^n} dy = \frac{n}{\theta^n} \cdot \frac{\theta^{n+1}}{n+1} = \frac{n}{n+1}\theta$$

$$E[Y_1^2] = \int_0^\theta y^2 \cdot \frac{ny^{n-1}}{\theta^n} dy = \frac{n}{\theta^n} \cdot \frac{\theta^{n+2}}{n+2} = \frac{n}{n+2}\theta^2$$

因此：
- $\frac{n+1}{n}Y_1$ 是 $\theta$ 的 MVUE
- $\frac{n+2}{n}Y_1^2$ 是 $\theta^2$ 的 MVUE

> ⭐ **答案**：$g(\theta)$ 的 MVUE = $\boxed{a\cdot\frac{n+2}{n}Y_1^2 + b\cdot\frac{n+1}{n}Y_1 + c}$

**参考**：[参数的函数与最小充分性](14%20最小充分性与从属统计量.md)

---

### 第 3 题（15 分）Bernoulli$(\theta)$ —— Fisher 信息量 + 三大检验统计量

#### (1) Fisher 信息量 $I(\theta)$（6 分）

$f(x;\theta) = \theta^x(1-\theta)^{1-x}$, $x \in \{0,1\}$。

$$\log f(X;\theta) = X\log\theta + (1-X)\log(1-\theta)$$

$$\frac{\partial \log f}{\partial\theta} = \frac{X}{\theta} - \frac{1-X}{1-\theta}$$

$$\frac{\partial^2 \log f}{\partial\theta^2} = -\frac{X}{\theta^2} - \frac{1-X}{(1-\theta)^2}$$

$$I(\theta) = -E\left[\frac{\partial^2 \log f}{\partial\theta^2}\right] = \frac{E[X]}{\theta^2} + \frac{1-E[X]}{(1-\theta)^2} = \frac{\theta}{\theta^2} + \frac{1-\theta}{(1-\theta)^2} = \frac{1}{\theta(1-\theta)}$$

> ⭐ **答案**：$\boxed{I(\theta) = \dfrac{1}{\theta(1-\theta)}}$

---

#### (2) 三大检验统计量（9 分）

$\theta_0 = 1/2$，$\widehat{\theta} = \overline{X}$（MLE）。

**似然比检验统计量 $\chi_L^2$**：

$$\ell(\widehat{\theta}) = \sum\left[X_i\log\overline{X} + (1-X_i)\log(1-\overline{X})\right] = n\overline{X}\log\overline{X} + n(1-\overline{X})\log(1-\overline{X})$$
$$\ell(\theta_0) = \sum\left[X_i\log\frac{1}{2} + (1-X_i)\log\frac{1}{2}\right] = -n\log 2$$

$$\chi_L^2 = -2\log\Lambda = 2[\ell(\widehat{\theta}) - \ell(\theta_0)] = 2n\left[\overline{X}\log\overline{X} + (1-\overline{X})\log(1-\overline{X}) + \log 2\right]$$

> ⭐ $\boxed{\chi_L^2 = 2n\left[\overline{X}\log\overline{X} + (1-\overline{X})\log(1-\overline{X}) + \log 2\right]}$

**Wald 检验统计量 $\chi_W^2$**：

$$I(\widehat{\theta}) = \frac{1}{\overline{X}(1-\overline{X})}$$

$$\chi_W^2 = n I(\widehat{\theta})(\widehat{\theta} - \theta_0)^2 = \frac{n}{\overline{X}(1-\overline{X})}\left(\overline{X} - \frac{1}{2}\right)^2$$

> ⭐ $\boxed{\chi_W^2 = \dfrac{n\left(\overline{X} - \frac{1}{2}\right)^2}{\overline{X}(1-\overline{X})}}$

**得分检验统计量 $\chi_R^2$**：

$$\ell'(\theta_0) = \sum_{i=1}^n\left(\frac{X_i}{\theta_0} - \frac{1-X_i}{1-\theta_0}\right) = \frac{\sum X_i}{1/2} - \frac{n-\sum X_i}{1/2} = 2n\overline{X} - 2n(1-\overline{X}) = 4n\overline{X} - 2n = 2n(2\overline{X} - 1)$$

$$I(\theta_0) = \frac{1}{\frac{1}{2} \cdot \frac{1}{2}} = 4$$

$$\chi_R^2 = \frac{[\ell'(\theta_0)]^2}{nI(\theta_0)} = \frac{[2n(2\overline{X} - 1)]^2}{4n} = \frac{4n^2(2\overline{X} - 1)^2}{4n} = n(2\overline{X} - 1)^2$$

> ⭐ $\boxed{\chi_R^2 = n(2\overline{X} - 1)^2}$

> 💡 三个统计量在大样本下都渐近服从 $\chi^2(1)$。

**参考**：[极大似然检验](10%20极大似然检验.md)

---

### 第 4 题（12 分）对数正态分布——指数族 + Neyman-Pearson

p.d.f.：$f(x,\theta) = \frac{1}{x\sqrt{2\pi}}\exp\left(-\frac{1}{2}(\log x - \theta)^2\right)$, $x>0$

#### (1) 判断指数分布类 + 完备充分统计量（5 分）

展开：
$$\log f(x,\theta) = -\log x - \frac{1}{2}\log(2\pi) - \frac{1}{2}(\log x - \theta)^2$$
$$= -\frac{1}{2}(\log x)^2 + \theta\log x - \frac{1}{2}\theta^2 - \log x - \frac{1}{2}\log(2\pi)$$

写成指数族标准形式：
$$f(x,\theta) = \exp\left\{\theta \cdot \log x - \frac{1}{2}(\log x)^2 - \log x - \frac{1}{2}\log(2\pi) - \frac{1}{2}\theta^2\right\}$$

识别：
- $p(\theta) = \theta$，
- $K(x) = \log x$
- $H(x) = -\frac{1}{2}(\log x)^2 - \log x - \frac{1}{2}\log(2\pi)$
- $q(\theta) = -\frac{1}{2}\theta^2$

支撑集 $S = \{x: x>0\}$ 不依赖于 $\theta$，$p(\theta)=\theta$ 非平凡连续。

> ⭐ 此分布**属于正则指数分布类**。

完备充分统计量：$\boxed{Y_1 = \sum_{i=1}^n \log X_i}$

---

#### (2) 最优拒绝域（7 分）

对于 $\theta_0 < \theta_1$，检验 $H_0:\theta=\theta_0$ vs $H_1:\theta=\theta_1$。

由 Neyman-Pearson 引理，计算似然比：

$$\frac{L(\theta_0; \mathbf{X})}{L(\theta_1; \mathbf{X})} = \frac{\exp\left(\theta_0\sum\log X_i - \frac{n}{2}\theta_0^2\right) \cdot \prod \frac{1}{X_i\sqrt{2\pi}}\exp\left(-\frac{1}{2}(\log X_i)^2\right)}{\exp\left(\theta_1\sum\log X_i - \frac{n}{2}\theta_1^2\right) \cdot \prod \frac{1}{X_i\sqrt{2\pi}}\exp\left(-\frac{1}{2}(\log X_i)^2\right)}$$

$$= \exp\left((\theta_0 - \theta_1)\sum_{i=1}^n\log X_i + \frac{n}{2}(\theta_1^2 - \theta_0^2)\right)$$

由于 $\theta_0 < \theta_1$，$\theta_0 - \theta_1 < 0$，该似然比关于 $Y_1 = \sum\log X_i$ **单调递减**。

NP 引理：拒绝 $H_0$ 当 $L(\theta_0)/L(\theta_1) \leq k$，即 $Y_1$ 足够大时。

> ⭐ 最优拒绝域形如：$\boxed{\{Y_1 \geq c\} = \left\{\sum_{i=1}^n \log X_i \geq c\right\}}$（不需要确定临界值 $c$）

> 💡 因为 $\theta_1 > \theta_0$，$H_1$ 下对数正态分布的 $\theta$ 更大，$\log X$ 的均值更大，所以 $\sum\log X_i$ 偏大时倾向于 $H_1$。

**参考**：[最优假设检验](15%20最优假设检验.md), [完备性与指数分布类](13%20完备性与指数分布类.md)

---

### 第 5 题（17 分）Poisson$(\theta)$ 中 $\theta^2$ 的 MVUE——两种思路

样本 $X_1,\ldots,X_n \sim \text{Po}(\theta)$，$E[X]=\text{Var}(X)=\theta$。完备充分统计量：$Y_1 = \sum X_i \sim \text{Po}(n\theta)$。

目标：求 $g(\theta)=\theta^2$ 的 MVUE。

---

#### 第一种思路（Lehmann-Scheffe / 直接纠偏）

**(a) $\theta$ 的 MVUE（3 分）**

$\widehat{\theta} = \overline{X} = Y_1/n$，因为 $E[\overline{X}]=\theta$，它是完备充分统计量的无偏函数。

> ⭐ $\boxed{\widehat{\theta} = \overline{X}}$

**(b) 纠偏得到 $\theta^2$ 的 MVUE（4 分）**

$$g(\widehat{\theta}) = \overline{X}^2$$

$$E[\overline{X}^2] = (E[\overline{X}])^2 + \text{Var}(\overline{X}) = \theta^2 + \frac{\theta}{n}$$

$\overline{X}^2$ 是 $\theta^2$ 的**有偏**估计，偏差 $= \frac{\theta}{n}$。

纠偏：$E[\overline{X}^2 - \overline{X}/n] = \theta^2 + \theta/n - \theta/n = \theta^2$

$\overline{X}^2 - \overline{X}/n = \frac{Y_1^2}{n^2} - \frac{Y_1}{n^2}$ 是完备充分统计量的无偏函数。

> ⭐ $\boxed{g(\theta)\text{ 的 MVUE} = \overline{X}^2 - \frac{\overline{X}}{n} = \frac{Y_1(Y_1-1)}{n^2}}$

---

#### 第二种思路（Rao-Blackwell）

**(a) $Y_2 = X_1^2 - X_1$ 是 $g(\theta)$ 的无偏估计（3 分）**

$$E[Y_2] = E[X_1^2] - E[X_1] = (E[X_1]^2 + \text{Var}(X_1)) - E[X_1] = \theta^2 + \theta - \theta = \theta^2$$

> $E[Y_2] = \theta^2 = g(\theta)$，**无偏** ✓。

---

**(b) 条件分布 $X_1 \mid Y_1=y \sim \text{Bin}(y, 1/n)$（3 分）**

对于 $x \in \{0,1,\ldots,y\}$：

$$P(X_1=x \mid Y_1=y) = \frac{P(X_1=x) \cdot P\left(\sum_{i=2}^n X_i = y-x\right)}{P(Y_1=y)}$$

- $P(X_1=x) = \frac{\theta^x e^{-\theta}}{x!}$
- $P(\sum_{i=2}^n X_i = y-x) = \frac{((n-1)\theta)^{y-x} e^{-(n-1)\theta}}{(y-x)!}$
- $P(Y_1=y) = \frac{(n\theta)^y e^{-n\theta}}{y!}$

代入：
$$P(X_1=x \mid Y_1=y) = \frac{\frac{\theta^x e^{-\theta}}{x!} \cdot \frac{((n-1)\theta)^{y-x} e^{-(n-1)\theta}}{(y-x)!}}{\frac{(n\theta)^y e^{-n\theta}}{y!}}$$

$$= \frac{y!}{x!(y-x)!} \cdot \frac{(n-1)^{y-x}}{n^y} = \binom{y}{x} \left(1-\frac{1}{n}\right)^{y-x} \left(\frac{1}{n}\right)^x$$

> ⭐ 这正是 $\text{Bin}(y, 1/n)$ 分布的 p.m.f. ✓

---

**(c) 计算 $E[Y_2 \mid Y_1=y]$ 得到 MVUE（4 分）**

$$E[Y_2 \mid Y_1=y] = E[X_1^2 \mid Y_1=y] - E[X_1 \mid Y_1=y]$$

对于 $X_1 \mid Y_1=y \sim \text{Bin}(y, 1/n)$：
$$E[X_1 \mid Y_1=y] = \frac{y}{n}, \quad \text{Var}(X_1 \mid Y_1=y) = y \cdot \frac{1}{n} \cdot \left(1-\frac{1}{n}\right)$$

$$E[X_1^2 \mid Y_1=y] = (E[X_1 \mid Y_1=y])^2 + \text{Var}(X_1 \mid Y_1=y) = \frac{y^2}{n^2} + \frac{y(n-1)}{n^2}$$

因此：
$$E[Y_2 \mid Y_1=y] = \left(\frac{y^2}{n^2} + \frac{y(n-1)}{n^2}\right) - \frac{y}{n} = \frac{y^2 - y}{n^2} = \frac{y(y-1)}{n^2}$$

> ⭐ $\boxed{g(\theta)\text{ 的 MVUE} = \frac{Y_1(Y_1-1)}{n^2} = \overline{X}^2 - \frac{\overline{X}}{n}}$

两种方法得到**一致结果**。

**参考**：[完备性与指数分布类](13%20完备性与指数分布类.md), [参数的函数与最小充分性](14%20最小充分性与从属统计量.md)

---

## 试卷考点分布

| 考点 | 题型 | 分值 | 对应讲义 |
|------|------|------|----------|
| 有效估计量与 MVUE 的关系 | 判断 | 2 | 第9讲 |
| 完备充分统计量唯一性 | 判断 | 2 | 第13讲 |
| MVUE 是完备充分统计量的函数 | 判断 | 2 | 第12-13讲 |
| 正态分布 LRT 的拒绝域 | 判断 | 2 | 第10讲 |
| 正态分布完备充分统计量 | 判断 | 2 | 第13讲 |
| 充分统计量判定 | 单选 | 3 | 第12讲 |
| 正则指数分布类识别 | 单选 | 3 | 第13讲 |
| 有效性定义 | 单选 | 3 | 第9讲 |
| MVUE 识别 | 单选 | 3 | 第4/13讲 |
| NP 最优拒绝域 | 单选 | 3 | 第15讲 |
| MLE + RCB + 有效性 | 计算 | 15 | 第4/9讲 |
| $g(\theta)$ 的 MVUE（两种分布） | 计算 | 16 | 第14讲 |
| Fisher 信息量 + 三大检验 | 计算 | 15 | 第9/10讲 |
| 指数族 + NP 拒绝域 | 计算 | 12 | 第13/15讲 |
| $\theta^2$ 的 MVUE（两种方法） | 计算 | 17 | 第14讲 |

---

## 易错点警示

> ⚠️ **1. 完备充分统计量"唯一" vs "唯一确定"**
> 完备充分统计量不是唯一的（$T$ 和 $2T$ 都可以），但由它构造的 MVUE 是唯一的。

> ⚠️ **2. 正则指数分布类的三个条件缺一不可**
> 最容易忽略的是"支撑集不依赖于 $\theta$"。$U[0,\theta]$ 和平移指数都因为支撑集依赖参数而不属于。

> ⚠️ **3. 有效性 $\leq 1$ 是一定成立的**
> 只要 RCB 存在且估计量无偏，$\text{Var} \geq \text{RCB}$，有效性 $= \text{RCB}/\text{Var} \leq 1$。

> ⚠️ **4. Exp 分布的参数化是常见陷阱**
> 确认 $f(x;\theta)=\frac{1}{\theta}e^{-x/\theta}$（$E[X]=\theta$）还是 $f(x;\theta)=\theta e^{-\theta x}$（$E[X]=1/\theta$），两种参数化下 MVUE 和 NP 拒绝域的方向不同。

> ⚠️ **5. 纠偏时注意 $E[\overline{X}^2] = \theta^2 + \frac{\text{Var}(X)}{n}$**
> $E[\overline{X}^2] = (E[\overline{X}])^2 + \text{Var}(\overline{X}) = \theta^2 + \frac{\sigma^2}{n}$。不同分布的 $\sigma^2$ 不同（Poisson: $\theta$; $N(\theta,\sigma_0^2)$: $\sigma_0^2$; Exp(均值为$\theta$): $\theta^2$）。

> ⚠️ **6. NP 检验中拒绝域方向的判断**
> 正确做法：写出似然比 $L(\theta_0)/L(\theta_1)$，判断其关于充分统计量 $Y$ 的单调性（递增还是递减），再确定 $Y \geq c$ 还是 $Y \leq c$。

---

## See Also

- [数理统计期末总结](数理统计期末总结.md) — 全部知识点汇总
- [09 Rao-Cramer下界与有效性](09%20Rao-Cramer下界与有效性.md)
- [10 极大似然检验](10%20极大似然检验.md)
- [12 充分统计量](12%20充分统计量.md)
- [13 完备性与指数分布类](13%20完备性与指数分布类.md)
- [14 最小充分性与从属统计量](14%20最小充分性与从属统计量.md)
- [15 最优假设检验](15%20最优假设检验.md)
- [LaTeX 试卷](../../assets/数理统计-期末样卷Spring25/数理统计-期末样卷Spring25.tex)
