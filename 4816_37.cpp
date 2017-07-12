
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e6+5;
const int mod = 1e9+7;
int f[N],g[N],Invg[N];
int quick_pow(int x,ll y)
{
	int res=1;
	while(y)
	{
		if(y&1)res = (ll)res*x%mod;
		x = (ll)x*x%mod;
		y>>=1;
	}
	return res;
}
int getmul(int l,int r)
{
	return (ll)g[r]*Invg[l-1]%mod;
}
int main()
{
	f[0] = 0,f[1] = 1;
	for(int i = 2;i<N;i++)
		f[i] = (f[i-1]+f[i-2])%mod;
	for(int i = 1;i<N;i++)g[i] = f[i];
	Invg[0] = 1,g[0]=1;
	for(int i = 1;i<N;i++)
	{
		Invg[i] = quick_pow(g[i],mod-2);
		for(int j = i+i;j<N;j+=i)
			g[j] = (ll)g[j]*Invg[i]%mod;
		g[i] = (ll)g[i-1]*g[i]%mod;
		Invg[i] = (ll)Invg[i-1]*Invg[i]%mod;
	}
	int cas,n,m;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%d%d",&n,&m);
		int ans = 1,last = 1;
		if(n>m)swap(n,m);
		for(int i = 1;i<= n;i=last+1)
		{
			last = min(n/(n/i),m/(m/i));
			ans = (ll)ans*quick_pow(getmul(i,last),(ll)(n/i)*(m/i))%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
