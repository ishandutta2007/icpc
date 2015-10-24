#include <bits/stdc++.h>
typedef long long LL;

const int N = 100000 + 5;
char str[N];
int n;
int sz[N];

LL work() {
    n = strlen(str);
    LL ret = 0;
    std::vector<std::pair<int,int>> stack;
    for (int i = n - 1; i >= 0; -- i) {
        if (str[i] == ')') {
            stack.push_back({0,i});
        } else {
            LL tmp = 0;
            while (stack.back().first != 0) {
                tmp += sz[i] * 1ll * sz[stack.back().second];
                sz[i] += sz[stack.back().second];
                stack.pop_back();
            }
            sz[i] ++;
            ret += tmp * 1ll * (stack.back().second - i + 1);
            stack.back() = {1,i};

        }
    }
    return ret;
}

int main() {
    scanf("%s",str);
    printf("%I64d\n",work());
}
