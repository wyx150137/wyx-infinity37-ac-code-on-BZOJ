
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
const int mod = 16777216;
typedef long long ll;
ll c[N],l[N],r[N];
int a[N],n;
ll getans(int x)
{
	ll ans =0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=c[i];
	return ans;
}
void update(int x,ll y)
{
	for(int i = x;i<=n;i+=i&(-i))
		(c[i]+=y+mod)%=mod;
}
int cnt1()
{
	memset(c,0,sizeof(c));
	ll ans = 0;
	for(int i = 1;i<= n;i++)
	{
		ans = (ans+(l[i]*(i-2)-getans(a[i])-l[i]*(l[i]-1)/2)*((ll)n-i-r[i])%mod+mod)%mod;
		update(a[i],i-1);
	}
	return (int)ans;
}
int cnt2()
{
	memset(c,0,sizeof(c));
	ll ans = 0;
	for(int i = 1;i<= n;i++)
	{
		ans = (ans+((ll)n-i-r[i])*getans(a[i])%mod+mod)%mod;
		update(a[i],l[i]);
	}
	return (int)ans;
}
int cnt3()
{
	memset(c,0,sizeof(c));
	ll ans =0;
	for(int i = n;i;i--)
	{
		ans = (ans+((ll)n-i-r[i])*(getans(a[i])-r[i]*(r[i]-1)/2)%mod+mod)%mod;
		update(a[i],a[i]-1);
	}
	return (int)ans;
}
int cnt4()
{
	ll ans = 0;
	for(int i = 1;i<= n;i++)
		ans = (ans+(n-i-r[i])*(n-i-r[i]-1)*(n-i-r[i]-2)/6)%mod;
	return (int)ans;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<= n;i++)
	{
		l[i]=getans(a[i]);
		r[i]=a[i]-1-l[i];
		update(a[i],1);
	}
	ll ans = ((cnt1()+cnt2()+cnt3()-cnt4())%mod+mod)%mod;
	printf("%lld\n",ans);
	return 0;
}
