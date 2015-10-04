#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int n;
void work() {
    if (n) {
        puts("win");
    }else {
        puts("fail");
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        work();
    }
    return 0;
}
