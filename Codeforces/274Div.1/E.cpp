#include <bits/stdc++.h>

const int N = 2000 + 5;

struct SegmentTree {
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
	int t[N<<2];
	void up(int rt) {
		t[rt] = std::min(t[rt<<1],t[rt<<1|1]);
	}
	void build(int *A,int l,int r,int rt) {
		if (l == r) {
			t[rt] = A[l];
			return ;
		}
		int mid = l+r>>1;
		build(A,lson);
		build(A,rson);
		up(rt);
	}
	void modify(int pos,int dt,int l,int r,int rt) {
		if (l == r) {
			t[rt] = dt;
			return ;
		}
		int mid = l+r>>1;
		if (pos <= mid) modify(pos,dt,lson);
		else modify(pos,dt,rson);
		up(rt);
	}
	int query(int L,int R,int l,int r,int rt) {
		if (L<=l && r<=R) 
			return t[rt];
		int mid = l+r>>1;
		if (L<=mid && mid<R)
			return std::min(query(L,R,lson),query(L,R,rson));
		if (L <= mid)
			return query(L,R,lson);
		return query(L,R,rson);
	}
}tree[N];

int n,m,nq;
int down[N][N],right[N][N];
int X[N],Y[N];
char str[N][N];
int answer;
int out[N];

int main() {
	scanf("%d%d%d",&n,&m,&nq);
	for (int i = 0; i < n; ++ i) {
		scanf("%s",str[i]);
	}
	for (int i = 0; i < nq; ++ i) {
		scanf("%d%d",X+i,Y+i); X[i] --; Y[i] --;
		str[X[i]][Y[i]] = 'X';
	}
	for (int i = n-1; i >= 0; -- i) {
		for (int j = m-1; j >= 0; -- j) {
			if (str[i][j] == 'X') {
				down[i][j] = 0;
				right[i][j] = 0;
			} else {
				down[i][j] = down[i+1][j] + 1;
				right[i][j] = right[i][j+1] + 1;
			}
		}
	}
	for (int i = 0; i < n; ++ i) {
		std::stack<std::pair<int,int> > stack;
		for (int j = 0; j < m; ++ j) {
			std::pair<int,int> tmp(down[i][j],j);
			while (!stack.empty() && stack.top().first>=down[i][j]) {
				std::pair<int,int> x = stack.top(); stack.pop();
				answer = std::max(answer,std::min(j-x.second,x.first));
				tmp.second = x.second;
			}
			stack.push(tmp);
		}
		while (!stack.empty()) {
			std::pair<int,int> x = stack.top(); stack.pop();
			answer = std::max(answer,std::min(m-x.second,x.first));
		}
	}
	for (int i = 0; i < n; ++ i) {
		tree[i].build(down[i],0,m-1,1);
	}
	out[nq] = answer;
	for (int t = nq-1; t > 0; -- t) {
		int x = X[t],y = Y[t];
		str[x][y] = '.';
		for (int j = y; j >= 0; -- j) {
			if (str[x][j] == 'X') break;
			right[x][j] = right[x][j+1] + 1;
		}
		int mx = m;
		for (int i = x; i >= 0; -- i) {
			if (str[i][y] == 'X') break;
			down[i][y] = down[i+1][y] + 1;
			tree[i].modify(y,down[i][y],0,m-1,1);
			mx = std::min(mx,right[i][y]);
			int p = mx+y-1;
			while (true) {
				if (p-answer-1+1 < 0) break;
				if (tree[i].query(p-answer-1+1,p,0,m-1,1) >= answer+1)
					answer ++;
				else
					break;
			}
		}
		mx = m;
		for (int i = x; i < n; ++ i) {
			if (str[i][y] == 'X') break;
			mx = std::min(mx,right[i][y]);
			int p = mx+y-1;
			while (true) {
				if (p-answer-1+1 < 0) break;
				if (i < answer+1-1) break;
				if (tree[i-answer-1+1].query(p-answer-1+1,p,0,m-1,1) >= answer+1)
					answer ++;
				else 
					break;
			}
		}
		out[t] = answer;
	}
	for (int i = 0; i <  nq; ++ i) {
		printf("%d\n",out[i+1]);
	}
	return 0;
}
