#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct Node {
        int raw,l,r;
        Node (int raw,int l,int r) : raw(raw),l(l),r(r) {}
        bool operator < (const Node &tt) const {
                return raw<tt.raw || raw==tt.raw && l<tt.l;
        }
};
vector<Node> dot;
queue<Node> que[2];
int n,m,cur = 0,nex = 1;
void append(Node x) { if (x.l<=x.r) que[nex].push(x); }
bool check() {
        if (m==0) return true;
        que[cur].push(Node(0,1,1));
        int pre = 0;
        for (int i = 0; i < m; i ++) {
                Node &x = dot[i];
                if (x.raw>pre+1 && !que[cur].empty()) {
                        append(Node(x.raw-1,que[cur].front().l,n));
                        swap(cur,nex);
                        while (!que[nex].empty()) que[nex].pop();
                }
                if (que[cur].empty()) {
                        if (i==m-1 || dot[i].raw!=dot[i+1].raw) swap(cur,nex);
                        pre = x.raw;
                        continue;
                }
                if (x.raw != pre)
                        append(Node(x.raw,que[cur].front().l,x.l-1));
                while (!que[cur].empty() && que[cur].front().r<=x.r) que[cur].pop();
                if (!que[cur].empty()) {
                        int bg,ed;
                        if (i==m-1 || x.raw!=dot[i+1].raw) ed = n;
                        else ed = dot[i+1].l-1;
                        bg = max(x.r+1,que[cur].front().l);
                        append(Node(x.raw,bg,ed));
                }
                if (i==m-1 || x.raw!=dot[i+1].raw) {
                        while (!que[cur].empty()) que[cur].pop();
                        swap(cur,nex);
                }
                pre = x.raw;
        }
        if (que[cur].empty()) return false;
        if (que[cur].front().raw!=n) return true;
        while (!que[cur].empty()) {
                int r = que[cur].front().r; que[cur].pop();
                if (r==n) return true;
        }
        return false;
}
int main() {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < m; i ++) {
                int a,b;
                scanf("%d%d",&a,&b);
                dot.push_back(Node(a,b,b));
        }
        sort(dot.begin(),dot.end());
        printf("%d\n",check() ? n-1<<1 : -1);
        return 0;
}
