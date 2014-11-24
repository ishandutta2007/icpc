/* Created Time: Tuesday, November 19, 2013 PM11:40:51 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long lld;
char s[4444];
lld sum[4444],fuc[555555];
lld a;
int main() {
    scanf("%lld",&a);
    scanf("%s",s+1);
    int len = strlen(s+1);
    for (int i = 1; s[i]; i ++)
        sum[i] = sum[i-1]+s[i]-'0';
    for (int i =1; i <= len; i ++) 
        for (int j = i; j <= len; j ++) 
            fuc[sum[j]-sum[i-1]] ++;
    lld ans = 0;
    for (int i = 1; i <= len; i ++)
        for (int j = i; j <= len; j ++) {
            lld x = sum[j]-sum[i-1];
            if (x==0) {
                if (a==0) ans += (lld) (len+1)*len/2;
                continue;
            }
            if (a%x==0 && a/x<555555) ans += fuc[a/x];
        }
    printf("%lld\n",ans);
    return 0;
}
