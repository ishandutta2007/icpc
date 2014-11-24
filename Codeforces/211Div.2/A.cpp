/* Created Time: Tuesday, November 19, 2013 AM11:16:58 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n;
void show(int x) {
    if (x>=5) printf("-O"),x -= 5;
    else printf("O-");
    printf("|");
    for (int i = 0; i < x; i ++)
        printf("O");
    printf("-");
    for (int i = 0; i < 4-x; i ++)
        printf("O");
    printf("\n");
}
int main() {
    scanf("%d",&n);
    if (n==0) {
        show(0);
        return 0;
    }
    while (n) {
        show(n%10);
        n /= 10;
    }
    return 0;
}
