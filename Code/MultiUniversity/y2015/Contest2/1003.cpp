#include <bits/stdc++.h>
int w[3],b[3];

struct Edge {
    int u,v,w;
};

void my_assert(bool flag) {
    while (flag == false);
}

bool check(std::vector<Edge> &e) {
    static int deg[6000 + 5][2];
    for (int i = 1; i <= w[0] + w[1] + w[2]; ++ i) deg[i][0] = deg[i][1] = 0;
    std::set<std::pair<int,int>> set;
    for (auto t : e) {
        deg[t.u][t.w] ++;
        deg[t.v][t.w] ++;
        int u = t.u;
        int v = t.v;
        if (u == v) return false;
        if (u > v) std::swap(u,v);
        if (set.find({u,v}) != set.end()) return false;
        set.insert({u,v});
    }
    int cnt[3][2] = {};
    for (int i = 1; i <= w[0] + w[1] + w[2]; ++ i) {
        cnt[deg[i][0]][0] ++;
        cnt[deg[i][1]][1] ++;
    }
    for (int i = 0; i < 3; ++ i) {
        if (cnt[i][0] != w[i] || cnt[i][1] != b[i]) return false;
    }
    return true;
}

void work() {
    if (w[1] % 2 == 1 || b[1] % 2 == 1) {
        puts("-1");
        return ;
    }
    std::vector<Edge> e;
    int d = 0;
    if (w[2] < b[2]) {
        std::swap(w[0],b[0]);
        std::swap(w[1],b[1]);
        std::swap(w[2],b[2]);
        d ^= 1;
    }
    for (int i = 0; i < w[2] + 1; ++ i) {
        e.push_back({i + 1,i + 2,0});
    }
    for (int i = 0; i < w[1] - 2; i += 2) {
        e.push_back({3 + w[2] + i,4 + w[2] + i,0});
    }

    for (int i = 1; i + 2 <= b[2] + 1; i += 2) {
        e.push_back({i,i + 2,1});
    }
    if (b[2] + 1 & 1) {
        e.push_back({b[2] + 1,w[1] + w[2] + w[0],1});
        e.push_back({w[1] + w[2] + w[0],b[2],1});
        for (int i = b[2]; i - 2 >= 1; i -= 2) {
            e.push_back({i,i - 2,1});
        }
    } else {
        e.push_back({b[2],w[0] + w[1] + w[2],1});
        e.push_back({w[0] + w[1] + w[2],b[2] + 1,1});
        for (int i = b[2] + 1; i - 2 >= 1; i -= 2) {
            e.push_back({i,i - 2,1});
        }
    }
    int l = b[2] + 2,r = w[0] + w[1] + w[2] - 1;
    int cnt = b[1] - 2;
    for (int i = l; i + 2 <= r && cnt; i += 4,cnt -= 2) {
        e.push_back({i,i + 2,1});
    }
    for (int i = l + 1; i + 2 <= r && cnt; i += 4, cnt -= 2) {
        e.push_back({i,i + 2,1});
    }
    if (cnt == 1) {
        e.push_back({r,r - 1,1});
        cnt --;
    }
    my_assert(cnt == 0);
    if (!check(e)) {
        printf("%d\n",1 / 0);
    }

    printf("%d\n",e.size());
    for (auto t : e) {
        printf("%d %d %d\n",t.u,t.v,t.w ^ d);
    }
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d%d%d%d%d",w + 0,w + 1,w + 2,b + 0,b + 1,b + 2);
        work();
    }
}
