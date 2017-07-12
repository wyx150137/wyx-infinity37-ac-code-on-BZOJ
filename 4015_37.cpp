
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define inf 0x1f1f1f1f
const int N = 210;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void clear()
{
	memset(head,0,sizeof(head));
	tot = 0;
}
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int q[N],fr,ta,fa[N],size[N];
vector <int> grav;
const int mod = 10007;
void Add(int &x,int y)
{
	if((x+=y)>=mod)
		x-=mod;
}
namespace solve1
{
	int f[N][N],g[N],fa[N],size[N];
	void dfs(int x)
	{
		size[x] = 1;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=fa[x])
			{
				fa[e[i].to] = x;
				dfs(e[i].to);
				size[x]+=size[e[i].to];
			}
	}
	void dp(int x)
	{
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=fa[x])
				dp(e[i].to);
		f[x][1] = 1;
		memset(g,0,sizeof(g));
		g[0] = 1;
		for(int j = head[x];j;j=e[j].next)
			if(e[j].to!=fa[x])
				for(int k = size[x]-1;k>=0;k--)
					for(int i = 1;i<= size[e[j].to] && i<=k;i++)
						Add(g[k],g[k-i]*f[e[j].to][i]%mod);
		for(int i = 1;i<size[x];i++)
			f[x][i+1] = g[i];
	}
	void work(int root)
	{
		memset(fa,0,sizeof(fa));
		dfs(root);
		memset(f,0,sizeof(f));
		dp(root);
		int res = 0;
		for(int all = 1;all<= size[root];all++)
		{
			memset(g,0,sizeof(g));
			g[0] = 1;
			for(int j = head[root];j;j=e[j].next)
				for(int k = all-1;k>= 0;k--)
					for(int i = 1;i<=size[e[j].to]&&i*2<all&&i<=k;i++)
						Add(g[k],g[k-i]*f[e[j].to][i]%mod);
			Add(res,g[all-1]);
		}
		printf("%d\n",res);
	}
}

namespace solve2
{
	int f[N][N],g[N],size[N];
	void dp(int x,int fa)
	{
		size[x] = 1;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=fa)
			{
				dp(e[i].to,x);
				size[x]+=size[e[i].to];
			}
		f[x][1] = 1;
		memset(g,0,sizeof(g));
		g[0] = 1;
		for(int j = head[x];j;j=e[j].next)
			if(e[j].to!=fa)
				for(int k = size[x]-1;k>=0;k--)
					for(int i = 1;i<= size[e[j].to]&&i<=k;i++)
						Add(g[k],g[k-i]*f[e[j].to][i]%mod);
		for(int i = 1;i<size[x];i++)
			f[x][i+1] = g[i];
	}
	void work(int r1,int r2)
	{
		memset(f,0,sizeof(f));
		dp(r1,r2),dp(r2,r1);
		int res = 0;
		for(int i = 1;i<= size[r1]&&i<= size[r2];i++)
			Add(res,f[r1][i]*f[r2][i]%mod);
		printf("%d\n",res);
	}
}
int main()
{
	//freopen("4015.in","r",stdin);
	//freopen("4015.out","w",stdout);
	int cas;
	scanf("%d",&cas);
	int n,a,b;
	for(int Cas = 1;Cas<= cas;Cas++)
	{
		printf("Case %d: ",Cas);
		clear();
		scanf("%d",&n);
		for(int i = 1;i<n;i++)
		{
			scanf("%d%d",&a,&b);
			add(a,b);
		}
		if(n<=2)puts("1");
		else
		{
			fr = 0;
			ta = -1;
			q[++ta] = 1;
			while(fr<=ta)
			{
				int x = q[fr++];
				for(int i = head[x];i;i=e[i].next)
					if(e[i].to!=fa[x])
					{
						fa[e[i].to] = x;
						q[++ta] = e[i].to;
					}
			}
			memset(size,0,sizeof(size));
			for(int i = ta;i>=0;i--)
				size[fa[q[i]]]+=++size[q[i]];
			size[0] = 0;
			grav.clear();
			int Min = inf,now;
			for(int i = 1;i<= n;i++)
			{
				now=n-size[i];
				for(int j = head[i];j;j=e[j].next)
					if(fa[e[j].to]==i)
						now = max(now,size[e[j].to]);
				if(now<Min)
				{
					Min = now;
					grav.clear();
					grav.push_back(i);
				}
				else if(now==Min)
					grav.push_back(i);
			}
			if(grav.size()==1)
				solve1::work(grav[0]);
			else
				solve2::work(grav[0],grav[1]);
		}
	}
	return 0;
}
