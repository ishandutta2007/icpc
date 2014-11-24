/* Created Time: Monday, November 25, 2013 AM08:02:38 CST */
#include <cstdio>
int n,k;
int a[111111];
int main() {
    int d;
    scanf("%d%d",&n,&k);
    for (int i = 0; i < n; i ++)
        scanf("%d",&d), a[i%k] += d;
    int minx = 0;
    for (int i = 1; i < k; i ++)
        if (a[i]<a[minx]) minx = i;
    printf("%d\n",minx+1);
    return 0;
}
