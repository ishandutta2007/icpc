#include <bits/stdc++.h>

const int N = 300000 + 5;
int n,m;
char str[N];

int main() {
    scanf("%d%d",&n,&m);
    scanf("%s",str + 1);
    int answer = 0;
    for (int i = 1; i <= n; ++ i) {
        if (str[i] == '.' && str[i - 1] == '.') {
            answer ++;
        }
    }
    for (int i = 0; i < m; ++ i) {
        int p;
        char s[2];
        scanf("%d%s",&p,s);
        if (str[p] == '.' && s[0] != '.') {
            if (str[p - 1] == '.') {
                answer --;
            }
            if (str[p + 1] == '.') {
                answer --;
            }
        } else if (str[p] != '.' && s[0] == '.') {
            if (str[p - 1] == '.') {
                answer ++;
            }
            if (str[p + 1] == '.') {
                answer ++;
            }
        }

        str[p] = s[0];
        printf("%d\n",answer);
    }
}
