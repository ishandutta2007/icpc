#include <bits/stdc++.h>
typedef long long LL;

const int N = 2500000 + 5;

bool doge[N];

bool isp(int x) {
    std::vector<int> A;
    while (x) {
        A.push_back(x % 10);
        x /= 10;
    }
    for (int i = 0; i < (int)A.size() - i - 1; ++ i) {
        if (A[i] != A[A.size() - i - 1])
            return false;
    }
    return true;
}

int A[N],B[N];

void init() {
    doge[0] = doge[1] = true;
    for (int i = 2; i < N; ++ i) {
        if (!doge[i]) {
            for (int j = i + i; j < N; j += i) {
                doge[j] = true;
            }
        }
    }
    for (int i = 1; i < N; ++ i) {
        A[i] = A[i - 1];
        B[i] = B[i - 1];
        A[i] += !doge[i];
        B[i] += isp(i);
    }
}

int main() {
    init();
    int p,q;
    scanf("%d%d",&p,&q);
    int answer = -1;
    for (int i = 1; i < N; ++ i) {
        if (q * 1ll * A[i] <= p * 1ll * B[i]) {
            answer = i;
        }
    }
    if (answer == -1) {
        puts("Palindromic tree is better than splay tree");
    } else {
        printf("%d\n",answer);
    }
}
