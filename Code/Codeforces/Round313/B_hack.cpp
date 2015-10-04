#include <bits/stdc++.h>

unsigned ran() {
    return rand() << 16 | rand();
}

char str[200000 + 5];

int main() {
    freopen("B_hack.data","w",stdout);
    srand(time(NULL));
    int n = 1;
    while ((n << 1) <= 200000) n <<= 1;
    n >>= 1;
    for (int i = 0; i < n; ++ i) {
        str[i] = 'a' + ran() % 26;
        printf("%c",str[i]);
    }
    puts("");
    str[n / 2 - 1] = (str[n / 2 - 1] + 25 - 'a') % 26 + 1;
    str[n - 1] = 'a' + rand() % 26;
    for (int i = n - 1; i >= 0; -- i) {
        printf("%c",str[i]);
    }
    puts("");
}
