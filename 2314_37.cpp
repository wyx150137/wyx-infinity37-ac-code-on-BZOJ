
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int mod = 1032992941;
ll f[N][2],g[N][2],h[N][2];
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
void dfs(int x,int fa)
{
	f[x][0] = 1,g[x][0] = INF,h[x][0] = 0;
	f[x][1] = g[x][1] = h[x][1] = 1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
			dfs(e[i].to,x);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
		{
			int mn = min(f[e[i].to][0],min(g[e[i].to][0],h[e[i].to][0]));
			ll tmp = 0;
			if(f[e[i].to][0]==mn)tmp+=f[e[i].to][1];
			if(g[e[i].to][0]==mn)tmp+=g[e[i].to][1];
			if(h[e[i].to][0]==mn)tmp+=h[e[i].to][1];
			f[x][0]+=mn,f[x][1]=f[x][1]*tmp%mod;

			mn = min(min(g[x][0]+f[e[i].to][0],g[x][0]+g[e[i].to][0]),h[x][0]+f[e[i].to][0]);
			tmp = 0;
			if(g[x][0]+f[e[i].to][0]==mn)tmp+=(g[x][1]*f[e[i].to][1])%mod;
			if(g[x][0]+g[e[i].to][0]==mn)tmp+=(g[x][1]*g[e[i].to][1])%mod;
			if(h[x][0]+f[e[i].to][0]==mn)tmp+=(h[x][1]*f[e[i].to][1])%mod;
			g[x][0] = mn;
			g[x][1] = tmp%mod;

			h[x][0]+=g[e[i].to][0];
			h[x][1] = h[x][1]*g[e[i].to][1]%mod;
		}
}
int main()
{
	int n,x,y;
	scanf("%d",&n);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,0);
	int ans1,ans2=0;
	ans1 = min(f[1][0],g[1][0]);
	if(f[1][0]==ans1)ans2+=f[1][1];
	if(g[1][0]==ans1)ans2+=g[1][1];
	ans2%=mod;
	printf("%d\n%d\n",ans1,ans2);
	return 0;
}
