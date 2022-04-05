# The admissibility theorem for ordinary generating functions

https://ac.cs.princeton.edu/home/

The construtions of union, cartesian product, sequence, powerset, multiset, and cycle are all admissible. The associated operators are as follows.

Sum: $\mathcal{A}=\mathcal{B}+\mathcal{C} \Rightarrow A(z)=B(z)+C(z)$

Cartesian product: $\mathcal{A}=\mathcal{B}\times \mathcal{C} \Rightarrow A(z)=B(z)\cdot C(z)$

Sequence: $\mathcal{A}=SEQ(\mathcal{B}) \Rightarrow A(z)=\frac{1}{1-B(z)}$

Powerset(01-knapsack): $\mathcal{A}=PSET(\mathcal{B}) \Rightarrow A(z)=\left\{ \begin{array}{**rcl**}\Pi_{n\ge 1}(1+z^n)^{B[n]} &\\ exp(\sum_{k=1}^{\infty}{\frac{(-1)^{k+1}}{k}{B(z^k)}})\end{array}\right.$

Multiset(unbounded-knapsack): $\mathcal{A}=MSET(\mathcal{B}) \Rightarrow A(z)=\left\{ \begin{array}{**rcl**}\Pi_{n\ge 1}(1-z^n)^{-B[n]} &\\ exp(\sum_{k=1}^{\infty}\frac{1}{k}B(z^k))\end{array}\right.$

Cycle: $\mathcal{A}=CYC(\mathcal{B}) \Rightarrow A(z)=\sum_{k=1}^{\infty}{\frac{\phi(k)}{k}\ln\frac{1}{1-B(z^k)}}$

For the sequence, powerset, multiset, and cycle translations, it is assumed that $\mathcal{B}_0=\emptyset$.
