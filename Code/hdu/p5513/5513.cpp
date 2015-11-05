#include <bits/stdc++.h>
typedef long long LL;

const int INF = 0x3f3f3f3f;
const int MOD = (int)1e9 + 7;
int A[800][7],B[800][7];
int n,m;
int w[2][1000000],s[2][1000000];
std::queue<int> que[2];
int cur,nex;

void decode(int *a,int mask) {
    for (int i = 0; i < m; ++ i) {
        a[i] = mask % m;
        mask /= m;
    }
}

void my_assert(bool flag) {
    while (!flag);
}

int encode(int *a) {
    int ret = 0;
    int hash[8] = {},cnt[8] = {},tot = 0;
    for (int i = 0; i < m; ++ i) {
        cnt[a[i]] ++;
    }
    for (int i = 0; i < m; ++ i) {
        if (a[i] != 0) {
            if (cnt[a[i]] == 1) {
                a[i] = 0;
            } else {
                if (hash[a[i]] == 0)
                    hash[a[i]] = ++ tot;
                a[i] = hash[a[i]];
            }
        }
    }
    for (int i = m - 1; i >= 0; -- i)
        ret = ret * m + a[i];
    return ret;
}

void show(int status) {
    int a[m];
    decode(a,status);
    for (int i = 0; i < m; ++ i) {
        printf("%d ",a[i]);
    }
    printf(":: %d %d\n",w[cur][status],s[cur][status]);
}

void update(int status,int nstatus,int cost,int cnt) {
    int tmp = w[cur][status] + cost;
    int sum = s[cur][status] * 1ll * cnt % MOD;
    if (tmp < w[nex][nstatus]) {
        if (w[nex][nstatus] == INF) {
            que[nex].push(nstatus);
            //printf("nex = %d,nstatus = %d\n",nex,nstatus);
        }
        w[nex][nstatus] = tmp;
        s[nex][nstatus] = sum;
    } else if (tmp == w[nex][nstatus]) {
        (s[nex][nstatus] += sum) %= MOD;
    }
}

void work() {
    memset(w,INF,sizeof(w));
    memset(s,0,sizeof(s));
    while (!que[0].empty()) que[0].pop();
    while (!que[1].empty()) que[1].pop();

    w[0][0] = 0;
    s[0][0] = 1;
    que[0].push(0);
    cur = 0,nex = 1;
    for (int raw = 0; raw < n; ++ raw) {
        for (int col = 0; col < m; ++ col) {
            while (!que[cur].empty()) {
                int status = que[cur].front(); que[cur].pop();
                //printf("raw = %d,col = %d,",raw,col);
                //show(status);
                int a[m];

                for (int e = 0; e < 1 << 2; ++ e) {
                    if (col == 0 && (e & 1)) continue;
                    if (raw == 0 && (e & 2)) continue;

                    int cost = ((e & 1) ? A[raw][col - 1] : 0) + ((e & 2) ? B[raw - 1][col] : 0);
                    int cnt = (e & 1) + (e >> 1 & 1) + 1;

                    if (e == 0) {
                        decode(a,status);
                        if (raw != 0 && a[col] == 0) continue;
                        a[col] = 0;
                        update(status,encode(a),cost,cnt);
                    } else if (e == 3) {
                        decode(a,status);
                        if (a[col - 1] != 0 && a[col - 1] == a[col]) continue;
                        if (a[col - 1] != 0 && a[col] != 0) {
                            int t = a[col - 1];
                            for (int i = 0; i < m; ++ i) {
                                if (a[i] == t)
                                    a[i] = a[col];
                            }
                        } else if (a[col - 1] != 0) {
                            a[col] = a[col - 1];
                        } else if (a[col] != 0) {
                            a[col - 1] = a[col];
                        } else {
                            a[col - 1] = a[col] = m;
                        }
                        update(status,encode(a),cost,cnt);
                    } else if (e == 1) {
                        decode(a,status);
                        if (raw != 0 && a[col] == 0) continue;
                        if (a[col - 1] == 0) {
                            a[col - 1] = a[col] = m;
                        } else {
                            a[col] = a[col - 1];
                        }
                        update(status,encode(a),cost,cnt);
                    } else if (e == 2) {
                        update(status,status,cost,cnt);
                    }
                }

                w[cur][status] = INF;
                s[cur][status] = 0;
            }
            std::swap(cur,nex);
        }
    }
    int status;
    if (m == 1) {
        status = 0;
    } else {
        int a[m];
        for (int i = 0; i < m; ++ i)
            a[i] = 1;
        status = encode(a);
    }
    printf("%d %d\n",w[cur][status],s[cur][status]);
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) { 
        scanf("%d%d",&n,&m);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m - 1; ++ j) {
                scanf("%d",&A[i][j]);
            }
        }
        for (int i = 0; i < n - 1; ++ i) {
            for (int j = 0; j < m; ++ j) {
                scanf("%d",&B[i][j]);
            }
        }
        printf("Case #%d: ",++ca);
        work();
    }
}
