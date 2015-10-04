#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

const int N = 100000 + 5;
int n,m,A,B;
std::vector<int> edges[N];
int dis[N];

int work1() { // A < B
    std::queue<int> que;
    std::fill(dis,dis + n,B);
    dis[0] = 0;
    que.push(0);
    while (!que.empty()) {
        int u = que.front(); que.pop();
        for (int i = 0; i < edges[u].size(); ++ i) {
            int v = edges[u][i];
            if (dis[v] > dis[u] + A) {
                dis[v] = dis[u] + A;
                que.push(v);
            }
        }
    }
    return dis[n - 1];
}

int work() {
    if (A < B) {
        return work1();
    }

    // A > B

    std::queue<int> que;
    std::fill(dis,dis + n,A);
    dis[0] = 0;
    que.push(0);
    std::set<int> set;
    for (int i = 1; i < n; ++ i) {
        set.insert(i);
    }

    while (!que.empty()) {
        int u = que.front(); que.pop();
        std::set<int> tmp;
        for (int i = 0; i < edges[u].size(); ++ i) {
            int v = edges[u][i];
            if (set.find(v) != set.end()) {
                set.erase(v);
                tmp.insert(v);
            }
        }
        for (std::set<int>::iterator it = set.begin();
                it != set.end(); ++ it) {
            int v = *it;
            if (dis[v] > dis[u] + B) {
                dis[v] = dis[u] + B;
                que.push(v);
            }
        }
        set.swap(tmp);
    }
    return dis[n - 1];
}

int main() {
    while (scanf("%d%d%d%d",&n,&m,&A,&B) == 4) {
        for (int i = 0; i < n; ++ i) {
            edges[i].clear();
        }
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b); a --; b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        printf("%d\n",work());
    }
}
