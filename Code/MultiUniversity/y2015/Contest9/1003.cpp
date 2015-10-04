#pragma comment(linker, "/STACK:1024000000,1024000000") 
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
typedef long long LL;

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

     Node *make_root() {
         access()->rev();
         return this;
     }
};

Node pool[N << 1],*bat,*node[N];
int n;

void lct_init() {
    bat = pool;
    nill = new(bat++) Node;
    nill->ch[0] = nill->ch[1] = nill->fa = nill;

    for (int i = 1; i <= n; ++ i) {
        node[i] = new(bat++) Node;
    }
}

std::vector<int> vd[N];
LL answer[N];

Node *get_min(Node *o) {
    while (true) {
        if (o->val == o->min_val)
            return o;
        if (o->ch[0]->min_val < o->ch[1]->min_val)
            o = o->ch[0];
        else
            o = o->ch[1];
    }
}

void init() {
    n = 100000;
    lct_init();
    for (int i = 1; i <= n; ++ i) {
        for (int j = i + i; j <= n; j += i) {
            vd[j].push_back(i);
        }
    }
    LL cur = 0;
    for (int i = 2; i <= n; ++ i) {
        for (int x : vd[i]) {
            Node *a = node[x];
            Node *b = node[i];
            a->access();
            b->access();
            if (a->fa == nill) {
                Node *t = new(bat++) Node(x);
                t->link(b);
                a->link(t);
                cur += x;
            } else {
                b->make_root();
                a->access();
                if (a->min_val >= x) continue;
                cur += x - a->min_val;
                Node *t = get_min(a)->splay();
                t->ch[1]->fa = nill;
                t->setc(nill,1);
                t->ch[0]->fa = nill;
                t->setc(nill,0);
                t->val = t->min_val = x;
                t->link(b);
                a->link(t);
            }
        }
        answer[i] = cur;
    }
}

int main() {
    init();
    int n;
    while (scanf("%d",&n) == 1) {
        printf("%I64d\n",answer[n]);
    }
}
