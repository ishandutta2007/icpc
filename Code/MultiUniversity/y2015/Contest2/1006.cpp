#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m;
bool mp[11][11];
int col[11][11];

int dfs(int u) {
    if(u == n) return 1;
    int cnt[3]; cnt[1]=cnt[2] = 0;
    int tmp[8], sum = 0;
    for(int i = 0;i < n; i++) if(mp[u][i]){
        if(i < u) {
            cnt[col[i][u]] ++;
        } else {
            tmp[sum++] = i;
        }
    }
    int ret = 0;
    for(int i = 0;i < 1<<sum; i++) {
        int cc[3]; cc[1]=cc[2] = 0;
        for(int j = 0;j < sum; j++) {
            if(i>>j&1) {
                cc[1]++;
                col[u][tmp[j]]=col[tmp[j]][u]=1;
            }
            else {
                cc[2]++;
                col[u][tmp[j]]=col[tmp[j]][u]=2;
            }
        }
        if(cc[1]+cnt[1]==cc[2]+cnt[2])
            ret += dfs(u+1);
    }
    return ret;
}

int solve() {
    memset(col, 0, sizeof(col));
    return dfs(0);
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        memset(mp, 0, sizeof(mp));
        int u, v;
        for(int i = 0;i < m; i++) {
            scanf("%d%d", &u, &v);
            u--; v--;
            mp[u][v] = mp[v][u] = 1;
        }
        printf("%d\n", solve());
    }
    return 0;
}
