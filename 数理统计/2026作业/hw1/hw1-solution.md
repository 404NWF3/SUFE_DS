# Assignment 1

## Problem 1

### 1.1 

设公司员工的年终绩效评分为一个随机变量 $X \sim N(75, 8^2)$，$x$ 为进入该名单的最小分数。则有

$$
P(X > x) = 0.05
$$

于是：

$$
1- \Phi(\frac{x-75}{8}) = 0.05
$$

最终解得：

$$
x = 88.16
$$

### 1.2

由题意得，综合成绩 $S$ 满足：
$$
S \sim N(0.6 \times 78 + 0.4 \times 72, 0.36 \times 9^2 + 0.16 \times 6^2) = N(75.6, 34.92)
$$

前15%的员工进入精英培养计划，设进入该计划的员工综合成绩的最小分数为 $s$，则有：
$$
P(S > s) = 0.15
$$
最终解得：

$$
s=81.72
$$

## Problem 2

### 2.1

由于：

$$P\{V > v\} = P\{(2W-1)X > v\} = P\{-X > v\ | W=0\}P{W=0} + P\{X > v\ | W=1\}P{W=1} = P\{X>v\}$$

所以：

$$
V \sim N(0, 1)
$$

### 2.2

$$
\text{Cov}(U, V) = EUV-EUEV
$$

其中，$EU=0$, $EV=0$, $EUV=E[X(2W-1)X]$，又 $X$ 与 $W$ 相互独立，所以: $EUV=E[X(2W-1)X]=E[X^2(2W-1)]=E[X^2]E[2W-1]=E[X^2] \times 0 = 0$

综上：

$$
\text{Cov}(U, V)=0
$$

### 2.3

不能构成一个二元正态分布。由 2.2 可知 $U$ 与 $V$ 不相关，接下来只要证明 $U$ 与 $V$ 不独立即可。

举一个反例有：

$$
P\{U>1, V>1\} = P\{X>1, (2W-1)X>1\} = P\{X>1, W=1\} = P\{X>1\} \times P\{W=1\} = (1-\Phi(1)) \times 0.5
$$

而
$$
P\{U>1\} \times P\{V>1\} = (1-\Phi(1))^2
$$

所以 $P\{U>1, V>1\} \neq P\{U>1\} \times P\{V>1\}$，$U$ 与 $V$ 不独立。

综上：$U$ 与 $V$ 不相关也不独立，所以不能构成一个二元正态分布。

## Problem 3

设 $Y_1, Y_2, \ldots, Y_n$ 为 $n$ 个独立同分布的随机变量，且 $Y_i \sim Po(\lambda)$，则 $X_n$ 可以表示为：

$$
X_n = \sum\limits_{i=1}^n Y_i
$$

根据中心极限定理：

当 $n \to \infty$ 时，

$$
\frac{X_n - n E[Y_i]}{\sqrt{nVar(Y_i)}} \to N(0, 1)
$$

其中，$E[Y_i] = \lambda, Var(Y_i) = \lambda$，故当 $n \to \infty$ 时：

$$
\frac{X_n - n\lambda}{\sqrt{n\lambda}} \to N(0, 1)
$$

## Problem 4

$X_1, X_2, \ldots, X_n$ 为 $n$ 个独立同分布的随机变量，且 $X_i \sim \text{Exp}(\theta)$，则不妨设 $S = \sum\limits_{i=1}^n X_i \sim \text{Gamma}(n, \frac{1}{\theta})$。

可以得到 $S$ 的 pdf：

$$
f_S(s) = \frac{1}{\Gamma(n)} \theta^n s^{n-1} e^{-s\theta}, s > 0
$$

又因为 $\bar{X} = \frac{S}{n}$，所以 $\bar{X}$ 的 pdf 为：

$$
f_{\bar{X}}(x) = f_S(nx) \cdot |J|, x > 0
$$

其中，$J$ 是 $S$ 关于 $\bar{X}$ 的Jacobian行列式，即 $J = \frac{dS}{d\bar{X}} = n$。所以：

$$
f_{\bar{X}}(x) = \frac{1}{\Gamma(n)} \theta^n (nx)^{n-1} e^{-nx\theta} \cdot n = \frac{1}{\Gamma(n)} (\theta n)^n x^{n-1} e^{-x\theta n}, x > 0
$$

所以 $\bar{X} \sim \text{Gamma}(n, \frac{1}{\theta n})$。

## Problem 5

### 5.1

一阶原点矩与期望：
$$
\mu_1=E[X]=\frac{-12-6-2+2+5+10}{6}=-0.5
$$

二阶原点矩：
$$
\mu_2=\frac{144+36+4+4+25+100}{6}=\frac{313}{6}
$$

