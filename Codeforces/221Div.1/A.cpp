#include <cstdio>
#include <algorithm>
using namespace std;
char ss[7][5];
int pp[4] = {1,8,6,9};
bool vis[4];
bool dfs(int x,char *s,int dep) {
        if (dep==4) {
                if (x%7==0) return true;
                return false;
        }
        for (int i = 0; i < 4; i ++) if (!vis[i]) {
                vis[i] = true;
                s[dep] = pp[i]+'0';
                bool judge = dfs(x*10+pp[i],s,dep+1);
                vis[i] = false;
                if (judge) return true;
        }
        return false;
}
void work(int x) {
        dfs(x,ss[x],0);
}
char s[1010100];
int cnt[10];
int main() {
        for (int i = 0; i < 7; i ++) work(i);
        scanf("%s",s);
        for (int i = 0; s[i]; i ++) cnt[s[i]-'0'] ++;
        for (int i = 0; i < 4; i ++) cnt[pp[i]] --;
        int val = 0;
        for (int i = 1; i < 10; i ++) {
                for (int j = 0; j < cnt[i]; j ++) {
                        val = (val*10+i)%7;
                        printf("%d",i);
                }
        }
        printf("%s",ss[val]);
        for (int i = 0; i < cnt[0]; i ++) printf("0");
        puts("");
        return 0;
}
