#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
using namespace std;
typedef pair<int,int> PII;
int n,ans[303000];
PII a[303000];
int main() {
        cin >> n;
        for (int i = 0; i < n; i ++) {
                cin >> a[i].first;
                a[i].second = i;
        }
        sort(a,a+n);
        int pre = 0;
        for (int i = 0; i < n; i ++) {
                if (a[i].first==pre) {
                        ans[a[i].second] = pre+1;
                        pre ++;
                } else if (a[i].first<pre) {
                        ans[a[i].second] = pre+1;
                        pre ++;
                } else {
                        ans[a[i].second] = a[i].first;
                        pre = a[i].first;
                }
        }
        for (int i = 0; i < n; i ++) cout << ans[i] << " ";
        cout << endl;
        return 0;
}