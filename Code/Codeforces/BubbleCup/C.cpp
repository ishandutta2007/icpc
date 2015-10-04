#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
const int N = 20 + 1;
int A[2][N][N],n;
int answer;
std::vector<int> u,v,p,way;
int graph[N][N];

void km(int i) {
    std::vector<int> minv(n + 1,INF);
    std::vector<bool> used(n + 1,false);
    p[n] = i;
    int j0 = n;
    do {
        used[j0] = true;
        int i0 = p[j0],delta = INF,j1;
        for (int j = 0; j < n; ++ j) {
            if (!used[j]) {
                int cur = graph[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }
                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }
        }
        for (int j = 0; j <= n; ++ j) {
            if (used[j]) {
                u[p[j]] += delta,v[j] -= delta;
            } else {
                minv[j] -= delta;
            }
        }
        j0 = j1;
    } while (p[j0] != -1);
    do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
    } while (j0 != n);
}

void search(int i,int friday,int saturday) {
    if (i == n) {
        answer = std::max(answer,v[n]);
        return ;
    }
    for (int day = 0; day < 2; ++ day) {
        if (day == 0 && friday == n / 2) {
            continue;
        }
        if (day == 1 && saturday == n / 2) {
            continue;
        }
        std::vector<int> t_u = u,t_v = v,t_p = p,t_way = way;
        for (int j = 0; j < n; ++ j) {
            graph[i][j] = -A[day][i][j];
        }
        km(i);
        search(i + 1,friday + (day == 0),saturday + (day == 1));
        u = t_u;
        v = t_v;
        p = t_p;
        way = t_way;
    }
}

int work() {
    search(0,0,0);
    return answer;
}

int main() {
    scanf("%d",&n);
    for (int c = 0; c < 2; ++ c) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                scanf("%d",&A[c][i][j]);
            }
        }
    }
    u.resize(n + 1);
    v.resize(n + 1);
    p.resize(n + 1,-1);
    way.resize(n + 1);
    printf("%d\n",work());
}
