#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
int K,x,n,m;
struct Line {
        int l,r,cnt;
        Line operator + (Line &tt) {
                Line ret;
                ret.l = l;
                ret.r = tt.r;
                ret.cnt = cnt + tt.cnt + (r && tt.l);
                return ret;
        }
}line[55];
bool check() {
        if (line[0].l+line[0].r+line[0].cnt*2>n) return false;
        if (line[1].l+line[1].r+line[1].cnt*2>m) return false;
        for (int i = 2; i < K; i ++) {
                line[i] = line[i-2]+line[i-1];
                if (line[i].cnt>x) return false;
        }
        if (line[K-1].cnt==x) return true;
        return false;
}
void show(Line &x,int len) {
        if (x.l) cout << "C";
        for (int i = 0; i < x.cnt; i ++) cout << "AC";
        int left = len-x.l-x.r-x.cnt*2;
        for (int i = 0; i < left; i ++) cout << "D";
        if (x.r) cout << "A";
        cout << endl;
}
void work() {
        for (int i = 0; i*2<=n; i ++)
                for (int j = 0; j*2<=m; j ++) 
                        for (int il = 0; il < 2; il ++)
                                for (int ir = 0; ir < 2; ir ++)
                                        for (int jl = 0; jl < 2; jl ++)
                                                for (int jr = 0; jr < 2; jr ++) {
                                                        line[0] = (Line) {il,ir,i};
                                                        line[1] = (Line) {jl,jr,j};
                                                        if (check()) {
                                                                show(line[0],n);
                                                                show(line[1],m);
                                                                return;
                                                        }
                                                }
        cout << "Happy new year!" << endl;
}
int main() {
        ios::sync_with_stdio(false);
        cin >> K >> x >> n >> m;
        work();
        return 0;
}