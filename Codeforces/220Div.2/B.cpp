#include <iostream>
#include <algorithm>
using namespace std;
typedef long long lld;
const int N = 101000;
typedef pair<int,lld> PII;
string s;
PII f[N][2];
void update(PII &a,PII b) {
        if (a.first<b.first) a = b;
        else if (a.first==b.first) a.second += b.second;
}
lld work() {
        f[0][0].second = 1;
        for (int i = 0; i < (int)s.length(); i ++) {
                if (f[i][1].second && s[i]-'0'+s[i-1]-'0'==9) 
                        update(f[i+1][0],PII(f[i][1].first+1,f[i][1].second));
                update(f[i+1][1],f[i][0]);
                update(f[i+1][1],f[i][1]);
        }
        PII ret = PII(0,0);
        update(ret,f[s.length()][0]);
        update(ret,f[s.length()][1]);
        return ret.second;
}
int main() {
        cin >> s;
        cout << work() << endl;
        return 0;
}