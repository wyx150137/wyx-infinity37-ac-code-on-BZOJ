
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const int mod = 998244353;
typedef long long ll;
int mu[N],prime[N],cnt,sum[N];
bool v[N];
void quick_mu()
{
	mu[1] = 1;
	for(int i = 2;i<N;i++)
	{
		if(!v[i])
		{
			prime[++cnt] =i;
			mu[i] = mod-1;
		}
		for(int j = 1;j<=cnt&&prime[j]*i<N;j++)
		{
			v[i*prime[j]] = true;
			if(i%prime[j])mu[i*prime[j]]=(mod-mu[i])%mod;
			else
			{
				mu[i*prime[j]]=0;
				break;
			}
		}
	}
}
ll getsum(ll n)
{
	return (n*(n+1)>>1)%mod;
}
int main()
{
	int n,m,x;
	scanf("%d%d%d",&n,&m,&x);
	quick_mu();
	ll ans = 0;
	ans=((getsum(n)*getsum(m)-n*getsum(m)-m*getsum(n))%mod+mod)%mod;
	if(n>m)swap(n,m);
	for(int i = 1;i<= n;i++)
	{
		ll tmp = i+x/i*i*2;
		for(int j = 1;j*i<=n;j++)
			(ans+=tmp*mu[j]%mod*(n/i/j)%mod*(m/i/j)%mod)%=mod;
	}
	ans = ans*((mod+1)>>1)%mod;
	printf("%lld\n",ans);
	return 0;
}
