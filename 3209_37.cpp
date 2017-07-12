
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL mod = 10000007;
LL c[55][55];
LL x,y;
LL quick_pow(LL x,LL y)
{
    if(y==0)return 1;
    LL tmp = quick_pow(x,y/2);
    if(y&1)return tmp*tmp%mod*x%mod;
    else return tmp*tmp%mod;
}
int main()
{
    c[1][0] = c[1][1] = 1;
    for(int i = 2;i<= 53;i++)
    {
        c[i][0] = 1;
        for(int j = 1;j<= 53;j++)
            c[i][j] = c[i-1][j-1]+c[i-1][j];
    }
    LL n,ans = 1,cnt = 0;
    scanf("%lld",&n);
    for(int i = 53;i>=1;i--)
    {
        if((n&((LL)1<<(i-1)))!=0)
        {
            ans = ans*(cnt+1)%mod;
            for(int j = i-1;j>=1;j--)
                ans = ans*quick_pow(j+cnt,c[i-1][j])%mod;
            cnt++;
        }
    }
    printf("%lld",ans);
    return 0;
}
