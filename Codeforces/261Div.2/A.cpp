#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>
#include <set>

int X[4],Y[4];

int main() {
    for (int i = 0; i < 2; ++ i) {
        scanf("%d%d",X+i,Y+i);
    }
    int dx = X[0]-X[1];
    int dy = Y[0]-Y[1];
    if (dx!=0 && dy!=0 && std::abs(dx)!=std::abs(dy)) {
        puts("-1");
        return 0;
    }
    if (dx==0) {
        X[2] = X[0] + dy;
        Y[2] = Y[0];
        X[3] = X[1] + dy;
        Y[3] = Y[1];
    } else if (dy==0) {
        X[2] = X[0];
        Y[2] = Y[0] + dx;
        X[3] = X[1];
        Y[3] = Y[1] + dx;
    } else {
        X[2] = X[0];
        Y[2] = Y[1];
        X[3] = X[1];
        Y[3] = Y[0];
    }
    printf("%d %d %d %d\n",X[2],Y[2],X[3],Y[3]);
    return 0;
}

