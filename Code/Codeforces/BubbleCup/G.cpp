#include <bits/stdc++.h>

const int N = 100000 + 5;
struct Node {
    Node *lc,*rc;
    int hash;
} pool[5000000 + 5],*bat,*nill;

const int MOD = (int)1e9 + 9;
int n,m;
std::vector<std::pair<int,int>> edges[N];
const int base = 233;
Node *val[N];
int prevv[N],preve[N];
int base_pow[N];
int que[N];

const int INF = 0x3f3f3f3f;
int dis[N];
int level[N];
int to[N];

bool vis[N];

void insert(Node *pre,Node *&cur,int p,int c,int l,int r) {
    cur = bat ++;
    *cur = *pre;
    if (l == r) {
        cur->hash = c;
        return ;
    }
    int mid = l + r >> 1;
    if (p <= mid) insert(pre->lc,cur->lc,p,c,l,mid);
    else insert(pre->rc,cur->rc,p,c,mid + 1,r);
    cur->hash = (cur->lc->hash + 1ll * cur->rc->hash * base_pow[mid - l + 1]) % MOD;
}

bool smallthen(Node *a,Node *b,int l,int r) {
    if (a->hash == b->hash)
        return false;
    if (l == r) {
        return a->hash < b->hash;
    }
    int mid = l + r >> 1;
    if (a->rc->hash != b->rc->hash)
        return smallthen(a->rc,b->rc,mid + 1,r);
    else
        return smallthen(a->lc,b->lc,l,mid);
}

int main() {
    bat = pool;
    nill = new(bat++) Node;
    nill->lc = nill->rc = nill;
    nill->hash = 0;

    base_pow[0] = 1;
    for (int i = 1; i < N; ++ i) 
        base_pow[i] = base_pow[i - 1] * 1ll * base % MOD;

    scanf("%d%d",&n,&m);
    for (int i = 0; i < m; ++ i) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        edges[a].push_back({b,c});
        edges[b].push_back({a,c});
    }
    std::fill(dis,dis + n,INF);
    std::fill(to,to + n,-1);
    dis[n - 1] = 0;
    int qf = 0,qe = 0;
    que[qe++] = n - 1;
    while (qf != qe) {
        int u = que[qf++];
        for (auto t : edges[u]) {
            if (t.second != 0) continue;
            int v = t.first;
            if (dis[v] == INF) {
                dis[v] = dis[u] + 1;
                to[v] = u;
                que[qe++] = v;
            }
        }
    }
    if (dis[0] != INF) {
        puts("0");
        std::vector<int> answer;
        for (int u = 0; u != -1; u = to[u]) {
            answer.push_back(u);
        }
        printf("%d\n",answer.size());
        for (int i = 0; i < answer.size(); ++ i) {
            if (i) putchar(' ');
            printf("%d",answer[i]);
        }
        puts("");
        return 0;
    }
    std::fill(level,level + n,INF);
    qf = qe = 0;
    que[qe++] = 0;
    level[0] = 0;
    while (qf != qe) {
        int u = que[qf++];
        if (dis[u] != INF) continue;
        for (auto t : edges[u]) {
            int v = t.first;
            if (level[v] == INF) {
                level[v] = level[u] + 1;
                que[qe++] = v;
            }
        }
    }
    val[0] = nill;
    qf = qe = 0;
    que[qe++] = 0;
    while (qf != qe) {
        int u = que[qf++];
        if (dis[u] != INF) continue;
        for (auto t : edges[u]) {
            int v = t.first;
            int c = t.second;
            if (level[v] != level[u] + 1) continue;
            Node *cur;
            insert(val[u],cur,level[u] + 1,c,0,n);
            if (val[v] == NULL || smallthen(cur,val[v],0,n)) {
                val[v] = cur;
                prevv[v] = u;
                preve[v] = c;
            }
            if (!vis[v]) {
                vis[v] = true;
                que[qe++] = v;
            }
        }
    }
    int best = n - 1;
    for (int i = 0; i < n; ++ i) {
        if (dis[i] == INF || val[i] == NULL) continue;
        if (val[best] == NULL || smallthen(val[i],val[best],0,n)) {
            best = i;
        } else if (val[i]->hash == val[best]->hash && dis[i] + level[i] < dis[best] + level[best]) {
            best = i;
        }
    }
    for (int u = best; u != 0; u = prevv[u]) {
        printf("%d",preve[u]);
    }
    puts("");
    std::vector<int> answer;
    for (int u = best; u != 0; u = prevv[u]) {
        answer.push_back(u);
    }
    answer.push_back(0);
    std::reverse(answer.begin(),answer.end());
    for (int u = to[best]; u != -1; u = to[u])
        answer.push_back(u);
    printf("%d\n",answer.size());
    for (int i = 0; i < answer.size(); ++ i) {
        if (i) putchar(' ');
        printf("%d",answer[i]);
    }
    puts("");
}
