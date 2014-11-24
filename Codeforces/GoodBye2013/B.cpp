#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
int n,a[333];
int main() {
        ios::sync_with_stdio(false);
        cin >> n;
        for (int i = 0; i < n; i ++) cin >> a[i];
        int dir = 1,sum = 0,pos = 0;
        for (int i = 0; i < n; i ++) sum += a[i];
        while (sum) {
                if (a[pos]) {
                        cout << 'P';
                        a[pos] --;
                        sum --;
                }
                pos += dir;
                if (pos==n) {
                        pos = n-2;
                        dir = -1;
                } else if (pos==-1) {
                        pos = 1;
                        dir = 1;
                }
                if (dir==1) cout << 'R';
                else cout << 'L';
        }
        cout << endl;
        return 0;
}