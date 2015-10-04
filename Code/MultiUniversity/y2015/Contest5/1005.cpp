#include <bits/stdc++.h>


int belong[666];

bool work(int a,int b) {
    if (belong[a] != belong[b]) {
        return a < b;
    }
    if (a == 4 && b == 5) return true;
    if (a == 5 && b == 4) return false;
    if (a == 12 && b == 13) return true;
    if (a == 13 && b == 12) return false;
    if (a == 7 && b == 8) return true;
    if (a == 8 && b == 7) return false;
    if (a == 15 && b == 16) return true;
    if (a == 16 && b == 15) return false;
    return a > b;
}

void init() {
    int tot = 0;
    for (int i = 1; i <= 100; ++ i) {
        if (i == 1 || i == 3 || i == 11 || i == 19
                || i == 37 || i == 55 || i == 87)
            ++tot;
        belong[i] = tot;
    }
}

int main() {
    init();
    int a,b;
    while (scanf("%d%d",&a,&b) == 2) {
        puts(work(a,b) ? "FIRST BIGGER" : "SECOND BIGGER");
    }
}
