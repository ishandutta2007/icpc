**不可约多项式(irreducible polynomial)** 或称**质式**, 是指不可被分解成两个非常数多项式之乘积的非常数多项式. 不可约的性质取决于系数所属于的域或环. 例如, 多项式 $x^2-2$ 在整数上不可约, 但在实数上是可约的, 且分解式为 $(x-\sqrt 2)(x+\sqrt 2)$.



**有理函数(rational function)** 是可以表示为以下形式的函数:

$$f(x)=\frac{a_mx^m+a_{m-1}x^{m-1}+\cdots+a_1x+a_0}{b_nx^n+b_{n-1}x^{n-1}+\cdots+b_1x+b_0}=\frac{P_m(x)}{Q_n(x)};\ m,n\in \mathbb{N}_0,\ b_i\mbox{ 不全为 }0.$$



**部分分式分解** 或 **部分分式展开** 是将有理函数分解成许多次数较低的有理函数的和的形式, 来降低分子或分母多项式的次数. 分解后的分式需满足以下条件:

- 分式的分母需为不可约多项式 (irreducible polynomial) 或其乘幂.
- 分式的分子多项式次数需比其分母多项式次数要低.

具体地说, 部分分式分解就是将 $\frac{P(x)}{Q(x)}$变成等式右边的形式:

$$\frac{P(x)}{Q(x)}=r(x)+\sum_{i}\frac{p_i(x)}{q_i(x)},$$
其中, $r(x)$ 是个多项式, $q_j(x)$ 是某个不可约多项式的幂, 并且满足 $Q(x)=\Pi_i q_i(x)$, 而 $p_j(x)$ 是某个度数小于 $q_j(x)$ 的度数的多项式. 

若仅追求降低次数以减小计算成本, 这里的不可约多项式可以换成 square-free 多项式 (即没有重根的多项式). (不过暂未听说 square-free 在有限域上存在不求出根的做法).

(另, 若 $P(x)$ 的度数小于 $Q(x)$ 的度数, 那直接有 $r(x)=0$.)


然而, 实际上有一个更严格的定理描述:

**定理** 若 $P(x)$ 和 $Q(x)$ 是域 $K$ 上的非零多项式. 把 $Q(x)$ 写成一些两两不同的不可约多项式的乘幂的形式:

$$Q(x)=\Pi_{i=1}^{n}q_i^{b_i}.$$
那么, 存在**唯一**的多项式 $r(x)$ 和 $p_{ij}(x)$ 满足:

$$\frac{F(x)}{G(x)}=r(x)+\sum_{i=1}^{k}\sum_{j=1}^{b_i}\frac{p_{ij}(x)}{q_{i}^j}.$$

且若 $deg(F(x))\lt deg(G(x))$, 那么 $r(x)=0$.

## 一般形式的做法
通分, 对 $x$ 的幂次逐项与 $P(x)$ 对齐, 构造线性系统, 高斯消元求解.


## 特定形式的分解过程

### 情形一

给定两多项式 $P(x)$ 和 $Q(x)=(x-\alpha_1)(x-\alpha_2)\cdots(x-\alpha_n)$, 其中 $\alpha_1,\alpha_2,\cdots,\alpha_n$ 是两两不同的常量, 且 $deg(P(x))\lt n$. 首先假定有如下形式的分解:

$$\frac{P(x)}{Q(x)}=\frac{c_1}{x-\alpha_1}+\frac{c_2}{x-\alpha_2}+\cdots+\frac{c_n}{x-\alpha_n},$$
那么, 该形式具有如下分解算式(该式子据说与拉格朗日插值强相关):

$$\frac{P(x)}{Q(x)}=\sum_{i=1}^{n}\frac{P(\alpha_i)}{Q'(\alpha_i)}\frac{1}{x-\alpha_i},$$
其中, $Q'(x)$ 表示对 $Q(x)$ 求导. 那么在已知所有 $\alpha_i$ 的情况下, 我们只需要对 $P(x)$ 和 $Q'(x)$ 分别做一次多项式多点求值, 就可以得到具体的分解形式. 时间复杂度为 $O(n\log^2(n))$.

(注意若 $deg(P(x))\ge deg(Q(x))$, 先做一次多项式长除法把余数提出, 再进行上述过程).

~~对于分母有重根或有度数高于 $1$ 的不可约多项式因子的情形, 没太研究明白怎么做, 应该还是高斯消元就可以了.~~

### 情形二

若 $P(x)=1$, $Q(x)= \Pi_{i=1}^n\frac{1}{1-\beta_{i}x}, \forall \beta_i\ne 0$. 该情形常见于生成函数理论中. 那么同样, 我们先假定有如下分解式:

$$\begin{array}{ll}
\frac{P(x)}{Q(x)}&=\frac{1}{Q(x)}\\
&=\frac{c_1}{1-\beta_1 x}+\frac{c_2}{1-\beta_2 x}+\cdots+\frac{c_n}{1-\beta_n x}\\
&=\frac{\sum_{i=1}^{n}c_i\Pi_{j!=i}(1-\beta_j x)}{Q(x)}
\end{array},$$
只看分子, 有

$$1=\sum_{i=1}^{n}c_i\Pi_{j!=i}(1-\beta_j x),$$
将 $x=\beta_k^{-1}$ 代入上式, 得到:

$$\begin{array}{ll}
1&=\sum_{i=1}^{n}c_i\Pi_{j!=i}(1-\beta_j\beta_k^{-1})\\
&=c_k\Pi_{j!=k}(1-\beta_j\beta_k^{-1}),
\end{array}$$

移项并整理符号得到

$$c_i=(\Pi_{j!=i}({1-\beta_j\beta_i^{-1}}))^{-1},$$
于是得到一个 $O(n^2)$ 所有 $c_i$ 的做法.

情形一与情形二在域上可互相转化.


## Reference

- [Partial fraction decomposition(wiki)](https://en.wikipedia.org/wiki/Partial_fraction_decomposition)
- [部分分式分解(wiki)](https://zh.wikipedia.org/wiki/部分分式分解)
- [有理函数(wiki)](https://zh.wikipedia.org/wiki/有理函數)
- [不可约多项式(wiki)](https://zh.wikipedia.org/wiki/不可约多项式)
