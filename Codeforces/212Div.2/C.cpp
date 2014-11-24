/* Created Time: Friday, November 15, 2013 AM11:50:48 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int a[5555],n;
int ll[5555][5555],rr[5555][5555];
int main() {
    scanf("%d",&n);
    int sum = 0;
    for (int i = 0; i < n; i ++) {
        scanf("%d",&a[i]);
        for (int j = 0; j < i; j ++)
            sum += (a[j]>a[i]);
    }

    for (int i = 0; i < n; i ++) {
        int cnt = 0;
        for (int j = i-1; j >= 0; j --)
            rr[j][i] = (cnt+=(a[j]>a[i]));
    }
    for (int i = 0; i < n; i ++) {
        int cnt = 0;
        for (int j = i+1; j < n; j ++)
            ll[i][j] = (cnt+=(a[i]<a[j]));
    }
    int maxn = 0,cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j ++) {
            int cur = rr[i+1][j]-(j-1-i-1+1-rr[i+1][j])-ll[i][j-1]+(j-1-i-1+1-ll[i][j-1])+(a[i]>a[j]?1:-1);
            if (cur>maxn) {
                maxn = cur;
                cnt = 1;
            } else if (cur==maxn) {
                cnt ++;
            }
        }
    }
    printf("%d %d\n",sum-maxn,cnt);
    return 0;
}