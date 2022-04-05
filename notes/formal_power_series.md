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
