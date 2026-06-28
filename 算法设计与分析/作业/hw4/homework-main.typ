#import "homework-template.typ": homework_template, solution

#import "algorithm-block.typ": *

#show: homework_template.with(
  course: [算法设计与分析],
  homework_title: [第 4 次作业],
  student_name: [倪伟丰],
  student_id: [2024110089],
  class_name: [24 大数据 2 班],
  teacher: [韩凯],
  due_date: [2026 年 3 月 27 日],
)
#show: style-algorithm



= 第1题

Quantum antimatter fuel comes in small pellets, which is convenient since the many moving parts of the LAMBCHOP each need to be fed fuel one pellet at a time. However, minions dump pellets in bulk into the fuel intake. You need to figure out the most efficient way to sort and shift the pellets down to a single pellet at a time. The fuel control mechanisms have three operations:

- Add 1 fuel pellet
- Remove 1 fuel pellet
- Divide the entire group of fuel pellets by 2 (due to the destructive energy released when a quantum antimatter pellet is cut in half, the safety controls will only allow this to happen if there is an even number of pellets)

Write a function called $"answer"(n)$ which takes a positive integer $n$ as a string and returns the minimum number of operations needed to transform the number of pellets to 1. Prove the correctness of your algorithm. (E.g. $29 \to 28 \to 14 \to 7 \to 8 \to 4 \to 2 \to 1$)


#solution[
我们使用贪心算法来求解这个问题。对于当前的燃料数量 $n, n != 1$，我们考虑以下情况：

1. 如果 $n$ 是偶数，我们可以直接执行除以 2 的操作，这样可以快速减少燃料数量。
2. 如果 $n$ 是奇数：
 - 如果 $n = 4k + 3, forall k = 1, 2, 3, ...  $，我们选择加 1，这样可以得到一个 4 的倍数 ，然后执行 2 次除以 2 的操作。
 - 如果 $n = 4k + 1, forall k = 1, 2, 3, ...  $，我们选择减 1，这样可以得到一个 4 的倍数，然后执行 2 次除以 2 的操作。
 - 如果 $n = 3$，我们选择减 1，这样可以得到 2，然后执行除以 2 的操作，两部内达到 1，如不是先 +1 再执行两次除以 2 的操作（这需要 3 步）。
]

#solution[
  由此我们得到以下function（使用C++）：

```cpp
int answer(string n) {
  int steps = 0;
  long long num = stoll(n);
  
  while (num != 1) {
    if (num % 2 == 0) {
      num /= 2;
    } else if (num == 3 || num % 4 == 1) {
      num -= 1;
    } else {
      num += 1;
    }
    steps++;
  }
  
  return steps;
}
```
  接下来我们需要证明：

  - 引理1：对于任何偶数 $n$，执行除以 2 的操作是最优的。
  - 引理2：对于任何奇数 $n$，如果 $n = 4k + 3, forall k = 1, 2, 3, ... $，执行加 1 的操作是最优的；如果 $n = 4k + 1, forall k = 1, 2, 3, ... $，执行减 1 的操作是最优的；如果 $n = 3$，执行减 1 的操作是最优的。
  - 引理3：当 $n=3$ 时，执行减 1 的操作是最优的。

  将以上引理数学化，即：
  假设 $T(n)$ 表示将 $n$ 转换为 1 所需的最小操作数。于是：
  - $T(1) = 0$
  - $T(3) = 2$
  - $forall k = 1, 2, 3, ... $    
    - $T(2k) = 1 + T(k)$
    - $T(4k + 1) = 1 + T(4k)$
    - $T(4k + 3) = 1 + T(4k + 4)$

  其中，不难证明，如果 $a$ 可以一步到达 $b$，那么：

  $
  T(a) <= 1 + T(b)
  $

  首先证明引理3，即：$T(3) = 2$
  显然，$T(3) = min\{T(2) + 1, T(4) + 1\} = min\{1 + T(2), 1 + T(4)\} = min\{1 + 1, 1 + 2\} = 2$

  接下来证明引理1，即：对于任何偶数 $n$，执行除以 2 的操作是最优的。

  $forall n = 2k, k = 1, 2, 3, ... $，$T(n) = 1 + min{T(n/2), T(n+1), T(n-1)}$，要证明引理1成立，即证明：

  $
  T(n/2) <= T(n+1) quad and quad T(n/2) <= T(n-1)
  $

  即：

  $
  T(k) <= T(2k+1) quad and quad T(k) <= T(2k-1)
  $ 

  对于 $k$ 分情况讨论：

  1. $k$ 为奇数，即 $k = 2m-1, forall m = 1, 2, 3, ...$
]

