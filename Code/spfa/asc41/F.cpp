#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;

std::pair<int,int> orders[200];
int n,m,cost;
int mat[200][100];
int left[1000];

bool check(int tot) {
    std::fill(left,left + 1000,m);
    for (int i = tot; i < n; ++ i) {
        int day = orders[i].first;
        std::vector<std::pair<int,int>> B;
        for (int j = 0; j < day; ++ j) {
            B.push_back({left[j],j});
        }
        std::sort(B.rbegin(),B.rend());
        if (B.size() < m || B[m - 1].first == 0) {
            return false;
        }
        for (int j = 0; j < m; ++ j) {
            left[B[j].second] --;
            mat[i][j] = B[j].second;
        }
    }
    return true;
}

bool mark[200][1000];
std::vector<int> edges[1000];
int vis[200],tlg;
int match[200];
int answer[200][100];

bool expath(int u) {
    for (int v : edges[u]) {
        if (vis[v] != tlg) {
            vis[v] = tlg;
            if (match[v] == -1 || expath(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void construct(int tot) {
    memset(left,0,sizeof(left));
    for (int i = tot; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            left[mat[i][j]] ++;
        }
    }
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < 1000; ++ j) {
            edges[j].clear();
        }
        for (int j = tot; j < n; ++ j) {
            for (int k = 0; k < m; ++ k) {
                if (!mark[j][mat[j][k]]) {
                    edges[mat[j][k]].push_back(j);
                }
            }
        }
        std::fill(match,match + 200,-1);
        std::vector<std::pair<int,int>> B;
        for (int j = 0; j < 1000; ++ j) {
            B.push_back({left[j],j});
        }
        std::sort(B.rbegin(),B.rend());
        int cnt = 0;
        for (auto t : B) {
            tlg ++;
            if (expath(t.second) && ++ cnt == n - tot) {
                break;
            }
        }
        for (int j = tot; j < n; ++ j) {
            assert(match[j] != -1);
            mark[j][match[j]] = true;
            answer[orders[j].second][i] = match[j];
            left[match[j]] --;
        }
    }

    for (int i = 0; i < tot; ++ i) {
        for (int j = 0; j < m; ++ j) {
            answer[orders[i].second][j] = 1000 + i * m + j;
        }
    }
}

void work() {
    std::sort(orders,orders + n);

    int l = 0,r = n;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << (r + 1) * cost << endl;
    check(r + 1);
    construct(r + 1);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (j) cout << ' ';
            cout << answer[i][j] + 1;
        }
        cout << endl;
    }
}

int main() {
    freopen("furniture.in","r",stdin);
    freopen("furniture.out","w",stdout);
    cin >> n >> m >> cost;
    for (int i = 0; i < n; ++ i) {
        int x;
        cin >> x;
        orders[i] = {x,i};
    }
    work();
}
