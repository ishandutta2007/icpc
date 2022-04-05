# 牛顿恒等式

https://en.wikipedia.org/wiki/Newton%27s_identities

## Elementary symmetric polynomial

https://en.wikipedia.org/wiki/Elementary_symmetric_polynomial

### Definition

The elementary symmetric polynomials in $n$ variables $x_1, x_2, ..., x_n$, written $e_k(x_1,x_2,...,x_n)$ for $k=0,1,2,...,n$, are defined by

$e_0(x_1,x_2,...,x_n)=1$,

$e_1(x_1,x_2,...,x_n)=\sum_{1\leq j\leq n}{x_j}$,

$e_2(x_1,x_2,...,x_n)=\sum_{1\leq j\lt k\leq n}{x_jx_k}$,

$e_3(x_1,x_2,...,x_n)=\sum_{1\leq j\lt k\lt l\leq n}{x_jx_kx_l}$,

$...$

$e_k(x_1,x_2,...,x_n)=\sum_{1\leq j_1\lt j_2\lt ...\lt j_k\leq n}{x_{j_1}x_{j_2}...x_{j_k}}$,

so that $e_k(x_1,x_2,...,x_n)=0$ if $k\gt n$.

### Properties

$\Pi_{j=1}^{n}{(\lambda-x_j)}=\lambda^n-e_1(x_1,x_2,...,x_n)\lambda^{n-1}+e_2(x_1,x_2,...,x_n)\lambda^{n-2}+...+(-1)^ne_n(x_1,x_2,...,x_n)=\sum_{i=0}^{n}{(-1)^ie_i(x_1,x_2,...,x_n)\lambda^{n-i}}$

## Complete homogeneous symmetric polynomial

https://en.wikipedia.org/wiki/Complete_homogeneous_symmetric_polynomial

### Definition

The complete homogeneous symmetric polynomial of degree $k$ in $n$ variables $x_1,x_2,...,x_n$, written $h_k$ for $k=0,1,2,...$, is the sum of all monomials of total degree $k$ in the variables.

Formally,

$h_k(x_1,x_2,...,x_n)=\sum_{1\leq j_1\leq j_2\leq...\leq j_k \leq n}{x_{j_1}x_{j_2}...x_{j_k}}$.

The formula can also be written as:

$h_k(x_1,x_2,...x_n)=\sum_{l_1+l_2+...+l_n=k,l_i\geq 0}{x_1^{l_1}x_2^{l_2}...x_n^{l_n}}$.

Yet another form:

$h_k(x_1,x_2,...,x_n)=\sum_{1\leq j_1,j_2,...,j_k\leq n}{\frac{m_1!m_2!...m_n!}{k!}x_{j_1}x_{j_2}...x_{j_k}}$,

here $m_p$ is the multiplicity of number $p$ in the sequence ${j_1,j_2,...,j_k}$.

### Properties

#### Generating function

$\sum_{k=0}^{\infty}{h_k(x_1,x_2,...,x_n)t^k}=\Pi_{i=1}^{n}\sum_{j=0}^{\infty}{(x_it)^j}=\Pi_{i=1}^{n}{\frac{1}{1-x_it}}$

#### Relation with the elementary symmetric polynomials

$\sum_{i=0}^{m}{(-1)^ie_i(x_1,x_2,...,x_n)h_{m-i}(x_1,x_2,...,x_n)=0}$ for all $m > 0$.

Proof:

$\sum_{k=0}^{\infty}{e_k(x_1,x_2,...,x_n)(-t)^k}=\Pi_{i=1}^{n}{(1-x_it)}$,

$[x^m](\sum_{k=0}^{\infty}{e_k(x_1,x_2,...x_n)(-t)^k})(\sum_{k=0}^{\infty}{h_k(x_1,x_2,...x_n)t^k})=[x^m](\Pi_{i=1}^{n}{(1-x_it)})(\frac{1}{\Pi_{i=1}^{n}{(1-x_it)}})=[x^m]{(1)}=[m=0]$,

extract coefficients on both sides for $m\gt 0$ and the prove done.

#### Relation with the Stirling numbers

$h_k(x_1,x_2,...,x_n)=\begin{Bmatrix}n+k \\ n\end{Bmatrix}$,

$e_k(x_1,x_2,...,x_n)=\begin{bmatrix}n+1 \\ n+1-k\end{bmatrix}$.

#### Relation with power sums

$kh_k=\sum_{i=1}^{k}{h_{k-i}p_i}$

## Power sums

$p_k(x_1,x_2,...,x_n)=\sum_{i=1}^{n}{x_i^k}$.

## Newton's identities

$ke_k(x_1,x_2,...,x_n)=\sum_{i=1}^{k}{(-1)^{i-1}e_{k-i}(x_1,x_2,...,x_n)p_i(x_1,x_2,...,x_n)}$, valid for all $n\geq1$.
