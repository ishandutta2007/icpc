# 题意

  [https://atcoder.jp/contests/arc145/tasks/arc145_f]()
  
给定 $N, M, P$, 问对于每个 $K \in [0,P-1]$, 有多少个序列 $A=(A_1,A_2,\cdots,A_n)$ 满足:
- $A_i\le A_{i+1}$.
- $A_i$ 是 $[0,M]$ 中的一个整数.
- $\sum_i A_i\equiv K \mod P$.

答案对 $998244353$ 取模.

数据范围:
- $1\le N,M\le 10^6$
- $1\le P \le 500$

# 题解

首先, 我们把 $A_i$ 变成 $A_i'=A_i+i-1$, 这样条件中的 $\le$ 就变成了 $\lt$, 而 $A_i'$ 的范围就变成了 $[0,M'=M+N)$.  在以后的讨论中我们用 $A'$ 和 $M'$ 替代原题设中的 $A$ 和 $M$.

那么我们就是要算多项式 $f(x)=[u^N]\Pi_{i=0}^{M-1}(1+x^iu) \mod (x^P - 1)$.

## 当 $M=PQ$, Q为整数

此时有:

$$\begin{array}{ll}
f(x)&=[u^N]\Pi_{i=0}^{PQ-1}(1+x^iu) \mod (x^P - 1)\\
&= [u^N]\Pi_{i=0}^{P-1}\Pi_{j=0}^{Q-1}(1+x^{jP+i}u) \mod (x^P - 1)\\
&= [u^N]\Pi_{i=0}^{P-1}\Pi_{j=0}^{Q-1}(1+x^{i}u) \mod (x^P - 1)\\
&= [u^N]\Pi_{i=0}^{P-1}(1+x^{i}u)^Q \mod (x^P - 1)\\
&= [u^N](\Pi_{i=0}^{P-1}(1+x^{i}u))^Q \mod (x^P - 1).
\end{array}$$

由于 $P$  很小, 我们来试试看单位根魔法.

定义符号 $\omega$, 满足 $\omega^{P}-1=0$ 且对于整数 $t\in [0,P-1]$, 有 $\omega^{tP}-1\ne 0$.

定义函数 $g(t)$:
$$g(t)=f(\omega^t)=[u^N](\Pi_{i=0}^{P-1}(1+\omega^{it}u))^Q \mod (\omega^{tP} - 1)=[u^N](\Pi_{i=0}^{P-1}(1+\omega^{it}u))^Q.$$
接下来我们要能够快速算出 $g(0), g(1), \cdots, g(P-1)$ 并对其使用傅立叶逆变换得到原来的 $f$.

定义多项式 $h(t)=\Pi_{i=0}^{P-1}(1+\omega^{it}u)$.

若一个单位根 $\omega^{n}$ 满足 $gcd(n,P)=1$, 则 $\omega^n$ 被称为本原单位根. 而非本原单位根都可以由本原单位根生成.

在这个题中, 我们最终要将 $\omega$ 都消掉, 所以本原单位根之间没有区别.

于是, 令 $c(t)=gcd(t,P)$, 有 $(\omega^{c(t)})^{\frac{P}{c(t)}}=1$. 我们对 $h(t)$ 中的单位根分类:

$$\begin{array}{ll}
h(t) &= \Pi_{i=0}^{P-1}(1+\omega^{it}u)\\
&= \Pi_{i=0}^{P-1}(1+\omega^{ic(t)}u)\\
&= \Pi_{i=0}^{\frac{P}{c(t)}-1}(1+\omega^{ic(t)}u)^{c(t)}.
\end{array}$$

由代数基本定理, 有等式 $x^n-1=\Pi_{i=0}^{n-1}(x-\omega^i)$. 于是:

$$\begin{array}{ll}
h(t) &= \Pi_{i=0}^{\frac{P}{c(t)}-1}(1+\omega^{ic(t)}u)^{c(t)}\\
&= ((-u)^{\frac{P}{c(t)}}\Pi_{i=0}^{\frac{P}{c(t)}-1}(-\frac{1}{u}-\omega^{ic(t)}))^{c(t)}\\
&= ((-u)^{\frac{P}{c(t)}}((-\frac{1}{u})^{\frac{P}{c(t)}}-1))^{c(t)}\\
&= (1-(-u)^{\frac{P}{c(t)}})^{c(t)}.
\end{array}$$

总结一下得到:

$$g(t)=[u^N]h(t)^Q=[u^N](1-(-u)^{\frac{P}{gcd(t,P)}})^{gcd(t,P)\cdot Q},$$

再进行二项式展开.

于是 $g(0),g(1),\cdots,g(P-1)$ 可以在 $O(P^2)$ 内得出. 另有 $g(P)=g(0)$.

然后进行傅立叶逆变换:

$$[x^i]f(x)=\frac{1}{P}\sum_{j=0}^{P-1}g(j)\omega^{-ij}.$$
还是之前对单位根的观察: 若 $gcd(i,P)=gcd(j,P)$, 那么有 $g(i)=g(j)=g(gcd(i,P))$. 于是:

$$\begin{array}{ll}
[x^i]f(x) &= \frac{1}{P}\sum_{j=0}^{P-1}g(j)\omega^{-ij}\\
&= \frac{1}{P}\sum_{c|P}g(c)\sum_{j=1}^{P}\omega^{-ij}[gcd(j,P)=c]\\
&= \frac{1}{P}\sum_{c|P}g(c)\sum_{j=1}^{\frac{P}{c}}\omega^{-ijc}[gcd(j,\frac{P}{c})=1]\\
&= \frac{1}{P}\sum_{c|P}g(c)\sum_{j=1}^{\frac{P}{c}}\omega^{-ijc}\sum_{d|gcd(j,\frac{P}{c})}\mu(d)\\
&= \frac{1}{P}\sum_{c|P}g(c)\sum_{d|\frac{P}{c}}\mu(d)\sum_{j=1}^{\frac{P}{cd}}\omega^{-ijcd}\\
&= \frac{1}{P}\sum_{c|P}g(c)\sum_{d|\frac{P}{c}}\mu(d)\frac{1-\omega^{-iP}}{1-\omega^{-icd}}.
\end{array}$$

如果 $1-\omega^{-icd}\ne 0$, 那么上式的最后一项是 $0$. 所以只用考虑 $1-\omega^{-icd}=0$ 的情况, 此时上式的最后一项等于1, 于是:

$$\begin{array}{ll}
[x^i]f(x) &= \frac{1}{P}\sum_{c|P}g(c)\sum_{d|\frac{P}{c}}\mu(d)[\omega^{-icd}=1]\\
&= \frac{1}{P}\sum_{c|P}g(c)\sum_{d|\frac{P}{c}}\mu(d)[P | icd].
\end{array}$$
## 当 $P\nmid M$

对 $[\lfloor\frac{M}{P}\rfloor\cdot P,M)$ 的部分暴力DP, 跟上一种情形组合一下即可. 


于是就做完了. 时间复杂度 $O(N+M+P^3)$.

# Reference

 感谢叉姐提供的题解. 我写完本篇, 发现自己基本是个翻译.