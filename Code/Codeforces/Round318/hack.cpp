#include <bits/stdc++.h>

int main() {
    int i,j,k;
    for (i = 1e9; i % 3 == 0 || i % 2 == 0; -- i);
    printf("i = %d\n",i);
    for (j = 1; j * 2 <= (int)1e9; j *= 2);
    for (k = 1; k * 3 <= (int)1e9; k *= 3);
    printf("%I64d\n",i * 1ll * j * k);
}
