#include <bits/stdc++.h>
typedef long long LL;

const int N = 50000 + 5;

int sa[N],rank[N],height[N];

void construct(const char *s,int n,int m = 256) {
    static int t1[N],t2[N],c[N];
    int *x = t1,*y = t2;
    int i,j,k,p,length;
    for (i = 0; i < m; ++ i) c[i] = 0;
    for (i = 0; i < n; ++ i) c[x[i] = s[i]] ++;
    for (i = 1; i < m; ++ i) c[i] += c[i - 1];
    for (i = n - 1; i >= 0; -- i) sa[--c[x[i]]] = i;
    for (k = 1; k <= n; k <<= 1) {
        p = 0;
        for (i = n - k; i < n; ++ i) y[p++] = i;
        for (i = 0; i < n; ++ i) if (sa[i] >= k) y[p++] = sa[i] - k;
        for (i = 0; i < m; ++ i) c[i] = 0;
        for (i = 0; i < n; ++ i) c[x[y[i]]] ++;
        for (i = 1; i < m; ++ i) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; -- i) sa[--c[x[y[i]]]] = y[i];
        std::swap(x,y);
        p = 1; x[sa[0]] = 0;
        for (i = 1; i < n; ++ i) 
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] 
                && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1: p ++;
        if (p >= n) break;
        m = p;
    }
    for (i = 0; i < n; ++ i) rank[sa[i]] = i;
    for (i = 0,length = 0; i < n; ++ i) {
        if (rank[i]) {
            j = sa[rank[i] - 1];
            while (s[i + length] == s[j + length]) length ++;
            height[rank[i]] = length;
            if (length) length --;
        }
    }
}

char str[N];
int K;
LL answer[32];
int n;
int L[N];

int dsu[N],ten[N],val[N],cnt[N][32];

int Find(int x) {
    if (x == -1 || dsu[x] == x) return x;
    int y = dsu[x];
    int z = dsu[x] = Find(dsu[x]);
    if (y != dsu[x]) {
        val[x] = (val[x] * ten[y - z] + val[y]) % K;
        int tmp[32] = {};
        for (int i = 0; i < K; ++ i) {
            tmp[(i * ten[y - z] + val[y]) % K] += cnt[x][i];
            tmp[i] += cnt[y][i];
        }
        for (int i = 0; i < K; ++ i) {
            cnt[x][i] = tmp[i];
        }
    }
    return z;
}

void work() {
    n = strlen(str);
    std::reverse(str,str + n);
    construct(str,n + 1);
    for (int i = 0; i < n; ++ i) {
        L[i] = 1;
    }
    for (int i = 2; i <= n; ++ i) {
        L[sa[i]] = height[i] + 1;
    }
    ten[0] = 1 % K;
    for (int i = 1; i <= n; ++ i) {
        ten[i] = ten[i - 1] * 10 % K;
    }
    /*
    for (int i = 0; i < n; ++ i) {
        dsu[i] = i;
        val[i] = (str[i] - '0') % K;
        for (int j = 0; j < K; ++ j) {
            cnt[i][j] = 0;
        }
        if (str[i] != '0') {
            cnt[i][val[i]] ++;
        }
    }
    */
    for (int i = 0; i < n; ++ i) {
        dsu[i] = i;
        for (int j = 0; j < K; ++ j) {
            cnt[i][j] = 0;
        }
    }
    memset(answer,0,sizeof(answer));
    for (int i = n - 1; i >= 0; -- i) {
        val[i] = (str[i] - '0') % K;
        if (str[i] != '0') {
            cnt[i][val[i]] ++;
        }
        int l = i + L[i] - 1;
        int r = n - 1;
        dsu[i] = i - 1;
        Find(r);
        Find(l - 1);
        for (int j = 0; j < K; ++ j) {
            answer[j] += cnt[r][j];
            if (l > 0) {
                answer[j] -= cnt[l - 1][j];
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (str[i] == '0') {
            answer[0] ++;
            break;
        }
    }
}

int main() {
    while (scanf("%s%d",str,&K) == 2) {
        work();
        for (int i = 0; i < K; ++ i) {
            if (i) putchar(' ');
            printf("%lld",answer[i]);
        }
        puts("");
    }

}
