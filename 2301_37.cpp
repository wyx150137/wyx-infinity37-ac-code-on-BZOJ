
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
int mu[N],prime[N],cnt,sum[N];
bool vis[N];
void quick_mu()
{
	mu[1] = 1;
	for(int i= 2;i<N;i++)
	{
		if(!vis[i])
		{
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j = 1;j<= cnt&&prime[j]*i<N;j++)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j])mu[i*prime[j]] = -mu[i];
			else
			{
				mu[i*prime[j]] = 0;
				break;
			}
		}
	}
	for(int i = 1;i<N;i++)
		sum[i] = sum[i-1]+mu[i];
}
typedef long long ll;
ll calc(int x,int y)
{
	if(x<0||y<0)return 0;
	ll ans = 0;
	int last = 0;
	for(int i = 1;i<=x&&i<=y;i = last+1)
	{
		last = min(y/(y/i),x/(x/i));
		ans+=(ll)(x/i)*(y/i)*(sum[last]-sum[i-1]);
	}
	return ans;
}
int main()
{
	quick_mu();
	int a,b,c,d,k;
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		ll ans = 0;
		ans+=calc(b/k,d/k);
		ans-=calc((a-1)/k,d/k);
		ans-=calc(b/k,(c-1)/k);
		ans+=calc((a-1)/k,(c-1)/k);
		printf("%lld\n",ans);
	}
	return 0;
}
