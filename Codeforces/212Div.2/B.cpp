/* Created Time: Thursday, November 14, 2013 PM11:53:09 CST */
#include <stdio.h>
#include <algorithm>
using namespace std;
int n,m;
int a[3333];
bool work() {
    if (a[0]==1) return false;
    if (a[m-1]==n) return false;
    int contiv = 0;
    for (int i = 1; i < m; i ++) {
        if (a[i]==a[i-1]+1) {
            contiv ++;
            if (contiv==2) return false;
        }
        else contiv = 0;
    }
    return true;
}
int main() {
    scanf("%d%d",&n,&m);
    for (int i = 0; i < m; i ++)
        scanf("%d",&a[i]);
    sort(a,a+m);
    puts(work() ? "YES" : "NO");
    return 0;
}