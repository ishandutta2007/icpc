#include <bits/stdc++.h>
typedef long long LL;

const LL Inf = (LL)1e14;
std::map<int,int> map;
int tot;
std::vector<std::pair<int,int>> A[100];
int n,m;
LL answer;
LL fee[100][8],last[100][8];

void search(int pos,int left,int money,LL tim) {
    if (money < 0) return ;
    if (tim >= answer) return ;
    if (left == 0) {
        answer = tim;
        return ;
    }
    if (pos == -1) {
        return ;
    }
    if (left > pos + 1) {
        return ;
    }
    if (fee[pos][left] > money) {
        return ;
    }
    if (last[pos][left] + tim >= answer) {
        return ;
    }
    for (int i = 0; i < A[pos].size(); ++ i) {
        search(pos - 1,left - 1,money - A[pos][i].second,tim + A[pos][i].first);
    }
    search(pos - 1,left,money,tim);
}

LL work() {
    if (tot < 7) return -1;
    for (int i = 0; i < tot; ++ i) {
        int p = 1;
        std::sort(A[i].begin(),A[i].end());
        for (int j = 1; j < A[i].size(); ++ j) {
            if (A[i][j].second < A[i][p - 1].second) {
                A[i][p ++] = A[i][j];
            }
        }
        A[i].resize(p);
    }
    std::sort(A,A + tot);
    answer = Inf;
    {
        std::vector<std::pair<int,int>> B;
        for (int i = 0; i < tot; ++ i) {
            B.push_back({A[i].back().second,A[i].back().first});
        }
        std::sort(B.begin(),B.end());
        answer = 0;
        LL cost = 0;
        for (int i = 0; i < 7; ++ i) {
            cost += B[i].first;
            answer += B[i].second;
        }
        if (cost > m) {
            return -1;
        }
    }
    {
        for (int i = 0; i < tot; ++ i) {
            std::vector<int> B,C;
            for (int j = 0; j <= i; ++ j) {
                B.push_back(A[j].back().second);
                C.push_back(A[j][0].first);
            }
            std::sort(B.begin(),B.end());
            std::sort(C.begin(),C.end());
            for (int j = 0; j <= 7; ++ j) {
                fee[i][j] = Inf;
                last[i][j] = Inf;
            }
            LL a = 0,b = 0;
            for (int j = 0; j < B.size() && j < 7; ++ j) {
                a += B[j];
                b += C[j];
                fee[i][j + 1] = a;
                last[i][j + 1] = b;
            }
        }
    }
    search(tot - 1,7,m,0);
    return answer;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        tot = 0;
        map.clear();
        for (int i = 0; i < n; ++ i) {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            if (b + 6 > m) continue;
            if (map.find(a) == map.end()) {
                map[a] = tot;
                A[tot].clear();
                tot ++;
            }
            A[map[a]].push_back({c,b});
        }
        printf("%lld\n",work());
    }
}
