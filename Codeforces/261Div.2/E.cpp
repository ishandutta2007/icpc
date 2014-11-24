#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>
#include <set>

const int N = 300000 + 5;

struct Edge {
    int u,v,w;
    void read() {
        scanf("%d%d%d",&u,&v,&w);
    }
    bool operator < (const Edge &tt) const {
        return w<tt.w;
    }
}edge[N];
int n,m,dp[N];

int main() {
    scanf("%d%d",&n,&m);

    for (int i = 0; i < m; ++ i) {
        edge[i].read();
    }
    std::sort(edge,edge+m);
    for (int i = 0,j = 1; i < m; i = j ++) {
        while (j<m && edge[j].w==edge[i].w) j ++;
        std::map<int,int> update;
        for (int k = i; k < j; ++ k) {
            Edge &e = edge[k];
            update[e.v] = std::max(update[e.v],dp[e.u]+1);
        }
        for (std::map<int,int>::iterator it = update.begin(); it != update.end(); ++ it) {
            dp[it->first] = std::max(dp[it->first],it->second);
        }
    }
    int answer = 0;
    for (int i = 1; i <= n; ++ i) 
        answer = std::max(answer,dp[i]);
    printf("%d\n",answer);
    return 0;
}

