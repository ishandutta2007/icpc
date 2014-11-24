/* Created Time: Monday, November 25, 2013 AM07:50:20 CST */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
int a[2],b[2],ans[2],cur,cc;
bool ok;
void read() {
    scanf("%d%d%d%d",&a[0],&a[1],&b[0],&b[1]);
    if (ok) return ;
    for (int i = 0; i < 2; i ++)
        for (int j = 0; j < 2; j ++) {
            if (a[i]+b[j]<=n) {
                cur = cc+1;
                ans[0] += a[i];
                ans[1] += n-a[i];
                ok = true;
                return ;
            }
        }
}
int main() {
    scanf("%d",&n);
    for (cc = 0; cc < 4; cc ++) {
        read();
    }
    if (!ok) puts ("-1");
    else printf("%d %d %d\n",cur,ans[0],ans[1]);
    return 0;
}
