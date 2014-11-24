#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int,int> PII;
const int N = 101000;
int n,m,s,ans[N];
vector<PII> a;
struct point {
        int b,c,id;
        bool operator < (const point &tt) const {
                return b<tt.b;
        }
}dot[N];
bool go(int day) {
        priority_queue<PII> que;
        int ptr = m-1,p = n-1,cost = 0;
        while (ptr>=0) {
                while (p>=0 && a[ptr].first<=dot[p].b) {
                        que.push(PII(-dot[p].c,dot[p].id));
                        p --;
                }
                if (que.size()==0) return false;
                PII f = que.top(); que.pop();
                cost -= f.first;
                if (cost>s) return false;
                for (int i = max(0,ptr-day); i <= ptr; i ++) ans[a[i].second] = f.second;
                ptr -= day;
        }
        return true;
}
int main() {
        ios::sync_with_stdio(false);

        cin >> n >> m >> s;
        for (int i = 0; i < m; i ++) {
                int x;
                cin >> x;
                a.push_back(PII(x,i));
        }
        for (int i = 0; i < n; i ++) cin >> dot[i].b;
        for (int i = 0; i < n; i ++) {
                cin >> dot[i].c;
                dot[i].id = i+1;
        }
        sort(dot,dot+n);
        sort(a.begin(),a.end());
        int minday = -1,l = 1,r = m;
        while (l<=r) {
                int mid = l+r>>1;
                if (go(mid)) minday = mid,r = mid-1;
                else l = mid+1;
        }
        if (minday==-1) cout << "NO" << endl;
        else {
                cout << "YES" << endl;
                go(minday);
                for (int i = 0; i < m; i ++) cout << ans[i] << " ";
                cout << endl;
        }
        return 0;
}
