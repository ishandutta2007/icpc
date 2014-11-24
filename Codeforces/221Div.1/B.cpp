#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
const int N = 5555;
int n,m,mat[N][N];
vector<string> s;
int work() {
        for (int i = 0; i < n; i ++) {
                int cnt = 0;
                for (int j = 0; j < m; j ++) {
                        if (s[i][j]=='1') cnt ++;
                        else cnt = 0;
                        mat[j][cnt] ++;
                }
        }
        int ret = 0;
        for (int j = 0; j < m; j ++) {
                int cnt = 0;
                for (int i = m; i > 0; i --) {
                        cnt += mat[j][i];
                        ret = max(ret,cnt*i);
                }
        }
        return ret;
}
int main() {
        ios::sync_with_stdio(false);
        cin >> n >> m;
        s.resize(n);
        for (int i = 0; i < n; i ++) cin >> s[i];
        cout << work() << endl;
        return 0;
}
