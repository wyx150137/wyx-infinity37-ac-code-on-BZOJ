
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 4e6+5;
const int mod = 1e9+7;
typedef long long ll;
struct P
{int l,r;}pos[2010];
int prime[N],inv[N],mu[N],g[N],f[N],w[N],sum[2010],P[N],s[N];
bool vis[N];
int cnt;
void quick_shai(int n)
{
	inv[0] = inv[1] = 1;
	for(int i = 2;i<=n;i++)
		inv[i] = (ll)(mod-mod/i)*inv[mod%i]%mod;
	cnt = 0;
	g[1] = mu[1] = 1;
	for(int i = 2;i<=n;i++)
	{
		if(!vis[i])
		{
			prime[++cnt] = i;
			mu[i] = -1;
			g[i] = (1-inv[i]+mod)%mod;
		}
		for(int j = 1;j<= cnt&&i*prime[j]<=n;j++)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j])
			{
				mu[i*prime[j]] = -mu[i];
				g[i*prime[j]] = (ll)g[i]*(1-inv[prime[j]]+mod)%mod;
			}
			else
			{
				mu[i*prime[j]] = 0;
				g[i*prime[j]] = g[i];
				break;
			}
		}
	}	
	f[0] = 0;
	for(int i = 1;i<=n;i++)
		f[i] = (f[i-1]+(ll)g[i]*i%mod*i%mod*i%mod)%mod;
}

int gcd(int a,int b)
{
	if(b==0)return a;
	return gcd(b,a%b);
}

int check(int n)
{
	if(!n)return 0;
	return (s[n]+sum[P[n]])%mod;
}

int main()
{
	int m,n;
	scanf("%d%d",&m,&n);
	quick_shai(n);
	int block = sqrt(n);
	int last;
	for(int i = 1;i<= n;i++)
		P[i] = (i-1)/block+1;
	last = P[n];
	pos[1].l = 1;
	for(int i = 2;i<= n;i++)
		if(P[i-1]<P[i]){pos[P[i-1]].r = i-1,pos[P[i]].l = i;}
	pos[last].r = n;
	memset(sum,0,sizeof(sum));
	for(int i = 0;i<= n;i++)w[i]=(ll)i*i%mod;
	for(int i = 1;i<= n;i++)s[i] = (s[i-1]+w[i])%mod;
	int a,b,k;
	ll x,y;
	int Last;
	while(m--)
	{
		scanf("%d%d%lld%d",&a,&b,&x,&k);
		int c = gcd(a,b);
		y = (ll)a/c*b/c;
		x/=y;x%=mod;
		int d = (x-w[c]+mod)%mod;w[c] = x;
		for(int i = c;i<= pos[P[c]].r;i++)s[i] = (s[i]+d)%mod;
		for(int i = P[c]+1;i<= last;i++)sum[i] = (sum[i]+d)%mod;
		ll ans = 0;
		for(int i = 1;i<= k;i = Last+1)
		{
			Last = k/(k/i);
			ans = (ans+(ll)(check(Last)-check(i-1)+mod)*f[k/i]%mod)%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
