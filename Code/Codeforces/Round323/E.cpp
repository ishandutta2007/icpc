#include <bits/stdc++.h>

const int MOD = (int)1e9 + 7;
int A[1 << 4][5];
int n;
char s[500 + 5];
int kind[500 + 5];

std::vector<std::pair<int,std::vector<int>>> stack;

int get_mask(int a,int r) {
    int mask = 0;
    for (int i = 0; i < n; ++ i) {
        mask |= (A[i][a] ^ r) << i;
    }
    return mask;
}

inline void add(int &a,int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}

void deal() {
    if (stack.size() < 3) {
        return ;
    }
    if (stack[stack.size() - 2].first < 0) {
        return ;
    }
    std::vector<int> v(1 << n);
    int p = stack[stack.size() - 2].first;
    if (s[p] == '&' || s[p] == '?') {
        std::vector<int> a = stack[stack.size() - 3].second,
            b = stack.back().second,c(1 << n);
        for (int i = 0; i < n; ++ i) {
            for (int mask = 0; mask < 1 << n; ++ mask) {
                if (mask >> i & 1) {
                    add(a[mask ^ 1 << i],a[mask]);
                    add(b[mask ^ 1 << i],b[mask]);
                }
            }
        }
        for (int mask = 0; mask < 1 << n; ++ mask) {
            c[mask] = a[mask] * 1ll * b[mask] % MOD;
        }
        for (int i = 0; i < n; ++ i) {
            for (int mask = 0; mask < 1 << n; ++ mask) {
                if (mask >> i & 1) {
                    add(c[mask ^ 1 << i],-c[mask]);
                }
            }
        }
        for (int mask = 0; mask < 1 << n; ++ mask) {
            add(v[mask],c[mask]);
        }
    }

    if (s[p] == '|' || s[p] == '?') {
        std::vector<int> a = stack[stack.size() - 3].second,
            b = stack.back().second,c(1 << n);
        for (int i = 0; i < n; ++ i) {
            for (int mask = 0; mask < 1 << n; ++ mask) {
                if (~mask >> i & 1) {
                    add(a[mask ^ 1 << i],a[mask]);
                    add(b[mask ^ 1 << i],b[mask]);
                }
            }
        }
        for (int mask = 0; mask < 1 << n; ++ mask) {
            c[mask] = a[mask] * 1ll * b[mask] % MOD;
        }
        for (int i = 0; i < n; ++ i) {
            for (int mask = 0; mask < 1 << n; ++ mask) {
                if (~mask >> i & 1) {
                    add(c[mask ^ 1 << i],-c[mask]);
                }
            }
        }
        for (int mask = 0; mask < 1 << n; ++ mask) {
            add(v[mask],c[mask]);
        }
    }
    stack[stack.size() - 3].second = v;
    stack.pop_back();
    stack.pop_back();
}

int work() {
    int len = strlen(s);
    for (int i = 0,last = 0; i < len; ++ i) {
        if (s[i] == '(') {
            last = 0;
            kind[i] = -1;
            continue;
        } else if (s[i] == ')') {
            last = 1;
            kind[i] = -2;
            continue;
        }
        kind[i] = (last ^= 1);
    }
    for (int i = 0; i < len; ++ i) {
        if (s[i] == '(') {
            stack.push_back({-1,std::vector<int>()});
        } else if (s[i] == ')') {
            stack[stack.size() - 2] = stack.back();
            stack.pop_back();
            deal();
        } else if (kind[i] == 0) {
            stack.push_back({i,std::vector<int>()});
        } else {
            std::vector<int> v(1 << n);
            for (int c = 0; c < 4; ++ c) {
                if (s[i] == 'A' + c || s[i] == '?') {
                    v[get_mask(c,0)] ++;
                }
                if (s[i] == 'a' + c || s[i] == '?') {
                    v[get_mask(c,1)] ++;
                }
            }
            stack.push_back({-3,v});
            deal();
        }
    }

    int mask = 0;
    for (int i = 0; i < n; ++ i)
        mask |= A[i][4] << i;

    return stack[0].second[mask];
}

int main() {
    scanf("%s",s);
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < 5; ++ j) {
            scanf("%d",&A[i][j]);
        }
    }
    printf("%d\n",work());
}
