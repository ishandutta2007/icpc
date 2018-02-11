const int kN = 20000 + 5;

struct kNode {
    kNode *fa,*go[26];
    int val;
    kNode(int _val = 0) : fa(0),val(_val) {
        memset(go,0,sizeof(go));
    }
};
kNode *root,*last,pool[kN],*bat;

void extend(int c) {
    kNode *p = last;
    kNode *np = new(bat++) kNode(p->val+1);
    while (p && p->go[c] == 0) {
        p->go[c] = np; p = p->fa;
    }
    if (p == 0) {
        np->fa = root;
    } else {
        kNode *q = p->go[c];
        if (p->val+1 == q->val) {
            np->fa = q;
        } else {
            kNode *nq = new(bat++) kNode(p->val+1);
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
