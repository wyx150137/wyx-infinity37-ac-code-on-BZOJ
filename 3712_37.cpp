
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 4e5+5;
const int K = 5e5+5;
int no[N],g[N],dep[N];
struct E
{int next,to;}e[N<<1];
int head[N],tot,fa[N][20],dfn[N];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
	fa[y][0] = x;
}
struct Opt
{int x,y,dp,no;}opt[K];
bool cmp(const Opt &a,const Opt &b)
{
	if(a.dp==b.dp)return a.no<b.no;
	else return a.dp>b.dp;
}
void dfs(int x,int id)
{
	dfn[x] = id;
	for(int j = 1;j<= 19;j++)
		fa[x][j] = fa[fa[x][j-1]][j-1];
	for(int i = head[x];i;i=e[i].next)
		dep[e[i].to] = dep[x]+1,
		dfs(e[i].to,id);
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i = 19;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x = fa[x][i];
	if(x==y)return x;
	for(int i = 19;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<= n;i++)scanf("%d",&g[i]),no[i]=i;
	int x,y;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(n+i,no[x]),add(n+i,no[y]);
		no[y] = n+i;
	}
	int tot = 0;
	for(int i = 1;i<= n+m;i++)if(!fa[i][0])dfs(i,++tot);
	int ask = 0;
	for(int i = 1;i<= k;i++)
	{
		scanf("%d%d",&x,&y);
		if(dfn[x]==dfn[y])opt[++ask] = (Opt){x,y,dep[getlca(x,y)],i};
	}
	sort(opt+1,opt+ask+1,cmp);
	long long ans = 0;
	for(int i = 1;i<= ask;i++)
	{
		int gd = min(g[opt[i].x],g[opt[i].y]);
		g[opt[i].x]-=gd,g[opt[i].y]-=gd;
		ans+=2*gd;
	}
	printf("%lld\n",ans);
	return 0;
}
