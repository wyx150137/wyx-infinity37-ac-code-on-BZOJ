
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int n,m,q;
namespace Cactus
{
	struct E
	{int next,to,val;}e[N];
	int head[N],tot=1;
	int fa[N],dep[N],dfn[N],Dfn;
	bool on_ring[N];
}
namespace RST
{
	struct E
	{
		int next,to,dis,val;
	}e[N];
	int head[N],tot=1,size[N],dis[N],n;
	int fa[N][18],dep[N];
	void add(int x,int y)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
		e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
	}
	void getinfo(int x,int pre)
	{
		dep[x] = dep[fa[x][0]]+1;
		for(int i = 1;i<= 17;i++)
			fa[x][i] =fa[fa[x][i-1]][i-1];
		if(x<=::n)
		{
			for(int i = head[x];i;i=e[i].next)
				if(i^pre^1)
				{
					if(e[i].to<=::n)e[i].dis = e[i].val = abs(Cactus::dep[e[i].to]-Cactus::dep[x]);
					else e[i].val = e[i].dis = 0;
				}
		}else
		{
			for(int i = head[x];i;i=e[i].next)
				if(i^pre^1)
				{
					e[i].dis = (Cactus::dep[e[i].to]-Cactus::dep[fa[x][0]]+size[x])%size[x];
					e[i].val = min(e[i].dis,size[x]-e[i].dis);
				}
		}
		for(int i = head[x];i;i=e[i].next)
			if(pre^i^1)
			{
				fa[e[i].to][0] = x;
				dis[e[i].to] = dis[x]+e[i].val;
				getinfo(e[i].to,i);
			}
	}
	int getlca(int x,int y)
	{
		if(dep[x]<dep[y])swap(x,y);
		for(int i = 17;i>= 0;i--)
			if(dep[fa[x][i]]>=dep[y])
				x = fa[x][i];
		if(x==y)return x;
		for(int i = 17;i>= 0;i--)
			if(fa[x][i]!=fa[y][i])
				x = fa[x][i],y = fa[y][i];
		return fa[x][0];
	}
	int go_up(int x,int d)
	{
		for(int i = 17;i>= 0;i--)
			if((d>>i)&1)x = fa[x][i];
		return x;
	}
	int getans(int x,int y)
	{
		int lca = getlca(x,y);
		if(lca<=::n)return dis[x]+dis[y]-dis[lca]*2;
		else
		{
			int tx = go_up(x,dep[x]-dep[lca]-1);
			int ty = go_up(y,dep[y]-dep[lca]-1);
			int tmp = ((Cactus::dep[tx]-Cactus::dep[ty])%size[lca]+size[lca])%size[lca];
			return dis[x]+dis[y]-dis[tx]-dis[ty]+min(tmp,size[lca]-tmp);
		}
	}
}
namespace Cactus
{
	void add(int x,int y,int f)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].val = f;
		e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].val = f;
	}
	void dfs(int x,int pre)
	{
		dfn[x] = ++Dfn;
		for(int i = head[x];i;i=e[i].next)if(i^pre^1)
		{
			if(!dfn[e[i].to])
			{
				fa[e[i].to] = x;
				dep[e[i].to] = dep[x]+e[i].val;
				on_ring[x] = false;
				dfs(e[i].to,i);
				if(!on_ring[x])
					RST::add(x,e[i].to);
			}else
			{
				if(dfn[e[i].to]>dfn[x])
					continue;
				int tmp = x;
				++RST::n;
				while(true)
				{
					RST::add(RST::n,tmp);
					on_ring[tmp] = true;
					if(tmp==e[i].to)break;
					tmp = fa[tmp];
				}
				RST::size[RST::n] = dep[x]-dep[e[i].to]+e[i].val;
			}
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	RST::n = n;
	int x,y,z;
	while(m--)
	{
		scanf("%d%d%d",&x,&y,&z);
		Cactus::add(x,y,z);
	}
	Cactus::dfs(1,0);
	RST::getinfo(1,0);
	while(q--)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",RST::getans(x,y));
	}
	return 0;
}
