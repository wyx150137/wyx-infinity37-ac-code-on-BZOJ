
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll base = 6000000000000000000ull;
const int N = 20;
ll quick_plus(ll x,ll y,ll mod)
{
	ll ans = 0;
	while(y)
	{
		if(y&1)(ans+=x)%=mod;
		x = (x+x)%mod;
		y>>=1;
	}
	return ans;
}
void getfib(ll n,ll &x,ll &y,ll mod)
{
	if(!n){x=0,y=1;return ;}
	else if(n==1){x=y=1;return ;}
	if(n&1){getfib(n-1,y,x,mod);y=(x+y)%mod;return;}
	ll a,b;
	getfib(n>>1,a,b,mod);
	x = (quick_plus(a,b,mod)+quick_plus(a,b>a?b-a:b-a+mod,mod))%mod;
	y = (quick_plus(a,a,mod)+quick_plus(b,b,mod))%mod;
}
ll Pow[N],b[N];
char s[N];
bool flag;
ll ans;
void dfs(int n,ll now,ll mod)
{
	if(flag)return ;
	ll x,y;
	getfib(now,x,y,Pow[n]);
	if(x!=b[n])return ;
	if(n==1){flag = true;ans = base+now;return ;}
	for(int i = 0;i<10;i++)
		dfs(n-1,(now+mod*i)%(mod*10),mod*10);
}
int main()
{
	scanf("%s",s+1);
	int n = strlen(s+1);
	for(int i = n;i;i--)
	{
		if(i==n)Pow[i]=1;
		else Pow[i]=Pow[i+1]*10;
		b[i]=b[i+1]+Pow[i]*(s[i]-'0');
	}
	for(int i = 1;i<= n;i++)Pow[i]*=10;
	for(int i = 0;i<60;i++)
		dfs(n,i,60);
	if(flag)printf("%llu\n",ans);
	else printf("NIE\n");
	return 0;
}
