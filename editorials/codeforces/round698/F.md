[Link](https://codeforces.com/contest/1477/problem/F)
Status: Under construction.
Code: Not implemented yet.

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
### The first part: $n=1$
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
&=\sum_{i=0}^{z}(-1)^i\binom{t+1}{i}(1-is)^t,
\end{array}$$
where $z=\lfloor\frac{1}{s}\rfloor$.

TBD QwQ.