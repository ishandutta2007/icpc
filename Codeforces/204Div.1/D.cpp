/* Created Time: Monday, November 18, 2013 PM04:15:42 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;
const int N = 100010;
int a[N],n,m,b_size,ans[N];
struct QQ {
    int l,r,b,id;
    bool operator < (const QQ &tt) const {
        return b<tt.b || b==tt.b && r<tt.r;
    }
}q[N];
bool first = true;
int prel,prer,kind,can_do,cnt[N];
struct QUE {
    deque <int> que;
    int diff,val;

    void add() { if (cnt[val]==0) kind ++; cnt[val] ++; }
    void remove() { cnt[val] --; if (cnt[val]==0) kind --; }

    void push_front(int x) {
        add();
        if (que.size()==0) {
            can_do ++;
            que.push_front(x);
        } else if (que.size()==1) {
            que.push_front(x);
            diff ++;
        } else {
            int v = que.front(); que.pop_front();
            if (que.front()-v!=v-x) {
                if (diff==1) can_do --;
                diff ++;
            }
            que.push_front(v);
            que.push_front(x);
        }
    }
    void pop_front() {
        remove();
        if (que.size()==1) {
            can_do --;
            que.pop_front();
        } else if (que.size()==2) {
            diff --;
            que.pop_front();
        } else {
            int x = que.front(); que.pop_front();
            int v = que.front(); que.pop_front();
            if (v-x!=que.front()-v) {
                diff --;
                if (diff==1) can_do ++;
            }
            que.push_front(v);
        }
    }

    void push_back(int x) {
        add();
        if (que.size()==0) {
            can_do ++;
            que.push_back(x);
        } else if (que.size()==1) {
            que.push_back(x);
            diff ++;
        } else {
            int v = que.back(); que.pop_back();
            if (x-v!=v-que.back()) {
                if (diff==1) can_do --;
                diff ++;
            }
            que.push_back(v);
            que.push_back(x);
        }
    }
    void pop_back() {
        remove();
        if (que.size()==1) {
            can_do --;
            que.pop_back();
        } else if (que.size()==2) {
            diff -- ;
            que.pop_back();
        } else {
            int x = que.back(); que.pop_back();
            int v = que.back(); que.pop_back();
            if (v-que.back()!=x-v) {
                diff --;
                if (diff==1) can_do ++;
            }
            que.push_back(v);
        }
    }
}dot[N];

int fuc(int l,int r) {
        if (prer<r)
            for (int i = prer+1; i <= r; i ++)
                dot[a[i]].push_back(i);
        if (l<prel)
            for (int i = prel-1; i >= l; i --)
                dot[a[i]].push_front(i);
        if (l>prel)
            for (int i = prel; i < l; i ++)
                dot[a[i]].pop_front();
        if (prer>r)
            for (int i = prer; i > r; i --)
                dot[a[i]].pop_back();
        prel = l;
        prer = r;
    return kind+(can_do==0);
}
int main() {
//    freopen("data.txt","r",stdin);
    for (int i = 1; i < N; i ++) dot[i].val = i;
    scanf("%d",&n);
    for (int i = 0; i < n; i ++)
        scanf("%d",&a[i]);
    b_size = int(sqrt(double(n)));
    scanf("%d",&m);
    for (int i = 0; i < m; i ++) {
        scanf("%d%d",&q[i].l,&q[i].r);
        q[i].l--,q[i].r--;
        q[i].id = i;
        q[i].b = q[i].l/b_size;
    }
    sort(q,q+m);
    prel = 0,prer = -1;
    for (int i = 0; i < m; i ++)
        ans[q[i].id] = fuc(q[i].l,q[i].r);
    for (int i = 0; i < m; i ++)
        printf("%d\n",ans[i]);
    return 0;
}
