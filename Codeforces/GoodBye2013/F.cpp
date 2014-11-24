#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1001000;
int plca[N][20],dep[N];
int lca(int a,int b) {
        if (dep[a]<dep[b]) swap(a,b);
        int delta = dep[a]-dep[b];
        for (int i = 0; i < 20; i ++) 
                if (delta>>i&1) a = plca[a][i];
        if (a!=b) {
                for (int i = 19; i >= 0; i --)
                        if (plca[a][i]!=plca[b][i])
                                a = plca[a][i],b = plca[b][i];
                a = plca[a][0];
        }
        return a;
}
int dis(int a,int b) {
        return dep[a]+dep[b]-2*dep[lca(a,b)];
}
int main() {
        ios::sync_with_stdio(false);
        int n,a,b,tot,diam,x;
        cin >> n;
        plca[2][0] = plca[3][0] = plca[4][0] = 1;
        dep[2] = dep[3] = dep[4] = 1;
        a = 2, b = 3,tot = 4,diam = 2;
        while (n--) {
                cin >> x;
                plca[++tot][0] = x; dep[tot] = dep[x]+1;
                for (int i = 1; i < 20; i ++)
                        plca[tot][i] = plca[plca[tot][i-1]][i-1];
                plca[++tot][0] = x; dep[tot] = dep[x]+1;
                for (int i = 1; i < 20; i ++)
                        plca[tot][i] = plca[plca[tot][i-1]][i-1];
                if (dis(a,tot)>diam) {
                        diam = dis(a,tot);
                        b = tot;
                } else if (dis(b,tot)>diam) {
                        diam = dis(b,tot);
                        a = tot;
                }
                cout << diam << endl;
        }
        return 0;
}