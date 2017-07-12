
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
const int mod = 1e9+7;
struct E
{int next,to;}e[N<<1];
int head[N],tot,big[N],f[N],fa[N],size[N];
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
}
void dfs(int x)
{
	f[x] = 1;size[x]=1;
	for(int i = head[x];i;i=e[i].next)
	{
		dfs(e[i].to);
		size[x]+=size[e[i].to];
	}
	for(int i = head[x];i;i=e[i].next)
	{
		if(size[e[i].to]<<1==size[x])
			f[x] = (ll)f[x]*big[e[i].to]%mod*f[e[i].to]%mod;
		else
			f[x] = (ll)f[x]*size[e[i].to]%mod*f[e[i].to]%mod;
	}
}
int main()
{
	//freopen("x.in","r",stdin);
	int n,m;
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%d%d",&n,&m);
		for(int i = 1;i<= n;i++)head[i]=big[i]=fa[i]=0;tot = 0;
		int x,y;
		for(int i = 1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			add(x,y);fa[y] = x;
		}
		for(int i = 1;i<= n;i++)
		{
			int now = i;
			while(now)
			{
				if(fa[now]<i)big[now]++;
				now = fa[now];
			}
		}
		for(int i = 1;i<= n;i++)
			if(!fa[i])
			{
				dfs(i);
				printf("%d\n",f[i]);
				break;
			}
	}
	return 0;
}
