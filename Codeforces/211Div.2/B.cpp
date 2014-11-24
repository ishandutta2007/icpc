/* Created Time: Tuesday, November 19, 2013 AM11:22:34 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n,k;
int a[155555];
int main() {
    scanf("%d%d",&n,&k);
    for (int i = 0; i < n; i ++)
        scanf("%d",&a[i]);
    int sum = 0,minx = 0,p = 1;
    for (int i = 0; i < k; i ++)
        sum += a[i];
    minx = sum;
    for (int i = k; i < n; i ++) {
        sum -= a[i-k];
        sum += a[i];
        if (sum<minx) {
            minx = sum;
            p = i-k+2;
        }
    }
    printf("%d\n",p);
    return 0;
}
