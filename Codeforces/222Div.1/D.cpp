#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef pair<int,int> PII;
const int N = 303000;
struct point {
        int l,v,r,id;
        void read() {
                cin >> l >> v >> r;
        }
        bool operator < (const point &tt) const {
                return v<tt.v;
        }
}dot[N],dot2[N];
int n;
struct Sgt {
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
        int delta[N<<2],tree[N<<2],mx[N<<2];
        void build(int l,int r,int rt) {
                mx[rt] = l;
                if (l==r) {
                        return ;
                }
                int mid = l+r>>1;
                build(lson);
                build(rson);
        }
        void down(int rt) {
                delta[rt<<1] += delta[rt];
                delta[rt<<1|1] += delta[rt];
                tree[rt<<1] += delta[rt];
                tree[rt<<1|1] += delta[rt];
                delta[rt] = 0;
        }
        void up(int rt) {
                if (tree[rt<<1]>tree[rt<<1|1]) {
                        tree[rt] = tree[rt<<1];
                        mx[rt] = mx[rt<<1];
                } else {
                        tree[rt] = tree[rt<<1|1];
                        mx[rt] = mx[rt<<1|1];
                }
        }
        void update(int L,int R,int dt,int l,int r,int rt) {
                if (L<=l && r<= R) {
                        tree[rt] += dt;
                        delta[rt] += dt;
                        return ;
                }
                int mid = l+r>>1;
                down(rt);
                if (L<=mid) update(L,R,dt,lson);
                if (R>mid)  update(L,R,dt,rson);
                up(rt);
        }
        PII query(int L,int R,int l,int r,int rt) {
                if (L<=l && r<=R) {
                        return PII(tree[rt],mx[rt]);
                }
                int mid = l+r>>1;
                down(rt);
                PII ret = PII(0,0);
                if (L<=mid) ret = max(ret,query(L,R,lson));
                if (R>mid)  ret = max(ret,query(L,R,rson));
                return ret;
        }
}sgt;
bool cmp(point a,point b) {
        return a.r<b.r;
}
int main() {
        ios::sync_with_stdio(false);
        cin >> n;
        for (int i = 0; i < n; i ++) {
                dot[i].read();
                dot[i].id = i;
                dot2[i] = dot[i];
        }
        sort(dot,dot+n);
        sort(dot2,dot2+n,cmp);
        sgt.build(1,300000,1);
        PII ans = PII(0,0);
        int p = 0,ptr = -1;
        for (int i = 0; i < n; i ++) {
                while (p<n && dot2[p].r<dot[i].v) {
                        point &c = dot2[p++];
                        sgt.update(c.l,c.v,-1,1,300000,1);
                }
                sgt.update(dot[i].l,dot[i].v,1,1,300000,1);
                PII tmp = sgt.query(dot[i].l,dot[i].v,1,300000,1);
                if (tmp.first>ans.first) {
                        ans = tmp;
                        ptr = i;
                }
        }
		vector<int> sol;
		for (int i = 0; i <= ptr; i ++) {
                if (dot[i].r>=dot[ptr].v && dot[i].v>=dot[ptr].l && dot[i].l<=ans.second && dot[i].v>=ans.second)
                        sol.push_back(dot[i].id+1);
		}
		sort(sol.begin(),sol.end());
		cout << ans.first << endl;
		for (int i = 0; i < (int)sol.size(); i ++) cout << sol[i] << " ";
		cout << endl;
        return 0;
}
