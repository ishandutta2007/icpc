#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

const int N = 1000 + 5;
int A[N],B[N];
int n;
int deg[N];
bool graph[N][N];

bool check(int ban) {
    for (int i = 0; i < n; ++ i) {
        graph[A[i]][B[i]] = false;
        deg[i] = 0;
    }
    for (int i = 0; i < n; ++ i) {
        if (i == ban) continue;
        if (graph[A[i]][B[i]] || A[i] == B[i])
            return false;
        deg[A[i]] ++;
        deg[B[i]] ++;
        graph[A[i]][B[i]] = true;
    }
    int cnt = 0;
    for (int i = 0; i < n; ++ i) {
        if (deg[i] < 1 || deg[i] > 2)
            return false;
        if (deg[i] == 1)
            cnt ++;
    }
    return cnt == 2;
}

bool work() {
    if (n == 1) return true;
    for (int i = 0; i < n; ++ i) {
        if (check(i)) return true;
    }
    return false;
}

int main() {
    while (scanf("%d",&n) == 1) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d",A + i,B + i); A[i] --; B[i] --;
            if (A[i] > B[i]) std::swap(A[i],B[i]);
        }
        puts(work() ? "YES" : "NO");
    }
}
