#include <bits/stdc++.h>

struct Tree {
	Tree *lc,*rc;
	int l,r;
	int v,lazy;
	Tree(int l=0,int r=0)
		:l(l),r(r),v(0),lazy(0) {}
	void build() {
		if (l == r) return ;
		int mid = l+r>>1;
		lc = new Tree(l,mid);
		rc = new Tree(mid+1,r);
		lc->build();
		rc->build();
	}
	void modify(int x,int L,int R) {
		if (L<=l && r<=R) {
			v |= x;
			lazy |= x;
			return ;
		}
		if (R<l || r<L) return ;
		down();
		lc->modify(x,L,R);
		rc->modify(x,L,R);
		v = lc->v & rc->v;
	}
	void down() {
		if (lazy == 0) return ;
		lc->lazy |= lazy;
		lc->v |= lazy;
		rc->lazy |= lazy;
		rc->v |= lazy;
		lazy = 0;
	}
	int query(int L,int R) {
		if (L<=l && r<=R) return v;
		if (R<l || r<L) return (1ll<<31)-1;
		down();
		return lc->query(L,R) & rc->query(L,R);
	}
	void show() {
		if (l == r) {
			printf("%d ",v);
			return ;
		}
		down();
		lc->show();
		rc->show();
	}
};

const int N = 100000 + 5;
int n,m;
int L[N],R[N],Q[N];

int main() {
	scanf("%d%d",&n,&m);
	Tree *tree = new Tree(1,n);
	tree->build();
	for (int i = 0; i < m; ++ i) {
		scanf("%d%d%d",L+i,R+i,Q+i);
		tree->modify(Q[i],L[i],R[i]);
	}
	for (int i = 0; i < m; ++ i) {
		if (tree->query(L[i],R[i]) != Q[i]) {
			puts("NO"); return 0;
		}
	}
	puts("YES");
	tree->show();
	puts("");
	return 0;
}
