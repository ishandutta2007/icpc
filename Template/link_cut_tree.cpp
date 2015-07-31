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

void lct_init() {
    bat = pool;
    nill = new(bat++) Node;
    nill->ch[0] = nill->ch[1] = nill->fa = nill;

    for (int i = 1; i <= n; ++ i) {
        node[i] = new(bat++) Node;
    }
}
