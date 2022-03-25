[link](https://atcoder.jp/contests/arc135/tasks/arc135_f)

## Problem description
Given an integer $N$. On an integer sequence $A=(1,2,\cdots,N)$, do the operations below exactly $K$ times.

- Let $n$ be the current number of terms in $A$. For all $i$ such that $1\le i\le n$ and $i\equiv 1 \mod 3$, delete the $i$-th term of $A$, simultaneously.

Find the sum of the terms of $A$ after $K$ operations, modulo $998244353$.

## Contraints
- $1\le N \le 10^{14}$
- $1\le K\le 100$

## Solution
We discuss on $0$-base. So after one operation, $(0,1,2,3,4,5,6,7,\cdots)$ will become $(1,2,4,5,7,\cdots)$.

Let $f(i)$ be the index of the $i$-th element before exactly one operation. Magically, we have

$$\begin{array}{ll}
f(i)&=3\lfloor\frac{i}{2}\rfloor+(i\mod 2)+1\\
&=3\lfloor\frac{i}{2}\rfloor+(i-2\lfloor\frac{i}{2}\rfloor)+1\\
&=\lfloor\frac{i}{2}\rfloor+i+1\\
&=\lfloor\frac{3i+2}{2}\rfloor.
\end{array}$$
The result is 

$$\sum_{i=0}^{n-1}(f^K(i)+1),\tag{1.1}$$ ^c5f980

where $n$ is the number of rest numbers after $K$ operations.

### If $K$ is large
If $K$ is large, then $n\approx N\cdot(\frac{2}{3})^K$ is small, we can just calculate according to the definition [[#^c5f980|(1.1)]], resulting in a complexity of $O(KN\cdot(\frac{2}{3})^K)$. It's suitable to apply this method if $K\gt 40$, roughly.

### If $K$ is small
#### An $O(K\cdot 2^K)$ algorithm

Observe $f(i+2)$:

$$\begin{array}{ll}
f(i+2)&=\lfloor\frac{3(i+2)+2}{2}\rfloor\\
&=\lfloor\frac{3i+2}{2}\rfloor+3\\
&=f(i)+3.
\end{array}$$
Observe $f(i+2^t)$:

$$\begin{array}{ll}
f(i+2^t)&=\lfloor\frac{3(i+2^t)+2}{2}\rfloor\\
&=\lfloor\frac{3i+2}{2}\rfloor+3\cdot 2^{t-1}\\
&=f(i)+3\cdot 2^{t-1}.
\end{array}$$
Observe $f^t(i+2^t)$:

$$\begin{array}{ll}
f^t(i+2^t)&=f^{t-1}(f(i)+3\cdot 2^{t-1})\\
&=f^t(i)+3^t,
\end{array}$$
Actually, it's in this form:

$$f^t(i)=f^t(i\mod 2^t)+\lfloor\frac{i}{2^t}\rfloor\cdot3^t.$$

So we classify $i$ according to their remainder when dividing $2^K$:

$$\begin{array}{ll}
\sum_{i=0}^{n-1}f^K(i)&=\sum_{r=0}^{2^K-1}\sum_{j=0,r+j\cdot 2^K\lt n}f^K(r+j\cdot 2^K)\\
&=\sum_{r=0}^{2^K-1}\sum_{j=0}^{\lfloor\frac{n-1-r}{2^K}\rfloor}(f^K(r)+j\cdot 3^K)\\
&=\sum_{r=0}^{2^K-1}((y_r+1)f^K(r)+\frac{y_r(y_r+1)}{2}\cdot 3^K),
\end{array}$$
where $y_r=\lfloor\frac{n-1-r}{2^K}\rfloor$.

#### An $O((K+\log(n))\cdot2^{\frac{K}{2}})$ algorithm

Consider $f^K(i)=f^P(f^Q(i))$, where $P=\lceil\frac{K}{2}\rceil$ and $Q=\lfloor\frac{K}{2}\rfloor$:

$$\begin{array}{ll}
\sum_{i=0}^{n-1}f^K(i)&=\sum_{i=0}^{n-1}f^P(f^Q(i))\\
&=\sum_{r=0}^{2^Q-1}\sum_{j=0}^{\lfloor\frac{n-1-r}{2^Q}\rfloor}f^P(f^Q(r+j\cdot 2^Q))\\
&=\sum_{r=0}^{2^Q-1}\sum_{j=0}^{\lfloor\frac{n-1-r}{2^Q}\rfloor}f^P(f^Q(r)+j\cdot 3^Q)\\
&=\sum_{r=0}^{2^Q-1}\sum_{j=0}^{\lfloor\frac{n-1-r}{2^Q}\rfloor}(f^P(f^Q(r)+j\cdot 3^Q \mod 2^P)+\lfloor\frac{f^Q(r)+j\cdot 3^Q}{2^P}\rfloor\cdot 3^P)\\
&=\sum_{r=0}^{2^Q-1}\sum_{j=0}^{\lfloor\frac{n-1-r}{2^Q}\rfloor}(g^P(f^Q(r)+j\cdot 3^Q \mod 2^P)+\frac{f^Q(r)+j\cdot 3^Q}{2^P}\cdot 3^P),
\end{array}$$
where $g^P(i)=f^P(i)-\frac{i}{2^P}\cdot 3^P$.

We can precompute $f^Q(\cdot), f^P(\cdot), g^P(\cdot), \sum_{j=0}^{2^t}g^P((\cdot)+j\cdot 3^Q)$, then binary lifting should work.

