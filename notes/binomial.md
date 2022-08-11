# 二项式

$\binom{n}{m}=\frac{n!}{m!(n-m)!}$

对称性: $\binom{n}{m}=\binom{n}{n-m}$

吸收/释放: $\binom{n}{m}=\frac{n}{m}\binom{n-1}{m-1}$

递推: $\binom{n}{m}=\binom{n-1}{m}+\binom{n-1}{m-1}=\frac{n}{m}\binom{n-1}{m-1}$

平行求和: $\sum_{i=0}^{n}{\binom{r+i}{i}}=\sum_{i=0}^{n}{\binom{r+i}{r}}=\binom{r+n+1}{n}$

上指标求和: $\sum_{i=0}^{n}{\binom{i}{m}}=\binom{n+1}{m+1}$

定义 $f_{A,i}=\sum_{j=0}^{A}\binom{i}{j}$, 有递推式 $f_{A,i+1}=2f_{A,i}-\binom{i}{A}$ 成立. 证明概要: 考虑走网格, 从 $i$ 的终点们各走一步.

斐波那契: $\forall n\ge 0, \sum_{i=0}^{n}\binom{n-i}{i}=fib_{n}$. Where $fib_0=fib_1=1,fib_i=fib_{i-1}+fib_{i-2}, \forall i\ge 2$.

范德蒙德卷积: 

$F(x)$ = $(1+x)^{n+m}=(1+x)^n(1+x)^m$

$F[k]$ = $\binom{n+m}{k}=\sum_{i=0}^{k}{\binom{n}{i}\binom{m}{k-i}}$

二项式定理:

$(x+y)^k=\sum_{i=0}^{k}{\binom{k}{i}x^iy^{k-i}}$

$\sum_{i=0}^{n}\binom{n}{i}=2^n$

$\sum_{i\ge 0}\binom{n}{2i}=\sum_{i\ge 0}\binom{n}{2i+1}=2^{n-1}$

容斥系数部分和: $\sum_{i=0}^{k}(-1)^{i}\binom{n}{i}=(-1)^k\binom{n-1}{k}$

广义二项式/广义二项式定理:

$\binom{\alpha}{i}=\frac{\alpha^{\underline{i}}}{i!}$, 其中 $\alpha$ 可以不为整数

$(x+y)^{\alpha}=\sum_{i=0}^{\infty}{\binom{\alpha}{i}x^iy^{\alpha-i}}$

上指标反转: $\binom{r}{k}=(-1)^k\binom{k-r-1}{k}$

$r^{\underline{k}}=(-1)^k(-r)^{\overline{k}}=(-1)^k(k-r-1)^{\underline{k}}$

$\sum_{i=0}^{\infty}{\binom{2i}{i}x^i}=\sum_{i=0}^{\infty}{\binom{-\frac{1}{2}}{i}(-4x)^i}=(1-4x)^{-\frac{1}{2}}$

下降幂和上升幂的二项式定理:

$(x+y)^{\underline{n}}=\sum_{i=0}^{n}{\binom{n}{i}x^{\underline{i}}y^{\underline{n-i}}}$

$(x+y)^{\overline{n}}=\sum_{i=0}^{n}{\binom{n}{i}x^{\overline{i}}y^{\overline{n-i}}}$

(tips: 挪一挪实际上就是范德蒙德卷积)

其他等式:

$\sum_{k=q}^{n}\binom{n}{k}\binom{k}{q}=2^{n-q}\binom{n}{q}$

$\sum_{i=0}^{n}\binom{2n}{i}=2^{2n-1}+\frac{1}{2}\binom{2n}{n}$

$\sum_{i=0}^{n}\binom{2n}{i}^2=\frac{1}{2}(\binom{4n}{2n}+\binom{2n}{n}^2)$

二项式与斯特林数:

$\sum_{i=0}^{n}\binom{n}{i}\cdot i=n\cdot 2^{n-1}$

$\sum_{i=0}^{n}\binom{n}{i}\cdot i^2=(n+n^2)\cdot 2^{n-2}$

一般情形:

$\begin{array}{ll}
\sum_{i=0}^{n}\binom{n}{i}\cdot i^k&=\sum_{i=0}^{n}\binom{n}{i}\sum_{j=0}^{k}\begin{Bmatrix}k\\j\end{Bmatrix}i^{\underline{j}}\\
&=\sum_{i=0}^{n}\binom{n}{i}\sum_{j=0}^{k}\begin{Bmatrix}k\\j\end{Bmatrix}j!\binom{i}{j}\\
&=\sum_{j=0}^{k}\begin{Bmatrix}k\\j\end{Bmatrix}\sum_{i=0}^{n}\binom{n}{i}j!\binom{i}{j}\\
&=\sum_{j=0}^{k}\begin{Bmatrix}k\\j\end{Bmatrix}2^{n-j}j!\binom{n}{j}\\
\end{array}$
