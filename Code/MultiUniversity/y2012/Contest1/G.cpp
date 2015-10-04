#include <bits/stdc++.h>

const int N = 300 + 5;
int n,cr,cc;
int A[N][N],B[N][N];
int cnt[100000 + 5];

void reverse() {
    std::swap(cr,cc);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < i; ++ j) {
            std::swap(A[i][j],A[j][i]);
            std::swap(B[i][j],B[j][i]);
        }
    }
}

bool check1() {
    std::vector<int> vec1[N],vec2[N];
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            vec1[j].push_back(A[i][j]);
            vec2[j].push_back(B[i][j]);
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (vec1[i].size() != n || vec2[i].size() != n)
            return false;
        std::sort(vec1[i].begin(),vec1[i].end());
        std::sort(vec2[i].begin(),vec2[i].end());
        for (int j = 0; j < n; ++ j) {
            if (vec1[i][j] != vec2[i][j])
                return false;
        }
    }
    return true;
}

template<int N>
struct Sat {
    int head[N],etot,stack[N],top;
    bool mark[N];
    struct Edge {
        int v,next;
    } g[300 * 300 * 300 * 2 * 2 * 2];

    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }

    void add_edge(int u,int v) {
        g[etot].v = v; g[etot].next = head[u]; head[u] = etot ++;
    }

    bool dfs(int u) {
        if (mark[u ^ 1]) return false;
        if (mark[u]) return true;
        mark[u] = true;
        stack[top++] = u;
        for (int i = head[u]; i != -1; i = g[i].next) {
            if (!dfs(g[i].v)) return false;
        }
        return true;
    }

    bool work(int n) {
        memset(mark,0,sizeof(mark));
        for (int i = 0; i < n; i += 2) {
            if (!mark[i] && !mark[i + 1]) {
                top = 0;
                if (!dfs(i)) {
                    while (top) mark[stack[--top]] = false;
                    if (!dfs(i + 1)) return false;
                }
            }
        }
        return true;
    }
};

Sat<300 * 300 * 2> sat;
std::vector<int> vp[100000 + 5];
int idx[100000 + 5],tot;

bool check2() {
    sat.init();
    for (int i = 1; i <= 100000; ++ i) {
        vp[i].clear();
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            vp[B[i][j]].push_back(j);
        }
    }
    tot = 0;
    for (int i = 1; i <= 100000; ++ i) {
        if (!vp[i].empty()) {
            idx[i] = tot ++;
        } else {
            idx[i] = -1;
        }
        if (!vp[i].empty() && vp[i].size() != 2) {
            sat.add_edge(idx[i] << 1 | 1,idx[i] << 1);
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            int a = A[i][j];
            for (int k = j + 1; k < n; ++ k) {
                int b = A[i][k];
                if (a == b) {
                    if (vp[a][0] == vp[a][1])
                        return false;
                } else {
                    for (int r = 0; r < vp[a].size(); ++ r) {
                        for (int t = 0; t < vp[b].size(); ++ t) {
                            if (vp[a][r] == vp[b][t]) {
                                sat.add_edge(idx[a] << 1 | r,idx[b] << 1 | t ^ 1);
                                sat.add_edge(idx[b] << 1 | t,idx[a] << 1 | r ^ 1);
                            }
                        }
                    }
                }
            }
        }
    }
    return sat.work(tot << 1);
}

int work() {
    {
        memset(cnt,0,sizeof(cnt));
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                cnt[A[i][j]] ++;
                if (B[i][j] < 1 || B[i][j] > 100000)
                    return -1;
                cnt[B[i][j]] --;
            }
        }
        for (int i = 1; i <= 100000; ++ i) {
            if (cnt[i])
                return -1;
        }
    }
    {
        bool flag = true;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                if (A[i][j] != B[i][j]) {
                    flag = false;
                }
            }
        }
        if (flag) {
            return 0;
        }
    }
    if (cr > cc) {
        reverse();
    }
    if (check1()) {
        return cr;
    }
    reverse();
    if (check1()) {
        return cc;
    }
    if (check2()) {
        return cr + cc;
    }
    reverse();
    if (check2()) {
        return cr + cc;
    }

    return (cr + cc) * 2 - std::max(cr,cc);
}

inline void read(int &x) {
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());
    for (x = 0; c >= '0'&& c <= '9'; c = getchar()) x = x * 10 + c - '0';
}

int main() {
    int cas;
    int ca = 0;
    read(cas);
    while (cas--) {
        read(n); read(cr); read(cc);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                read(A[i][j]);
            }
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                read(B[i][j]);
            }
        }
        printf("Case #%d: ",++ca);
        int answer = work();
        if (answer == -1) {
            puts("Take off the shoes!");
        } else {
            printf("%d\n",answer);
        }
    }
}
