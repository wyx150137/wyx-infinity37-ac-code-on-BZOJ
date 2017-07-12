
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
ll oula(ll x)
{
	ll ans = x;
	for(ll i = 2;i*i<= x;i++)
	{
		if(x%i==0)ans = ans/i*(i-1);
		while(x%i==0)x/=i;
	}
	if(x!=1)ans = ans/x*(x-1);
	return ans%mod;
}
int main()
{
	ll n,m;
	scanf("%lld%lld",&n,&m);
	printf("%lld\n",(n%mod)*(m%mod)%mod*oula(n)%mod*oula(m)%mod);
	return 0;
}
