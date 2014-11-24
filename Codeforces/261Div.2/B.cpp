#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>
#include <set>

const int N = 200000 + 5;
int n,A[N];

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d",A+i);
    }
    std::sort(A,A+n);
    int answer = A[n-1] - A[0];
    if (answer==0) {
        printf("%d %I64d\n",0,(long long)n*(n-1)/2);
        return 0;
    }
    int count_small = 0;
    for (int i = 0; i < n; ++ i) {
        count_small += A[i]==A[0];
    }
    int count_big = 0;
    for (int i = 0; i < n; ++ i) {
        count_big += A[i]==A[n-1];
    }
    printf("%d %I64d\n",answer,(long long)count_small * count_big);
    return 0;
}

