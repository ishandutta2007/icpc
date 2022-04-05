# Matroid

## Definition

Matroid is a pair $<X, I>$ where $X$ is called ground set and $I$ is set of all independent subsets of $X$.

## Axiomatic properties

1. $\emptyset$ is independent.
2. Any subset of independent set is independent.
3. If independent set $A$ has smaller size than independent set $B$, there exists at least one element in $B$ that can be added into $A$ without loss of independency.

## Ranking function

Ranking function $r(S)$ tells maximum size of independent size for some $S$, which is a subset of ground set.

## Rado-Edmonds algorithm

Can be seen as a generization of Kruskal's minimum spanning tree algorithm.

# Matroid intersection

## Formulation

Given two matroids $M_1=<X,I_1>$ and $M_2=<X,I_2>$, we are to find any set $S$ with $\max_{S\in{I_1\cap I_2}}{|S|}$.

## Min-max theorem

$\max_{S\in{I_1\cap I_2}}{|S|}=\min_{U\subseteq X}{(r_1(U)+r_2(X\backslash U))}$

## Terminology

$D_{(M_1,M_2)}{(S)}$ is the exchange graph $G = (S \cup (X\backslash S), E)$ where:
- $(x,y)\in E \Leftrightarrow x\in S, y\in (X\backslash S), S-x+y\in I_1$.
- $(y,x)\in E \Leftrightarrow x\in S, y\in (X\backslash S), S-x+y\in I_2$.


$y\in Y_1 \Leftrightarrow y\in (X\backslash S), S+y\in I_1$.

$y\in Y_2 \Leftrightarrow y\in (X\backslash S), S+y\in I_2$.


## Algorithm

Start with an empty $S$ and then repeat the following until we fail to do this:

1. Build exchange graph $D_{(M_1,M_2)}{(S)}$.
2. Find "free to include vertices" sets $Y_1$ and $Y_2$.
3. Find augmenting path without shortcuts $P$ from any element in $Y_1$ to any element in $Y_2$.
4. Alternate inclusion into $S$ of all elements in $P$.

## Extend to weighted version

When finding augmenting path, minimize pair $(Weight, NumOfEdges)$.

# Puzzles

Weighted matroid intersection: http://codeforces.com/contest/1556/problem/H

# Reference

https://codeforces.com/blog/entry/69287
