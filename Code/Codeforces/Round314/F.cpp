#include <bits/stdc++.h>
typedef long long LL;

LL dp[71][71];
bool vis[71][71];
int n,m;
std::vector<std::pair<std::string,int>> as[71];

bool check(int x,int y,int l,int r,int L,int R) {
    for (auto t : as[x]) {
        std::string op = t.first;
        int b = t.second;
        if (op == "=") {
            if (b != y) {
                return false;
            }
        } else if (op == "<") {
            if (!(l <= b && b <= r)) {
                return false;
            }
        } else if (op == ">") {
            if (!(b < L || b > R)) {
                return false;
            }
        } else if (op == "<=") {
            if (!(L <= b && b <= R)) {
                return false;
            }
        } else if (op == ">=") {
            if (b != y && !(b < L || b > R)) {
                return false;
            }
        }
    }
    return true;
}

void calc(int l,int r) {
    if (l > r) return ;
    if (vis[l][r]) {
        return ;
    }
    vis[l][r] = true;
    if (r - l + 1 == 2) {
        if (check(l,r,l + 1,r - 1,l,r) && check(r,l,l + 1,r - 1,l,r)) {
            dp[l][r] = 1;
        }
        return ;
    }
    if (check(l,l + 1,l + 2,r,l,r) && check(l + 1,l,l + 2,r,l,r)) {
        calc(l + 2,r);
        dp[l][r] += dp[l + 2][r];
    }
    if (check(r - 1,r,l,r - 2,l,r) && check(r,r - 1,l,r - 2,l,r)) {
        calc(l,r - 2);
        dp[l][r] += dp[l][r - 2];
    }
    if (check(l,r,l + 1,r - 1,l,r) && check(r,l,l + 1,r - 1,l,r)) {
        calc(l + 1,r - 1);
        dp[l][r] += dp[l + 1][r - 1];
    }
}

int main() {
    scanf("%d%d",&n,&m);
    bool bad = false;
    for (int i = 0; i < m; ++ i) {
        int a,b;
        char str[13];
        scanf("%d%s%d",&a,str,&b);
        if (a == b) {
            if (str[0] == '=' || str[1] == '=') {
                continue;
            }
            bad = true;
        }
        as[a].push_back({std::string(str),b});
        if (str[0] == '>') {
            str[0] = '<';
        } else if (str[0] == '<') {
            str[0] = '>';
        }
        as[b].push_back({std::string(str),a});
    }
    if (bad) {
        puts("0");
        return 0;
    }
    calc(1,2 * n);
    printf("%I64d\n",dp[1][2 * n]);
}
