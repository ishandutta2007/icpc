#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <string>

struct Node *nill;

struct Node {
    Node *fa,*ch[2];
    bool rev_tag;
    int val,vmax;
    int sz,vc;
    // sz   : splay子树的节点以及虚树节点和.
    // vc   : 虚树节点和.
    // vmax : splay子树最大val.

    //      : 所有修改操作只关于access后的根进行.

    Node(int _val = 0) {
        rev_tag = false;
        fa = ch[0] = ch[1] = nill;
        val = vmax = _val;
        sz = 1;
        vc = 0;
    }

    void up() {
        if (this == nill) return ;
        vmax = std::max(val,std::max(ch[0]->vmax,ch[1]->vmax));
        sz = 1 + vc + ch[0]->sz + ch[1]->sz;
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
        if (!isroot()) fa->D();
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
        for (Node *p = this,*q = nill; p != nill; ) {
            p->splay();
            p->vc += p->ch[1]->sz;
            p->vc -= q->sz;
            p->setc(q,1);
            q = p;
            p = p->fa;
        }
        return splay();
    }

    void link(Node *p) {
        p->access();
        make_root()->fa = p;
        p->vc += sz;
        p->up();
    }

    Node *make_root() {
        access()->rev();
        down();
        return this;
    }

    Node *get_max() {
        Node *p = this;
        while (true) {
            p->down();
            if (p->val >= p->ch[0]->vmax && p->val >= p->ch[1]->vmax) {
                return p;
            }
            if (p->ch[0]->vmax >= p->ch[1]->vmax) {
                p = p->ch[0];
            } else {
                p = p->ch[1];
            }
        }
    }
};

const int kN = 400000 + 5;
Node pool[kN],*node[kN],*alloc;
int n;

void lct_init() 
{
    alloc = pool;
    nill = new(alloc ++) Node();
    nill->fa = nill->ch[0] = nill->ch[1] = nill;
    nill->sz = 0;

    for (int i = 1; i <= n; ++ i) {
        node[i] = new(alloc ++) Node();
    }
}
