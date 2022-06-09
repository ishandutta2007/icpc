# The admissibility theorem for exponential generating functions

The **EGF** of a sequence $(A_n)$ is the formal power series

$$A(z)=\sum_{n>=0}A_n\frac{z^n}{n!}.$$

It's also said that the variable $z$ marks $\textit{size}$ in the generating function.

With the standard notation for coefficients of series, the cofficient $A_n$ in an EGF is then recovered by
$$A_n=n!\cdot[z^n]A(z).$$

**Binomial convolutions.** Let $a(z), b(z), c(z)$ be EGFs, with $a(z)=\sum_{n}a_n\frac{z^n}{n!}$, and so on. The binomial convolution formula is:

$$\mbox{if } a(z)=b(z)\cdot c(z),\mbox{ then } a_n=\sum_{i=0}^{n}\binom{n}{i}b_ic_{n-i}.$$


**Basic admissibility, labelled universe.** The constructions of combinatorial sum,  labelled product, sequence, set, and cycle are all admissible. Associated operators on EGFs are:

Sum:  $\mathcal{A}=\mathcal{B}+\mathcal{C}\Rightarrow A(z)=B(z)+C(z)$,

Product: $\mathcal{A}=\mathcal{B}\star\mathcal{C}\Rightarrow A(z)=B(z)C(z)$,

Sequence: $\mathcal{A}=SEQ(\mathcal{B})\Rightarrow A(z)=\frac{1}{1-B(z)}$,

Sequence with $k$ components: $\mathcal{A}=SEQ_k(\mathcal{B})\Rightarrow A(z)=B(z)^k$,

Set: $\mathcal{A}=SET(\mathcal{B})\Rightarrow A(z)=\exp(B(z))$,

Set with $k$ components: $\mathcal{A}=SET_k(\mathcal{B})\Rightarrow A(z)=\frac{1}{k!}B(z)^k$,

Cycle: $\mathcal{A}=CYC(\mathcal{B})\Rightarrow A(z)=\log\frac{1}{1-B(z)}$,

Cycle with $k$ components: $\mathcal{A}=CYC_k(\mathcal{B})\Rightarrow A(z)=\frac{1}{k}B(z)^k$.


