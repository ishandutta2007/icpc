#include <bits/stdc++.h>
using LL = long long ;

const int INF = 0x3f3f3f3f;
const int N = (1 << 20) + 5;
int n,A[N];
int high[N];
int count[N];

int work() {
    for (int mask = 0; mask < 1 << 20; ++ mask) {
        for (int i = 0; i < 20; ++ i) {
            if (mask >> i & 1) {
                count[mask] = i + 1;
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        int t = 0,a = A[i];
        while (a) {
            t ++;
            a >>= 1;
        }
        high[i] = t;
    }
    int ret = INF;
    for (int h = 1; h < 20; ++ h) {
        int aim = (1 << h) - 1;
        for (int i = 0; i < n; ++ i) {
            int a = A[i];
            if (high[i] < h) {
                a <<= h - high[i];
            } else {
                a >>= high[i] - h;
            }
            aim &= a;
        }
        int tmp = 0;
        for (int i = 0; i < n; ++ i) {
            int a = A[i];
            int t = tmp;
            if (high[i] < h) {
                tmp += count[(aim >> h - high[i]) ^ a] << 1;
                a <<= h - high[i];
                tmp += h - high[i];
            } else {
                a >>= high[i] - h;
                tmp += high[i] - h;
                tmp += count[aim ^ a] << 1;
            }
        }
        if (ret > tmp) {
            ret = tmp;
        }
    }
    return ret;
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A + i);
    }
    printf("%d\n",work());
}
