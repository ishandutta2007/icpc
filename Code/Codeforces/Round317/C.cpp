#include <bits/stdc++.h>

const int N = 200000 + 5;
std::vector<int> literals[N];
std::vector<int> clauses[N << 1];
int n,m;
int answer[N];
bool good[N];
int dfn[N],tim;
bool vis[N];

void remark(int u) {
    if (vis[u]) return ;
    vis[u] = true;
    for (int l : literals[u]) {
        if (answer[l >> 1] == -1 || answer[l >> 1] == (l & 1 ^ 1)) {
            answer[l >> 1] = l & 1 ^ 1;
            for (int v : clauses[l ^ 1]) {
                good[v] = true;
                remark(v);
            }
        }
    }
}

int get_cycle(int u) {
    dfn[u] = ++ tim;
    for (int l : literals[u]) {
        if (answer[l >> 1] == (l & 1)) continue;
        int tmp = answer[l >> 1];
        answer[l >> 1] = l & 1 ^ 1;
        for (int v : clauses[l ^ 1]) {
            if (!dfn[v]) {
                int t = get_cycle(v);
                if (t != -1) {
                    answer[l >> 1] = tmp;
                    return t;
                }
            } else if (dfn[v] < dfn[u]) {
                answer[l >> 1] = tmp;
                return l ^ 1;
            }
        }
        answer[l >> 1] = tmp;
    }
    return -1;
}

void paint(int l) {
    answer[l >> 1] = l & 1;
    for (int v : clauses[l]) {
        good[v] = true;
        remark(v);
    }
}

bool work() {
    memset(answer,-1,sizeof(answer));
    for (int i = 0; i < m << 1; ++ i) {
        if (clauses[i].empty()) {
            answer[i >> 1] = i & 1 ^ 1;
            for (int v : clauses[i ^ 1]) {
                good[v] = true;
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (good[i]) {
            remark(i);
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (vis[i] || dfn[i]) continue;
        int key = get_cycle(i);
        if (key == -1) {
            for (int l : literals[i]) {
                if (answer[l >> 1] == -1) {
                    key = l;
                    break;
                }
            }
            if (key == -1)
                return false;
        }
        paint(key);
    }
    for (int i = 0; i < n; ++ i) {
        bool flag = false;
        for (int l : literals[i]) {
            if (answer[l >> 1] == (l & 1)) 
                flag = true;
        }
        if (!flag) {
            return false;
        }
    }
    puts("YES");
    for (int i = 0; i < m; ++ i) {
        printf("%d",answer[i]);
    }
    puts("");
    return true;
}

int main() {
    scanf("%d%d",&n,&m);
    for (int i = 0; i < n; ++ i) {
        int x,y;
        scanf("%d",&x);
        for (int j = 0; j < x; ++ j) {
            scanf("%d",&y);
            int d = 1;
            if (y < 0) {
                y = -y;
                d = 0;
            }
            y --;
            literals[i].push_back(y << 1 | d);
            clauses[y << 1 | d].push_back(i);
        }
    }
    if (!work()) {
        puts("NO");
    }
}
