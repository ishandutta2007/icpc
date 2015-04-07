const int INF = 0x3f3f3f3f;

template<int N> 
struct KM {
    int lv[N],rv[N],la[N],ra[N],left[N],G[N][N],n,m;
    bool expath(int u) {
        lv[u] = 1;
        for (int i = 0; i < m; i ++) 
            if (!rv[i] && la[u]+ra[i]==G[u][i]) {
                rv[i] = 1;
                if (left[i]==-1 || expath(left[i]))
                    return left[i] = u,true;
            }
        return false;
    }
    void init() {
        for (int i = 0; i < N; i ++)
            for (int j = 0; j < N; j ++) G[i][j] = -INF;
    }
    int km(int _n,int _m) {
        n = _n; m = _m;
        memset(left,-1,sizeof(left));
        for (int i = 0; i < n; i ++) {
            la[i] = -INF;
            for (int j = 0; j < m; j ++) la[i] = max(la[i],G[i][j]);
        }
        for (int i = 0; i < m; i ++) ra[i] = 0;
        for (int u = 0; u < n; u ++) {
            for (int i = 0; i < n; i ++) lv[i] = 0;
            for (int i = 0; i < m; i ++) rv[i] = 0;
            while (!expath(u)) {
                int d = INF;
                for (int i = 0; i < n; i ++) if (lv[i])
                    for (int j = 0; j < m; j ++) if (!rv[j])
                        d = min(d,la[i]+ra[j]-G[i][j]);
                for (int i = 0; i < n; i ++) 
                    if (lv[i]) la[i] -= d,lv[i] = 0;
                for (int i = 0; i < m; i ++)
                    if (rv[i]) ra[i] += d, rv[i] = 0;
            }
        }
        int ret = 0;
        for (int i = 0; i < m; i ++) if (left[i]!=-1) ret += G[left[i]][i];
        return ret;
    }
};
