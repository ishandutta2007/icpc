#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
char s[5555];
int cnt[5555];
int main() {
        int ans = 0;
        scanf("%s",s);
        int len = strlen(s);
        
        for (int i = 0; i+3 < len; i ++) {
                cnt[i+1] += cnt[i];
                if (s[i]=='b' && s[i+1]=='e' && s[i+2]=='a' && s[i+3]=='r') cnt[i+1] ++;
        }
        for (int i = 0; i < len; i ++)
                for (int j = i+3; j < len; j ++) {
                        if (cnt[j-3+1]-cnt[i]) ans ++;
                }
        printf("%d\n",ans);
        return 0;
}
