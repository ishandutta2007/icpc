#include <bits/stdc++.h>

const int N = 1000000 + 5;
bool mark[N];

int main() {
    int n;
    scanf("%d",&n);
    int mx = 0,now = 0;
    for (int i = 0; i < n; ++ i) {
        char str[2];
        int x;
        scanf("%s%d",str,&x);
        if (str[0] == '+') {
            mark[x] = true;
            now ++;
            mx = std::max(mx,now);
        } else {
            if (!mark[x]) {
                mx ++;
                now ++;
            }
            mark[x] = false;
            now --;
        }
    }
    printf("%d\n",mx);
}
