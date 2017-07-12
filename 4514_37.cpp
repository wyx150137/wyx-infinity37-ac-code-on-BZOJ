
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int N = 305;
const int M = N*N+10*N;
const int maxX = 1e5+5;
int prime[maxX],cnt;
bool vis[maxX];
struct E
{
	int next,to,from;
	ll c,f;
}e[M];
int head[N],tot = 1,from[N];
void add(int x,int y,ll f,ll c)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].f = f;e[tot].c = c;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].f = 0;e[tot].c = -c;
	e[tot].from = y,e[tot-1].from = x;
}
queue<int>Q;
bool v[N];
ll dis[N],rl[N];
void spfa(int S,int T)
{
	for(int i = S;i<= T;i++)dis[i] = -INF;
	Q.push(S);
	dis[S] = 0,vis[S] = true;
	rl[S] = INF;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		v[x] = false;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].f&&dis[x]+e[i].c>dis[e[i].to])
			{
				dis[e[i].to] = dis[x]+e[i].c;
				from[e[i].to] = i;
				rl[e[i].to] = min(rl[x],e[i].f);
				if(!v[e[i].to])
				{
					Q.push(e[i].to);
					v[e[i].to] = true;
				}
			}
	}
}
void init()
{
	for(int i = 2;i<maxX;i++)
	{
		if(!vis[i])
			prime[++cnt] = i;
		for(int j = 1;j<= cnt&&i*prime[j]<maxX;j++)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j]==0)break;
		}
	}
}
int a[N],b[N],c[N],f[N];
int main()
{
	init();
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		ll tmp = a[i];
		for(int j = 1;(ll)prime[j]*prime[j]<=(ll)tmp;j++)
			while(tmp%prime[j]==0)f[i]++,tmp/=prime[j];
		if(tmp!=1&&tmp!=-1)f[i]++;
	}
	for(int i = 1;i<= n;i++)scanf("%d",&b[i]);
	for(int i = 1;i<= n;i++)scanf("%d",&c[i]);
	for(int i = 1;i<= n;i++)
		if(f[i]&1)
			for(int j = 1;j<= n;j++)
				if(f[j]==f[i]-1&&a[i]%a[j]==0||f[j]==f[i]+1&&a[j]%a[i]==0)
					add(i,j,INF,(ll)c[i]*c[j]);
	int S = 0,T = n+1;
	for(int i = 1;i<= n;i++)
		if(f[i]&1)
			add(S,i,b[i],0);
		else add(i,T,b[i],0);
	ll now = 0,ans = 0;
	ll tmp = 0;
	while(true)
	{
		spfa(S,T);
		if(dis[T]==-INF||now+dis[T]<0)break;
		if(dis[T]>=0)tmp = rl[T];
		else tmp = min(rl[T],now/(-dis[T]));
		ans+=tmp;
		now+=dis[T]*tmp;
		for(int i = from[T];i;i=from[e[i].from])
			e[i].f-=tmp,e[i^1].f+=tmp;
	}
	printf("%lld\n",ans);
	return 0;
}
