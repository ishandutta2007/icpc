#include <stdio.h>
#include <string.h>
#include <algorithm>

struct Node {
    Node *go[28],*pr;
    int val;
    int cnt;
    int deg;

    Node(int _val = 0) {
        //memset(go,0,sizeof(go));
        pr = NULL;
        val = _val;
        deg = 0;
        cnt = 0;
    }
} pool[1000000 + 5],*bat,*root,*last;

void sam_init() {
    bat = pool;
    root = new(bat++) Node;
    last = new(bat++) Node(1);
    last->pr = root;
}

void extend(int c) {
    Node *p = last;
    Node *np = new(bat++) Node(p->val + 1);
    while (p && p->go[c] == 0) {
        p->go[c] = np; p = p->pr;
    }
    if (p == 0) {
        np->pr = root;
    } else {
        Node *q = p->go[c];
        if (p->val + 1 == q->val) {
            np->pr = q;
        } else {
            Node *nq = new(bat++) Node(p->val + 1);
            memcpy(nq->go,q->go,sizeof(q->go));
            nq->pr = q->pr;
            q->pr = nq;
            np->pr = nq;
            while (p && p->go[c] == q) {
                p->go[c] = nq;
                p = p->pr;
            }
        }
    }
    last = np;
}

int n,m;
char sa[200000 + 5],sb[200000 + 5];

Node *que[1000000 + 5];

void prepare() {
    int qf = 0,qe = 0;
    for (int i = 0; i < bat - pool; ++ i) {
        if (pool[i].pr)
            pool[i].pr->deg ++;
    }
    for (int i = 0; i < bat - pool; ++ i) {
        if (pool[i].deg == 0) {
            que[qe++] = pool + i;
            pool[i].cnt = 1;
        }
    }
    while (qf != qe) {
        Node *u = que[qf++];
        if (u->pr) {
            u->pr->cnt += u->cnt;
            if (--u->pr->deg == 0)
                que[qe++] = u->pr;
        }
    }
}

int main() {
    sam_init();
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%s",sa);
        for (int j = 0; sa[j]; ++ j)
            extend(sa[j] - 'a');
        extend(26);
        for (int j = 0; sa[j]; ++ j)
            extend(sa[j] - 'a');
        extend(27);
    }
    prepare();
    scanf("%d",&m);
    for (int i = 0; i < m; ++ i) {
        scanf("%s%s",sa,sb);
        Node *cur = root;
        for (int j = 0; sb[j]; ++ j) {
            if (cur) cur = cur->go[sb[j] - 'a'];
        }
        if (cur) cur = cur->go[26];
        for (int j = 0; sa[j]; ++ j) {
            if (cur) cur = cur->go[sa[j] - 'a'];
        }
        int answer = 0;
        if (cur) answer = cur->cnt;
        printf("%d\n",answer);
    }
}
