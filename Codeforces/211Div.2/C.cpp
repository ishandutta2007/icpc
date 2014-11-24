/* Created Time: Tuesday, November 19, 2013 AM11:35:12 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char s[222222];
int main() {
    scanf("%s",s);
    int cur = 0;
    for (int i = 0; s[i]; i ++) {
        int j = i,cnt = 0;
        while (s[j]==s[i]) j ++,cnt ++;
        if (cnt>=3) cnt = 2;
        if (cur==2) cnt = 1;
        for (int k = 0; k < cnt; k ++)
            printf("%c",s[i]);
        cur = cnt;
        i = j-1;
    }
    return 0;
}
