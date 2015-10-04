#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100000+5;
const int Mod = 1e9+7;
int n, a[N], nxt[N], pre[N], l[N], r[N];
vector<int> vt[N];

void init(int n) {
    for(int i = 1;i <= n;i ++) 
        for(int j = i;j <= n;j += i)
            vt[j].push_back(i);
}

int main() {
    init(10000);
    while(scanf("%d", &n) == 1) {
        for(int i = 1;i <= n; i++) scanf("%d", &a[i]);
        for(int i = 1;i <= n;i ++) {
            int c = a[i];
            l[i] = 0;
            for(int j = 0;j < vt[c].size(); j++) {
                l[i] = max(l[i], pre[vt[c][j]]);
            }
            pre[a[i]] = i;
        }
        for(int i = n;i >= 1; i--) {
            int c = a[i];
            r[i] = n+1;
            for(int j = 0;j < vt[c].size(); j++) {
                if(nxt[vt[c][j]] != 0) r[i] = min(r[i], nxt[vt[c][j]]);
            }
            nxt[a[i]] = i;
        }
        for(int i = 1;i <= n; i++) nxt[a[i]] = pre[a[i]] = 0;
        int ans = 0;
        for(int i = 1;i <= n; i++) {
            ans += 1ll*(i-l[i])*(r[i]-i)%Mod;
            if(ans >= Mod) ans -= Mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}
