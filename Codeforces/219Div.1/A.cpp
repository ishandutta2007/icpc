#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 501000;
int n,a[N];
bool check(int p) {
    for (int i = p-1; i >= 0; i --) {
        if (a[i]*2>a[n-p+i]) return false;
    }
    return true;
}
int work() {
    int l = 0,r = n>>1;
    while (l<=r) {
        int mid = l+r>>1;
        if (check(mid)) l = mid+1;
        else r = mid-1;
    }
    return n-(l-1);
}
int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; i ++) scanf("%d",&a[i]);
    sort(a,a+n);
    printf("%d\n",work());
    return 0;
}
