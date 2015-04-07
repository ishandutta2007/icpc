const int N = 10200;

struct Node *nill;

struct Node {
    Node *fa,*ch[2];
    bool rev;
    void down() {
        if (this==nill) return ;
        if (rev==false) return ;
        rev = false;
        ch[0]->reverse();
        ch[1]->reverse();
    }
    void up() {
        if (this == nill) return ;
        // 
    }
    void reverse() { 
        std::swap(ch[0],ch[1]); 
        rev ^= 1; 
    }
    bool d() { 
        return fa->ch[1]==this; 
    }
    bool isroot() { 
        return fa==nill || fa->ch[0]!=this && fa->ch[1]!=this; 
    }
    void setc(Node *p,int c) {
        ch[c] = p;
        p->fa = this;
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
    void D() {
        if (this==nill) return ;
        fa->D();
        down();
    }
    Node *splay() {
        D();
        while (!isroot()) {
            if (!fa->isroot())
                d()==fa->d() ? fa->rot() : rot();
            rot();
        }
        return this;
    }
    Node *access() {
        for (Node *p = this,*q = nill; p!=nill; q = p,p = p->fa)
            p->splay()->setc(q,1);
        return splay();
    }
    void link(Node *p) {
        splay()->fa = p;
    }
    void rootable() {
        access()->reverse();
    }
};
