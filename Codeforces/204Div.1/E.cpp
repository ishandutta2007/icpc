/* Created Time: Friday, November 15, 2013 PM01:06:48 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 2222;
const int INF = 0x3f3f3f3f;
int n,a[N],f[N][N];
struct point {
    int val,pos,lm,rm;
    bool operator < (const point &tt) const {
        return val>tt.val || val==tt.val && pos<tt.pos;
    }
}dot[N];
int get(int l,int r) {
    f[0][0] = 0;
    for (int i = 1; i <= r-l+1; i ++) {
        int lm = dot[i+l-1].lm;
        int rm = dot[i+l-1].rm;
        f[i][0] = f[i-1][0]+lm;
        for (int j = 1; j < i; j ++)
            f[i][j] = min(f[i-1][j-1]+rm,f[i-1][j]+lm+j);
        f[i][i] = f[i-1][i-1]+rm;
    }
    int ret = INF;
    for (int i = 0; i <= r-l+1; i ++) {
        ret = min(ret,f[r-l+1][i]);
    }
    return ret;
}
int work() {
    for (int i = 0; i < n; i ++) {
        dot[i].val = a[i];
        dot[i].pos = i;
        for (int j = 0; j < i; j ++)
            dot[i].lm += (a[i]>a[j]);
        for (int j = i+1; j < n; j ++)
            dot[i].rm += (a[i]>a[j]);
    }
    sort(dot,dot+n);
    int ret = 0;
    for (int i = 0; i < n; i ++) {
        int p = i+1;
        while (p<n && dot[p].val==dot[i].val) p ++;
        ret += get(i,p-1);
        i = p-1;
    }
    return ret;
}
int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; i ++) {
        scanf("%d",&a[i]);
        a[i] = abs(a[i]);
    }
    printf("%d\n",work());
    return 0;
} 