二阶中心矩：
$$
\sigma_2=\mu_2-\mu_1^2=\frac{313}{6}-(-0.5)^2 \approx 51.9167.
$$

### 5.2

样本均值：
$$
\mu_1 = \bar x=\frac{1}{10}\sum x_i=\frac{-4}{10}=-0.4.
$$
样本二阶原点矩：
$$
\mu_2 = \frac{1}{10}\sum x_i^2=\frac{382}{10}=38.2.
$$
样本二阶中心矩：
$$
\sigma_2 = \frac{1}{10}\sum (x_i-\bar x)^2=38.04.
$$
样本方差：
$$
s^2=\frac1{9}\sum (x_i-\bar x)^2 \approx 42.2667.
$$

### (3) 是否可以计算非零的一阶中心矩？

不能。一阶中心矩恒为 0：
$$
E[X-\mu]=0,\qquad \frac1n\sum (x_i-\bar x)=0.
$$

## Problem 6

### 6.1

不是。$\mu$ 未知，所以 $Y=X_1-\mu$ 不是统计量

### 6.2

是。$\sigma$ 已知，而且 $\max\{X_1, \ldots, X_i\}$ 计算依赖于样本。所以 $Y=\frac{\max\{X_1, \ldots, X_i\}}{\sigma_0}$ 是统计量

### 6.3

是。$Y=X_1-X_2$ 计算只依赖于样本，所以是统计量

## Problem 7

$Y_1, Y_2, \ldots, Y_m \sim Exp(\frac{1}{2})$ i.i.d，$\text{Exp}(\frac{1}{2})$ 又等价于 $\text{Gamma}(1, 2)$，根据 Gamma 分布的可加性，$S=\sum\limits_{i=1}^m Y_i \sim \text{Gamma}(m, 2)$。

可以写出 $S$ 的 pdf：

$$
f_S(s) = \frac{1}{2^m \cdot \Gamma(m)}  \cdot s^{m-1} \cdot e^{-2s} = \frac{1}{2\Gamma(m)} (\frac{s}{2})^{m-1} e^{-\frac{s}{2}}, s > 0
$$

这正好是 $\chi^2(2m)$ 分布的 pdf，所以 $\sum\limits_{i=1}^m Y_i \sim \chi^2(2m)$。

## Problem 8

### 8.1

$\bar{A}=\frac{1}{n}\sum\limits_{i=1}^n A_i$，则 $\bar{A} \sim N(\mu, \frac{\sigma^2}{n})$。

计算 $A_1$ 与 $\bar{A}$ 的协方差矩阵有：
$$\text{Cov}(A_1, \bar{A}) = \text{Cov}(A_1, \frac{1}{n}\sum\limits_{i=1}^n A_i)=\frac{1}{n}\text{Cov}(A_1, \bar{A})$$

由于 $A_1$ 与 $A_2, A_3, \ldots, A_n$ 相互独立，所以 $\text{Cov}(A_1, A_i) = 0$，当 $i \neq 1$ 时。又因为 $\text{Cov}(A_1, A_1) = Var(A_1) = \sigma^2$，所以：

$$
\text{Cov}(A_1, \bar{A}) = \frac{\sigma^2}{n}
$$

于是可以计算出 $(A_1, \bar{A})$ 的协方差矩阵：

$$
\Sigma = \begin{bmatrix}\sigma^2 & \frac{\sigma^2}{n} \\
\frac{\sigma^2}{n} & \frac{\sigma^2}{n}\end{bmatrix}
$$

综上，$(A_1, \bar{A})$ 的联合分布为：
$$
(A_1, \bar{A}) \sim N\left(\begin{bmatrix} \mu \\ \mu \end{bmatrix}, \Sigma \right)
$$

### 8.2

$$
\sum\limits_{i=1}^n\frac{1}{\sigma^2}{(A_i-\bar{A})^2} = \frac{1}{\sigma^2}\sum\limits_{i=1}^n (A_i-\mu+\mu-\bar{A})^2=\sum\limits_{i=1}^n \frac{(A_i-\mu)^2}{\sigma^2} + \sum\limits_{i=1}^n \frac{(\bar{A}-\mu)^2}{\sigma^2} - 2\sum\limits_{i=1}^n \frac{(A_i-\mu)(\bar{A}-\mu)}{\sigma^2}
$$

