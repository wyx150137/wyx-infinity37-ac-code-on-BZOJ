
#include <stdio.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
typedef long long ll;
int n,q;
ll a[N];
int main()
{
	ll sum = 0;
	scanf("%d%d",&n,&q);
	for(int i = 0;i<n;i++)
	{
		scanf("%lld",&a[i]);
		(sum+=a[i]*i)%=(n-1);
	}
	if(sum)a[sum]--;
	for(int i = 1;i<n;i++)
		a[i]+=a[i-1];
	ll tmp = 0;
	for(int i = 1;i<= q;i++)
	{
		scanf("%lld",&tmp);
		int ans = upper_bound(a,a+n,tmp)-a;
		if(ans==n)ans=-1;
		printf("%d\n",ans);
	}
	return 0;
}
