/* Created Time: Friday, November 15, 2013 AM12:52:35 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long lld;
const int N = 101000;
const lld lim = (lld)1e9;
typedef pair<lld,int> PII;
int fa[N],n,m,p,q;
lld cnt[N];
int Find(int x) {
    return fa[x]==x ? x : fa[x] = Find(fa[x]);
}
int id[N];
void work() {
    for (int i = 1; i <= n; i ++)
        fa[i] = i;
    int sqt = n;
    for (int i = 0; i < m; i ++) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        a = Find(a);
        b = Find(b);
        cnt[b] += c;
        if (a==b) continue;
        fa[a] = b;
        cnt[b] += cnt[a];
        sqt --;
    }
    if (sqt<q || sqt==n&&p!=0&&q==n || sqt-p>q) {
        puts("NO");
        return ;
    }
    puts("YES");
    priority_queue <PII, vector<PII>, greater<PII> > que;
    for (int i = 1; i <= n; i ++) {
        int a = Find(i);
        que.push(PII(cnt[a],a));
    }
    int cur = 0;
    while (sqt>q) {
        PII f = que.top(); que.pop();
        f.second = Find(f.second);
        if (f.first!=cnt[f.second]) continue;
        if (cur==0) {
            cur = f.second;
            continue;
        } else {
            if (f.second==cur) continue;
            cur = Find(cur);
            f.second = Find(f.second);
            lld cost = min(lim,cnt[f.second]+cnt[cur]+1);
            fa[f.second] = fa[cur];
            cnt[cur] += cnt[f.second]+cost;
            printf("%d %d\n",f.second,cur);
            que.push(PII(cnt[cur],cur));
            cur = 0;
            sqt --;
            p --;
        }
    }
    int u,v;
    for (int i = 1; i <= n; i ++)
    {
        int a = Find(i);
        if (id[a]) {
            u = id[a];
            v = i;
            break;
        } else {
            id[a] = i;
        }
    }
    for (int i = 0; i < p; i ++) {
        printf("%d %d\n",u,v);
    }
}
int main() {
    scanf("%d%d%d%d",&n,&m,&p,&q);
    work();
    return 0;
}