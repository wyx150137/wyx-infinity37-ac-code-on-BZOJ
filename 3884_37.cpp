
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll quick_pow(ll x,ll y,ll mod)
{
	ll re = 1;
	while(y)
	{
		if(y&1)(re*=x)%=mod;
		(x *= x)%=mod;
		y>>=1;
	}
	return re;
}
ll oula(ll x)
{
	ll phi = x;
	for(ll i = 2;i*i<=x;i++)
		if(x%i==0)
		{
			phi = phi/i*(i-1);
			while(x%i==0)x/=i;
		}
	if(x!=1)phi = phi/x*(x-1);
	return phi;
}
ll calc(ll mod)
{
	if(mod==1)return 0;
	ll ans = 1,cnt = 0,MOD = mod;
	while(mod%2==0)
		ans*=2,cnt++,mod/=2;
	int phi = oula(mod);
	ans = ans*quick_pow(2,((calc(phi)-cnt)%phi+phi)%phi,MOD)%MOD;
	return ans;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int x;
		scanf("%d",&x);
		printf("%lld\n",calc(x));
	}
	return 0;
}
