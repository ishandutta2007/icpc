#include <bits/stdc++.h>
using LL = long long;

const int N = 50000 + 5;
LL answer;
int n,m;
std::vector<int> edges[N];

struct Node *nill;
struct Node {
	Node *ch[2],*fa;
	int val,cnt,sbt,lazy;
	LL sum,pairs;
	void show() {
		//printf("isroot=%d val=%d cnt=%d sbt=%d lazy=%d sum=%I64d pairs=%I64d\n",\
				isroot(),val,cnt,sbt,lazy,sum,pairs);
	}
	bool isroot() {
		return fa==nill || fa->ch[0]!=this && fa->ch[1]!=this;
	}
	bool d() {
		return fa->ch[1]==this;
	}
	void up() {
		if (this==nill) return ;
		sum = ch[0]->sum + ch[1]->sum + (LL)cnt*val;
	}
	void make(int dt) {
		if (this == nill) return ;
		pairs += (LL)cnt*dt*2;
		sbt += dt;
		lazy += dt;
	}
	void down() {
		if (lazy) {
			ch[0]->make(lazy);
			ch[1]->make(lazy);
			lazy = 0;
		}
	}
	void D() {
		if (!isroot()) fa->D();
		down();
	}
	void setc(Node *p,int c) {
		ch[c] = p;
		p->fa =this;
		up();
	}
	void rot() {
		Node *f = fa,*ff = fa->fa;
		int c = d(),cc = fa->d();
		f->setc(ch[c^1],c);
		this->setc(f,c^1);
		if (ff->ch[cc]==f) ff->setc(this,cc);
		else this->fa = ff;
	}
	Node *splay() {
		for (D(); !isroot(); rot())
			if (!fa->isroot())
				d()==fa->d() ? fa->rot() : rot();
		return this;
	}
	Node *access() {
		for (Node *p = this,*q = nill; p != nill; q = p,p = p->fa) {
			if (q != nill) {
				while (q->ch[0] != nill) q = q->ch[0];
				q->splay();
			}
			p->splay();
			p->cnt = p->sbt - q->sbt;
			p->setc(q,1);
		}
		return splay();
	}
	Node *get_fa() {
		if (ch[0] == nill) return fa;
		Node *p = ch[0];
		while (p->ch[1] != nill) p = p->ch[1];
		return p;
	}
}dot[N];

void dfs(int u) {
	dot[u].cnt = 1;
	dot[u].pairs = 1;
	for (int v : edges[u]) {
		dfs(v);
		dot[u].pairs += (LL)dot[u].cnt*dot[v].cnt*2;
		dot[u].cnt += dot[v].cnt;
	}
	dot[u].sbt = dot[u].cnt;
	dot[u].up();
	answer += dot[u].pairs * dot[u].val;
}

void move(int v,int u) {
	dot[u].access(); dot[v].splay();
	if (dot[v].fa == nill)
		std::swap(u,v);
	//printf("u = %d,v = %d\n",u,v);

	Node *f = dot[v].get_fa()->access();
	f->cnt -= dot[v].sbt;
	f->make(-dot[v].sbt);
	f->up();
	answer -= f->sum * dot[v].sbt * 2;

	//printf("half = %lld\n",answer);

	dot[u].access();
	//printf("u = %d\n",u);
	//dot[u].show();
	answer += dot[u].sum * dot[v].sbt * 2;
	dot[u].make(dot[v].sbt);
	dot[u].cnt += dot[v].sbt;
	dot[u].up();
	dot[v].fa = dot+u;
	//printf("final = %lld\n",answer);
}

int main() {
	scanf("%d",&n);
	nill = dot;
	for (int i = 0; i <= n; ++ i) {
		dot[i].ch[0] = dot[i].ch[1] = dot[i].fa = nill;
	}
	for (int i = 2; i <= n; ++ i) {
		int x;
		scanf("%d",&x);
		edges[x].push_back(i);
		dot[i].fa = dot+x;
	}
	for (int i = 1; i <= n; ++ i) {
		scanf("%d",&dot[i].val);
	}
	dfs(1);
	printf("%.13f\n",(double)answer/n/n);
	//printf("answer = %lld\n",answer);
	scanf("%d",&m);
	while (m--) {
		char op[2];
		int a,b;
		scanf("%s%d%d",op,&a,&b);
		if (op[0] == 'P') {
			move(a,b);
		} else {
			dot[a].access();
			answer += (LL)(b-dot[a].val)*dot[a].pairs;
			dot[a].val = b;
			dot[a].up();
		}
		printf("%.13f\n",(double)answer/n/n);
		//printf("answer = %lld\n",answer);
		/*for (int i = 1; i <= n; ++ i) {
			dot[i].show();
		}*/
	}
	return 0;
}
