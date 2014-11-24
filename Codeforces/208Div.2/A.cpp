/* Created Time: Monday, November 25, 2013 PM02:07:37 CST */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[1010];
int l[1010],r[1010],tot;
bool go(int l1,int r1,int l2,int r2) {
    if (l1>l2) {
        swap(l1,l2);
        swap(r1,r2);
    }
    if (l2<r1 && r1<r2 && l1<l2) return true;
    return false;
}
bool check() {
    int n;
    scanf("%d",&n);
    int d,x;
    scanf("%d",&d);
    for (int i = 1; i < n; i ++) {
        scanf("%d",&x);
        l[tot] = d;
        r[tot] = x;
        if (l[tot]>r[tot]) swap(l[tot],r[tot]);
        for (int i = 0; i < tot-1; i ++) {
            if (go(l[i],r[i],l[tot],r[tot])) return true;
        }
        d = x;
        tot ++;
    }
    return false;
}
int main() {
    puts(check()? "yes" : "no");
    return 0;
}
