
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int mod;
typedef long long LL;
const int N = 5000005;
int a[N],sa,sb,sc,sd,n;
int F(int x)
{
	LL ans = 0;
	LL x2 = (LL)x*x%mod;LL x3 = x2*x%mod;
	ans = (((ans+(LL)sa*x3%mod)%mod+(LL)sb*x2%mod)%mod+(LL)sc*x%mod)%mod+sd;
	ans = ans%mod;
	return ans;
}
bool judge(int b)
{
	int mx = 1;
	for(int i = 1;i<= n;i++)
	{
		mx = max(mx,a[i]-b);
		if(mx>a[i]+b)return false;
	}
	return true;
}
int main()
{
	scanf("%d%d%d%d%d%d%d",&n,&sa,&sb,&sc,&sd,&a[1],&mod);
	for(int i = 2;i<= n;i++)
		a[i] = (F(a[i-1])+F(a[i-2]))%mod;
	int l = 0,r = mod+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(judge(mid))r = mid;
		else l = mid+1;
	}
	printf("%d\n",l);
	return 0;
}
