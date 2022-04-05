# 反演

本质上是求逆.

## Formulation

Assume that $f[n] = \sum_{i}{a_{n,i}g[i]}$. Given $f$, find $g$.

## Framework of prove

Assume $Ax=b$, given $b$, find $x$.

At the first step, we find some $B$ s.t. $BA=I$, then:

$x=Ix\iff\\
x=(BA)x\iff\\
x=B(Ax)\iff\\
x=Bb\\
Q.E.D.$

## 二项式反演

### Core formula

$(1 - 1)^n = \sum_{i=0}^{n}{\binom{n}{i}(-1)^i} = [n = 0]$

where $[n = 0]$ means $1$ if $n$ is zero, otherwise $0$.

Given $f[n] = \sum_{i=0}^{n}{\binom{n}{i}g[i]}$, we have:

$g[n] = \sum_{i=0}^{n}{\binom{n}{i}(-1)^{n-i}f[i]}$.

### Prove

$g[n] = \sum_{m=0}^{n}{\binom{n}{m}[n-m=0]g[m]}\iff\\
g[n] = \sum_{m=0}^{n}{\binom{n}{m}\sum_{i=0}^{n-m}{\binom{n-m}{i}(-1)^{i}g[m]}}\iff\\
g[n] = \sum_{i=0}^{n}{\binom{n}{i}(-1)^i\sum_{m=0}^{n-i}{\binom{n-i}{m}g[m]}}\iff\\
g[n] = \sum_{i=0}^{n}{\binom{n}{i}(-1)^if[n-i]}\iff\\
g[n] = \sum_{i=0}^{n}{\binom{n}{n-i}(-1)^{n-i}f[i]}\\
Q.E.D.$

## 莫比乌斯反演

### Core formula

$\sum_{d|n}\mu(d)=[n=1]$.

Given $f[n] = \sum_{d|n}g[d]$, we have:

$g[n] = \sum_{d|n}\mu(\frac{n}{d})f[d]$.

### Prove

$g[n] = \sum_{m|n}[\frac{n}{m}=1]g[m]\iff\\
g[n] = \sum_{m|n}\sum_{d|\frac{n}{m}}\mu(d)g[m]\iff\\
g[n] = \sum_{d|n}\mu(d)\sum_{m|\frac{n}{d}}g[m]\iff\\
g[n] = \sum_{d|n}\mu(d)f[\frac{n}{d}]\iff\\
g[n] = \sum_{d|n}\mu(\frac{n}{d})f[d]\\
Q.E.D.$

## 子集反演 

### Core formula

$\sum_{T\subseteq S}(-1)^{|T|}=[S = \emptyset]$

Given $f[S] = \sum_{T\subseteq S}g[T]$, we have:

$g[S] = \sum_{T\subseteq S}(-1)^{|S|-|T|}f[T]$.

### Prove

$g[S] = \sum_{W\subseteq S}[S\setminus W = \emptyset]g[W]\iff\\
g[S] = \sum_{W\subseteq S}\sum_{T\subseteq {S\setminus W}}(-1)^{|T|}g[W]\iff\\
g[S] = \sum_{T\subseteq S}(-1)^{|T|}\sum_{W\subseteq {S\setminus T}}g[W]\iff\\
g[S] = \sum_{T\subseteq S}(-1)^{|T|}g[S\setminus T]\iff\\
g[S] = \sum_{T\subseteq S}(-1)^{|S|-|T|}g[T]\\
Q.E.D.$

### Applications

#### A1

对于任意的关于集合$S$的函数, 我们有:

$f[S] = \sum_{T\subseteq S}\sum_{P\subseteq T}(-1)^{|T|-|P|}f(P)$

##### Prove

$RHS = \sum_{P\subseteq S}f[P]\sum_{P\subseteq T \subseteq S}(-1)^{|T|-|P|}$

$RHS = \sum_{P\subseteq S}f[P]\sum_{i=0}^{|S|-|P|}\binom{|S|-|P|}{i}(-1)^{i}$

$RHS = \sum_{P\subseteq S}f[P](1 - 1)^{|S|-|P|}$

$RHS = f[S] = LHS$

$Q.E.D.$

##### 相关题目

https://www.luogu.com.cn/problem/P5206

## 单位根反演

### Core formula

$\omega_n$: $n$次单位根 s.t. $\omega_n^n=1$ (e.g. 复数域上的$e^{\frac{2\pi i}{n}}$).

$\frac{1}{n}\sum_{k=0}^{n-1}\omega_n^{vk} = [v\equiv 0\mod n]$

Given $f[m]=\sum_{k=0}^{n-1}\omega_n^{mk}g[k]$, we have:

$g[m]=\frac{1}{n}\sum_{k=0}^{n-1}\omega_n^{-mk}f[k]$.

### Applications

$[p+q\equiv r \mod n]\iff\\
[p+q-r\equiv 0 \mod n]\iff\\
\frac{1}{n}\sum_{k=0}^{n-1}\omega_n^{(p+q-r)k}\iff\\
\frac{1}{n}\sum_{k=0}^{n-1}\omega_n^{-rk}\omega_n^{pk}\omega_n^{qk}$

at where $p,q,r$ looks more independent.

# Reference
[炫酷反演魔术](https://vfleaking.blog.uoj.ac/blog/87)
