const int N = 50000 + 5;
int sa[N],rank[N],height[N];
void construct(const char *s,int n,int m = 256) {
    static int t1[N],t2[N],c[N];
    int *x = t1,*y = t2;
    int i,j,k,p,l;
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
    for (i = 0,l = 0; i < n; ++ i) {
        if (rank[i]) {
            j = sa[rank[i] - 1];
            while (s[i + l] == s[j + l]) l++;
            height[rank[i]] = l;
            if (l) l--;
        }
    }
}
