#include <bits/stdc++.h>
typedef long long LL;

int ch[800000 + 5][26];
int depth[800000 + 5];
int idx[800000 + 5][2],itot;
int tot;
int n;
std::vector<int> vec[200000 + 5];
LL answer;
std::vector<std::pair<int,int>> pr;

char str[800000 + 5];

void insert(char *str,int b,int id) {
    int cur = 0;
    while (*str) {
        int c = *str++ - 'a';
        if (ch[cur][c] == 0) {
            ch[cur][c] = tot;
            depth[tot] = depth[cur] + 1;
            tot ++;
        }
        cur = ch[cur][c];
    }
    if (idx[cur][b] == 0) {
        idx[cur][b] = itot ++;
    }
    vec[idx[cur][b]].push_back(id);
}

int merge(int a,int b) {
    if (vec[a].size() < vec[b].size()) {
        std::swap(a,b);
    }
    vec[a].insert(vec[a].end(),vec[b].begin(),vec[b].end());
    return a;
}

void dfs(int u) {
    for (int c = 0; c < 26; ++ c) {
        if (ch[u][c]) {
            dfs(ch[u][c]);
            idx[u][0] = merge(idx[u][0],idx[ch[u][c]][0]);
            idx[u][1] = merge(idx[u][1],idx[ch[u][c]][1]);
        }
    }
    auto &A = vec[idx[u][0]];
    auto &B = vec[idx[u][1]];
    int tmp = std::min(A.size(),B.size());
    for (int i = 0; i < tmp; ++ i) {
        pr.push_back({A[A.size() - i - 1],B[B.size() - i - 1]});
        answer += depth[u];
    }
    A.resize(A.size() - tmp);
    B.resize(B.size() - tmp);
}

void work() {
    dfs(0);
    printf("%I64d\n",answer);
    for (auto t : pr) {
        printf("%d %d\n",t.first + 1,t.second + 1);
    }
}

int main() {
    tot = 1;
    itot = 1;
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%s",str);
        insert(str,0,i);
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%s",str);
        insert(str,1,i);
    }
    work();
}
