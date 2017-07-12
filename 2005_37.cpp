
#include<stdio.h>
typedef long long LL;
long long f[100005];
LL min(LL a,LL b)
{
    if(a>b)return b;
    return a;
}
int main()
{
    LL n,m;
    scanf("%lld%lld",&n,&m);
    LL tmp = min(n,m);
    LL ans = 0;
    for(LL i = tmp;i>=1;i--)
    {
        f[i] = (n/i)*(m/i);
        for(LL j = 2;j<= n/i;j++)
        {
            f[i] = f[i] - f[i*j];
        }
        ans = ans+f[i]*(2*i-1);
    }
    printf("%lld",ans);
    return 0;
}
