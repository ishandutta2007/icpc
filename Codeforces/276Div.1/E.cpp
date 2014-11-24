#include <bits/stdc++.h>

const int N = 100000 + 5;
int n,m,L[N],R[N],W[N],answer[N];
std::pair<int,int> order[N],A[N];

struct Node {
	int l,r,m,len;
	Node(int x = 0) 
		:l(x),r(x),m(x),len(1) {}
	Node operator + (const Node &t) const {
		Node ret;
		ret.l = l;
		ret.r = t.r;
		ret.m = std::max(m,t.m);
		ret.len = len+t.len;
		ret.m = std::max(ret.m,r+t.l);
		if (l == len) ret.l = len+t.l;
		if (t.r == t.len) ret.r = r+t.len;
		return ret;
	}
};

struct SegmentTree {
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
	Node t[N<<2];
	void modify(int pos,int dt,int l,int r,int rt) {
		if (l == r) {
			t[rt] = Node(dt);
			return ;
		}
		int mid = l+r>>1;
		if (pos <= mid) modify(pos,dt,lson);
		else modify(pos,dt,rson);
		t[rt] = t[rt<<1] + t[rt<<1|1];
	}
	Node query(int L,int R,int l,int r,int rt) {
		if (L<=l && r<=R)
			return t[rt];
		int mid = l+r>>1;
		if (L<=mid && mid<R)
			return query(L,R,lson) + query(L,R,rson);
		if (L<=mid)
			return query(L,R,lson);
		return query(L,R,rson);
	}
}sgt;

void work(int low,int high,int ql,int qr) {
	if (low > high) return ;
	if (ql > qr) return ;
	int mid = low+high>>1;
	int l = std::lower_bound(A,A+n,std::make_pair(mid,0)) - A;
	int r = std::upper_bound(A,A+n,std::make_pair(high,n+1)) - A - 1;
	for (int i = l; i <= r; ++ i) {
		sgt.modify(A[i].second,1,1,n,1);
	}
	for (int i = ql; i <= qr; ++ i) {
		int id = order[i].second;
		bool ok = sgt.query(L[id],R[id],1,n,1).m>=W[id];
		order[i].first = ok;
		if (ok) {
			answer[id] = mid;
		}
	}
	int p = ql-1;
	for (int i = ql; i <= qr; ++ i) {
		if (order[i].first == 0)
			std::swap(order[++p],order[i]);
	}
	work(low,mid-1,ql,p);
	for (int i = l; i <= r; ++ i) {
		sgt.modify(A[i].second,0,1,n,1);
	}
	work(mid+1,high,p+1,qr);
}

int main() {
	scanf("%d",&n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d",&A[i].first);
		A[i].second = i+1;
	}
	std::sort(A,A+n);
	scanf("%d",&m);
	for (int i = 0; i < m; ++ i) {
		scanf("%d%d%d",L+i,R+i,W+i);
	}
	for (int i = 0; i < m; ++ i) {
		order[i] = std::make_pair(0,i);
	}
	work(1,(int)1e9,0,m-1);
	for (int i = 0; i < m; ++ i) {
		printf("%d\n",answer[i]);
	}
	return 0;
}