#solution[
  此时，先证明：

  $
  T(2m-1) <= T(4m-1)
  $
  
  - 当 $m=1$ 时： $T(1) <= T(3)$
  
  - 当 $m >= 2$ 时：

  $
  T(4m-1) = 1 + T(4m) = 2 + T(2m)
  $

  $
  T(2m-1) <= 1 + T(2m) <= 2 + T(2m) = T(4m-1)
  $
  
  所以，根据数学归纳法，$T(2m-1) <= T(4m-1)$ 得证。

  再证明：

  $
  T(2m-1) <= T(4m-3)
  $

  - 当 $m=1$ 时： $T(1) <= T(1)$
  
  - 当 $m >= 2$ 时：

  $
  T(4m-3) = 1 + T(4m-4) = 2 + T(2m-2)
  $

  $
  T(2m-1) <= 1 + T(2m-2) <= 2 + T(2m-2) = T(4m-3)
  $

  所以，根据数学归纳法，$T(2m-1) <= T(4m-3)$ 得证。

  2. $k$ 为偶数，即 $k = 2m, forall m = 1, 2, 3, ...$

  此时，先证明：

  $
  T(2m) <= T(4m + 1)
  $

  - 当 $m=1$ 时： $T(2) <= T(5)$
  - 当 $m >= 2$ 时：

  $
  T(4m+1) = 1 + T(4m) = 2 + T(2m) >= T(2m)
  $

  所以，根据数学归纳法，$T(2m) <= T(4m + 1)$ 得证。

  再证明：

  $
  T(2m) <= T(4m - 1)
  $

  - 当 $m=1$ 时： $T(2) <= T(3)$
  - 当 $m >= 2$ 时：

  $
  T(4m-1) = 1 + T(4m) = 2 + T(2m) >= T(2m)
  $

  所以，根据数学归纳法，$T(2m) <= T(4m - 1)$ 得证。

  综上，$T(n/2) <= T(n+1)$ 且 $T(n/2) <= T(n-1)$ 得证，引理1得证。
]

#solution[
  接下来证明引理2，即：对于任何奇数 $n$，如果 $n = 4k + 3, forall k = 1, 2, 3, ... $，执行加 1 的操作是最优的；如果 $n = 4k + 1, forall k = 1, 2, 3, ... $，执行减 1 的操作是最优的。

  先证明：

  $
  forall k = 1, 2, 3, ..., T(4k+1) = 1 + T(4k)
  $

  $
  T(4k+1) = 1 + min{T(4k), T(4k+2)}
  $

  也就是证明： $T(4k+2) >= T(4k)$

  - 当 $k=1$ 时： $T(6) = 1+T(3) = 3$，$T(4) = 1+T(2) = 2$，所以 $T(6) >= T(4)$
  - 当 $k >= 2$ 时：

  $T(4k+2) = 1+T(2k+1)$，$T(4k) = 1+T(2k)$

  接下来只需要证明：

  $
  T(2k+1) >= T(2k)
  $

  1. $k = 2m, forall m = 1, 2, 3, ...$

  $T(2k+1) = T(4m+1) = 1+T(4m) = 3+T(m)$

  $T(2k) = T(4m) = 2+T(m)$

  此时：$T(2k) <= T(2k+1)$

  2. $k = 2m-1, forall m = 1, 2, 3, ...$

  $T(2k+1) = T(4m-1) = 1+T(4m) = 2+T(2m)$

  $T(2k) = T(4m-2) = 1 + T(2m-1) <= 2 + T(2m) = T(2k+1)$

  所以：$T(2k+1) >= T(2k)$ 得证。

所以，根据数学归纳法，$T(4n+2)>=T(4n)$

  再证明：

  $
  forall k = 1, 2, 3, ..., T(4k+3) = 1 + T(4k+4)
  $

  $
  T(4k+3) = 1 + min{T(4k+2), T(4k+4)}
  $

  也就是证明： $T(4k+2) >= T(4k+4)$

  - 当 $k=1$ 时： $T(6) = 1 + T(3) = 3$，$T(8) = 1 + T(4) = 2+ T(2) = 3$，所以 $T(6) >= T(8)$
  - 当 $k >= 2$ 时：

  $
  T(4k+2) = 1 + T(2k+1)
  $

  $
  T(4k+4) = 1 + T(2k+2)
  $

  接下来只需要证明：

  $
  T(2k+1) >= T(2k + 2)
  $

  1. $k = 2m, forall m = 1, 2, 3, ...$

  $T(2k+1) = T(4m+1)= 1+T(4m) = 2 + T(2m) >= 1 + T(2m+1) = T(4m+2)$

  2. $k = 2m-1, forall m = 1, 2, 3, ...$

  $
  T(2k+1) = T(4m-1) = 1 + T(4m) = 2 + T(2m)>= 1 + T(2m+1) = T(4m+2)
  $

  所以：$T(2k+1) >= T(2k + 2)$ 得证

  所以，根据数学归纳法： $T(4k+2) >= T(4k+4)$ 得证

  引理2证明完毕。

  由此，我们完成了对以上贪心算法正确性的证明。其时间复杂度为 $log(n)$

]
