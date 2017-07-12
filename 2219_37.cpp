
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 100005;
const ll INF = 0x7fffffffffffffffll;
int cas,num;
ll A,B,K;
ll prime[10005];
struct Hash
{
	#define mod 100007
	int head[mod],nxt[N],id[N],tot;
	ll val[N];
	void clear()
	{
		tot = 0;
		memset(head,0,sizeof(head));
	}
	int Insert(ll x,int k)
	{
		int tmp = x%mod;
		for(int i = head[tmp];i;i=nxt[i])
			if(val[i]==x)
				return id[i];
		if(k==-1)return -1;
		val[++tot] = x;
		id[tot] = k;
		nxt[tot] = head[tmp];
		head[tmp] = tot;
	}
}hmp;
ll quick_pow(ll x,ll y,ll p=INF)
{
	ll res = 1;
	while(y)
	{
		if(y&1)res = res*x%p;
		x = x*x%p;
		y>>=1;
	}
	return res;
}
bool check(int x,ll p,ll k)
{
	for(int i = 1;i<= num;i++)
		if(quick_pow(x,k/prime[i],p)==1)
			return false;
	return true;
}
void get_fac(ll p)
{
	num = 0;
	for(ll i = 2;i*i<= p;i++)
		if(p%i==0)
		{
			prime[++num] = i;
			while(p%i==0)p/=i;
		}
	if(p>1)prime[++num] = p;
}
ll get_root(ll p,ll x)
{
	get_fac(x);
	for(int i = 2;;i++)
		if(check(i,p,x))return i;
}
void ex_gcd(ll a,ll b,ll &x,ll &y,ll &d)
{
	if(b==0)
	{
		d = a;
		x = 1;
		y = 0;
		return ;
	}
	ex_gcd(b,a%b,y,x,d);
	y-=a/b*x;
}
ll get_inv(ll a,ll b)
{
	ll x,y,d;
	ex_gcd(a,b,x,y,d);
	b/=d;
	return (x%b+b)%b;
}
ll BSGS(ll a,ll g,ll p)
{
	hmp.clear();
	ll m = sqrt(p)+1,tmp=1;
	for(int i = 0;i<m;i++,tmp=tmp*g%p)hmp.Insert(tmp,i);
	ll Inv = get_inv(tmp,p);
	int k;
	for(int i = 0;i<m;i++,a=a*Inv%p)
	{
		k = hmp.Insert(a,-1);
		if(k!=-1)return m*i+k;
	}
}
ll gcd(ll a,ll b)
{
	if(b==0)return a;
	return gcd(b,a%b);
}
ll solve(ll a,ll b,ll p,ll t)
{
	ll MOD = quick_pow(p,t),ret=0,phi,g,ind,tmp;
	b = b%MOD;
	if(!b)return quick_pow(p,t-((t-1)/a+1));
	while(b%p==0)ret++,b/=p;
	if(ret%a)return 0;
	t-=ret;
	MOD = quick_pow(p,t);
	phi = MOD-MOD/p;
	g = get_root(MOD,phi);ind = BSGS(b,g,MOD);
	tmp = gcd(a,phi);
	if(ind%tmp)return 0;
	return tmp*quick_pow(p,ret-ret/a);
}
int main()
{
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%lld%lld%lld",&A,&B,&K);
		ll ans = 1;
		K = 2*K+1;
		for(ll i= 2;i*i<= K;i++)
			if(K%i==0)
			{
				int ret = 0;
				while(K%i==0)K/=i,ret++;
				ans*=solve(A,B,i,ret);
			}
		if(K>1&&ans)ans*=solve(A,B,K,1);
		printf("%lld\n",ans);
	}
	return 0;
}
