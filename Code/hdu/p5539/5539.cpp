#include <bits/stdc++.h>
typedef long long LL;

const int N = 100 + 5;
const int MOD = (int)1e9 + 7;
int X[N][2],Y[N][2],C[N],n;
LL answer[N];

struct O : std::vector<int> {
    void prepare() {
        std::sort(begin(),end());
        erase(std::unique(begin(),end()),end());
    }

    int get(int x) {
        return std::lower_bound(begin(),end(),x) - begin();
    }
} ss;

struct Line {
    int l,r,y,s;

    bool operator < (const Line &rhs) const {
        return y < rhs.y;
    }

    void show() {
        printf("l = %d,r = %d,y = %d,s = %d\n",l,r,y,s);
    }
};

struct SegmentTree {
    int s[N << 4],cnt[N << 4];

    void up(int l,int r,int rt) {
        if (cnt[rt]) {
            s[rt] = ss[r + 1] - ss[l];
        } else if (l != r) {
            s[rt] = s[rt << 1] + s[rt << 1 | 1];
        } else {
            s[rt] = 0;
        }
    }

    void modify(int L,int R,int dt,int l,int r,int rt) {
        if (L <= l && r <= R) {
            cnt[rt] += dt;
            up(l,r,rt);
            return ;
        }
        int mid = l + r >> 1;
        if (L <= mid) modify(L,R,dt,l,mid,rt << 1);
        if (mid < R) modify(L,R,dt,mid + 1,r,rt << 1 | 1);
        up(l,r,rt);
    }

    int query(int L,int R,int l,int r,int rt) {
        if (L <= l && r <= R) {
            return s[rt];
        }
        if (cnt[rt]) {
            return ss[std::min(R,r) + 1] - ss[std::max(l,L)];
        }
        int mid = l + r >> 1;
        int ret = 0;
        if (L <= mid) ret += query(L,R,l,mid,rt << 1);
        if (mid < R) ret += query(L,R,mid + 1,r,rt << 1 | 1);
        return ret;
    }
} sgt;

LL deal(std::vector<std::vector<Line>> &vec,int id,std::vector<Line> &cross) {
    int l = ss.get(X[id][0]),r = ss.get(X[id][1] + 1) - 1;
    int tot = 0;
    LL points = (Y[id][1] - Y[id][0] + 1) * 1ll * (X[id][1] - X[id][0] + 1);
    for (auto &ve : vec) {
        int pre = 0;
        LL fuck = 0;
        for (Line &line : ve) {
            int now = line.y;
            int ll = std::max(pre,Y[id][0]);
            int rr = std::min(now,Y[id][1] + 1);
            int len = rr - ll;
            if (len > 0) {
                fuck += sgt.query(l,r,0,ss.size() - 1,1) * 1ll * len;
            }
            sgt.modify(line.l,line.r,line.s,0,ss.size() - 1,1);
            pre = line.y;
        }
        if (fuck > 0) {
            for (Line &line : ve) {
                cross.push_back(line);
            }
            points = points - fuck + 1;
        } else {
            vec[tot++] = ve;
        }
    }
    vec.resize(tot);
    return (points - 1) % MOD * 1ll * C[id] % MOD;
}

LL solve(int tot) {
    std::vector<std::vector<Line>> vec;
    LL ret = 0;
    for (int i = 0; i < tot; ++ i) {
        std::vector<Line> cross;
        ret += deal(vec,i,cross);
        cross.push_back({ss.get(X[i][0]),ss.get(X[i][1] + 1) - 1,Y[i][0],1});
        cross.push_back({ss.get(X[i][0]),ss.get(X[i][1] + 1) - 1,Y[i][1] + 1,-1});
        std::sort(cross.begin(),cross.end());
        vec.push_back(cross);
    }
    return ret % MOD;
}

void work() {
    ss.clear();
    for (int i = 0; i < n; ++ i) {
        ss.push_back(X[i][0]);
        ss.push_back(X[i][1] + 1);
    }
    ss.prepare();

    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < i; ++ j) {
            if (C[i] > C[j]) {
                std::swap(X[i][0],X[j][0]);
                std::swap(X[i][1],X[j][1]);
                std::swap(Y[i][0],Y[j][0]);
                std::swap(Y[i][1],Y[j][1]);
                std::swap(C[i],C[j]);
            }
        }
        answer[i] = solve(i + 1);
    }
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d",&n);
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d%d%d%d",&X[i][0],&Y[i][0],&X[i][1],&Y[i][1],&C[i]);
        }
        work();
        for (int i = 0; i < n; ++ i) {
            printf("%lld\n",answer[i]);
        }
    }
}
