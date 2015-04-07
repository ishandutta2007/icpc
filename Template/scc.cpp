const int N = 100000 + 5;

int dfn[N],low[N],belong[N],stack[N],instack[N],tim,top,tot,n,m;
std::vector<int> edges[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    stack[top++] = u;
    instack[u] = 1;
    for (int v : edges[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u],low[v]);
        } else if (instack[v]) {
            low[u] = std::min(low[u],dfn[v]);
        }
    }
    if (low[u]==dfn[u]) {
        while (true) {
            int v = stack[--top];
            instack[v] = 0;
            belong[v] = tot;
            if (v==u) break;
        }
        tot ++;
    }
}

void scc() {
    top = tim = tot = 0;
    memset(dfn,0,sizeof(dfn));
    memset(instack,0,sizeof(instack));
    for (int i = 0; i < n; i ++) if (!dfn[i]) tarjan(i);
}
