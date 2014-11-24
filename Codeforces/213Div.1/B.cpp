/* Created Time: Wednesday, November 20, 2013 PM06:44:50 CST */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 555555;
int n,d,c[55];
bool exist[N+7];
void work() {
    sort(c,c+n);
    int sum = 0,i,j;
    for (i = 0; i < n && sum+d>=c[i]; i ++) sum += c[i];
    n = i;
    exist[0] = true;
    for (i = 0; i < n; i ++) for (j = N; j >= c[i]; j --)
            exist[j] |= exist[j-c[i]];
    int ans = 0;
    for (i = 0; i < sum; )
    {
        for (j = i+d; j > i; j --)
        {
            if (exist[j]) 
            {
                ans ++;
                i = j;
                break;
            }
        }
    }
    printf("%d %d\n",sum,ans);
}
int main() {
    scanf("%d%d",&n,&d);
    for (int i = 0; i < n; i ++)
        scanf("%d",&c[i]);
    work();
    return 0;
}
