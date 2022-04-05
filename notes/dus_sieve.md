# 杜教筛

## 前置

### 狄利克雷卷积

狄利克雷卷积是一个作用在数论函数($\mathbb{Z}^{+}\rightarrow\mathbb{C}$)间的二元运算:

$(f\ast g)[n]=\sum_{ij=n}f[i]g[j]$ 或

$(f\ast g)[n]=\sum_{d|n}f[d]g[\frac{n}{d}]$

积性: 若数论函数$f$满足$f[1]=1$且若$p,q$互质有$f[pq]=f[p]f[q]$, 称$f$为积性函数.

狄利克雷卷积保积性: 若$f,g$是积性函数,则$(f\ast g)$也是积性函数.


## 杜教筛

### 问题描述

给出积性函数$f$, 求$S[n]=\sum_{i=1}^{n}f[i]$.

### 算法框架

我们找到另外两个容易算的积性函数$g,h$满足$h=(f\ast g)$.

则 $g[1]S[n]=\sum_{i=1}^{n}h[i] - \sum_{i=2}^{n}g[i]S[\lfloor\frac{n}{i}\rfloor]$.

### 推导过程

$\sum_{i=1}^{n}h[i]\iff\\
\sum_{m=1}^{n}\sum_{i|m}{f[\frac{m}{i}]g[i]}\iff\\
\sum_{i=1}^{n}g[i]\sum_{j=1}^{\lfloor\frac{n}{i}\rfloor}f[j]\iff\\
\sum_{i=1}^{n}g[i]S[\lfloor\frac{n}{i}\rfloor]$

拆出右侧第一项得到:

$g[1]S[n]=\sum_{i=1}^{n}h[i] - \sum_{i=2}^{n}g[i]S[\lfloor\frac{n}{i}\rfloor]$.

## 时间复杂度

假定$\sum_{i=1}^{n}h[i]$和$\sum_{i=l}^{r}g[i]$都能$O(1)$得出, 则算法整体复杂度为$O(n^{\frac{3}{4}})$.

优化: 若先线性预处理出前$n^{\frac{2}{3}}$项, 则算法整体复杂度为$O(n^{\frac{2}{3}})$.

## 常见的积性函数及等式

元函数 $\epsilon: \epsilon[n]=\left\{\begin{array}{l}1, n = 1\\ 0, otherwise\end{array}\right.$

单位常函数 $I: I[n]=1$

恒等函数 $id: id[n]=n$

幂函数 $id_k: id_k[n]=n^k$

约数个数函数 $d: d[n]=\sum_{d|n}1$

约数和函数 $\sigma: \sigma[n]=\sum_{d|n}d$

欧拉函数 $\phi: \phi[n]=\sum_{i=1}^{n}[gcd(n,i)=1]$

莫比乌斯函数 $\mu: \mu[n]=\left\{\begin{array}{l}1, n=1\\(-1)^r, n=\Pi_{i=1}^{r}{p_i^{\alpha_i}},\alpha_i=1\\0,otherwise\end{array}\right.$

$\mu \ast I = \epsilon$

$\phi \ast I = id$

$id \ast \mu = \phi$


# Reference

https://oi-wiki.org/math/number-theory/du/

https://www.cnblogs.com/peng-ym/p/9446555.html

https://zhuanlan.zhihu.com/p/137619492
