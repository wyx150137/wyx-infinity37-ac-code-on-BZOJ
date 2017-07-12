
#include <stdio.h>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e7+5;
int mu[N],prime[N/10],cnt,f[2005],g[2005],k,stack[2005],top;
bool vis[N];
int gcd(int a,int b)
{
	if(b==0)return a;
	return gcd(b,a%b);
}
void get_mu()
{
	mu[1] = 1;
	for(int i = 2;i<N;i++)
	{
		if(!vis[i])
		{
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j = 1;j<= cnt&&i*prime[j]<N;j++)
		{
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
			else
				mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i = 1;i<= k;i++)
		f[i] = f[i-1]+(gcd(i,k)==1),g[i]=g[i-1]+(gcd(i,k)==1)*mu[i];
	for(int i = 2;i<= k;i++)if(k%i==0&&mu[i])stack[++top]=i;
	for(int i = 1;i<N;i++)mu[i]+=mu[i-1];
}
map<ll,int>mp,mp2;
inline int calc_mu(int x)
{
	if(x<N)return mu[x];
	if(mp.count(x))mp[x];
	int t = 1;
	for(int i = 2,last;i<= x;i=last+1)
	{
		last = x/(x/i);
		t-=(last-i+1)*calc_mu(x/i);
	}
	return mp[x] = t;
}
inline int calc(int x)
{
	if(x<=k)return g[x];
	if(mp2.count(x))return mp2[x];
	int tmp = calc_mu(x);
	for(int i = 1;i<= top && stack[i]<=x;i++)
	{
		tmp = tmp-(mu[stack[i]]-mu[stack[i]-1])*calc(x/stack[i]);
	}
	return mp2[x] = tmp;
}
inline int F(int x)
{
	return (x/k)*f[k]+f[x%k];
}
int main()
{
	int n,m;
	scanf("%d%d%d",&n,&m,&k);
	get_mu();
	ll ans = 0;
	for(int i = 1,last;i<=min(n,m);i=last+1)
	{
		last = min(n/(n/i),m/(m/i));
		ans += (ll)(calc(last) - calc(i-1)) * F(m/i) * (n/i);
	}
	printf("%lld\n",ans);
	return 0;
}
