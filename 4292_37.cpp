
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
bool check(ll ans,int num)
{
	int tmp = 0;
	while(ans)
	{
		int k = ans%10;
		ans/=10;
		tmp +=k*k;
	}
	return tmp==num;
}
int main()
{
	ll k,a,b,ans=0;
	scanf("%lld%lld%lld",&k,&a,&b);
	for(int i = max(a/k-2,0ll);i<= min(b/k+2,1458ll);i++)
		if(check(k*i,i)&&k*i<=b&&k*i>=a)
			ans++;
	printf("%lld\n",ans);
	return 0;
}
