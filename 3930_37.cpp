
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
const int mod = 1e9+7;
int d[2*N];
ll quick_pow(ll x,ll y)
{
	if(y==0)return 1;
	ll tmp = quick_pow(x,y>>1);
	if(y&1)return tmp*tmp%mod*x%mod;
	else return tmp*tmp%mod;
}
int main()
{
	ll n,k,a,b;
	scanf("%lld%lld%lld%lld",&n,&k,&a,&b);
	ll l = a/k,r=b/k;
	if(a%k)l++;
	for(int i = N-5;i>=1;i--)
	{
		ll L = l/i,R = r/i;
		if(l%i)L++;
		if(l<=r)
		{
			d[i]=quick_pow(R-L+1,n%(mod-1));
			d[i]=(d[i]-(R-L+1)+mod)%mod;
			for(int j = i*2;j<N;j+=i)
				d[i]=(d[i]-d[j]+mod)%mod;
		}
	}
	if(l==1)d[1] = (d[1]+1)%mod;
	printf("%d\n",d[1]);
	return 0;
}
