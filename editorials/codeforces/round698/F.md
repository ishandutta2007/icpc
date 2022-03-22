[Link](https://codeforces.com/contest/1477/problem/F)
Status: Under construction.
Code: TLEing.

## Problem description
Given $n$ segments with length $l_1,l_2,\cdots,l_n$ and an integer $k$, perform the following operation repeatedly until the maximum length over all segments does not exceed $k$:

- Pick a segment with probability proportional to its length $x$.
- Pick a real number $r\in (0,x)$ uniformly at random, then break the segment into two segments with length $r$ and $x-r$ respectively.

Calculate the expected number of operations under field $\mathtt{F}_{998244353}$.

## Constraints
- $1\le n\le 50$
- $1\le k\le 2000$
- $1\le l_i\le 2000$
- $1\le\sum_{i}l_i\le 2000$

## Solution
### A simpler version: $n=1$
Let $X_0=0\lt X_1\lt X_2\lt\cdots\lt X_t\lt l$ be random variables corresponding to the positions of $t$ operations.

To simplify notation, let $s=\frac{k}{l}$. 

Let $p_t$ be the probability of the event $E=\cap_{i=1}^{t}\{\omega | X_i-X_{i-1}\le s\}\cap \{\omega | 1-X_t\le s\}$.

Take random variables $Y_i$ to be $X_i-X_{i-1}$, then we have

$$E=\cap_{i=1}^{t}\{\omega | Y_i\le s\}\cap\{\omega|\sum_{i=1}^{t}Y_i\ge 1-s\},$$
The joint PDF has the form of

$$f(y_1,y_2,\cdots,y_t)=t!I_{0\le y_i\le 1, \sum_iy_i\le 1},$$
where $I$ is the indicator function.

Then,

$$\begin{array}{ll}
p_t&=t!\int_{0\le y_i\le s, 1-s\le\sum_{y_i}\le 1}dy_1dy_2\cdots dy_t\\
&=t!s^t\int_{0\le y_i\le 1, \frac{1}{s}-1\le\sum_{y_i}\le \frac{1}{s}}dy_1dy_2\cdots dy_t.\end{array}$$

Now we can think $Y_1,Y_2,\cdots,Y_t$ follow $i.i.d$ uniform distribution over $[0,1]$. The sum of $Y_1,Y_2,\cdots,Y_t$ follows exactly the Irwin-Hall distribution whose CDF is 

$$F(x;t)=\frac{1}{t!}\sum_{i=0}^{\lfloor x\rfloor}(-1)^i\binom{t}{i}(x-i)^t.$$
Thus,

$$\begin{array}{ll}
p_t&=t!s^t(F(\frac{1}{s};t)-F(\frac{1}{s}-1;t))\\
&=s^t(\sum_{i=0}^{\lfloor \frac{1}{s}\rfloor}(-1)^i\binom{t}{i}(\frac{1}{s}-i)^t-\sum_{i=0}^{\lfloor \frac{1}{s}\rfloor-1}(-1)^i\binom{t}{i}(\frac{1}{s}-1-i)^t)\\
&=\sum_{i=0}^{z}(-1)^i\binom{t}{i}(1-is)^t-\sum_{i=0}^{z-1}(-1)^i\binom{t}{i}(1-(i+1)s)^t\\
&=\sum_{i=0}^{z}(-1)^i\binom{t}{i}(1-is)^t+\sum_{i=1}^{z}(-1)^i\binom{t}{i-1}(1-is)^t\\
&=\sum_{i=0}^{z}(-1)^i\binom{t+1}{i}(1-is)^t,\tag{1.1}
\end{array}$$

^be26c4

where $z=\lfloor\frac{1}{s}\rfloor$.

### The complete version

Let $q_{j,m}$ be the probability that $m$ operations are peformed on segment $j$ but there still exists segments produced by segment $j$ with length greater than $k$. So we have:

$$\begin{array}{ll}
q_{j,m}&=1-\sum_{i=0}^{\lfloor\frac{l_j}{k}\rfloor}(-1)^i\binom{m+1}{i}(1-\frac{ik}{l_j})^m\\
&=-\sum_{i=1}^{\lfloor\frac{l_j}{k}\rfloor}(-1)^i\binom{m+1}{i}(1-\frac{ik}{l_j})^m
\end{array}$$


Therefore, probability that one fails to finish the task within $m$ rounds is

$$1-\sum_{j_1+j_2+\cdots+j_n=m}\frac{m!}{j_1!j_2!\cdots j_n!}\Pi_{r=1}^{n}(1-q_{r,j_r})(\frac{l_j}{L})^{j_r},$$
where $L=\sum_{r=1}^{n}l_r$.

Let 

$$Q_{r}(x)=\sum_{i=0}^{\infty}\frac{1-q_{r,i}}{i!}(\frac{l_rx}{L})^i,$$
and

$$P_{exp}(x)=e^x-\Pi_{r=1}^{n}Q_{r}(x),$$
then, $P(1)$, where $P(x)$ is the OGF version of $P_{exp}(x)$, is the final result.

Let's focus on rearrange $Q_r(x)$:

$$\begin{array}{ll}
Q_{r}(x)&=\sum_{i=0}^{\infty}\frac{1-q_{r,i}}{i!}(\frac{l_rx}{L})^i\\
&=\sum_{i=0}^{\infty}\frac{1}{i!}(1+\sum_{j=1}^{\lfloor\frac{l_r}{k}\rfloor}(-1)^j\binom{i+1}{j}(1-\frac{jk}{l_r})^i)(\frac{l_rx}{L})^i\\
&=e^{\frac{l_rx}{L}}+\sum_{i=0}^{\infty}\frac{1}{i!}\sum_{j=1}^{\lfloor\frac{l_r}{k}\rfloor}(-1)^j\binom{i+1}{j}(1-\frac{jk}{l_r})^i(\frac{l_rx}{L})^i\\
&=e^{\frac{l_rx}{L}}+\sum_{j=1}^{\lfloor\frac{l_r}{k}\rfloor}(-1)^j\sum_{i=0}^{\infty}\frac{1}{i!}\binom{i+1}{j}(1-\frac{jk}{l_r})^i(\frac{l_rx}{L})^i\\
&=e^{\frac{l_rx}{L}}+\sum_{j=1}^{\lfloor\frac{l_r}{k}\rfloor}(-1)^j\sum_{i=0}^{\infty}\frac{1}{i!}\binom{i+1}{j}(\frac{l_r-jk}{L}x)^i\\
&=e^{\frac{l_rx}{L}}+\sum_{j=1}^{\lfloor\frac{l_r}{k}\rfloor}(-1)^j\sum_{i=j-1}^{\infty}\frac{i+1}{j!(i+1-j)!}(\frac{l_r-jk}{L}x)^i\\
&=e^{\frac{l_rx}{L}}+\sum_{j=1}^{\lfloor\frac{l_r}{k}\rfloor}(-1)^j\sum_{i=j-1}^{\infty}(\frac{i+1-j}{j!(i+1-j)!}(\frac{l_r-jk}{L}x)^i+\frac{j}{j!(i+1-j)!}(\frac{l_r-jk}{L}x)^i)\\
&=e^{\frac{l_rx}{L}}+\sum_{j=1}^{\lfloor\frac{l_r}{k}\rfloor}(-1)^j(\sum_{i=j}^{\infty}\frac{1}{j!(i-j)!}(\frac{l_r-jk}{L}x)^i+\sum_{i=j-1}^{\infty}\frac{1}{(j-1)!(i+1-j)!}(\frac{l_r-jk}{L}x)^i)\\
&=e^{\frac{l_rx}{L}}+\sum_{j=1}^{\lfloor\frac{l_r}{k}\rfloor}(-1)^j(\frac{(\frac{l_r-jk}{L}x)^{j}}{j!}e^{\frac{l_r-jk}{L}x}+\frac{(\frac{l_r-jk}{L}x)^{j-1}}{(j-1)!}e^{\frac{l_r-jk}{L}x})\\
&=e^{\frac{l_rx}{L}}+\sum_{j=1}^{\lfloor\frac{l_r}{k}\rfloor}(-1)^j(\frac{(\frac{l_r-jk}{L})^{j}}{j!}x^j+\frac{(\frac{l_r-jk}{L})^{j-1}}{(j-1)!}x^{j-1})e^{\frac{l_r-jk}{L}x}.\\

\end{array}$$

A trick: If there is a EGF term $x^De^{Cx}$, then the corresponding OGF will be 

$$\begin{array}{ll}
\sum_{i=0}^{\infty}\frac{(D+i)!}{i!}C^ix^{D+i}
&=D!\sum_{i=0}^{\infty}\binom{D+i}{i}C^ix^{D+i}\\
&=D!x^{D}\sum_{i=0}^{\infty}\binom{D+i}{i}(Cx)^i\\
&=\frac{D!x^{D}}{(1-Cx)^{D+1}}.
\end{array}$$
So that $P_{exp}(x)=\sum_{i}\sum_{j}coef_{i,j}x^ie^{jx}$ can be done in $O(nL^2log(L))$, with NTT techs.

Then, it's easy to calculate $P(1)$, all done.

UPD: $O(nL^2log(L))$ is a little slow to pass.
