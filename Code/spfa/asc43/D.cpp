#include <bits/stdc++.h>

using namespace std;

int is[11], sum[11], delay[11], blood[11];
bool killed[11], used[11];

int num[555], cost[1<<20], val[1<<20];

char s[] = ".GRS";
int pr[11], pp[555];

int q[] = {0,0,0,3,3,1,1,1,1,1};

int main() {
//    freopen("defend.in", "r", stdin);
//    freopen("defend.out", "w", stdout);
    int ii = 0;
    for(int i =0 ;i < 10; i++) {
        ii = ii<<2|q[i];
    }
//    printf("ii = %d\n", ii);
    int h;
    scanf("%d", &h);
    int mx = 0;
    for(int i = 0;i < 555; i++) num[i] = 0;
//    for(int i = 15701;i <= 15701; i++) { 
    for(int i = 0;i < 1<<20; i++) {
        
        for(int j = 0;j < 10; j++) {
            is[j] = i>>(10-j-1<<1)&3;
        }
//        for(int j = 0;j < 10; j++) printf("%d ", is[j]); puts("");
        sum[0] = is[0]==3;
        for(int j = 1;j < 10; j++) sum[j] = sum[j-1] + (is[j]==3);
        delay[0] = 1;
        for(int j = 1;j < 10; j++) {
            if(j-5 >= 0) delay[j] = sum[j]-sum[j-5]+1;
            else    delay[j] = sum[j] + 1;
        }
//        for(int j = 0;j < 10; j++) printf("%d ", delay[j]); puts("");
        cost[i] = 0;
        for(int j = 0;j < 10; j++) {
            if(is[j] == 1) cost[i] += 3;
            else if(is[j]==2) cost[i] += 10;
            else if(is[j]==3) cost[i] += 5;
        }
        mx = max(mx, cost[i]);
        for(int j = 0;j < 10; j++) blood[j] = h;
        memset(killed, 0, sizeof(killed));
        int ti = 1;
        for(int j = 0;j < 10; j++) {
            if(is[j] == 2) {
                for(int k = 0;k < 10; k++) if(!killed[k]){
                    int st = ti+k, ed = ti+delay[j]-1+k;
                    while(st%3) st++;
                    while(ed%3) ed--;
                    if(st <= ed) blood[k] -= 4*((ed-st)/3+1);
                    if(blood[k] <= 0){
                        killed[k] = 1;
                    }
                }
            } else if(is[j]==1) {
                int can = delay[j];
                for(int k = 0;k < 10; k++) {
                    can = min(delay[j], can+1);
                    if(killed[k]) continue;
                    if(can >= blood[k]) {
                        can -= blood[k];
                        blood[k] = 0;
                        killed[k] = 1;
                    } else {
                        blood[k] -= can;
                        can = 0;
                    }
                }
            }
            ti += delay[j];
//            printf("ti = %d\n", ti);
//            for(int k =0 ;k < 10; k++) printf("%d ", blood[k]); puts("");
        }
        int kill = 0;
        for(int j = 0;j < 10; j++) if(killed[j]) kill++;
        val[i] = kill;
//        printf("kill = %d\n", kill);
        if(num[cost[i]] < kill) {
            num[cost[i]] = kill;
            pp[cost[i]] = i;
        }
    }
    for(int i = 1;i <= mx; i++) num[i] = max(num[i], num[i-1]);
    for(int i = 1;i <= mx; i++) if(num[i] > num[i-1]) {
        printf("$%d -> kill %d with ", i, num[i]);
        int cur = pp[i];
//        printf("cur = %d\n", cur);
        for(int j = 9;j >= 0; j--) {
            pr[j] = cur&3;
            cur >>= 2;
        }
        for(int j = 0;j < 10; j++) {
            printf("%c", s[pr[j]]);
        }
        puts("");
    }
    return 0;
}
