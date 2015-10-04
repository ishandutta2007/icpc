#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <assert.h>

int n;

void work() {
    if (n <= 3) {
        puts("-1");
    } else if (n == 4) {
        printf("1 * 2\n");
        printf("5 + 3\n");
        printf("6 + 4\n");
    } else if (n == 5) {
        printf("1 * 2\n");
        printf("6 * 3\n");
        printf("7 - 4\n");
        printf("8 / 5\n");
    } else if (n == 6) {
        printf("1 - 2\n");
        printf("7 + 3\n");
        printf("8 + 4\n");
        printf("9 + 5\n");
        printf("10 + 6\n");
    } else if (n == 7) {
        printf("1 + 2\n");
        printf("8 + 3\n");
        printf("9 / 4\n");
        printf("10 + 5\n");
        printf("11 + 6\n");
        printf("12 + 7\n");
    } else if (n == 8) {
        printf("1 - 2\n");
        printf("9 * 3\n");
        printf("10 * 4\n");
        printf("11 * 5\n");
        printf("12 + 6\n");
        printf("13 + 7\n");
        printf("14 + 8\n");
    } else if (n == 9) {
        printf("1 + 2\n");
        printf("10 + 3\n");
        printf("4 / 5\n");
        printf("11 - 12\n");
        printf("6 / 7\n");
        printf("13 - 14\n");
        printf("8 / 9\n");
        printf("15 - 16\n");
    } else if (n == 10) {
        printf("1 / 2\n");
        printf("3 / 4\n");
        printf("5 / 6\n");
        printf("7 / 8\n");
        printf("9 + 10\n");
        printf("15 + 11\n");
        printf("16 + 12\n");
        printf("17 + 13\n");
        printf("18 + 14\n");
    } else if (n == 11) {
        printf("1 - 2\n");
        printf("12 * 3\n");
        printf("13 * 4\n");
        printf("14 * 5\n");
        printf("15 + 6\n");
        printf("16 + 7\n");
        printf("8 / 9\n");
        printf("17 + 18\n");
        printf("10 / 11\n");
        printf("19 + 20\n");
    } else if (12 <= n && n <= 14) {
        printf("1 + 2\n");
        int left = n * 2 - 24;
        int cur = n + 1;
        int p = 3;
        for (int i = 0; i < left; ++ i) {
            printf("%d / %d\n",p,p + 1);
            p += 2;
            printf("%d - %d\n",cur,cur + 1);
            cur += 2;
        }
        int t = cur;
        assert(p + 1 <= n);
        printf("%d - %d\n",p,p + 1);
        t ++;
        p += 2;
        for (int i = p; i <= n; ++ i) {
            printf("%d * %d\n",t,i);
            t ++;
        }
        printf("%d + %d\n",cur,2 * n - 2);
    } else if (15 <= n && n <= 16) {
        printf("1 + 2\n");
        int cur = n + 1;
        int p = 3;
        for (int i = 0; i < 24 - n - 2; ++ i) {
            printf("%d + %d\n",cur++,p++);
        }
        printf("%d / %d\n",cur++,p++);
        printf("%d + %d\n",cur++,p++);
        assert(p + 1 <= n);
        printf("%d - %d\n",p,p + 1);
        p += 2;
        int t = cur + 1;
        for (int i = p; i <= n; ++ i) {
            printf("%d * %d\n",t++,i);
        }
        printf("%d + %d\n",cur,2 * n - 2);
    } else if (17 <= n && n <= 23) {
        int cnt = 0;
        printf("1 / 2\n");
        cnt ++;
        int cur = n + 1;
        int p = 3;
        int left = 24 - n;
        printf("%d + %d\n",p++,cur++);
        cnt ++;
        left --;
        for (int i = 0; i < left; ++ i) {
            printf("%d / %d\n",p,p + 1);
            p += 2;
            cnt ++;
            printf("%d + %d\n",cur,cur + 1);
            cur += 2;
            cnt ++;
        }
        assert(n - (cnt + 1) >= 2);
        printf("%d - %d\n",p,p + 1);
        cnt ++;
        p += 2;
        int t = cur + 1;
        for (int i = p; i <= n; ++ i) {
            printf("%d * %d\n",t++,i);
            cnt ++;
        }
        printf("%d + %d\n",cur,2 * n - 2);
    } else if (n == 24) {
        printf("1 - 2\n");
        int t = n + 1;
        for (int i = 3; i <= 23; ++ i) {
            printf("%d * %d\n",i,t++);
        }
        printf("%d + %d\n",t,24);
    } else if (25 <= n && n <= 45) {
        printf("1 / 2\n");
        printf("3 - %d\n",n + 1);
        int cur = n + 2;
        int p = 4;
        int left = n - 1 - 24;
        for (int i = 0; i < left; ++ i) {
            printf("%d / %d\n",p,p + 1);
            p += 2;
            printf("%d - %d\n",cur,cur + 1);
            cur += 2;
        }
        assert(p + 1 <= n);
        printf("%d - %d\n",p,p + 1);
        int t = cur + 1;
        p += 2;
        for (int i = p; i <= n; ++ i) {
            printf("%d * %d\n",t++,i);
        }
        printf("%d + %d\n",cur,2 * n - 2);
    } else {
        printf("1 + 2\n");
        int cur = n + 1;
        int p = 3;
        for (int i = 0; i < 22; ++ i) {
            printf("%d + %d\n",cur++,p++);
        }
        printf("%d / %d\n",cur++,p++);
        printf("%d - %d\n",p,p + 1);
        p += 2;
        int t = cur + 1;
        for (int i = p; i <= n; ++ i) {
            printf("%d * %d\n",t++,i);
        }
        printf("%d + %d\n",cur,2 * n - 2);
    }
}


int main() {
    while (scanf("%d",&n) == 1) {
        work();
    }
}
