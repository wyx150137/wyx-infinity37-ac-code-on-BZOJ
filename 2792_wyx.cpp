
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+10;
ll m;
ll n;
ll x[maxn];
ll cx[maxn];
ll lc[maxn];
ll rc[maxn];
ll sum[maxn];
ll b;
int pos=1;
bool check(ll mid)
{
	ll ans=0,t;
	int i;
	memcpy(x,cx,sizeof(ll)*(n+10));
	memset(sum,0,sizeof(sum));
	for(i=1;i<n;i++)
		if(x[i+1]-x[i]>mid)
		{
			ans+=x[i+1]-x[i]-mid;
			x[i+1]=x[i]+mid;
		}
	for(i=n;i>1;i--)
		if(x[i-1]-x[i]>mid)
		{
			ans+=x[i-1]-x[i]-mid;
			x[i-1]=x[i]+mid;
		}
	if(ans>m)
		return false;
	for(i=1;i<=n;i++)
		sum[i]=sum[i-1]+x[i];
	ll l=1,r=1;
	for(i=1;i<=n;i++)
	{
		t=ans;
		while(l<i&&x[l]-(i-l)*mid<0)
			++l;
		while(r<n&&x[r+1]-(r+1-i)*mid>0)
			++r;
		t+=sum[r]-sum[l-1]-((r-i+1)*(r-i)/2+(i-l+1)*(i-l)/2)*mid;
		if(t<=m)
		{
			pos=i;
			return true;
		}
	}
	return false;
}
int main()
{
//	freopen("river15.in","r",stdin);
//	freopen("river.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&cx[i]);
		b=max(b,cx[i]);
	}
	int l=0,r=b;
	int mid;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d %d\n",pos,l);
}
