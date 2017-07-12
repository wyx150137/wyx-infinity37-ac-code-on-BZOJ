
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1e9+7;
ll quick_pow(ll x,ll y)
{
	if(y==0)return 1;
	ll tmp = quick_pow(x,y>>1);
	if(y&1)return tmp*tmp%mod*x%mod;
	else return tmp*tmp%mod;
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	printf("%lld\n",quick_pow(2,(ll)n*k));
	return 0;
}
