
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
const int M = 6e4+5;
const int INF = 0x3f3f3f3f;
int f[M<<1][2];
namespace Cactus
{
	struct E
	{int next,to;}e[M<<1];
	int head[N],tot=1,n;
	int dfn[N],low[N],Dfn,stk[N],top;
}
namespace R_S_Tree
{
	struct E
	{int next,to;}e[M<<2];
	int head[N<<1],tot=1,n;
	void add(int x,int y)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
		e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
	}
	void dp(int x,int fa)
	{
		f[x][1]=1;
		if(x<=Cactus::n)
		{
			for(int i = head[x];i;i=e[i].next)
				if(e[i].to!=fa)
				{
					dp(e[i].to,x);
					if(e[i].to>Cactus::n)continue;
					f[x][0]+=max(f[e[i].to][0],f[e[i].to][1]);
					f[x][1]+=f[e[i].to][0];
				}
		}else
		{
			static int g[M<<1][2];
			int top = 0;
			for(int i = head[x];i;i=e[i].next)
				if(e[i].to!=fa)
					dp(e[i].to,x);
			for(int i = head[x];i;i=e[i].next)
			{
				g[++top][0] = f[e[i].to][0];
				g[top][1] = f[e[i].to][1];
			}
			for(int i = top-1;i>=1;i--)
			{
				g[i][0]+=max(g[i+1][0],g[i+1][1]);
				g[i][1]+=g[i+1][0];
			}
			f[fa][0] = g[1][0];
			for(int i = 1;i<top;i++)
			{
				g[i][0]-=max(g[i+1][0],g[i+1][1]);
				g[i][1]-=g[i+1][0];
			}
			g[top][1] = -INF;
			for(int i = top-1;i>=1;i--)
			{
				g[i][0]+=max(g[i+1][0],g[i+1][1]);
				g[i][1]+=g[i+1][0];
			}
			f[fa][1] = g[1][1];
		}
	}
}
namespace Cactus
{
	void add(int x,int y)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
		e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
	}
	void dfs(int x,int pre)
	{
		stk[++top] = x;
		dfn[x] = low[x] = ++Dfn;
		for(int i = head[x];i;i=e[i].next)if(i!=(pre^1))
		{
			if(!dfn[e[i].to])
			{
				dfs(e[i].to,i);
				low[x] =min(low[x],low[e[i].to]);
				if(low[e[i].to]>=dfn[x])
				{
					int tmp;
					R_S_Tree::n++;
					do
					{
						tmp = stk[top--];
						R_S_Tree::add(tmp,R_S_Tree::n);
					}while(tmp!=e[i].to);
					R_S_Tree::add(x,R_S_Tree::n);
				}
			}else low[x] = min(low[x],dfn[e[i].to]);
		}
	}
};
int main()
{
	int m;
	scanf("%d%d",&Cactus::n,&m);
	R_S_Tree::n = Cactus::n;
	int x,y;
	while(m--)
	{
		scanf("%d%d",&x,&y);
		Cactus::add(x,y);
	}
	Cactus::top = 0,Cactus::Dfn = 0;
	Cactus::dfs(1,0);
	R_S_Tree::dp(1,0);
	printf("%d\n",max(f[1][0],f[1][1]));
	return 0;
}
