#include <bits/stdc++.h>

const int N = 100000 + 5;
const int INF = 0x3f3f3f3f;

struct Node *nill;
struct Node {
    Node *fa,*ch[2];
    bool rev_tag;
    int val,min_val;

    Node(int _val = INF) {
        rev_tag = false;
        fa = ch[0] = ch[1] = nill;
        val = min_val = _val;
    }

    void up() {
        if (this == nill) return ;
        min_val = std::min(val,std::min(ch[0]->min_val,ch[1]->min_val));
    }

    void down() {
        if (this == nill || !rev_tag) return ;
        rev_tag = false;
        ch[0]->rev();
        ch[1]->rev();
    }

    void rev() {
        std::swap(ch[0],ch[1]);
        rev_tag ^= 1;
    }

    bool d() {
        return fa->ch[1] == this;
    }

    bool isroot() {
        return fa == nill || fa->ch[0] != this && fa->ch[1] != this;
    }

    void setc(Node *p,int c) {
        ch[c] = p;
        p->fa = this;
        up();
    }

    void rot() {
        Node *f = fa,*ff = fa->fa;
        int c = d(),cc = fa->d();
        f->setc(ch[c ^ 1],c);
        this->setc(f,c ^ 1);
        if (ff->ch[cc] == f) ff->setc(this,cc);
        else this->fa = ff;
    }

    void D() {
        if (this == nill) return ;
        fa->D();
        down();
    }

    Node *splay() {
        D();
        while (!isroot()) {
            if (!fa->isroot()) {
                d() == fa->d() ? fa->rot() : rot();
            }
            rot();
        }
        return this;
    }

    Node *access() {
        for (Node *p = this,*q = nill; p != nill; q = p,p = p->fa)
            p->splay()->setc(q,1);
        return splay();
    }

    void link(Node *p) {
        make_root()->fa = p;
    }

    Node* make_root() {
        access()->rev();
        return this;
    }
};

Node pool[N << 1],*bat,*node[N];
std::vector<int> edges[N];
std::vector<std::pair<int,int>> queries[N];
int n,m,nq;
int answer[N];

struct Bit {
    int C[N];

    void modify(int p,int dt) {
        for (int i = p; i > 0; i -= i & -i) C[i] += dt;
    }

    int query(int p) {
        int ret = 0;
        for (int i = p; i <= n; i += i & -i) ret += C[i];
        return ret;
    }

    void clear() {
        std::fill(C,C + n + 1,0);
    }
} bit;

void lct_init() {
    bat = pool;
    nill = new(bat++) Node;
    nill->ch[0] = nill->ch[1] = nill->fa = nill;

    for (int i = 1; i <= n; ++ i) {
        node[i] = new(bat++) Node;
    }
}

Node *get_min(Node *o) {
    Node *ret = o;
    while (o != nill) {
        if (o->val < ret->val) {
            ret = o;
        }
        if (o->ch[0]->min_val < o->ch[1]->min_val) {
            o = o->ch[0];
        } else {
            o = o->ch[1];
        }
    }
    return ret;
}

void modify(int l,int r) {
    Node *a = node[l]->make_root();
    Node *b = node[r]->access();
    if (a->isroot()) {
        Node *t = new(bat++) Node(l);
        t->link(b);
        a->link(t);
    } else {
        Node *p = get_min(b)->splay();
        p->ch[0]->fa = nill;
        p->setc(nill,0);
        p->ch[1]->fa = nill;
        p->setc(nill,1);
        bit.modify(p->val,-1);
        p->val = p->min_val = l;
        p->link(b);
        a->link(p);
    }

    bit.modify(l,1);
}

void work() {
    lct_init();
    bit.clear();

    for (int i = 1; i <= n; ++ i) {
        for (int l : edges[i]) {
            modify(l,i);
        }
        for (auto q : queries[i]) {
            answer[q.second] = n - bit.query(q.first);
        }
    }
}

int main() {
    while (scanf("%d%d%d",&n,&m,&nq) == 3) {
        for (int i = 1; i <= n; ++ i) {
            edges[i].clear();
            queries[i].clear();
        }
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b);
            if (a > b) std::swap(a,b);
            if (a < b) {
                edges[b].push_back(a);
            }
        }
        for (int i = 0; i < nq; ++ i) {
            int l,r;
            scanf("%d%d",&l,&r);
            queries[r].push_back({l,i});
        }
        work();
        for (int i = 0; i < nq; ++ i) {
            printf("%d\n",answer[i]);
        }
    }
}
