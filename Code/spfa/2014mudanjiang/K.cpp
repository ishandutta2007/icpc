#include <bits/stdc++.h>

const int N = 1000 + 5;

char str[N];

int work() {
    int ret = 0;
    int n = strlen(str);
    int co = 0;
    int nu = 0;
    for (int i = 0; i < n; ++ i) {
        co += str[i] == '*';
    }
    nu = n - co;
    int cnt = 0;
    if (nu < co + 1) {
        ret = co + 1 - nu;
        cnt = co + 1 - nu;
    }
    for (int i = 0,j = n - 1; i < n; ++ i) {
        if (str[i] != '*') {
            cnt ++;
            continue;
        }
        if (cnt - 1 >= 1) {
            -- cnt;
            continue;
        }
        while (str[j] == '*') -- j;
        std::swap(str[i],str[j]);
        ret ++;
        i --;
    }
    return ret;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%s",str);
        printf("%d\n",work());
    }
}
