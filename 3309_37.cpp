
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e7+5;
int g[N],last[N],t[N],prime[N/10],cnt;
bool vis[N];
int sum[N];
void quick_mu()
{
	for(int i =2;i<N;i++)
	{
		if(!vis[i])
		{
			prime[++cnt] = i;
			g[i] = last[i] = t[i] = 1;
		}
		for(int j = 1;j<= cnt&&i*prime[j]<N;j++)
		{
			int x = i*prime[j];
			vis[x] = true;
			if(i%prime[j]==0)
			{
				last[x] = last[i];
				t[x] = t[i]+1;
				if(last[x]==1)g[x] = 1;
				else g[x] = (t[last[x]]==t[x]?-g[last[x]]:0);
				break;
			}
			last[x] = i;t[x] = 1;
			g[x] = (t[i]==1?-g[i]:0);
		}
	}
	for(int i = 1;i<N;i++)
		sum[i] = sum[i-1]+g[i];
}
ll getans(int x,int y)
{
	int last;
	ll ans = 0;
	for(int i = 1;i<=x&&i<= y;i = last+1)
	{
		last = min(x/(x/i),y/(y/i));
		ans+=(ll)(x/i)*(y/i)*(sum[last]-sum[i-1]);
	}
	return ans;
}
int main()
{
	int t,n,m;
	scanf("%d",&t);
	quick_mu();
	while(t--)
	{
		scanf("%d%d",&n,&m);
		printf("%lld\n",getans(n,m));
	}
	return 0;
}
