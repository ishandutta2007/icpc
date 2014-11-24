#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>
#include <set>

const int N = 1000000 + 5;
int n,A[N],prefix[N],suffix[N],C[N];

void bitmodify(int p) {
    for (int i = p; i < N; i += i&-i) C[i] ++;
}
int bitquery(int p) {
    int ret = 0; for (int i = p; i > 0; i -= i&-i) ret += C[i]; return ret;
}

int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d",A+i);
    }
    std::map<int,int> count;
    for (int i = 1; i <= n; ++ i) {
        count[A[i]] ++;
        prefix[i] = count[A[i]];
    }
    count.clear();
    for (int i = n; i >= 1; -- i) {
        count[A[i]] ++;
        suffix[i] = count[A[i]];
    }
    long long answer = 0;
    for (int i = n; i > 0; -- i) {
        answer += bitquery(prefix[i]-1);
        bitmodify(suffix[i]);
    }
    printf("%I64d\n",answer);
    return 0;
}

