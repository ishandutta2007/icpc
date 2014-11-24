#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char s[50],c[50];
int main() {
        scanf("%s%s",s,c);
        int left = 0;
        for (int i = 0; s[i]!='|'; i ++) left ++;
        int len = strlen(s);
        int right = len-1-left;
        int clen = strlen(c);
        int dt = left-right;
        if (dt>0) {
                if ((clen-dt<0) || (clen-dt&1)) {
                        puts("Impossible"); return 0;
                }
                for (int i = 0; i < left; i ++) putchar(s[i]);
                int xx = clen-dt>>1;
                for (int i = 0; i < xx; i ++) putchar(c[i]);
                putchar('|');
                for (int i = left+1; s[i]; i ++) putchar(s[i]);
                for (int i = xx; c[i]; i ++) putchar(c[i]);
                puts("");
        } else {
                if (clen+dt<0 || (clen+dt&1)) {
                        puts("Impossible"); return 0;
                }
                for (int i = 0; i < left; i ++) putchar(s[i]);
                int xx = clen+dt>>1;
                for (int i = 0; i < clen-xx; i ++) putchar(c[i]);
                putchar('|');
                for (int i = left+1; s[i]; i ++) putchar(s[i]);
                for (int i = clen-xx; c[i]; i ++) putchar(c[i]);
                puts("");
        }

        return 0;
}
