const int N = 20000 + 5;

struct Node {
    Node *fa,*go[26];
    int val;
    Node(int _val = 0) : fa(0),val(_val) {
        memset(go,0,sizeof(go));
    }
};
Node *root,*last,pool[N],*bat;

void extend(int c) {
    Node *p = last;
    Node *np = new(bat++) Node(p->val+1);
    while (p && p->go[c] == 0) {
        p->go[c] = np; p = p->fa;
    }
    if (p == 0) {
        np->fa = root;
    } else {
        Node *q = p->go[c];
        if (p->val+1 == q->val) {
            np->fa = q;
        } else {
            Node *nq = new(bat++) Node(p->val+1);
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
