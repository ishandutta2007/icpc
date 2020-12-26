template<int kN> 
struct Sat {
    int head[kN],etot,stack[kN],top;
    bool mark[kN];
    struct Edge {int v,next;} g[501000];
    void init() {
        memset(head,-1,sizeof(head)); etot = 0;
    }
    void addEdge(int u,int v) {
        g[etot].v = v; g[etot].next = head[u]; head[u] = etot ++;
    }
    bool dfs(int u) {
        if (mark[u^1]) return false;
        if (mark[u]) return true;
        mark[u] = true;
        stack[top++] = u;
        for (int i = head[u]; i != -1; i = g[i].next) {
            int v = g[i].v;
            if (!dfs(v)) return false;
        }
        return true;
    }
    bool work(int n) {
        memset(mark,0,sizeof(mark));
        for (int i = 0; i < n; i += 2) {
            if (!mark[i] && !mark[i+1]) {
                top = 0;
                if (!dfs(i)) {
                    while (top) mark[stack[--top]] = false;
                    if (!dfs(i+1)) return false;
                }
            }
        }
        return true;
    }
};
