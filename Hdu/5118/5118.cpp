#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
typedef long long LL;

#define snuke(it,x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end();\
            ++ it)

const int N = 100000 + 5;

struct Integer {
    int value;
    Integer(int _value = 0)
        : value(_value) {}
    Integer operator + (const Integer &t) const {
        Integer ret(value+t.value);
        if (ret.value > (int)1e8)
            ret.value = (int)1e8+1;
        return ret;
    }
    bool operator < (const Integer &t) const {
        return value < t.value;
    }
    int operator () () {
        return value;
    }
};

struct Node *nill;
struct Node {
    Node *ch[2];
    int lazy,val;
    Integer sz;
}pool[N*50],*bat,*dot[N];

int n,m,nq,kind[N];
std::vector<std::pair<int,int> > edges[N];

void newNode(Node *&o) {
    o = bat ++;
    o->ch[0] = o->ch[1] = nill;
    o->lazy = o->val = 0;
    o->sz = Integer(1);
}

void init() {
    bat = pool;
    newNode(nill);
    nill->sz = Integer(0);
}

Node *copy(Node *o) {
    if (o->sz() == 0) return nill;
    Node *ret = bat ++;
    ret->ch[0] = o->ch[0];
    ret->ch[1] = o->ch[1];
    ret->lazy = o->lazy;
    ret->val = o->val;
    ret->sz = o->sz;
    return ret;
}

Node *make(Node *o,int dt) {
    if (o->sz() == 0) return nill;
    Node *ret = copy(o);
    ret->val += dt;
    ret->lazy += dt;
    return ret;
}

Node *down(Node *o) {
    Node *ret = copy(o);
    ret->lazy = 0;
    ret->ch[0] = make(o->ch[0],o->lazy);
    ret->ch[1] = make(o->ch[1],o->lazy);
    return ret;
}

unsigned ran() {
    static unsigned ranx = 123456789;
    return ranx += ranx<<2|1;
}

bool lor(int a,int b) {
    return ran()%(a+b)<a;
}

void merge(Node *&o,Node *a,Node *b) {
    if (a->sz() == 0) {
        o = b;
    } else if (b->sz() == 0) {
        o = a;
    } else if (lor(a->sz(),b->sz())) {
        o = down(a);
        merge(o->ch[1],o->ch[1],b);
        o->sz = o->ch[0]->sz + Integer(1) + o->ch[1]->sz;
    } else {
        o = down(b);
        merge(o->ch[0],a,o->ch[0]);
        o->sz = o->ch[0]->sz + Integer(1) + o->ch[1]->sz;
    }
}

void prepare() {
    static int que[N],degree[N];
    int qf = 0,qe = 0;
    std::fill(degree,degree+n+1,0);
    for (int u = 1; u <= n; ++ u) {
        snuke(it,edges[u]) {
            int v = it->second;
            degree[v] ++;
        }
    }
    que[qe++] = 1;
    while (qf != qe) {
        int u = que[qf++];
        snuke(it,edges[u]) {
            int v = it->second;
            if (--degree[v] == 0) {
                que[qe++] = v;
            }
        }
    }
    for (int I = qe-1; I >= 0; -- I) {
        int u = que[I];
        std::sort(edges[u].begin(),edges[u].end());
        dot[u] = nill;
        snuke(it,edges[u]) {
            int v = it->second;
            merge(dot[u],dot[u],dot[v]);
            if (dot[u]->sz() > (int)1e8) break;
        }
        dot[u] = make(dot[u],1);
        if (kind[u] == 1) {
            Node *t;
            newNode(t);
            merge(dot[u],t,dot[u]);
        }
    }
}

int query(int K) {
    Node *o = dot[1];
    int tmp = 0;
    while (K) {
        if (o->ch[0]->sz() + 1 == K) {
            return o->val + tmp;
        }
        tmp += o->lazy;
        if (o->ch[0]->sz() >= K) {
            o = o->ch[0];
        } else {
            K -= o->ch[0]->sz() + 1;
            o = o->ch[1];
        }
    }
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        printf("Case #%d:\n",++ca);
        scanf("%d%d%d",&n,&m,&nq);
        init();
        for (int i = 2; i <= n; ++ i) {
            scanf("%d",kind+i);
        }
        std::fill(edges,edges+n+1,std::vector<std::pair<int,int> >());
        for (int i = 0; i < m; ++ i) {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            edges[a].push_back(std::make_pair(c,b));
        }
        prepare();
        while (nq--) {
            int K;
            scanf("%d",&K);
            if (dot[1]->sz() < K) {
                puts("-1");
                continue;
            }
            printf("%d\n",query(K));
        }
    }
    return 0;
}
