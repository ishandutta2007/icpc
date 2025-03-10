# 线性规划的对偶
## 标准形式的线性规划
考虑标准形式的线性规划问题

$$\begin{array}{ll} minimize & c^Tx\\
subject\ to & Ax=b\\
&x\succeq 0,\end{array}$$
其中, 不等式约束函数为 $f_i(x)=-x_i,\ i=1,\cdots,n$. 为了推导Lagrange函数, 对 $n$ 个不等式约束引入Lagrange乘子 $\lambda_i$, 对等式约束引入Lagrange乘子 $v_i$, 我们得到

$$L(x,\lambda,v)=c^Tx-\sum_{i=1}^{n}\lambda_ix_i+v^T(Ax-b)=-b^Tv+(c+A^Tv-\lambda)^Tx.$$
对偶函数为

$$g(\lambda,v)=\inf_xL(x,\lambda,v)=-b^Tv+inf_x(c+A^Tv-\lambda)^Tx,$$
可以很容易确定对偶函数的解析表达式, 因为线性函数只有恒为 $0$ 时才有下界. 因此,

$$g(\lambda,v)=\left\{\begin{array}{ll}-b^Tv, & A^Tv-\lambda+c=0\\
-\infty, & \mbox{其他情况}.\end{array}\right.$$
注意到对偶函数 $g$ 只有在 $R^n\times R^p$ 上的一个正常仿射子集上才是有限值.

对偶问题可以重写为如下标准形式

$$\begin{array}{ll}minimize & b^Tv\\
subject\ to & A^Tv-\lambda+c=0\\
& \lambda\succeq 0.\end{array}$$
## 不等式形式线性规划的Lagrange对偶
类似地, 我们可以写出不等式形式的线性规划问题

$$\begin{array}{ll}minimize & c^Tx\\
subject\ to & Ax\preceq b\end{array}$$
的Lagrange对偶问题. Lagrange函数为

$$L(x,\lambda)=c^Tx+\lambda(Ax-b)=-b^T\lambda+(A^T\lambda+c)^Tx,$$
所以对偶函数为

$$g(\lambda)=\inf_xL(x,\lambda)=-b^T\lambda+\inf_x(A^T\lambda+c)^Tx,$$
同样, 若线性函数不是恒值, 则线性函数的下确界是 $-\infty$, 因此上述问题的对偶函数为

$$g(\lambda)=\left\{\begin{array}{ll}-b^T\lambda, & A^T\lambda+c=0\\
-\infty, & \mbox{其他情况}.\end{array}\right.$$
称对偶变量 $\lambda$ 是可行的, 如果 $\lambda \succeq 0$ 且 $A^T\lambda+c=0$.

和前面一样, 对偶问题可以重写为如下标准形式

$$\begin{array}{ll}minimize & b^T\lambda\\
subject\ to & A^T\lambda+c=0\\
& \lambda\succeq 0.\end{array}$$

