/* Created Time: Monday, November 25, 2013 PM04:38:17 CST */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 101010;   
int n,a[N],mx[3];
bool cmp(int x,int y) { return a[x]>a[y]; }
void fuc(int l,int r) {
    int cnt = min(3,r-l+1);
    if (cnt==0) {
        puts("0"); return ;
    }
    for (int i = 0; i < cnt; i ++) {
        mx[i] = l+i;
    }
    sort(mx,mx+cnt,cmp);
    for (int i = l+cnt; i <= r; i ++) {
        mx[cnt] = i;
        sort(mx,mx+cnt+1,cmp);
    }
    sort(mx,mx+cnt);
    if (cnt) {
        for (int i = l; i < mx[0]; i ++) 
            puts("pushStack");
        puts("pushQueue");
        if (cnt>=2) {
            for (int i = mx[0]+1; i < mx[1]; i ++)
                puts("pushQueue");
            puts("pushBack");
            if (cnt>=3) {
                for (int i = mx[1]+1; i <= mx[2]; i ++)
                    puts("pushStack");
            }
        }
    }
    for (int i = mx[cnt-1]+1; i <= r; i ++)
        puts("pushBack");
    printf("%d popQueue",cnt);
    if (cnt>=2) printf(" popFront");
    if (cnt>=3) printf(" popStack");
    puts("");
}
void work() {
    int pre = 0;
    for (int i = 0; i < n; i ++) 
        if (a[i]==0) {
            fuc(pre,i-1);
            pre = i+1;
        } 
    if (pre!=n) {
        for (int i = pre; i < n; i ++)
            puts("pushFront");
    }
}
int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; i ++)
        scanf("%d",&a[i]);
    work();
    return 0;
}