$$
=\sum\limits_{i=1}^n \frac{(A_i-\mu)^2}{\sigma^2}+n \frac{(\bar{A}-\mu)^2}{\sigma^2}-2(\bar{A}-\mu)\sum\limits_{i=1}^n \frac{(A_i-\mu)}{\sigma^2}
$$
$$
=\sum\limits_{i=1}^n \frac{(A_i-\mu)^2}{\sigma^2}-n \frac{(\bar{A}-\mu)^2}{\sigma^2}
$$
其中：$\sum\limits_{i=1}^n \frac{(A_i-\mu)^2}{\sigma^2} \sim \chi^2(n)$，又 $(\frac{\bar{A}-\mu}{\sigma^2/ \sqrt{n}})^2 \sim \chi^2(1)$

故：

$$
\sum\limits_{i=1}^n\frac{1}{\sigma^2}{(A_i-\bar{A})^2} \sim \chi^2(n-1)
$$

### 8.3

$$
\frac{\bar{A}-\mu}{\frac{1}{n}\sqrt{\sum\limits_{i=1}^n B_i^2}} = \frac{\frac{(\bar{A}-\mu)\sqrt{n}}{\sigma}}{\sqrt{\sum\limits_{i=1}^n \left(\frac{B_i}{\sigma}\right)^2/n}}
$$

其中：$\frac{(\bar{A}-\mu)\sqrt{n}}{\sigma} \sim N(0, 1)$，$\sum\limits_{i=1}^n \left(\frac{B_i}{\sigma}\right)^2 \sim \chi^2(n)$

根据 $t$ 分布的定义：

$$
\frac{\bar{A}-\mu}{\frac{1}{n}\sqrt{\sum\limits_{i=1}^n B_i^2}} \sim t(n)
$$

### 8.4

$$
\frac{\frac{1}{n-1}\sum\limits_{i=1}^n (A_i-\bar{A})^2}{\frac{1}{n}\sum\limits_{i=1}^nB_i^2} = \frac{\frac{1}{n-1}\sum\limits_{i=1}^n \left(\frac{A_i-\bar{A}}{\sigma}\right)^2}{\frac{1}{n}\sum\limits_{i=1}^n\left(\frac{B_i}{\sigma}\right)^2} 
$$

其中，由 8.2 可知： $\frac{1}{n-1}\sum\limits_{i=1}^n \left(\frac{A_i-\bar{A}}{\sigma}\right)^2 \sim \chi^2(n-1)$，$\frac{1}{n}\sum\limits_{i=1}^n\left(\frac{B_i}{\sigma}\right)^2 \sim \chi^2(n)$

根据 $F$ 分布的定义：

$$
\frac{\frac{1}{n-1}\sum\limits_{i=1}^n (A_i-\bar{A})^2}{\frac{1}{n}\sum\limits_{i=1}^nB_i^2} \sim F(n-1, n)
$$

## Problem 9

### 9.1

令 $A = X_1-X_2$, $B=X_3+X_4$, $D=Y_1-Y_2$。易得到：

$$
A \sim N(0, 8), B \sim N(2, 8), D \sim N(0, 18)
$$

又 $U$ 是 $\chi^2$ 分布，$U=aA^2+b(B-c)^2+dD^2$，则容易知道，当 $a=\frac{1}{8}$, $b=\frac{1}{8}$, $c=2$, $d=\frac{1}{18}$ 时，$(\frac{A}{2\sqrt{2}})^2+(\frac{B-2}{2\sqrt{2}})^2+(\frac{D}{3\sqrt{2}})^2$ 恰好是三个服从 $\chi^2(1)$ 的分布相加，所以 $U \sim \chi^2(3)$。

### 9.2

$$
V=\frac{\sqrt{m}(X_5-1)}{\sqrt{U}}=\sqrt{m} \times \frac{\frac{X_5-1}{2}}{\sqrt{U/3}} \times \frac{2}{\sqrt{3}}
$$

其中，V是 $t$ 分布，使得$\sqrt{m} \times \frac{2}{\sqrt{3}}=1$，从而求得 $m=\frac{3}{4}$，所以 $V \sim t(3)$。

### 9.3

$$
V^2 = \frac{\left( \frac{X_5-1}{2} \right)^2/1}{U/3}
$$

其中，$\left( \frac{X_5-1}{2} \right)^2 \sim \chi^2(1)$，$U \sim \chi^2(3)$

根据 $F$ 分布的定义，$V^2 \sim F(1, 3)$

## Problem 10

$X \sim F(3, 5)$，$Y \sim F(5, 3)$，则根据 $F$ 分布的性质，有 $Y$ 的 $5\%$ 分位数等于 $X$ 的 $95\%$ 分位数的倒数，$Y$ 的 $95\%$ 分位数等于 $X$ 的 $5\%$ 分位数的倒数。

所以， $Y$ 的 $5\%$ 分位数为 $\frac{1}{5.409} \approx 0.1849$，$Y$ 的 $95\%$ 分位数为 $\frac{1}{0.111} \approx 9.009$。