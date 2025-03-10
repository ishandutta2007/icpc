# 斯特林数

## 第一类斯特林数

第一类斯特林数可以定义为对应下降阶乘的展开式的各项系数, 即

$x^{\underline{n}}=x\cdot(x-1)\cdot..\cdot(x-n+1)=\sum_{k=0}^{n}s(n,k)x^k$

其中$s(n,k) (0 \leq k \leq n)$即为第一类斯特林数.

例: $x^{\underline{3}}=x(x-1)(x-2)=0\cdot x^0+2\cdot x^1-3\cdot x^2+1\cdot x^3$

由此可知, $s(n,k)$是代数数, 或称为有符号(第一类)斯特林数.

有符号(第一类)斯特林数的绝对值$|s(n,k)|$可以看作(或直接定义为)把$n$个元素排列成$k$个非空圆圈(循环排列)的方案数. 或称无符号第一类斯特林数.

无符号第一类斯特林数一般记为$c(n,k)$或$\begin{bmatrix}n\\k\end{bmatrix}$.

无符号第一类斯特林数可以定义为对应上升阶乘的展开式的各项系数, 即

$x^{\overline{n}}=x\cdot(x+1)\cdot..\cdot(x+n-1)=\sum_{k=0}^{n}\begin{bmatrix}n\\k\end{bmatrix}x^k$

有符号斯特林数与无符号斯特林数存在以下关系:

$s(n,k)=(-1)^{n-k}\begin{bmatrix}n\\k\end{bmatrix}$

无符号斯特林数有如下递推式:

$\begin{bmatrix}n+1\\k\end{bmatrix}=n\begin{bmatrix}n\\k\end{bmatrix}+\begin{bmatrix}n\\k-1\end{bmatrix}$

其中$k\gt 0$, 且初始条件为$\begin{bmatrix}0\\0\end{bmatrix}=1, \begin{bmatrix}n\\0\end{bmatrix}=\begin{bmatrix}0\\n\end{bmatrix}=0 (n\gt 0)$.

有符号斯特林数有如下递推式:

$s(n+1,k)=-n\cdot s(n,k)+s(n,k-1)$

## 第二类斯特林数

第二类斯特林数可以用下降阶乘定义为:

$x^n=\sum_{k=0}^{n}\begin{Bmatrix}n\\k\end{Bmatrix}x^{\underline{k}}=\sum_{k=0}^{n}\begin{Bmatrix}n\\k\end{Bmatrix}\binom{x}{k}k!$

其中$\begin{Bmatrix}n\\k\end{Bmatrix}$即为第二类斯特林数, 或记为$S(n,k)$. 等式最右侧常用于对形如$x^n$的贡献进行分解.

第二类斯特林数可以看作(或定义为)将含有$n$个元素的集合拆为$k$个非空集合的方案数.

第二类斯特林数可以使用如下公式进行计算:

$\begin{Bmatrix}n\\k\end{Bmatrix}=\frac{1}{k!}\sum_{i=0}^{k}(-1)^i\binom{k}{i}(k-i)^n=\sum_{i=0}^{k}\frac{(-1)^i}{i!}\frac{(k-i)^n}{(k-i)!}$

于是可以通过一次多项式卷积对所有的$k$算出$\begin{Bmatrix}n\\k\end{Bmatrix} (0 \leq k \leq n)$.

第二类斯特林数有如下递推式:

$\begin{Bmatrix}n+1\\k\end{Bmatrix}=k\begin{Bmatrix}n\\k\end{Bmatrix}+\begin{Bmatrix}n\\k-1\end{Bmatrix}$

其中$k\gt 0$且初始条件为$\begin{Bmatrix}0\\0\end{Bmatrix}=1,\begin{Bmatrix}0\\n\end{Bmatrix}=\begin{Bmatrix}n\\0\end{Bmatrix}=0(n\gt 0)$

### 其他性质

贝尔数($B_n$, 基数为$n$的集合的划分方案数)与第二类斯特林数有如下关系:

$B_n=\sum_{k=0}^{n}\begin{Bmatrix}n\\k\end{Bmatrix}$


# Reference 

https://zh.wikipedia.org/wiki/%E6%96%AF%E7%89%B9%E7%81%B5%E6%95%B0
