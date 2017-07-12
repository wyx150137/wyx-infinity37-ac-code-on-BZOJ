
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
const int mod = 1e9+7;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y){e[++tot].to=y;e[tot].next=head[x];head[x]=tot;}
ll quick_pow(ll x,ll y)
{
	if(y==0)return 1;
	ll tmp = quick_pow(x,y>>1);
	if(y&1)return tmp*tmp%mod*x%mod;
	else return tmp*tmp%mod;
}
int deg[N],tdeg[N],invdeg[N],n,m,s,t;
ll ans;
void init()
{
	for(int i = 1;i<= n;i++)
		invdeg[i] = quick_pow(deg[i],mod-2);
}
queue<int>Q;
ll f[N];
void topo()
{
	f[t] = ans;
	for(int i = 1;i<= n;i++)
		if(!tdeg[i])
			Q.push(i);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		f[x] = (ll)f[x]*invdeg[x]%mod;
		for(int i = head[x];i;i=e[i].next)
		{
			(f[e[i].to]+=f[x])%=mod;
			if(!(--tdeg[e[i].to]))
				Q.push(e[i].to);
		}
	}
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);
	int x,y;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
		deg[y]++;
		tdeg[y]++;
	}
	deg[t]++;
	ans = 1;
	for(int i = 2;i<= n;i++)
		ans = ans*deg[i]%mod;
	if(t==1)
		printf("%lld\n",ans);
	else
	{
		init();
		topo();
		printf("%lld\n",(ans-f[s]+mod)%mod);
	}
	return 0;
}
