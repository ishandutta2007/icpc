#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
typedef __int64 lld;
const lld INF = 1LL<<61;

lld divide(lld a, lld b, lld &x, lld &y) {
    lld a1[] = {a, b/2, b-b/2};
    lld a2[] = {a, 1, b-1};
    sort(a1, a1 + 3);
    sort(a2, a2 + 3);
    if (a2[1] >= a1[1]) {
        x = 1; y = b - 1;
    }else {
        x = b/2; y = b - b/2;
    }
    return max(a1[1], a2[1]);
}

vector<lld> ans;
lld A[3];

void work(int cas) {
    printf("Case #%d:\n", cas);
    ans.clear();
    while (true) {
        sort(A, A + 3);
        if (A[0] == 0) break;
        if (A[1] == 1) {
            ans.push_back(1);
            A[1] = A[2] / 2;
            A[2] = A[2] - A[1];
            continue;
        }

        lld x1, y1, x2, y2;
        lld a = divide(A[0], A[1], x1, y1);
        lld b = divide(A[0], A[2], x2, y2);
        if (a >= b) {
            ans.push_back(A[2]);
            A[1] = x1;
            A[2] = y1;
        }else {
            ans.push_back(A[1]);
            A[1] = x2;
            A[2] = y2;
        }
    }
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%I64d%c", ans[i], " \n"[i+1 == ans.size()]);
    }
    return ;
}

int main() {
    freopen("eating.in", "r", stdin);
    freopen("eating.out", "w", stdout);
    int cas = 0;
    while (cin >> A[0] >> A[1] >> A[2] && A[0]) {
        work(++ cas);
    }
    return 0;
}
