#include <bits/stdc++.h>

const int N = 100 + 5;
int n;

std::vector<std::pair<std::pair<int,int>,int> > trains;
int sx,sy;
bool ok[N][3];

bool work() {
    ok[0][sx] = true;
    for (int t = 0; t + 1 < n; ++ t) {
        bool boom[3] = {};
        for (auto w : trains) {
            int x = w.first.first;
            int h = w.first.second - 2 * t;
            int l = w.second;
            int L = h;
            int R = h + l - 1;
            if (L <= t + 1 && t + 1 <= R)
                boom[x] = true;
        }
        for (int j = 0; j < 3; ++ j) {
            if (ok[t][j] && !boom[j]) {
                ok[t + 1][j] = true;
                if (j) ok[t + 1][j - 1] = true;
                if (j != 2) ok[t + 1][j + 1] = true;
            }
        }
        for (auto w : trains) {
            int x = w.first.first;
            int h = w.first.second - 2 * t;
            int l = w.second;
            int L = h - 2;
            int R = h + l - 1;
            if (L <= t + 1 && t + 1 <= R) {
                ok[t + 1][x] = false;
            }
        }
    }
    return ok[n - 1][0] | ok[n - 1][1] | ok[n - 1][2];
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%*d",&n);
        memset(ok,false,sizeof(ok));
        trains.clear();
        for (int i = 0; i < 3; ++ i) {
            char s[N];
            scanf("%s",s);
            for (int j = 0; j < n; ++ j) {
                if (s[j] == 's') {
                    sx = i,sy = j;
                }
            }
            for (int c = 0; c < 26; ++ c) {
                int cnt = 0;
                int head = -1;
                for (int j = 0; j < n; ++ j) {
                    if (s[j] == 'A' + c) {
                        if (head == -1) head = j;
                        cnt ++;
                    }
                }
                if (cnt) {
                    trains.push_back(std::make_pair(std::make_pair(i,head),
                                cnt));
                }
            }
        }
        puts(work() ? "YES" : "NO");
    }
}
