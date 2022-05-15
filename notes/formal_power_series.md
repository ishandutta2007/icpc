# 形式幂级数

$\sum_{i=0}^{\infty}{x^i}=\frac{1}{1-x}$

$\sum_{i=0}^{\infty}{a^ix^i}=\frac{1}{1-ax}$

$\sum_{i=0}^{\infty}{x^{ik}}=\frac{1}{1-x^k}$

$\sum_{i=0}^{\infty}{c^ix^{ik}}=\frac{1}{1-cx^k}$

$\sum_{i=0}^{\infty}{\frac{x^i}{i!}}=e^x$

$x\frac{\partial}{\partial{x}}\sum_{i=0}^{\infty}{a_ix^i}=\sum_{i=0}^{\infty}{ia_ix^i}$

$\sum_{i=0}^{n}{\binom{n}{i}(-x)^i}=(1-x)^n$

$\sum_{i=0}^{\infty}{\binom{n+i}{i}x^i}=\frac{1}{(1-x)^{n+1}}$

平移: $[x^n]x^tF(x)=F[n-t]$

拉伸: $F(x^k)=\sum_{i=0}^{\infty}{F[i]x^{ik}}$

$\sum_{i=0}^{\infty}{\frac{a^{\underline{i}}}{i!}x^i}=(1+x)^a$

$ln(\frac{1}{1-x})=\sum_{i=1}^{\infty}{\frac{x^i}{i}}$

$ln(F(x))=-\sum_{i=1}^{\infty}{\frac{(1-F(x))^i}{i}}$

$e^{F(x)}=\sum_{i=0}^{\infty}{\frac{F(x)^i}{i!}}$


## 一些特殊情形下 EGF 与 OGF 的转化

首先定义 $F_{exp}(x)=\sum_{i=0}^{\infty}\frac{f_ix^i}{i!}$ 和 $F(x)=\sum_{i=0}^{\infty}f_ix^i$.

以下式子常用于已知EGF表示, 需要求OGF表示(或反过来)的场合.

$F_{exp}(x)=\sum_{i}A_ie^{C_ix}\Leftrightarrow F(x)=\sum_{i}\frac{A_i}{1-C_ix}$.

$F_{exp}(x)=\sum_{i}x^{D_i}e^{C_ix}\Leftrightarrow F(x)=\sum_{i}\frac{D_i!x^{D_i}}{(1-C_ix)^{D_i+1}}$.


## Taylor shift

以下讨论一个从 $F(x)=\sum_{i=0}^{n-1}a_ix^i$ 变换到 $F(x+t)=\sum_{i=0}^{n-1}b_ix^i$ 的办法.

[source](https://codeforces.com/blog/entry/99646)

泰勒展开的算子形式: $e^{tD}F(x)=F(x+t)$, 其中 $D=\frac{d}{dx}$, $F(x)$ 为形式幂级数(实际上, 条件为解析函数).

定义形式幂级数环上的两个线性算子:

Borel 算子: $\mathcal{B}(x^i)=\frac{x^i}{i!}$.

Laplace 算子: $\mathcal{L}(x^i)=i!x^i$.

容易看出有 $\mathcal{B}(\mathcal{L}(F(x)))=\mathcal{L}(\mathcal{B}(F(x)))=F(x)$ 成立.

另一个重要的观察是,

$$D^i\mathcal{B}(x^j)=\frac{x^{j-i}}{(j-i)!}=\mathcal{B}(x^{j-i}),$$

泛化可得:

$$D^i\mathcal{B}(F(x))=\mathcal{B}(x^{-i}F(x))$$

对任意的形式幂级数 $F(x)$ 成立. 这里我们定义 对于所有的 $i\gt j$ 有 $(j-i)!=\infty$. 因此有 $\mathcal{B}(x^k)=0,\forall k\lt 0$.

由于Borel算子的线性性, 可以更进一步泛化得到:

$$G(D)\mathcal{B}(F(x))=\mathcal{B}(G(x^{-1})F(x))$$
对任意的形式幂级数 $F(x)$ 和 $G(x)$ 成立.

结合第一条性质以及泰勒展开, 我们得到:

$$F(x+t)=e^{tD}F(x)=e^{tD}\mathcal{B}(\mathcal{L}(F(x)))=\mathcal{B}(e^{tx^{-1}}\mathcal{L}(F(x))).$$
