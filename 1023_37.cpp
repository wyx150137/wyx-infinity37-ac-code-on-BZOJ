
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const int M = 2e6+5;
struct E
{int next,to;}e[M];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int f[N],fa[N],a[N],dep[N],pos[N],low[N],q[N],Dfn,ans;
void solve(int x,int y)
{
	int cnt = dep[y]-dep[x]+1,h = 1,t = 1,i;
	for(i = y;i!=x;i = fa[i])a[cnt--]=f[i];a[1] = f[x];
	cnt = dep[y]-dep[x]+1,q[1] = 1;
	for(i=1;i<=cnt;i++)a[i+cnt]=a[i];
	for(i=2;i<=cnt+(cnt>>1);i++)
	{
		if(i-q[h]>(cnt>>1))h++;
		ans = max(ans,a[i]+i+a[q[h]]-q[h]);
		while(h<=t&&a[i]-i>=a[q[t]]-q[t])
			t--;
		q[++t] = i;
	}
	for(int i = 2;i<= cnt;i++)
		f[x] = max(f[x],a[i]+min(i-1,cnt-i+1));
}
void dfs(int x)
{
	pos[x] = low[x] = ++Dfn;
	for(int i = head[x];i;i=e[i].next)
	{
		if(e[i].to==fa[x])continue;
		if(!pos[e[i].to])
		{
			fa[e[i].to] = x;
			dep[e[i].to] = dep[x]+1;
			dfs(e[i].to);
		}
		low[x] = min(low[x],low[e[i].to]);
		if(low[e[i].to]>pos[x])
		{
			ans = max(ans,f[e[i].to]+f[x]+1);
			f[x] = max(f[x],f[e[i].to]+1);
		}
	}
	for(int i = head[x];i;i=e[i].next)
		if(fa[e[i].to]!=x&&pos[x]<pos[e[i].to])
			solve(x,e[i].to);
}
int main()
{
	int n,m,cnt;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		int x,y;
		scanf("%d",&cnt);
		scanf("%d",&x);
		for(int j = 2;j<= cnt;j++)
		{
			scanf("%d",&y);
			add(x,y);
			x = y;
		}
	}
	dfs(1);
	printf("%d\n",ans);
	return 0;
}
