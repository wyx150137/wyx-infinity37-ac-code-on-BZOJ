
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1e9+7;
const int N = 405;
int c[N][N];
ll quick_pow(ll x,ll y)
{
	if(y==0)return 1;
	ll tmp = quick_pow(x,y>>1);
	if(y&1)return tmp*tmp%mod*x%mod;
	else return tmp*tmp%mod;
}
void init()
{
	c[0][0] = 1;
	for(int i = 1;i<N;i++)
	{
		c[i][0] = 1;
		for(int j = 1;j<N;j++)
			c[i][j] = (c[i-1][j-1]+c[i-1][j])%mod;
	}
}
int main()
{
	int n,m,p;
	ll ans = 0;
	init();
	scanf("%d%d%d",&n,&m,&p);
	for(int i = 0;i<= n;i++)
		for(int k = 0;k<= p;k++)
		{
			ans+=(ll)c[n][i]*c[p][k]%mod*((n+m+p-i-k)%2?-1:1)*quick_pow(1-quick_pow(k+1,i),m)%mod;
			ans=(ans%mod+mod)%mod;
		}
	printf("%lld\n",ans);
	return 0;
}
