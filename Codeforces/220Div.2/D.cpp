#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1001000;
int n,m,a[N];
int ran() { static int ranx = 789654123; return ranx += ranx<<2|1; }
struct Node {
        Node *ch[2];
        int v,sz,r;
}*nill,*root,memo[N];
int tot;
void up(Node *o) {
        o->sz = o->ch[0]->sz + o->ch[1]->sz+1;
}
void New_node(Node *&o,int v) {
        o = &memo[tot++];
        o->ch[0] = o->ch[1] = nill;
        o->sz = 1; o->v = v; o->r = ran();
}
void merge(Node *&o,Node *a,Node *b) {
        if (a==nill) o = b;
        else if (b==nill) o = a;
        else {
                if (a->r > b->r) {
                        o = a;
                        merge(o->ch[1],a->ch[1],b);
                        up(o);
                } else {
                        o = b;
                        merge(o->ch[0],a,b->ch[0]);
                        up(o);
                }
        }
}
void cut(Node *o,Node *&a,Node *&b,int k) {
        if (k==0) {
                a = nill; b = o;
        } else if (o->sz == k) {
                a = o; b = nill;
        } else {
                if (o->ch[0]->sz >= k) {
                        b = o;
                        cut(o->ch[0],a,b->ch[0],k);
                        up(b);
                } else {
                        a = o;
                        cut(o->ch[1],a->ch[1],b,k - o->ch[0]->sz - 1);
                        up(a);
                }
        }
}
void ins(int v) {
        Node *a;
        New_node(a,v);
        merge(root,root,a);
}
void del(int p) {
        Node *a,*b,*c;
        cut(root,a,b,p-1);
        cut(b,b,c,1);
        merge(root,a,c);
}
void del() {
        int p = upper_bound(a,a+m,root->sz)-a;
        for (int i = p-1; i >= 0; i --) 
                del(a[i]);
}
void show(Node *o) {
        if (o==nill) return ;
        show(o->ch[0]);
        printf("%d",o->v);
        show(o->ch[1]);
}
int main() {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < m; i ++) scanf("%d",&a[i]);
        New_node(nill,0);
        nill->sz = 0;
        root = nill;
        while (n--) {
                int d;
                scanf("%d",&d);
                if (d!=-1) 
                        ins(d);
                else 
                        del();
        }
        if (root->sz == 0) 
                puts("Poor stack!");
        else {
                show(root);
                puts("");
        }
        return 0;
}