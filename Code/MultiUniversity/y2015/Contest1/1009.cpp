#pragma comment(linker, "/STACK:1024000000,1024000000") 
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <set>

const int N = 100000 + 5;
const int LOG = 18;
int n,m;
std::vector<std::pair<int,int> > edges[N];
int plca[N][LOG];
int depth[N];
int dfn[N],dlo,rd[N];
int dis[N];

void dfs(int u,int fa) {
    rd[dlo] = u;
    dfn[u] = dlo ++;
    plca[u][0] = fa;
    for (int i = 1; i < LOG; ++ i) {
        plca[u][i] = -1;
        if (plca[u][i - 1] != -1) {
            plca[u][i] = plca[plca[u][i - 1]][i - 1];
        }
    }
    for (int i = 0; i < edges[u].size(); ++ i) {
        int v = edges[u][i].first;
        int w = edges[u][i].second;
        if (v == plca[u][0]) continue;
        depth[v] = depth[u] + 1;
        plca[v][0] = u;
        dis[v] = dis[u] + w;
        dfs(v,u);
    }
}

int get_lca(int a,int b) {
    if (depth[a] < depth[b]) std::swap(a,b);
    for (int i = 0; i < LOG; ++ i) {
        if (depth[a] - depth[b] >> i & 1) {
            a = plca[a][i];
        }
    }
    if (a == b) return a;
    for (int i = LOG - 1; i >= 0; -- i) {
        if (plca[a][i] != plca[b][i]) {
            a = plca[a][i];
            b = plca[b][i];
        }
    }
    return plca[a][0];
}

int get_dis(int a,int b) {
    return dis[a] + dis[b] - 2 * dis[get_lca(a,b)];
}

void prepare() {
    dlo = 0;
    dfs(0,-1);
}

int main() {
    int cas;
    int ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c); a --; b --;
            edges[a].push_back(std::make_pair(b,c));
            edges[b].push_back(std::make_pair(a,c));
        }
        prepare();
        printf("Case #%d:\n",++ca);
        std::set<int> set;
        std::set<int>::iterator it;
        int now = 0;
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); b --;
            if (a == 1) {
                if (set.find(dfn[b]) == set.end()) {
                    if (set.empty()) {
                        set.insert(dfn[b]);
                    } else {
                        it = set.lower_bound(dfn[b]);
                        if (it == set.end()) {
                            int u = rd[*set.rbegin()];
                            int v = rd[*set.begin()];
                            now -= get_dis(u,v);
                            now += get_dis(u,b);
                            now += get_dis(v,b);
                            set.insert(dfn[b]);
                        } else {
                            int u = rd[*it];
                            int v = -1;
                            if (it == set.begin()) {
                                v = rd[*set.rbegin()];
                            } else {
                                v = rd[*--it];
                            }
                            now -= get_dis(u,v);
                            now += get_dis(u,b);
                            now += get_dis(v,b);
                            set.insert(dfn[b]);
                        }
                    }
                }
            } else {
                if (set.find(dfn[b]) != set.end()) {
                    set.erase(dfn[b]);
                    if (!set.empty()) {
                        it = set.lower_bound(dfn[b]);
                        if (it == set.end()) {
                            int u = rd[*set.rbegin()];
                            int v = rd[*set.begin()];
                            now -= get_dis(u,b);
                            now -= get_dis(v,b);
                            now += get_dis(u,v);
                        } else {
                            int u = rd[*it];
                            int v = -1;
                            if (it == set.begin()) {
                                v = rd[*set.rbegin()];
                            } else {
                                v = rd[*--it];
                            }
                            now -= get_dis(u,b);
                            now -= get_dis(v,b);
                            now += get_dis(u,v);
                        }
                    }
                }
            }
            printf("%d\n",now >> 1);
        }
    }
}
