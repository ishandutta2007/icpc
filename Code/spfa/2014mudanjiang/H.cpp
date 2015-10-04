#include <bits/stdc++.h>

std::string str;

struct Node {
    int l,r;
    std::map<std::string,Node*> map;
} pool[50000 + 5],*bat,*root;

void build(Node *o,int l,int r) {
    o->l = l;
    o->r = r;
    o->map.clear();
    if (l >= r || str[l] == '"')
        return ;
    for (int i = l + 1; i < r - 1; ) {
        if (str[i] == '"') {
            int j = i + 1;
            while (str[j] != ':') ++ j;
            Node *c = bat ++;
            o->map[str.substr(i,j - i)] = c;
            i = j = j + 1;
            int cnt = 0;
            while (j < r - 1 && (cnt || str[j] != ',')) {
                if (str[j] == '{')
                    cnt ++;
                else if (str[j] == '}')
                    cnt --;
                ++ j;
            }
            build(c,i,j);
            i = j + 1;
        }
    }
}

void construct() {
    bat = pool;
    root = bat ++;
    build(root,0,str.length());
}

std::string work(std::string q) {
    Node *cur = root;
    for (int i = 0; i < q.length(); ) {
        int j = i + 1;
        while (j < q.length() && q[j] != '.') ++ j;
        std::string key = q.substr(i,j - i);
        if (cur->map.find(key) == cur->map.end()) {
            return "Error!";
        }
        cur = cur->map[key];
        i = j + 1;
    }
    return str.substr(cur->l,cur->r - cur->l);
}

char s[1000000 + 5];

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%s",s);
        str = s;
        construct();
        int m;
        scanf("%d",&m);
        for (int i = 0; i < m; ++ i) {
            scanf("%s",s);
            printf("%s\n",work(s).c_str());
        }
    }
}
