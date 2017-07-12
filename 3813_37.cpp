
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
typedef long long ll;
const int mod = 19961993;
typedef pair<ll,ll> PLL;
pair <ll,ll> val[N<<2];
int prime[105],env[105],cnt;
bool v[405];
ll quick_pow(ll x,ll y)
{
	if(y==0)return 1;
	ll tmp = quick_pow(x,y>>1);
	if(y&1)return tmp*tmp%mod*x%mod;
	else return tmp*tmp%mod;
}
void init()
{
	for(int i = 2;cnt<=60;i++)
	{
		if(!v[i])prime[++cnt]=i;
		for(int j = 1;j<=cnt&&i*prime[j]<=400;j++)
		{
			v[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
	for(int i = 1;i<= 60;i++)
		env[i] = quick_pow(prime[i],mod-2);
}
void push_up(int p)
{
	val[p].first = val[p<<1].first|val[p<<1|1].first;
	val[p].second = val[p<<1].second*val[p<<1|1].second%mod;
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		val[p].first|=1<<2;
		val[p].second = 3;
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push_up(p);
}
void update(int p,int l,int r,int x,ll v)
{
	if(l==r)
	{
		val[p].first = 0;
		for(int i = 1;i<= 60;i++)
			if(v%prime[i]==0)
				val[p].first|=(1ll<<i);
		val[p].second = v%mod;
		return ;
	}
	int mid = (l+r)>>1;
	if(x<=mid)update(p<<1,l,mid,x,v);
	else update(p<<1|1,mid+1,r,x,v);
	push_up(p);
}
PLL uni(PLL a,PLL b)
{
	a.first |= b.first;
	(a.second *= b.second)%=mod;
	return a;
}
pair<ll,ll> getans(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return val[p];
	pair <ll,ll>ans;
	int mid = (l+r)>>1;
	ans.first = 0,ans.second = 1;
	if(a<=mid)ans=uni(ans,getans(p<<1,l,mid,a,b));
	if(b >mid)ans=uni(ans,getans(p<<1|1,mid+1,r,a,b));
	return ans;
}
int main()
{
	int n = 1e5;
	int m;
	init();
	build(1,1,n);
	scanf("%d",&m);
	while(m--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(a==1)
			update(1,1,n,b,c);
		else
		{
			PLL ans = getans(1,1,n,b,c);
			ll Ans = ans.second;
			for(int i =1;i<= 60;i++)
				if((ans.first>>i)&1)
					Ans = Ans*(prime[i]-1)%mod*env[i]%mod;
			printf("%lld\n",Ans);
		}
	}
	return 0;
}
