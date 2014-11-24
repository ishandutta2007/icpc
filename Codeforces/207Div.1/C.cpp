/* Created Time: Tuesday, November 19, 2013 PM12:54:53 CST */
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n,a[5];
int work() {
        int ret = 0,x;
        x = min(a[1],a[2]);
        ret += x;
        a[3] += x;
        a[1] -= x;
        a[2] -= x;

        if (a[1]) 
        {
                x = a[1]/3;
                ret += x*2;
                a[1] %= 3;
                a[3] += x;
                if (a[3]>=a[1]) 
                {
                        ret += a[1];
                        return ret;
                } else {
                        ret += a[1]-1;
                        if (a[4]>=3-a[1]) 
                        {
                                ret += 3-a[1];
                                return ret;
                        } 
                        else 
                        {
                                return -1;
                        }
                }
        } else if (a[2]) 
        {
                x = a[2]/3;
                ret += x*2;
                a[2] %= 3;
                a[3] += 2*x;

                if (a[2]==2) 
                {
                        ret += 2;
                        return ret;
                }
                else if (a[2]==1) 
                {
                        if (a[4]>=1) 
                        {
                                ret += 1;
                                return ret;
                        }
                        else if (a[3]>=2)
                        {
                                ret += 2;
                                return ret;
                        }
                        else 
                        {
                                return -1;
                        }
                }
        }

        return ret;
}
int main() {
        scanf("%d",&n);
        while (n--) {
                int d;
                scanf("%d",&d);
                a[d] ++;
        }
        printf("%d\n",work());
        return 0;
}
