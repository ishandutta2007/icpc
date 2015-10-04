#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

ull n;
ull qa[233], qb[233];

bool solve(int s, int a) {
    int x = s-a;
    for(int i = 1;i <= x; i++) qa[i] = i;
    if(n < s) return false;
    for(int i = 0;i < a; i++) {
        qb[1] = 1;
        for(int j = 1;j <= x; j++) {
            ull cur = n-qa[j];
           if(cur >= qb[j]) {
               qb[j+1] = qa[j]+qb[j];
           } else {
               return false;
           }
        }
        for(int j = 1;j <= x+1; j++) qa[j] = qb[j];
        x++;
    }
    return true;
}

int a, b, s, t;

int main() {
    bool first = true;
    while(scanf("%llu%d%d%d%d", &n, &a, &b, &s, &t) == 5) {
        if(!first) puts("");
        first = false;
        if(!solve(s, a)) {
            puts("-1");
        } else {
            for(int i = 1;i <= s; i++) printf("%llu%c", qa[i],i==s?'\n':' ');
        }
        if(!solve(t, b)) {
            puts("-1");
        } else {
            for(int i = 1;i <= t; i++) printf("%llu%c", n-qa[i]+1,i==t?'\n':' ');
        }
    }
    return 0;
}
