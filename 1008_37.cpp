
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
long long mod = 100003;
long long quick(long long x,long long y)
{
    if(y==0)return 1;
    long long tmp = quick(x,y/2);
    if(y%2==1)return tmp*tmp%mod*x%mod;
    else return tmp*tmp%mod;
}
int main()
{
    long long n,m;
    scanf("%lld%lld",&m,&n);
    long long ans = quick(m,n);
    long long not_ = m*quick(m-1,n-1)%mod;
    printf("%lld\n",((ans-not_)%mod+mod)%mod);
    return 0;
}
