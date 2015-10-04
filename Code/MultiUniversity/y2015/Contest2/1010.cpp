#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
const int N = 500000 + 5;
int A[N],sum[N],n,m,K;
int R[N];
int next[N];
int que[N],qf,qe;

bool check(int limit) {
    qf = qe = 0;
    que[qe++] = INF;
    for (int i = n; i >= 1; -- i) {
        while (qe - qf >= 2 && que[qf + 1] - i >= limit) qf ++;
        if (qf != qe && que[qf] - i >= limit) {
            next[i] = que[qf];
            que[qe++] = i;
        }
        while (qf != qe && R[i] < que[qf]) qf ++;
    }
    return qf != qe;
}

void work() {
    {
        int cnt = 0,last = 0;
        for (int i = 1; i <= n; ++ i) {
            if (sum[i] + (i - 1) * K <= 0) {
                puts("Poor Hero!");
                return ;
            }
            if (sum[i] + last * K <= 0) {
                cnt ++;
                last = i - 1;
            }
        }
        if (cnt <= 1) {
            puts("Poor JRY!");
            return ;
        }
    }
    for (int i = 1; i <= n; ++ i) {
        R[i] = INF;
    }
    for (int i = 1; i <= n; ++ i) {
        if (sum[i] > 0) {
            continue;
        }
        int L = 1 + (-sum[i]) / K;
        R[L] = std::min(R[L],i - 1);
    }
    int l = 1,r = n - 1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    check(l - 1);
    printf("%d\n",l - 1);
    std::vector<int> answer;
    for (int u = que[qe - 1]; u < n; u = next[u]) {
        answer.push_back(u);
    }
    {
        int j = 0,last = 0;
        for (int i = 1; i <= n; ++ i) {
            while (sum[i] + K * last <= 0) {
                last = answer[j++];
            }
        }
        answer.resize(j);
    }
    printf("%d\n",answer.size());
    for (int i = 0; i < answer.size(); ++ i) {
        if (i) putchar(' ');
        printf("%d",answer[i]);
    }
    puts("");
}

inline void read(int &x) {
    char c; bool sign = false;
    for (c = getchar(); c < '0' || c > '9'; c = getchar()) if (c == '-') sign = true;
    for (x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
    sign && (x = -x);
}

int main() {
    //freopen("1010_std.in","r",stdin);
    //freopen("1010.out","w",stdout);
    while (scanf("%d%d%d",&n,&m,&K) == 3) {
        sum[0] = m;
        for (int i = 1; i <= n; ++ i) {
            read(A[i]);
            sum[i] = sum[i - 1] - A[i];
        }
        work();
    }
}
