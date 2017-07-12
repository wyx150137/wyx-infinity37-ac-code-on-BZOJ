
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e7+5;
int prime[N/10],mu[N],sum[N],g[N],cnt;
bool vis[N];
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
			if(i%prime[j])mu[i*prime[j]] = -mu[i];
			else
			{
				mu[i*prime[j]] = 0;
				break;
			}
		}
	}
	for(int i = 1;i<=cnt;i++)
		for(int j = 1;j*prime[i]<N;j++)
			g[j*prime[i]]+=mu[j];
	for(int i = 1;i<N;i++)
		sum[i] = sum[i-1]+g[i];
}
void solve(int n,int m)
{
	ll ans = 0;
	int last;
	for(int i = 1;i<=n&&i<=m;i = last+1)
	{
		last = min(m/(m/i),n/(n/i));
		ans+=(ll)(n/i)*(m/i)*(sum[last]-sum[i-1]);
	}
	printf("%lld\n",ans);
}
int main()
{
	int t;
	scanf("%d",&t);
	quick_mu();
	while(t--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		solve(x,y);
	}
	return 0;
}
