Source: https://atcoder.jp/contests/arc136/tasks/arc136_f

是一道生成函数题.

与 [\[ZJOI2019\]开关](https://www.luogu.com.cn/problem/P5326) 几乎一致, 除了最后的DP部分.

## Problem description

给定一个 $H\times W$ 的 $01$ 网格和其每个格子的初始状态($0\ or\ 1$), 和目标状态集 $T$. $T$ 由整数序列 $A_1,A_2,\cdots,A_H$ 描述: 要求目标状态里的第 $i$ 行具有恰好 $A_i$ 个 $1$.

重复以下操作:

等概率随机选择一个格子, 将其值翻转 ($0\rightarrow 1\ or\ 1\rightarrow 0$).

问第一次到达任意目标状态的期望操作次数. 对 $998244353$ 取模.

$1\le H,\ W\le 50.$

## Solution
定义 $f_i$ 表示从起始状态出发走 $i$ 步后到达任意目标状态的概率.

定义 $g_i$ 表示从任意目标状态出发走 $i$ 步后到达任意目标状态的概率.

定义 $h_i$ 表示从起始出发走 $i$ 步后**第一次**到达任意目标状态的概率.

$f,g,h$ 可用其对应OGF形式关联:

$$G(x)H(x)=F(x),$$
其中

$$\begin{array}{l}
F(x)=\sum_{i=0}^{\infty}f_ix^i,\\
G(x)=\sum_{i=0}^{\infty}g_ix^i,\\
H(x)=\sum_{i=0}^{\infty}h_ix^i.\\
\end{array}$$
那么我们有

$$H(x)=\frac{F(x)}{G(x)},$$
所求期望为 $H'(1)$.

以下研究如何求 $F(x)$, 对于 $G(x)$ 可使用类似技术求出.

我们考虑算出每行对应的GF, 相乘得到整体的GF. 由于不同行的操作间具有顺序, 此处我们需要在EGF体系下计算.

对于一个格子, 其翻转奇数次的EGF为 $E_{odd}(x)=\frac{e^{\frac{x}{HW}}-e^{-\frac{x}{HW}}}{2}$, 翻转偶数次的EGF为 $E_{even}(x)=\frac{e^{\frac{x}{HW}}+e^{-\frac{x}{HW}}}{2}$.

那么通过枚举每行里 $0\rightarrow 1$ 的次数, 我们可以得到以下形式:

$$F_{exp}(x)=\Pi\sum E_{odd}(x)^aE_{even}(x)^b=2^{-HW}\sum_{k=-HW}^{HW}coef_{f,k}e^{\frac{kx}{HW}},$$
其中 $F_{exp}(x)=\sum_{i=0}^{\infty}f_i\frac{x^i}{i!}$ 是 $f$ 序列的EGF形式.

但我们实际上需要的是其OGF形式, 也就是 $F(x)=\sum_{i=0}^{\infty}f_ix^i$.

观察 $e^{kx}=\sum_{i=0}^{\infty}\frac{k^ix^i}{i!}$ 和 $\frac{1}{1-kx}=\sum_{i=0}^{\infty}k^ix^i$ 的对应项系数知, 对于 $e^{kx}$ 的线性组合, 我们直接将 $e^{kx}$ 替换为 $\frac{1}{1-kx}$, 就可以实现EGF到OGF的转换.

所以有

$$F(x)=2^{-HW}\sum_{k=-HW}^{HW}coef_{f,k}\frac{1}{1-\frac{k}{HW}x},$$
相应地, 有

$$G(x)=2^{-HW}\sum_{k=-HW}^{HW}coef_{g,k}\frac{1}{1-\frac{k}{HW}x}.$$
回到式 $H(x)=\frac{F(x)}{G(x)}$, 由于 $G(x)$ 中含有 $\frac{1}{1-x}$ 项, 直接求导代 $1$ 会导致其不收敛. 所以我们对上下式同乘 $(1-x)$ 再处理:

$$H'(1)=(\frac{(1-x)F(x)}{(1-x)G(x)})'|_{x=1}.$$
令 $U(x)=(1-x)F(x),\ V(x)=(1-x)G(x)$, 于是

$$\begin{array}{ll}H'(1)&=(\frac{U(x)}{V(x)})'|_{x=1}\\
&=\frac{U'(x)V(x)-U(x)V'(x)}{V(x)^2}|_{x=1}\\
&=\frac{U'(1)V(1)-U(1)V'(1)}{V(1)^2}.\end{array}$$
其中

$$\begin{array}{ll}U(1)&=(1-x)F(x)|_{x=1}\\
&=2^{-HW}\sum_{k=-HW}^{HW}coef_{f,k}\frac{1-x}{1-\frac{k}{HW}x}|_{x=1}\\
&=2^{-HW}coef_{f,HW}\\
&=2^{-HW}|T|,
\end{array}$$
式中 $T$ 是目标状态集, $V(1)$ 与 $U(1)$ 具有相似的形式

$$V(1)=(1-x)G(x)|_{x=1}=2^{-HW}|T|,$$

以及
$$\begin{array}{ll}
U'(1)&=((1-x)F(x))'|_{x=1}\\
&=(2^{-HW}\sum_{k=-HW}^{HW}coef_{f,k}\frac{1-x}{1-\frac{k}{HW}x})'|_{x=1}\\
&=2^{-HW}\sum_{k=-HW}^{HW-1}coef_{f,k}(\frac{1-x}{1-\frac{k}{HW}x})'|_{x=1}\\
&=2^{-HW}\sum_{k=-HW}^{HW-1}coef_{f,k}\frac{1}{\frac{k}{HW}-1},\\
\end{array}$$
$V'(1)$ 与 $U'(1)$ 具有相似的形式

$$V'(1)=((1-x)G(x))'|_{x=1}=2^{-HW}\sum_{k=-HW}^{HW-1}coef_{g,k}\frac{1}{\frac{k}{HW}-1},$$

于是有

$$\begin{array}{ll}
H'(1)&=\frac{U'(1)-V'(1)}{2^{-HW}|T|}\\
&=\frac{\sum_{k=-HW}^{HW-1}(coef_{f,k}+coef_{g,k})\frac{1}{\frac{k}{HW}-1}}{|T|}\\
&=\frac{1}{|T|}\sum_{k=-HW}^{HW-1}(coef_{f,k}+coef_{g,k})\frac{HW}{k-HW},
\end{array}$$

~~然后力气大一点硬DP就完了.~~

DP的时候要注意对每行先展开再乘, 由于每行展开只有 $O(W)$ 项, 整体复杂度是 $O((HW)^2)$.