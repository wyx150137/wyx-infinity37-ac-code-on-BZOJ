
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define ll long long
typedef  long long LL;
const int mod = 10000007;
ll f[100][100],g[100][100],n;
using namespace std;
LL power(LL a,LL b)
{
	LL res = 1;
	for(;b;b>>=1,a=a%mod*a%mod)
		if(b&1)
			res = res * a % mod;
	return res;
}

ll cal(ll x)
{
	ll t(0),c(0),ans(1);
	for (t=0;1ll<<t<=x;t++);
	for (;t;t--)
	{
		if ((1ll<<t-1)&x)
		{
			for (int i=1;i<=t;i++)
				(ans*=power(i+c,f[t][i]))%=mod;
			if (c)(ans*=c)%=mod;c++;
		}   
	}
	return (ans*c)%mod;
}
int main()
{
	scanf("%lld",&n);
	f[1][0]=1;g[1][1]=1;
	for (int i=2;i<=60;i++)
		for (int j=0;j<=i;j++)
		{
 			f[i][j]=(f[i-1][j]+g[i-1][j]);
 			if (j!=0)g[i][j]=(f[i-1][j-1]+g[i-1][j-1]);
		}
	printf("%lld",cal(n));
}
