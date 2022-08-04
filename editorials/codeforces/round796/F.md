[https://codeforces.com/contest/1687/problem/F]()

**Status: Under construction.**


# 题意

给出两个整数 $N$ 和 $S$. 对于所有的整数 $K\in [0,N-1]$, 问有多少长度为 $N$ 的排列 $p_1,p_2,\cdots,p_N$ 满足:
- $S=\sum_{i=1}^{N-1}[p_i+1=p_{i+1}]$
- $K=\sum_{i=1}^{N-1}[p_i\lt p_{i+1}]$

答案对 $998244353$ 取模.

限制

- $1\le N \le 250000$
- $0\le S\lt N$

# 题解

## Preliminary

**Eulerian number**

https://en.wikipedia.org/wiki/Eulerian_number

Eulerian number $E(n,m)$ 表示有多少长度为 $n$ 的排列 $p_1,p_2,\cdots,p_N$, 满足恰好有 $m$ 个位置 “上升”, 即 $p_i\lt p_{i+1}$.

整体来说, Eulerian number 可由一个 bivariate generating function 描述.

固定 $n$ 的话有:

$$E_n(t)=\sum_{m=0}^n E(n,m)t^m,$$

而关于 $n$ 的部分需要用指数生成函数描述:

$$E(x,t) = \sum_{n=0}^{\infty}E_n(t)\cdot \frac{x^n}{n!}=\frac{t-1}{t-e^{(t-1)x}}.$$
一般的记法为:

$$E(n,m)=\genfrac<>{0}{}{n}{m}=[\frac{x^n}{n!}][t^m]E(x,t).$$

显式的算式是存在的:

$$E(n,m)=\sum_{k=0}^{m+1}(-1)^k\binom{n+1}{k}(m+1-k)^n.$$
# 正文

令 $f_{N,S}(K)$ 表示原问题的答案. 我们考虑用二项式直接算 $p_i+1=p_{i+1}$ 的部分:

$$f_{N,S}(K)=\binom{N-1}{S}f_{N-S,0}(K-S).$$
简记 $N'=N-S$ 及 $K'=K-S$.

$f_{N',0}(K')$ 表示长度为 $N'$ 的排列, 恰好有 $K'$ 个位置 $i$ 满足 $p_i\lt p_{i+1}$, 且不存在 $p_i+1=p_{i+1}$ 的方案数. 让我们容斥掉第二个限制:

$$\begin{array}{ll}
f_{N',0}(K') &= \sum_{j=0}^{K'}(-1)^{j}\binom{N'-j-1}{j}E(N'-j,K'-j).
\end{array}$$
然后不会了.