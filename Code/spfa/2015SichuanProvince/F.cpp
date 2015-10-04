#include <stdio.h>
#include <string.h>
#include <algorithm>

const int N = 100000 + 5;
const int M = 10000 + 5;

int n,A[N],B[N];
int C[N];
int bit[M];

void modify(int p,int dt) {
    for (int i = p + 1; i < M; i += i & -i) 
        bit[i] = std::max(bit[i],dt);
}

int query(int p) {
    int ret = 0;
    for (int i = p + 1; i > 0; i -= i & -i)
        ret = std::max(ret,bit[i]);
    return ret;
}

void clear() {
    memset(bit,0,sizeof(bit));
}

int solve() {
    clear();
    for (int i = 1; i < n; ++ i) {
        B[i] = 10000 - B[i];
    }
    for (int i = 1; i < n; ++ i) {
        if (B[i] != 0) {
            int tmp = query(B[i]);
            modify(B[i],10000 - B[i] + tmp);
        }
        C[i] = query(10000);
    }
    int ret = 0;
    clear();
    for (int i = n - 1; i >= 1; -- i) {
        ret = std::max(ret,C[i] + query(10000));
        if (B[i] != 0) {
            int tmp = query(B[i]);
            modify(B[i],10000 - B[i] + tmp);
        }
    }
    return ret + 10000;
}

int work() {
    if (n == 1) {
        return A[0] == 10000 ? 10000 : 0;
    }
    int ret = 0;
    for (int core = 0; core < n; ++ core) {
        if (A[core] == 10000) {
            for (int i = 0; i < n; ++ i) {
                B[i] = A[(core + i) % n];
            }
            ret = std::max(ret,solve());
        }
    }
    return ret;
}

int main() {
    while (scanf("%d",&n) == 1) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d",A + i);
        }
        printf("%d\n",work());
    }
}
