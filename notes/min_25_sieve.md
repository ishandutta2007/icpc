# min_25筛
## 求不超过 $n$ 的质数数量, $n\le10^{11}$

首先, 我们形式化定义一下埃氏筛函数:

$g(k,n)=\sum_{i=2}^n[mindiv(i)\gt p_k \vee isprime(i)],$

其中 $mindiv(i)$ 是 $i$ 的最小的质因子, $p_k\ (k=1,2,\cdots)$ 是第 $k$ 小的质数, $isprime(i)$ 对于质数返回 $True$ 否则 $False$. 这个函数简单说就是埃氏筛到第 $k$ 个质数后剩下的数的数量.

### 定理1 
有如下等式成立

$$g(k,n)=\left\{\begin{array}{ll}g(k-1,n)-g(k-1,\lfloor \frac{n}{p_k}\rfloor)+g(k-1,p_{k-1}),& p_k^2\le n\\
g(k-1,n),& p_k^2\gt n\end{array}\right.$$

### 证明
分析转移:

当 $p_k^2\gt n$ 时, $p_k$ 不会筛掉任何一个数, 所以有 $g(k,n)=g(k-1,n)$.

当 $p_k^2\le n$ 时, 我们有

$$\begin{array}{ll}g(k,n)&=g(k-1,n)-\sum_{i=2}^n[mindiv(i)=p_k\wedge \neg isprime(i)]\\
&=g(k-1,n)-\sum_{q=2}^{\lfloor \frac{n}{p_k}\rfloor}[mindiv(q)\ge p_k\wedge \neg isprime(p_k\cdot q)]\\
&=g(k-1,n)-\sum_{q=2}^{\lfloor \frac{n}{p_k}\rfloor}[mindiv(q)\ge p_k]\\
&=g(k-1,n)-\sum_{q=2}^{\lfloor \frac{n}{p_k}\rfloor}[mindiv(q)\gt p_{k-1}\vee isprime(q)]\ +\sum_{q=2}^{\min(\lfloor \frac{n}{p_k}\rfloor,p_{k-1})}[isprime(q)]\\
&=g(k-1,n)-g(k-1,\lfloor \frac{n}{p_k}\rfloor)+\sum_{q=2}^{p_{k-1}}[isprime(q)]\\
&=g(k-1,n)-g(k-1,\lfloor \frac{n}{p_k}\rfloor)+\sum_{q=2}^{p_{k-1}}[mindiv(q)\gt p_{k-1}\vee isprime(q)]\\
&=g(k-1,n)-g(k-1,\lfloor \frac{n}{p_k}\rfloor)+g(k-1,p_{k-1}).\end{array}$$

定义 $\pi_k(n)=\sum_{i=2}^n[isprime(i)]\cdot i^k$. 有 $\pi(n)\equiv\pi_0(n)$ 即为所求.

由定义知 $\pi(n)=g(k',n)$, 其中 $k'$ 为最大的满足 $p_k^2\le n$ 的 $k$.

观察 [[#定理1]] 可知, $g(\cdot,\cdot)$ 仅在形如 $\lfloor\frac{n}{i}\rfloor$ 处取值, 故只有 $O(\sqrt{n})$ 种.

使用 [[#定理1]] 直接算的复杂度是 $O(\frac{n^{\frac{3}{4}}}{log(n)})$. 不会证.
