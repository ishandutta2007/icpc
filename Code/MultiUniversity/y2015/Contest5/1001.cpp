#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
typedef unsigned long long LL;

const int N = 90000 + 5;

struct Node {
    Node *fa,*go[26];
    LL ways[26];
    LL way;
    int dis;
    bool vis;
    Node(int _dis = 0) : fa(0),dis(_dis),way(1),vis(false) {
        memset(go,0,sizeof(go));
        memset(ways,0,sizeof(ways));
    }
} pool[N << 1],*bat,*last,*root;

void extend(int c) {
    Node *p = last;
    Node *np = new(bat++) Node(p->dis + 1);
    while (p && p->go[c] == 0) {
        p->go[c] = np; p = p->fa;
    }
    if (p == 0) {
        np->fa = root;
    } else {
        Node *q = p->go[c];
        if (p->dis + 1 == q->dis) {
            np->fa = q;
        } else {
            Node *nq = new(bat++) Node(p->dis + 1);
            memcpy(nq->go,q->go,sizeof(q->go));
            nq->fa = q->fa;
            q->fa = nq;
            np->fa = nq;
            while (p && p->go[c] == q) {
                p->go[c] = nq;
                p = p->fa;
            }
        }
    }
    last = np;
}

void dfs(Node *u) {
    if (u->vis) {
        return ;
    }
    u->vis = true;
    for (int c = 0; c < 26; ++ c) {
        if (u->go[c] == NULL) {
            u->ways[c] ++;
        } else {
            dfs(u->go[c]);
            u->way += u->go[c]->way;
            for (int t = 0; t < 26; ++ t) {
                u->ways[t] += u->go[c]->ways[t];
            }
        }
    }
}

void construct(char *str) {
    bat = pool;
    root = last = new(bat++) Node;
    for ( ; *str; ++ str) {
        extend(*str - 'a');
    }
    dfs(root);
}

char A[N],B[N];
LL cnt[26];

LL work() {
    construct(B);
    for (int c = 0; c < 26; ++ c) {
        if (root->go[c]) {
            cnt[c] = root->go[c]->way;
        } else {
            cnt[c] = 0;
        }
    }
    construct(A);
    LL ret = root->way;
    for (int c = 0; c < 26; ++ c) {
        ret += root->ways[c] * cnt[c];
    }
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%s%s",A,B);
        printf("%I64u\n",work());
    }
}
