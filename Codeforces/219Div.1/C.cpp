#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
typedef __int64 lld;
const int N = 150010;
int n,m,d,cur,nex,pretime,passtime;
lld dp[2][N];
vector <int> bag;
deque <int> que;
void trans() {
    while (!que.empty()) que.pop_front();
    for (int i = 1; i <= n; i ++) {
        while (!que.empty() && i-que.front()>(lld)passtime*d) que.pop_front();
        while (!que.empty() && dp[cur][que.back()]<=dp[cur][i]) que.pop_back();
        que.push_back(i);
        int pos = que.front();
        lld tmp = dp[cur][pos];
        for (int j = 0; j < bag.size(); j ++) {
            tmp -= abs(i-bag[j]);
        }
        dp[nex][i] = tmp;
    }
    while (!que.empty()) que.pop_front();
    for (int i = n; i >= 1; i --) {
        while (!que.empty() && que.front()-i>(lld)passtime*d) que.pop_front();
        while (!que.empty() && dp[cur][que.back()]<=dp[cur][i]) que.pop_back();
        que.push_back(i);
        int pos = que.front();
        lld tmp = dp[cur][pos];
        for (int j = 0; j < bag.size(); j ++) {
            tmp -= abs(i-bag[j]);
        }
        dp[nex][i] = max(dp[nex][i],tmp);
    }
    swap(cur,nex);
}
lld work() {
    cur = 0; nex = 1;
    lld sum = 0;
    passtime = N;
    for (int i = 0; i < m; i ++) {
        int a,b,t;
        scanf("%d%d%d",&a,&b,&t);
        sum += b;
        if (!i || pretime==t) {
            bag.push_back(a);
            pretime = t;
            continue;
        } else {
            trans();
            passtime = t-pretime;
            bag.clear();
            pretime = t;
            bag.push_back(a);
        }
    }
    trans();
    lld ret = (lld)-1e30;
    for (int i = 1; i <= n; i ++) ret = max(ret,dp[cur][i]);
    return ret+sum;
}
int main() {
    scanf("%d%d%d",&n,&m,&d);
    printf("%I64d\n",work());
    return 0;
}
