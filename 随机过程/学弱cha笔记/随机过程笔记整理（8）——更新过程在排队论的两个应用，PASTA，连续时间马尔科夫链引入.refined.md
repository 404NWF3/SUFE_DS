# 随机过程|笔记整理（8）——更新过程在排队论的两个应用，PASTA，连续时间马尔科夫链引入

上一节笔记：[学弱猹：随机过程|笔记整理（7）——更新奖赏过程：交替更新过程，生存与濒死时间，观察悖论](https://zhuanlan.zhihu.com/p/341164317)

---

大家好！

这一节我们还是以更新过程的应用为主，主要会介绍排队论的几个具体的模型，并且介绍一些与这些模型有关的性质。

那么我们开始吧。

## 目录

- 排队论模型1：$GI/G/1$
  - 其它量化的结果
- 排队论模型2：$M/G/1$
  - [PASTA性质](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=PASTA%E6%80%A7%E8%B4%A8&zhida_source=entity)
- [连续时间马尔科夫链](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E8%BF%9E%E7%BB%AD%E6%97%B6%E9%97%B4%E9%A9%AC%E5%B0%94%E7%A7%91%E5%A4%AB%E9%93%BE&zhida_source=entity)
  - 全新的转移概率：[跳跃速率](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E8%B7%B3%E8%B7%83%E9%80%9F%E7%8E%87&zhida_source=entity)
  - [Kolmogorov方程](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=Kolmogorov%E6%96%B9%E7%A8%8B&zhida_source=entity)

## 排队论模型1：$GI/G/1$

一般来说，排队论模型都会用一些字母做一个简化。$GI/G/1$就是指一种特定的模型。$GI$的意思是general input，$G$就是general service time，$1$就是“一个服务器”的意思。连在一起说，就是

> 有一个理发店[排队模型](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E6%8E%92%E9%98%9F%E6%A8%A1%E5%9E%8B&zhida_source=entity)，相邻两个人到达的时间差服从分布$F$（general input）。到达理发店之后，只有一个理发师（一个服务器），理发师的服务时间服从一个分布$G$（general service time）。分布$F$的均值为$\frac 1 \lambda$，分布$G$的均值为$\frac 1 \mu$。

这里的均值写成$\frac 1 \lambda$和$\frac 1 \mu$，其实可以理解为**排队和服务速率分别**为$\lambda, \mu$。如果按照这么理解，下面这个性质直观上就很容易理解了。

> Proposition 1:\
> 如果$\lambda < \mu$，并且一开始有$k$个人在排队（$k$有限），那么以概率为1，队列会清空。

这个性质直观上来看，就是如果服务的速率比排队的速率要快，那么最终队伍几乎一定会空。如果我们稍微不严谨一点，就理解为“一定会空”。这自然是符合我们的认知的。

首先要理解什么是“队列清空”。首先因为一开始就有人在排队，所以不会出现”没人服务“的情况。因此简单来说，**排队的过程和服务的过程可以分别拉出来看**。所以抽象出来，如果我们认为一开始$k$个人的服务时间一共为$z_0$，后面每一个人所需要的服务时间为$s_i$（$s_1$是除一开始的$k$个外，第一个到达的人的服务时间），并且假设相邻两个点之间的时间差为$t_i$的话（除一开始的$k$个，经过$t_1$之后，第一个人到达，之后以此类推）那么总结来看，就是希望说明

> $P(z_0 + s_1 + \ldots + s_n < t_1 + \ldots + t_{n + 1}, \exists n) = 1$

因为如果这个不等式满足，就说明第$n + 1$个人还没有到达，第$n$个人就完成了服务，也就是”队列清空“的含义。

如果要说明这一点，其实可以利用[大数定律](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E5%A4%A7%E6%95%B0%E5%AE%9A%E5%BE%8B&zhida_source=entity)，也就是说说明

> $t_1 + \ldots + t_{n + 1} - (z_0 + s_1 + \ldots + s_n) > 0, a.s.$

**下面我们会做一点不严格的模糊，因为严格说明需要[高等概率论](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E9%AB%98%E7%AD%89%E6%A6%82%E7%8E%87%E8%AE%BA&zhida_source=entity)的知识**。这里两边除以$n$，然后$\frac {z_0} n$会趋于0（以概率为1），然后再注意到

> $\frac{t_1 + \ldots + t_{n + 1}}{n} \to \frac 1 {\lambda}, a.s.$
> $\frac{s_1 + \ldots + s_n}{n} \to \frac 1 \mu, a.s.$

所以结合$\lambda < \mu$就可以得到结论。

我们再强调一遍，**这里的说法其实都是不严谨的推论**。事实上在我们利用大数定律的时候，有些地方会有“以概率为1”的额外条件，**读者在阅读的时候还是要注意这一点**，虽然在应用层面上可以忽略这一句话。

## 其它量化的结果

很显然我们不可能就这么结了，事实上对于这个模型，有很多数量是可以研究的。

首先就是**整个系统中的人数**，这里我们**假设一开始没有人在队列中**。在时间$s$时，我们可以定义出$X_s, X_{s, Q}$这两个量。这里的$X_s$表示在整个系统的人数，而$X_{s, Q}$则表示**还在排队的人数**（因为排队就是queue）。自然会有

> $X_{s, Q} = X_s - I(X_s > 0)$

因为这个系统中只有一个服务器（理发师），所以如果$X_s > 0$，说明有人在系统中，那么一定会有人在接受服务，这个时候排队的人数自然是整个系统的人数再减1，否则就不用变。因此我们就可以用[示性函数](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E7%A4%BA%E6%80%A7%E5%87%BD%E6%95%B0&zhida_source=entity)进行表达。

同样的，对于每一个人，也可以[量化](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=3&q=%E9%87%8F%E5%8C%96&zhida_source=entity)他们在等待的时间（这里的等待不是排队的时间，而是**在整个系统停留的时间**）。对于第$m$个人，我们可以设出$W_m, W_{m, Q}$这两个量，其中$W_m$是第$m$个人停留在系统的时间，$W_{m ,Q}$是他在排队的，**未接受服务**的时间。那么有

> $W_{m, Q} = W_m - s_m$

有了这些之后，按照惯例，我们也会计算**这些量长期的表现**。以$X_s, X_{s, Q}$为例，我们可以设

> $\frac 1 t \int_0^t X_s ds \to L$
> $\frac 1t \int_0^t X_{s, Q}ds \to L_Q$

其中$t \to \infty$。那么有

> $L_Q = L - 1 + \pi(0)$
> $\pi(0) = \lim_{t \to \infty} \frac 1 t \int_0^t I(X_s = 0)ds$

代入$X_{s, Q}$的[表达式](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E8%A1%A8%E8%BE%BE%E5%BC%8F&zhida_source=entity)就可以得到结论。

同样的，对于$W_m, W_{m, Q}$，我们也可以设

> $\frac 1n \sum_{m = 1}^n W_m \to W$
> $\frac 1n \sum_{m =1}^n W_{m, Q} \to W_Q$

那么我们有

> $W_Q = W - \frac 1 \mu$

这是因为根据大数定律，我们有$\frac 1n \sum_{m = 1}^n s_m \to \frac 1\mu$（这里没有“以概率为1”的条件，是因为这里用的就是最简单的，同分布情况下的**<a href="https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E5%BC%BA%E5%A4%A7%E6%95%B0%E5%AE%9A%E5%BE%8B&zhida_source=entity">强大数定律</a>**）。

这些基本的数量定义完之后，我们就可以介绍关于这些数量之间关系的定理了。

> Theorem 1: [Little&#39;s Formula](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=Little%26%2339%3Bs+Formula&zhida_source=entity)
> $L = \lambda_a W, L_Q = \lambda_a W_Q$

这里的$\lambda_a$表示的是长期来看，**加入排队的人**的速率。也就是说，如果没有加入排队（也就是说，上一个人还没有服务完，下一个人就不等了，直接跑路了），是不会记入的。换句话说，如果每一个人都没有经历过这种“排队但是没有享受到服务”的情况，那么$\lambda_a = \lambda$。

我们先说第二个，事实上，我们只需要说明

> $\frac 1 t\int_0^t X_{s, Q} ds \simeq \frac 1t \sum_{i = 1}^{N_a(t)} W_{i, Q}$

但这个很容易，因为如果我们思考一个“单纯的排队系统”，也就是不考虑直接加入服务的人。那么注意到，$X_s$在一段时间的均值，**其实就是每一个人等待时间的均值**。这可以通过下图解释。

![图片](https://pic2.zhimg.com/v2-f842ec62c4e2386c41b79d955308813b_1440w.jpg)

区间上标的数字表示**当前队列有几个人**。而$W_1, W_2$就是**每一个人排队的时间**（不包括服务时间）。其实很容易发现，这只是用两种不同的方法在计算$W_1 + W_2$而已。

简单变换一下，就可以有

> $\frac 1t \sum_{i = 1}^{N_a(t)} W_{i,Q} = \frac{N_a(t)}t \frac 1{N_a(t)}\sum_{i = 1}^{N_a(t)}W_{i,Q} \to \lambda_a W_Q$

这就得到了结论。

我们再来看$L = \lambda_a W$这个如何证明。事实上就是要说明，$\frac 1 t \int_0^t X_s ds$的极限是$\lambda_a W$。使用类似的方式，我们可以得到

> $\frac 1 t\int_0^t X_s ds \simeq \frac 1t \sum_{i = 1}^{N_a(t)} W_i$

但是这里我们考虑的是“完整的系统”，也就是说**依然考虑那些没有排队，直接加入系统的人**。剩下的步骤都是一模一样的，所以就不用多提了，我们交给读者补充。

事实上，根据这个结论，我们会有下面的推论。

> Corollary 1:\
> $\pi(0) = 1 - \frac{\lambda_a}{\mu}$

这个证明非常简单，把之前的式子代进来就可以了。我们交给读者完成。

这里的$\pi(0)$就是我们之前的定义，简单来说就是**队列空闲的时间**占比。反过来说，$1 - \pi(0)$就是**队列繁忙的时间**。在这里就是$\frac{\lambda_a}\mu$。

## 排队论模型2：$M/G/1$

这是另外一个排队论模型，相比较上一个模型，区别仅仅在于，**人到达的时间是具备[马尔科夫性](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E9%A9%AC%E5%B0%94%E7%A7%91%E5%A4%AB%E6%80%A7&zhida_source=entity)的**。在这里具体来说，就是到达时间$t_i$服从[指数分布](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E6%8C%87%E6%95%B0%E5%88%86%E5%B8%83&zhida_source=entity)$\exp(\lambda)$。那么对于这个问题，我们可以画出这样的一张图。

![图片](https://pic3.zhimg.com/v2-c294933966f7e9641e14248610066dc4_1440w.jpg)

这里$I_n$表示的是“空闲时间”（也就是“等待时间”），而$B_n$表示的就是“繁忙时间”（也就是“服务时间”）。蓝色三角形表示**顾客到来**，红色的表示**顾客离开**。所以可以看出，我们这里实际上是可以利用上一节的更新奖赏过程的，“等待时间”和“服务时间”交替。

这里很多人不理解的地方就是，完全有可能，**新的人来排队的时候，之前的人还没有服务完**，这里的图会不会有问题？但这里要用到的技巧其实上一节就提过了，就是对于泊松到达时间而言，无论从哪里开始，经过的等待时间都是服从$\exp(\lambda)$的。用一张图解释如下。

![图片](https://pic4.zhimg.com/v2-440380dc04a9972e5686ec815c50c963_1440w.jpg)

这也是随机过程一个比较难理解的地方。不过在之后如果还是一样的技巧，我们就不画图了2333。

如果是交替随机过程，那么长期来看的“空闲时间占比”以及“繁忙时间占比”就容易计算了。这里我们可以直接给出答案为

> $\pi(0) = \frac { \frac 1 \lambda}{\frac 1 \lambda + E(B_1)}$

## PASTA性质

**PASTA**（Poisson Arrivals See Time Averages）性质是$M/G/1$模型的一个特有性质。这个性质的简单概括就是。

> Theorem 2:\
> 在同一个时间点，一个[泊松](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=2&q=%E6%B3%8A%E6%9D%BE&zhida_source=entity)到达的人看到的前面的队列的性质，和一个“上帝视角”看这个队列的性质，是一致的。

乍一看估计一俩懵逼。一个好的描述它的数学式子就是$N(t) - N(t-) = 1$，我们考虑在时间$t$来了一个人，并且加入了排队，那么注意到，因为“泊松到达”的性质，所以$(t - \epsilon, t)$和$(0, t -\epsilon)$区间上的队列性质是无关的（$\epsilon$自然是可以任意小的）。简单来说，**这个人加入了排队不会对之前任何时间的队列产生任何的影响，它在这个时间点到来，不会包含任何之前时间的信息**。那么这样的话，其实这个人加入不加入队列，对于$(0, t- \epsilon)$这个区间上的队列就无所谓了。

即使讲到这里，估计还是挺多人听不明白，我们再举一个反例。考虑一下如果$t_i \sim U[1, 2], s_i = 1$。$t_i$是等待时间，$s_i$是服务时间。是那么从外人来看，我们一定可以知道，肯定有一段时间有人来过并接受过服务，然后又走了，然后又有人来了，以此类推。但是如果是“排队者”，情况就不一样了，因为$t_i \ge 1 = s_i$，所以**无论它什么时候来排队，看到的队列都一定是空的**。这就不符合PASTA性质，因为**两个人在同一个时间看这个队列，看到的结果是不一样的**。换句话说，你在任何一个时间去看，只要是泊松到达，那么无论这个人是属于队列的，还是不属于队列的，所观察到的队列性质都是一模一样的。

至于为什么看到的不一样，其实也可以做一些解释，这是因为在这个语境中，你可以了解到

> $(t-1, t)$一定无人到达。

画画图就能看出来这一点。但这一点就暴露出了问题，因为**这并不符合马尔科夫性**（可以通过当前，知道过去部分时间的队列情况）。所以对于这个例子不符合PASTA性质，也就好理解了。

做一点简单的延伸，则可以得到这样的性质。

> Corollary 2:\
> 长期来看，队列中有$n$个人所占的时间比例，和最后到达者发现自己队伍前面有$n$个人（包括他自己）的次数所占比例是相同的。

数学上的定义是

> $\frac 1t \int_0^t X_s ds$和$\frac 1n \sum_{i = 1}^n X_{s_i}$趋于同一极限。

这里的$X_s$就是之前说的，队列中的排队人数。

乍一看也是一个挺难懂的结论，所以我们举一个例子。

> Proposition 1:\
> 在$M/G/1$排队模型中，设$Z_s$为在$s$时刻，所有的顾客还需要的服务时间。利用PASTA性质和$Z_s$，证明$W_Q = \frac{\lambda E(\frac {s_i^2} 2 )}{1 - \lambda E(s_i)}$。

比方说$s$时刻有三个人，一个人还需要等待2分钟，一个人还需要等待3分钟，一个人已经进行了半分钟的服务，并且每个人服务时间都是固定的1分钟，那么还需要的总服务时间就是2.5分钟。

这个地方为什么能和$W_Q$有关系，是因为$W_Q$考虑的是在队列等待的时间，所以是和PASTA有关系的。但总体上来说要说明这个结论还是不太容易的，[建模](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E5%BB%BA%E6%A8%A1&zhida_source=entity)需要对PASTA有足够的理解。

首先自然需要看看，什么是$\frac 1t \int_0^t Z_s ds$。因为这个相当于“所有的顾客还需要的服务时间的平均”，所以老样子，我们可以把它拆分为每一个人的情况，并且忽略$(N(t), t)$这一段的情况。（**还不清楚这一段是什么意思的话，建议回头看一下之前的内容了，因为可能后面就跟不上了**）那么这样的话，会有

> $\frac 1t \int_0^t Z_s ds \simeq \frac 1t \sum_{i = 1}^{N(t) }[s_iW_{i, Q} + \int_0^{s_i}(s_i - x)dx] \to \lambda[ E(s_1)W_Q + \frac {E(s_1^2)}2]$

分成每一个人考虑之后，第一项对应的就是这个人“还在排队的时候”，那么在排队的时候，在那个点他需要的服务时间一直都是$s_i$。第二项对应的是这个人“已经在接受服务的时候”，那么随着时间的推移，还需要的服务时间就会不断减少，这个过程就是一个积分。每一个人的还需要的服务时间的积分，和“按照时间考虑，一段时间内所有人还需要的服务时间”，表达的含义相同，所以式子的结果也应该是相同的。

后面的极限状态直接大数定律就可以得到，我们就不多说了。

所以这和$W_Q$又有什么关系呢？注意到Corollary 2是怎么推出来的，因为PASTA，所以每一个人的到达不会有任何对之前队列的影响，所以对于$X_s$这个量，是否具备“[上帝视角](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=2&q=%E4%B8%8A%E5%B8%9D%E8%A7%86%E8%A7%92&zhida_source=entity)”并不重要。同样的我们也可以用到$Z_s$上，也就是说，对于$\frac 1t \int_0^t Z_s ds$，我们可以考虑把它转换为

> 最后到达者看到的工作量的平均

这个“看到的工作量”指的是$Z_s$的定义，也即“看到之前的等待时间平均”。那么我们注意到，最后到达的人，**他只能看到之前人的在队列中的等待情况，因此i不需要额外加上服务时间**，这里就是$ W_{i, Q}$，大数定律平均一下就是$W_Q$，也就是说我们可以得到

> $\lambda [E(s_1)W_Q + \frac {E(s_1^2)}2] \to W_Q$

（有的人可能会问**为什么不乘上$\lambda_a$**而是乘上$\lambda$。这是因为，$\lambda_a < \lambda$是在产生“排队但是没有接受服务”的情况下才会发生的，这个概率在$M/G/1$的模型下是0，虽然这并不代表它不会发生。想想为什么？）通过解$W_Q$就可以得到结论。

好的，我们来举一个与它有关的实际的计算题。

> Problem 1:\
> 考虑一个$M/G/1$排队模型，在一个理发店中，顾客到来的速率服从速率为$\frac 16$的[泊松分布](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E6%B3%8A%E6%9D%BE%E5%88%86%E5%B8%83&zhida_source=entity)，而理发所需要的时间平均为5min，[标准差](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E6%A0%87%E5%87%86%E5%B7%AE&zhida_source=entity)为$\sqrt {59}$ min。问
> 
> 1. 长期来看，队列空闲的概率$\pi(0)$。
> 2. 长期来看，一个顾客的平均排队时间和留在队列的总时间。
> 3. 长期来看，队列平均有多长？

这几个问题都是需要利用上面提到的几个性质的。提取一下信息，我们发现$\lambda = \frac 16$，$\mu = \frac 15$，所以根据公式有

> $\pi(0) = 1 - \frac{\lambda}{\mu} = \frac 16$

这就是第一题。

第二题事实上就是在求$W$和$W_Q$。而对于$W_Q$，我们可以利用公式，得到

> $W_Q = \frac{\lambda E(s_i^2)/2}{1 - \lambda E(s_i)} = 42$

这是因为$E(s_i^2) = 5^2 + 59 = 84$。那么自然还会有$W = W_Q + s_1 =47$。这样的话，平均的[队列长度](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E9%98%9F%E5%88%97%E9%95%BF%E5%BA%A6&zhida_source=entity)就是$L = \lambda W = \frac {47}6$。当然如果要是不考虑那些服务中的人的话，[平均队列长度](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E5%B9%B3%E5%9D%87%E9%98%9F%E5%88%97%E9%95%BF%E5%BA%A6&zhida_source=entity)就是$L_Q = \lambda W_Q = 7$，这也就是第二题和第三题。

PASTA性质是$M/G/1$模型中一个比较难理解的性质，它的应用其实我自己也感觉有点扑朔迷离。但是**考虑到它在之后还是具备一定的用武之地，我们建议大家还是多花时间去理解这里我们的描述和相关的例子**。

好的，那么关于$M/G/1$这个排队论模型，我们也就介绍到这里。

## 连续时间马尔科夫链

**连续时间马尔科夫链**（continuous time Markov chain，CTMC）是区别于[离散马尔科夫链](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E7%A6%BB%E6%95%A3%E9%A9%AC%E5%B0%94%E7%A7%91%E5%A4%AB%E9%93%BE&zhida_source=entity)的，另外一种体现马尔科夫性的一种随机过程模型。**因为连续时间的存在**，在讨论它的性质，应用等的时候，都会与之前的[离散模型](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E7%A6%BB%E6%95%A3%E6%A8%A1%E5%9E%8B&zhida_source=entity)有一定的区别。

那么我们看一看，连续时间马尔科夫链是如何定义的。

> Definition 1: Continuous Time Markov Chain\
> 设状态空间有限/[无限可数](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E6%97%A0%E9%99%90%E5%8F%AF%E6%95%B0&zhida_source=entity)，那么如果[随机变量](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E9%9A%8F%E6%9C%BA%E5%8F%98%E9%87%8F&zhida_source=entity)集合$\{X_t, t \ge 0\}$满足$P(X_{s + t} = j |X_s = i, X_{s_k} = i_k, 0 \le k \le n) = P(X_t = j|X_0 = i)$对于任意的$0 \le s_0 < \ldots < s_n < s$和任意可能的$i_0, \ldots, i_n, i ,j $都成立（$i, j$属于状态空间），则称序列满足连续时间马尔科夫性。

虽然这个定义很长很复杂，但其实直观来说，就是，之后的事情与之前无关，并且具备时间的[齐次性](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E9%BD%90%E6%AC%A1%E6%80%A7&zhida_source=entity)。也就是说在$s$这个点来看，时间$s + t$发生的事件的可能性，应该和在$0$这个点来看，时间$t$发生的事件的可能性一致。

我们从这个定义也可以看出来，连续时间马尔科夫链的“连续”二字就体现在，**不再存在离散马尔科夫链的“步数”这个概念**，所以后面我们会发现，不能再使用之前的[转移概率矩阵](https://zhida.zhihu.com/search?content_id=164101530&content_type=Article&match_order=1&q=%E8%BD%AC%E7%A7%BB%E6%A6%82%E7%8E%87%E7%9F%A9%E9%98%B5&zhida_source=entity)来描述了。具体如何弥补这个缺陷，后面再提。

举一个简单的例子来帮助理解这个概念吧。

> Problem 2:\
> 设$\{Y_n\}$是离散时间马尔科夫链，转移概率为$u(i, j)$，$N(t)$服从一个速率为$\lambda$的泊松过程，$Y_n$和$N(t)$这两个量相互独立。那么说明$X_t = Y_{N(t)}$就是一个连续时间马尔科夫链。

下面这一张图解释了这个问题。

![图片](https://pic2.zhimg.com/v2-304a928f5cd88e7b59b5c177175cbd8b_1440w.jpg)

简单来说，就是$X_t$在$[0, T_1)$的时候对应$Y_0$（$T_1$就是第一次泊松到达的时刻），$[T_1, T_2)$的时候对应$Y_1$，等等。那么根据泊松过程的特性，就可以得到这里连续时间的马尔科夫性。因为我们取$X_s = i$，并且画出另外
