
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 105;
const int mod = 1e9+7;
int quick_pow(int x,int y)
{
	int res = 1;
	while(y)
	{
		if(y&1)res = (ll)res*x%mod;
		x = (ll)x*x%mod;
		y>>=1;
	}
	return res;
}
int fac[N*N],env[N*N],Pow[N];
void init()
{
	fac[0] = env[0] = 1;
	for(int i = 1;i<= 10000;i++)
		fac[i] = (ll)fac[i-1]*i%mod;
	env[10000] = quick_pow(fac[10000],mod-2);
	for(int i = 9999;i>=1;i--)
		env[i] = (ll)env[i+1]*(i+1)%mod;
}
ll C(int n,int m)
{
	if(m>n)return 0;
	return (ll)fac[n]*env[m]%mod*env[n-m]%mod;
}
int f[N],g[N],rnk[N],s[N];
int n,m,k;
int main()
{
	init();
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<= m;i++)scanf("%d",&s[i]);
	int mxrnk=0;
	for(int i = 1;i<= m;i++)scanf("%d",&rnk[i]),mxrnk=max(mxrnk,rnk[i]);
	for(int i = n-mxrnk;i>= k;i--)
	{
		f[i] = C(n-1,i);
		for(int j = 1;j<= m;j++)
			f[i] = (ll)f[i]*C(n-i-1,rnk[j]-1)%mod;
		for(int j = i+1;j<= n-mxrnk;j++)
			f[i] = (f[i]-(ll)f[j]*C(j,i)%mod+mod)%mod;
	}
	int ans = 1;
	for(int i = 1;i<= m;i++)
	{
		g[0] = s[i];
		Pow[0] = 1;
		for(int j = 1;j<= n;j++)
		{
			Pow[j] = (ll)Pow[j-1]*s[i]%mod;
			g[j] = quick_pow(s[i]+1,j+1)-1;
			for(int k = 1;k<= j;k++)
				(g[j]+=mod-C(j+1,k+1)*g[j-k]%mod)%=mod;
			g[j]=(ll)g[j]*quick_pow(C(j+1,1),mod-2)%mod;
		}
		int now = 0;
		for(int j = 0,k = 1;j<rnk[i];j++,k = -k)
			now = (now+(ll)(mod+k)*C(rnk[i]-1,j)%mod*g[n-rnk[i]+j]%mod*Pow[rnk[i]-j-1]%mod)%mod;
		ans = (ll)ans*now%mod;
	}
	printf("%lld\n",(ll)ans*f[k]%mod);
	return 0;
}
