
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int mod = 1e9+7;
const int N = 1e5+5;
typedef long long ll;
int n,T;
ll tr[N<<2],lazy[N<<2];
ll sum[N],a[N],inv[10005];
ll quick_pow(ll x,ll y)
{
	ll res = 1;
	while(y)
	{
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
void Push_down(int p,int l,int r)
{
	if(l==r||lazy[p]==1)return ;
	tr[p<<1] = tr[p<<1]*lazy[p]%mod;lazy[p<<1] = lazy[p<<1]*lazy[p]%mod;
	tr[p<<1|1] = tr[p<<1|1]*lazy[p]%mod;lazy[p<<1|1] = lazy[p<<1|1]*lazy[p]%mod;
	lazy[p] = 1;
}
void build(int p,int l,int r)
{
	lazy[p] = 1;
	if(l==r)
	{
		if(l!=n)tr[p] = 2ll*quick_pow(3,n-l-1)%mod*sum[l]%mod;
		else tr[p] = sum[n];
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	tr[p] = (tr[p<<1]+tr[p<<1|1])%mod;
}
void Update(int p,int l,int r,int a,int b,int x)
{
	Push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		tr[p]=tr[p]*x%mod;
		lazy[p]=lazy[p]*x%mod;
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)Update(p<<1,l,mid,a,b,x);
	if(b >mid)Update(p<<1|1,mid+1,r,a,b,x);
	tr[p] = (tr[p<<1]+tr[p<<1|1])%mod;
}

int main()
{
	for(int i = 1;i<= 10000;i++)inv[i]=quick_pow(i,mod-2);
	scanf("%d%d",&n,&T);
	for(int i = 1;i<= n;i++)scanf("%lld",&a[i]);
	sum[0]=1;
	for(int i = 1;i<= n;i++)sum[i]=sum[i-1]*a[i]%mod;
	build(1,1,n);
	while(T--)
	{
		int pos;ll x;
		scanf("%d%lld",&pos,&x);
		Update(1,1,n,pos,n,inv[a[pos]]*x%mod);
		a[pos] = x;
		printf("%lld\n",tr[1]);
	}
	return 0;
}
