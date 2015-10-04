#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

typedef long long llint;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

const int MAX = 55;

int N;
int reach[MAX];
vector<int> adj[MAX];

int sz[MAX];
int depth[MAX];
llint dp[MAX][2][MAX][MAX];

llint f[2][MAX][MAX];
llint g[2][MAX][MAX];

void rec(int x, int dad) {
    for (int y : adj[x]) {
        if (y == dad) continue;

        depth[y] = depth[x] + 1;
        rec(y, x);
    }

    memset(f, 0, sizeof f);
    f[0][0][N] = 1;
    f[1][0][depth[x]] = 1;

    sz[x] = 1;
    for (int y : adj[x]) {
        if (y == dad) continue;
        memset(g, 0, sizeof g);

        REP(s, 2) REP(a, sz[x]+1) REP(d, N+1) if (f[s][a][d]) {
            REP(ss, 2) REP(aa, sz[y]+1) REP(dd, N+1) if (dp[y][ss][aa][dd]) {
                int sss = s ^ ss;
                int aaa = a + aa;
                int ddd = min(d, dd);
                g[sss][aaa][ddd] += f[s][a][d] * dp[y][ss][aa][dd];
            }
        }

        memcpy(f, g, sizeof g);
        sz[x] += sz[y];
    }

    memset(g, 0, sizeof g);
    REP(s, 2) REP(a, sz[x]+1) REP(d, N+1) if (f[s][a][d]) {
        int ss = s;
        int aa = a + (d < N && depth[x] + reach[x] >= d);
        int dd = d;
        g[ss][aa][dd] += f[s][a][d];
    }
    memcpy(f, g, sizeof g);

    memcpy(dp[x], f, sizeof f);
}

int main(void) {
    int TC;
    scanf("%d", &TC);
    REP(ti, TC) {
        scanf("%d", &N);
        REP(i, N) scanf("%d", &reach[i]);

        REP(i, N) adj[i].clear();
        FOR(i, 1, N) {
            int p; scanf("%d", &p); --p;
            adj[p].push_back(i);
            adj[i].push_back(p);
        }

        depth[0] = 0;
        rec(0, -1);

        // long double pos = 0;
        // long double neg = 0;

        // vector<long double> v;

        long double ans = 0;

        llint pos = 0, neg = 0;
        long double posd = 0, negd = 0;

        for (int a = N; a >= 1; --a) {
            llint sum = 0;
            REP(s, 2) REP(d, N+1) {
                llint w = dp[0][s][a][d];
                if (s == 0) sum -= w;
                if (s == 1) sum += w;
            }


            sum *= N;
            if (sum > 0) {
                pos += sum / a;
                posd += (sum % a) / (long double)a;
            }
            if (sum < 0) {
                neg += -sum / a;
                negd += (-sum % a) / (long double)a;
            }

            //      ans += sum * N / (long double)a / 100000;

            // if (sum > 0) pos += +sum / (long double)a;
            // if (sum < 0) neg += -sum / (long double)a;
            // v.push_back(sum * N / (long double)a);
        }

        // TRACE(pos _ neg);
        // long double ans = pos - neg;


        // auto cmp = [] (long double a, long double b) {
        //   return fabsl(a) > fabsl(b);
        // };
        // sort(v.begin(), v.end(), cmp);
        // ans = 0;
        // for (auto x : v) ans += x;

        ans = posd - negd;
        ans += pos - neg;
        printf("Case #%d: %.10lf\n", ti+1, (double)ans);
    }
    return 0;
}
