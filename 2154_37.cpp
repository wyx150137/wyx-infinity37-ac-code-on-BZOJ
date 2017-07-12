
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e7+5;
const int mod = 20101009;
int mu[N],prime[N/10],cnt;
bool vis[N];
ll sum[N];
void quick_mu()
{
	mu[1] = 1;
	for(int i = 2;i<N;i++)
	{
		if(!vis[i])
		{
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j = 1;j<= cnt&&i*prime[j]<N;j++)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j])
				mu[i*prime[j]] = -mu[i];
			else
			{
				mu[i*prime[j]] = 0;
				break;
			}
		}
	}
	for(int i = 1;i<N;i++)
		sum[i] = (sum[i-1]+(ll)i*i*mu[i])%mod;
}
ll Sum(ll x)
{
	x %= mod;
	return x*(x+1)%mod*10050505%mod;
}
ll F(int x,int y)
{
	int last;
	ll ans = 0;
	for(int i = 1;i<=x&&i<=y;i=last+1)
	{
		last = min(x/(x/i),y/(y/i));
		(ans+=Sum(x/i)*Sum(y/i)%mod*(sum[last]-sum[i-1]))%=mod;
	}
	return ans;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int last;
	quick_mu();
	ll ans = 0;
	for(int i = 1;i<= n&&i<= m;i=last+1)
	{
		last = min(n/(n/i),m/(m/i));
		(ans+=F(n/i,m/i)*(Sum(last)-Sum(i-1)))%=mod;
	}
	printf("%lld\n",(ans%mod+mod)%mod);
	return 0;
}
