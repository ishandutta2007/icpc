# min-max 容斥

let $U$ = {$a_1, a_2, .., a_n$},

$\min(S)$ = $\min_{a_i \in S}{a_i}$,

$\max(S)$ = $\max_{a_i \in S}{a_i}$,

then we have

$\max(S)$ = $\sum_{T \subseteq S}{(-1)^{\vert T \vert +1}\min(T)}$,

$\min(S)$ = $\sum_{T \subseteq S}{(-1)^{\vert T \vert +1}\max(T)}$,

and it has an expectation form:

$E(\max(S))$ = $\sum_{T \subseteq S}{(-1)^{\vert T \vert +1}E(\min(T))}$,

$E(\min(S))$ = $\sum_{T \subseteq S}{(-1)^{\vert T \vert +1}E(\max(T))}$.

We can extend it to kth min/max:

$Kthmax(S)$ = $\sum_{T \subseteq S}{(-1)^{\vert T \vert -k}\binom{\vert T \vert -1}{k-1}\min(T)}$,

$Kthmin(S)$ = $\sum_{T \subseteq S}{(-1)^{\vert T \vert -k}\binom{\vert T \vert -1}{k-1}\max(T)}$,

again, it has an expectation form:

$E(Kthmax(S))$ = $\sum_{T \subseteq S}{(-1)^{\vert T \vert -k}\binom{\vert T \vert -1}{k-1}E(\min(T))}$,

$E(Kthmin(S))$ = $\sum_{T \subseteq S}{(-1)^{\vert T \vert -k}\binom{\vert T \vert -1}{k-1}E(\max(T))}$.

