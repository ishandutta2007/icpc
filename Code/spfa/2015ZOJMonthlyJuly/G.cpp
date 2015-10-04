#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 100000+5;

struct PP {
    int l, r, x;
    bool be;
    PP(){}
    PP(int l,int r,int x,bool be):l(l),r(r),x(x),be(be){}
    bool operator < (const PP&a) const {
        if(x != a.x)
            return x < a.x;
        return r > a.r;
    }
}q[60*N];
//vector<PP> q;

int val[N], nxt[N], a[N], b[N];

int gcd(int a, int b) {
    return b ? gcd(b, a%b) : a;
}

void deal(int a[], int n, int be, int &tot) {
    nxt[1] = 1; val[1] = a[1];
//    q.push_back(PP(1,1,val[1],be));
    q[tot++] = PP(1,1,val[1],be);
    for(int i = 2;i <= n; i++) {
        val[i] = a[i];
        nxt[i] = i;
        int cur = i;
        while(cur > 0) {
            val[cur] = gcd(val[cur], a[i]);
            while(nxt[cur]-1 > 0 && gcd(a[i],val[nxt[cur]-1])==val[cur]) {
                nxt[cur] = nxt[nxt[cur]-1];
            }
//            q.push_back(PP(nxt[cur],i,val[cur],be));
            q[tot++] = PP(i-cur+1,i-nxt[cur]+1,val[cur],be);
            cur = nxt[cur]-1;
        }
    }
}

int n, m;

void solve() {
    int tot = 0;
    deal(a, n, 0, tot);
    deal(b, m, 1, tot);
    sort(q, q+tot);
    int ans1 = 0;
    ll ans2 = 0;
    for(int i = 0;i < tot; i++) {
        int cr = i;
        int mx = -1;
        int l1 = -1, r1 = -1, l2 = -1, r2 = -1;
        while(cr < tot && q[cr].x==q[i].x) {
            if(q[cr].be==0) {
                if(l2 !=-1 && l2 <= q[cr].r) {
                    mx = max(mx, q[cr].r);
                }
                if(l1==-1 || l1 > q[cr].r) {
                    l1 = q[cr].l; r1 = q[cr].r;
                } else l1 = min(l1, q[cr].l);
            } else {
                if(l1 != -1 && l1 <= q[cr].r) {
                    mx = max(mx, q[cr].r);
                }
                if(l2==-1 || l2 > q[cr].r) {
                    l2 = q[cr].l; r2 = q[cr].r;
                } else l2 = min(l2, q[cr].l);
            }
            cr++;
        }
        if(mx != -1 && mx >= ans1) {
            int c1 = 0, c2 = 0;
            for(int j = i;j < cr; j++) {
                if(q[j].be==0 && q[j].l <= mx && q[j].r >= mx)
                c1++;
                else if(q[j].be==1 && q[j].l <= mx && q[j].r >= mx)
                c2++;
            }
            if(ans1 < mx) {
                ans1 = mx;
                ans2 = 1ll*c1*c2;
            } else if(ans1 == mx)
                ans2 += 1ll*c1*c2;
        }
        i = cr-1;
    }
    printf("%d %lld\n", ans1, ans2);
}

int main() {
    while(scanf("%d%d", &n, &m) == 2) {
        for(int i = 1;i <= n; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 1;i <= m; i++) scanf("%d", &b[i]);
        solve();
    }
    return 0;
}
