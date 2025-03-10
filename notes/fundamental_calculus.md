# 微积分基础

求导的线性性:

$(F(x)+G(x))'=F'(x)+G'(x)$

$(c \cdot F(x))'=c \cdot F'(x)$

部分初等函数的导数:

$(C)'=0$

$(x^k)'=kx^{k-1}$

$(e^x)'=e^x$

$(a^x)'=a^x\ln(a)$

$(\ln(x))'=\frac{1}{x}$

$(\log_a(x))'=\frac{1}{x\ln(a)}$

$(\sin(x))'=\cos(x)$

$(\cos(x))'=-\sin(x)$

乘法法则: $(F(x)G(x))'=F'(x)G(x)+F(x)G'(x)$

除法法则: $(\frac{F(x)}{G(x)})'=\frac{F'(x)G(x)-F(x)G'(x)}{G^2(x)}$

莱布尼兹公式: $(\frac{d}{dx})^k(F(x) \cdot G(x))=\sum_{i=0}^{k}{\binom{k}{i}(\frac{d}{dx})^iF(x)(\frac{d}{dx})^{k-i}G(x)}$

链式法则: $\frac{dy}{dx}\frac{d}{dy}=\frac{d}{dx}$

偏导数链式法则: 画出变量的DAG, 对所有路径求和

复合函数求导: $(G(F(x)))'=G'(F(x))F'(x)$

即 $\frac{d}{dx}G(F(x))=\frac{dF(x)}{dx}\frac{d}{dF(x)}G(F(x))=G'(F(x))F'(x)$

反函数(复合逆)求导: $F(x)$的反函数$G(x)$的导数为$\frac{1}{F'(x)}$, 或写作$\frac{dx}{dy}=\frac{1}{\frac{dy}{dx}}$

积分的线性性:

$\int(F(x)+G(x))dx=\int{F(x)dx}+\int{G(x)dx}$

$\int{cF(x)dx}=c\int{F(x)dx}$

积分中的链式法则: $\int{G'(F(x))F'(x)dx}=G(F(x))+C$, 即逆用求导的链式法则

分步积分法: 由$(F(x)G(x))'=F'(x)G(x)+F(x)G'(x)$移项并两边积分得$\int{F'(x)G(x)dx}=F(x)G(x)-\int{F(x)G'(x)dx}$

泰勒展开: $F(x)=\sum_{i=0}^{\infty}{\frac{F^{(i)}(a)}{i!}(x-a)^i}$

麦克劳林级数: 在$x=0$处作泰勒展开, $F(x)=\sum_{i=0}^{\infty}{\frac{F^{(i)}(0)}{i!}x^i}$
