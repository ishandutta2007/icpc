#include <bits/stdc++.h>


inline void read(int &x) {
    char c; bool sign = false;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        if (c == '-') sign = true;
    for (x = 0; c >= '0' && c <= '9'; c = getchar()) 
        x = x * 10 + c - '0';
    sign && (x = -x);
}


int main() {
    int n;
    while (scanf("%d",&n) == 1) {
        int cnt = 0;
        int mx = (int)-1e9;
        for (int i = 0; i < n; ++ i) {
            int op;
            read(op);
            if (op == 1) {
                int x;
                read(x);
                cnt ++;
                if (x > mx) {
                    mx = x;
                }
            } else if (op == 2) {
                if (cnt) {
                    cnt --;
                    if (cnt == 0) {
                        mx = (int)-1e9;
                    }
                }
            } else {
                if (cnt == 0) {
                    puts("0");
                } else {
                    printf("%d\n",mx);
                }
            }
        }
    }
}
