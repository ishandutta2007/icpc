#include <bits/stdc++.h>

using namespace std;

const int N = 1000+5;
int n, pos[N], pr[N];

int main() {
    freopen("avangard.in", "r", stdin);
    freopen("avangard.out", "w", stdout);
    int n;
    scanf("%d", &n);
    if(n == 1) {
        puts("Yes\n1\n");return 0;
    }
    int ans = -1;
    for(int i = 2;i < n-1; i++) {
        bool flag = true;
        for(int j = 1;j < n; j++) {
            int cur = j*i%n;
            if(cur==0) flag = false;
            if(cur==j) flag = false;
            if((n-j) == cur) flag = false;
        }
        if(flag) {
            ans = i;
            break;
        }
    }
    if(ans == -1) return puts("No") , 0;
//    printf("%d\n", ans);
    for(int i = 1;i <= n; i++) pos[i] = i;
    puts("Yes");
    for(int i = 1;i <= n; i++) {
        for(int j = 1;j <= n; j++) pr[pos[j]] = j;
        for(int j = 1;j <= n; j++)
            printf("%d ", pr[j]); puts("");
        for(int j = 1;j <= n; j++) {
            pos[j] += ans;
            if(pos[j] > n) pos[j] -= n;
        }
    }
    return 0;
}
