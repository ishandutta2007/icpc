#include <stdio.h>
#include <string.h>
#include <algorithm>
typedef long long LL;

const int N = 100000 + 5;
char str[3145728 + 5];

bool work() {
    int n = strlen(str);
    int d = 0;
    for (int i = 0; i < n; ++ i) {
        if (str[i] != 'v') {
            str[d++] = str[i];
        } else {
            if (str[i + 1] == 'v') {
                str[d++] = 'w';
            } else {
                str[d++] = 'v';
            }
        }
    }
    str[d] = 0;
    int now = 0;
    for (int i = 0; i < d; ++ i) {
        if (now == 0 && str[i] == 'w') now ++;
        else if (now == 1 && str[i] == 'y') now ++;
        else if (now == 2 && str[i] == 'h') return true;
    }
    return false;
}

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%s",str);
        puts(work() ? "Yes" : "No");
    }
}

