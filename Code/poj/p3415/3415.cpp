#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef long long LL;

const int N = 100000 + 5;
char sa[N],sb[N];
int K;

struct Node {
    Node *go[26],*par;
    int val;
    int deg;
    int sz;
    Node (int _val = 0) : par(0),val(_val) {
        memset(go,0,sizeof(go));
    }
} *root,*last,pool[N * 5],*bat;

void sam_init() {
    bat = pool;
    root = new(bat++) Node;
    last = new(bat++) Node(1);
    last->par = root;
}

void extend(int c) {
    Node *p = last;
    Node *np = new(bat++) Node(p->val + 1);
    while (p && p->go[c] == 0) {
        p->go[c] = np; p = p->par;
    }
    if (p == 0) {
        np->par = root;
    } else {
        Node *q = p->go[c];
        if (q->val == p->val + 1) {
            np->par = q;
        } else {
            Node *nq = new(bat++) Node(p->val + 1);
            memcpy(nq->go,q->go,sizeof(q->go));
            nq->par = q->par;
            q->par = nq;
            np->par = nq;
            while (p && p->go[c] == q) {
                p->go[c] = nq; p = p->par;
            }
        }
    }
    last = np;
}

Node *que[N * 5];

LL calc() {
    for (Node *i = pool; i < bat; ++ i)
        i->deg = i->sz = 0;
    for (Node *i = pool; i < bat; ++ i)
        if (i->par)
            i->par->deg ++;
    int qf = 0,qe = 0;
    for (Node *i = pool; i < bat; ++ i) {
        if (i->deg == 0) {
            i->sz = 1;
            que[qe++] = i;
        }
    }
    LL ret = 0;
    while (qf != qe) {
        Node *u = que[qf++];
        int r = u->val;
        int l = 1;
        if (u->par)
            l = u->par->val + 1;
        if (l < K) 
            l = K;
        if (l <= r)
            ret += (r - l + 1) * 1ll * u->sz * (u->sz - 1) / 2;
        if (u->par) {
            u->par->sz += u->sz;
            if (--u->par->deg == 0)
                que[qe++] = u->par;
        }
    }
    return ret;
}

LL work() {
    sam_init();
    for (int i = 0; sa[i]; ++ i)
        extend(sa[i] - 'a');
    LL ret = -calc();
    last = new(bat++) Node(last->val + 1);
    last->par = root;
    for (int i = 0; sb[i]; ++ i)
        extend(sb[i] - 'a');
    ret += calc();
    sam_init();
    for (int i = 0; sb[i]; ++ i)
        extend(sb[i] - 'a');
    ret -= calc();
    return ret;
}

int main() {
    while (scanf("%d",&K) == 1) {
        if (K == 0) break;
        scanf("%s%s",sa,sb);
        printf("%lld\n",work());
    }
    return 0;
}
