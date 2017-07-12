
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 10005;
ll a[N],r[N];
ll dec[N];
struct Ans
{
	int j,i;ll val;
	bool operator<(const Ans &s)const
	{
		return val<s.val;
	}
}e[N];
int getans(ll x,int n)
{
	int l = 1,r = n+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(e[mid].val<x)l=mid+1;
		else r = mid;
	}
	return l;
}
int main()
{
	int cnt = 0,tot=0;
	a[1] = 1,a[2] = 2;
	dec[++cnt] = 0,dec[++cnt]=1;
	for(int i = 3;;i++)
	{
		if(i&1)a[i] = a[i-1]*2;
		else a[i] = a[i-1]+r[i-1];
		for(int j = i;j;j--)
			dec[++cnt] = a[i]-a[j];
		sort(dec+1,dec+cnt+1);
		cnt = unique(dec+1,dec+cnt+1)-dec-1;
		for(int j = 1;j<=cnt;j++)
			if(dec[j]!=j-1)
				{r[i] = j-1;break;}
		if(!r[i])r[i]=cnt;
		if(a[i]-a[i-1]>10000000000ll){tot=i;break;}
	}
	int tmp = 0;
	for(int i = 1;i<= tot;i++)
		for(int j = 1;j<i;j++)
			e[++tmp] = (Ans){i,j,a[i]-a[j]};
	sort(e+1,e+tmp+1);
	int n;
	ll q;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%lld",&q);
		int t = getans(q,tmp);
		if(e[t].val==q)printf("%d %d\n",e[t].j,e[t].i);
		else
		{
			ll ans = q-t+1;
			printf("%lld %lld\n",tot+ans*2-1,tot+ans*2-2);
		}
	}
	return 0;
}
