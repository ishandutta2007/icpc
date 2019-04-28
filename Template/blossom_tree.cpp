const int kN = 200 + 5;
std::deque<int> que;
bool graph[kN][kN],inq[kN],inblossom[kN];
int match[kN],pre[kN],base[kN];

int find_ancestor(int u,int v) {
  bool inpath[kN] = {};
  while (true) {
    u = base[u];
    inpath[u] = true;
    if (match[u] == -1) break;
    u = pre[match[u]];
  }
  while (true) {
    v = base[v];
    if (inpath[v]) return v;
    v = pre[match[v]];
  }
}

void reset(int u,int anc) {
  while (u != anc) {
    int v = match[u];
    inblossom[base[u]] = true;
    inblossom[base[v]] = true;
    v = pre[v];
    if (base[v] != anc) pre[v] = match[u];
    u = v;
  }
}

void contract(int u,int v,int n) {
  int anc = find_ancestor(u,v);
  memset(inblossom,0,sizeof(inblossom));
  reset(u,anc);
  reset(v,anc);
  if (base[u] != anc) pre[u] = v;
  if (base[v] != anc) pre[v] = u;
  for (int i = 0; i < n; ++ i) {
    if (inblossom[base[i]]) {
      base[i] = anc;
      if (!inq[i]) {
        que.push_back(i);
        inq[i] = true;
      }
    }
  }
}

bool dfs(int s,int n) {
  for (int i = 0; i < n; ++ i) {
    pre[i] = -1;
    inq[i] = false;
    base[i] = i;
  }
  que.clear();
  que.push_back(s);
  inq[s] = true;
  while (!que.empty()) {
    int u = que.front();
    que.pop_front();
    for (int v = 0; v < n; ++ v) {
      if (graph[u][v] && base[v] != base[u] && match[u] != v) {
        if (v == s || (match[v] != -1 && pre[match[v]] != -1)) {
          contract(u,v,n);
        } else if (pre[v] == -1) {
          pre[v] = u;
          if (match[v] != -1) {
            que.push_back(match[v]);
            inq[match[v]] = true;
          } else {
            u = v;
            while (u != -1) {
              v = pre[u];
              int w = match[v];
              match[u] = v;
              match[v] = u;
              u = w;
            }
            return true;
          }
        }
      }
    }
  }
  return false;
}

int solve(int n) {
  memset(match,-1,sizeof(match));
  int answer = 0;
  for (int i = 0; i < n; ++ i) {
    if (match[i] == -1 && dfs(i,n)) {
      answer ++;
    }
  }
  return answer;
}
