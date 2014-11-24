#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
int n,m,x,y,a,b;
int go(int ex,int ey) {
        int tx = abs(ex-x);
        int ty = abs(ey-y);
        if (tx%a || ty%b) return INF;
        tx /= a;
        ty /= b;
        if (abs(tx-ty)&1) return INF;
        if (tx<ty) {
                if (x-a<1 && x+a>n) return INF;
        } else if (tx>ty) {
                if (y-b<1 && y+b>m) return INF;
        }
        return max(tx,ty);
}
int main() {
        cin >> n >> m >> x >> y >> a >> b;
        int ans = INF;
        ans = min(ans,go(1,m));
        ans = min(ans,go(n,1));
        ans = min(ans,go(n,m));
        ans = min(ans,go(1,1));
        if (ans==INF)
                cout << "Poor Inna and pony!" << endl;
        else
                cout << ans << endl;
        return 0;
}