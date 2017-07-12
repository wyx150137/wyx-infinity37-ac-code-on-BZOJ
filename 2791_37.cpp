
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 500005;
int fa[N][20];
int a[N],on_ring[N],v[N],pos[N],size[N],root[N],dep[N],n;
void dfs(int x,int id)
{
	v[x] = id;
	if(v[a[x]]==v[x])
	{
		int tmp = 1;
		for(int i = x;i!=x||tmp==1;i = a[i],tmp++)
			on_ring[i] = id,pos[i] = tmp,root[i] = i;
		size[id] = --tmp;
		return ;
	}
	if(!v[a[x]])
		dfs(a[x],id);
	if(!on_ring[x])
	{
		fa[x][0] = a[x];
		dep[x] = dep[a[x]]+1;
		root[x] = root[a[x]];
	}
}
void init()
{
	for(int j = 1;j<= 19;j++)
		for(int i = 1;i<= n;i++)
			fa[i][j] = fa[fa[i][j-1]][j-1];
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i = 19;i>= 0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x = fa[x][i];
	if(x==y)return x;
	for(int i = 19;i>= 0;i--)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
int dist(int x,int y,int p)
{
	return (y-x+p)%p;
}
void solve(int x,int y)
{
	if(on_ring[root[x]]!=on_ring[root[y]])
	{
		printf("-1 -1\n");
		return ;
	}
	if(root[x]==root[y])
	{
		int lca = getlca(x,y);
		printf("%d %d\n",dep[x]-dep[lca],dep[y]-dep[lca]);
		return ;
	}
	int fx = root[x],fy = root[y];
	int x1=dep[x]+dist(pos[fx],pos[fy],size[on_ring[fx]]),y1=dep[y];
	int x2=dep[x],y2=dep[y]+dist(pos[fy],pos[fx],size[on_ring[fy]]);
	if(max(x1,y1)!=max(x2,y2))
	{
		if(max(x1,y1)<max(x2,y2))printf("%d %d\n",x1,y1);
		else printf("%d %d\n",x2,y2);
		return ;
	}
	if(min(x1,y1)!=min(x2,y2))
	{
		if(min(x1,y1)<min(x2,y2))printf("%d %d\n",x1,y1);
		else printf("%d %d\n",x2,y2);
		return ;
	}
	printf("%d %d\n",max(x1,y1),min(x1,y1));
}
int main()
{
	int q,x,y;
	scanf("%d%d",&n,&q);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	int rings = 0;
	for(int i = 1;i<= n;i++)
		if(!v[i])
		{
			rings++;
			dfs(i,rings);
		}
	init();
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d",&x,&y);
		solve(x,y);
	}
	return 0;
}
