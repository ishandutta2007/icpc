#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i,x) for (int i = 0; i < (int)x.size(); i ++)
typedef pair<int,int> PII;
const int N = 101000;
vector<int> graph[N];
vector<PII> qnode[N];
int n,m,sz[N],sum[N],ans[N],freq[N],col[N],st[N],ed[N],tim,cop[N];
void get_size(int u,int fa) {
        sz[u] = 1;
        cop[tim] = col[u];
        st[u] = tim ++;
        rep(i,graph[u]) {
                int v = graph[u][i];
                if (v==fa) continue;
                get_size(v,u);
                sz[u] += sz[v];
        }
        ed[u] = tim-1;
}
void clear_all(int u) {
        for (int i = st[u]; i <= ed[u]; i ++)
                sum[freq[cop[i]]--] --;
}
void add_all(int u) {
        for (int i = st[u]; i <= ed[u]; i ++)
                sum[++freq[cop[i]]] ++;
}
void dfs(int u,int fa) {
        int big = -1;
        int id = -1;
        rep(i,graph[u]) {
                int v = graph[u][i];
                if (v==fa) continue;
                if (sz[v]>big) {
                        big = sz[v];
                        id = v;
                }
        }
        rep(i,graph[u]) {
                int v = graph[u][i];
                if (v==fa || v==id) continue;
                dfs(v,u);
                clear_all(v);
        }
        if (id!=-1) dfs(id,u);
        rep(i,graph[u]) {
                int v = graph[u][i];
                if (v==fa || v==id) continue;
                add_all(v);
        }
        sum[++freq[col[u]]] ++;
        rep(i,qnode[u]) {
                int id = qnode[u][i].first;
                int k = qnode[u][i].second;
                ans[id] = sum[k];
        }
}
int main() {
        ios::sync_with_stdio(false);
        cin >> n >> m;
        for (int i = 0; i < n; i ++) cin >> col[i];
        for (int i = 0; i < n-1; i ++) {
                int a,b;
                cin >> a >> b;
                a --; b --;
                graph[a].push_back(b);
                graph[b].push_back(a);
        }
        for (int i = 0; i < m; i ++) {
                int a,b;
                cin >> a >> b;
                a --;
                qnode[a].push_back(PII(i,b));
        }
        get_size(0,-1);
        dfs(0,-1);
        for (int i = 0; i < m; i ++) cout << ans[i] << endl;
        return 0;
}
