
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
typedef long long ll;
int a[N],cnt;
ll sum[N],pos[N];
int c[N];
void update(int x)
{
	for(int i = x;i<N;i+=i&(-i))
		c[i]++;
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i;i-=i&(-i))
		ans+=c[i];
	return ans;
}
int getans(int l,int r)
{
	return getans(r)-getans(l-1);
}
int upper(ll x)
{
	int l = 1,r = cnt+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(pos[mid]<=x)l = mid+1;
		else r = mid;
	}
	return l-1;
}
int lower(ll x)
{
	int l = 1,r = cnt+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(pos[mid]<x)l = mid+1;
		else r = mid;
	}
	return l;
}
int main()
{
	int n,L,R;
	scanf("%d%d%d",&n,&L,&R);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		sum[i] = sum[i-1]+a[i];
		pos[i] = sum[i];
	}
	sort(pos+1,pos+n+2);
	cnt = 1;
	for(int i = 2;i<= n+1;i++)
		if(pos[i]!=pos[cnt])
			pos[++cnt]=pos[i];
	ll ans = 0;
	update(lower(0));
	for(int i = 1;i<= n;i++)
	{
		ans+=getans(lower(sum[i]-R),upper(sum[i]-L));
		update(lower(sum[i]));
	}
	printf("%lld\n",ans);
	return 0;
}
