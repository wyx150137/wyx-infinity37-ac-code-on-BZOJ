
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int fa[N],size[N],son[N],top[N],id[N],pos[N],dep[N],sum[N][155],a[N];
void dfs1(int x,int f)
{
	fa[x] = f;
	size[x]++;
	dep[x] = dep[f]+1;
	int p = fa[x];
	for(int i =1;i<= 150&&p;p = fa[p],i++)sum[x][i] = sum[p][i]+a[x];
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to!=f)
		{
			dfs1(e[i].to,x);
			size[x]+=size[e[i].to];
			if(size[e[i].to]>size[son[x]])son[x] = e[i].to;
		}
	}
}
int cnt;
void dfs2(int x,int tp)
{
	top[x] = tp;
	id[++cnt] = x;
	pos[x] = cnt;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=son[x]&&e[i].to!=fa[x])
			dfs2(e[i].to,e[i].to);
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x = fa[top[x]];
	}
	if(dep[x]<dep[y])return x;
	return y;
}
int find(int x,int y)
{
	while(dep[x]-dep[top[x]]<y)
	{
		y-=dep[x]-dep[top[x]]+1;
		x = fa[top[x]];
	}
	return id[pos[x]-y];
}
int ask(int x,int y,int z)
{
	int ans = 0;
	if(z<=150)return sum[x][z]-sum[y][z]+a[y];
	while(top[x]!=top[y])
	{
		int i;
		for(i = pos[x];i>=pos[top[x]];i-=z)ans+=a[id[i]];
		x = find(x,pos[x]-i);
	}
	for(int i = pos[x];i>=pos[y];i-=z)ans+=a[id[i]];
	return ans;
}
int solve(int x,int y,int z)
{
	int ans = 0,lca = getlca(x,y);
	int lth = dep[x]+dep[y]-2*dep[lca];
	if(lth%z)ans+=a[y];
	y = find(y,lth%z);
	int t1 = find(x,(dep[x]-dep[lca])/z*z);
	if(dep[y]<=dep[lca])return ans+ask(x,t1,z);
	int t2 = find(y,(dep[y]-dep[lca])/z*z);
	if(t1==t2)ans-=a[t1];
	return ans+ask(x,t1,z)+ask(y,t2,z);
}
int b[N],c[N];
int main()
{
	int n,x,y;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i = 1;i<= n;i++)scanf("%d",&b[i]);
	for(int i = 1;i< n;i++)
	{
		scanf("%d",&x);
		printf("%d\n",solve(b[i],b[i+1],x));
	}
	return 0;
}
