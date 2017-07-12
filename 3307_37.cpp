
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
const int M = 6000005;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int fa[N][25],dep[N],cnt;
void dfs(int x,int f)
{
	fa[x][0] = f;
	dep[x] = dep[f]+1;
	for(int i = head[x];i;i =e[i].next)
		if(e[i].to!=fa[x][0])
			dfs(e[i].to,x);
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i = 22;i>= 0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x = fa[x][i];
	if(x==y)return x;
	for(int i = 22;i>= 0;i--)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
int maxn[M],ls[M],rs[M],seg,maxno[M],root[N],n,m;
void update(int &p,int l,int r,int x,int c)
{
	if(!p)p = ++seg;
	if(l==r)
	{
		maxn[p] += c;
		maxno[p] = l;
		if(!maxn[p])maxno[p] =0;
		return ;
	}
	int mid = (l+r)>>1;
	if(x<=mid)update(ls[p],l,mid,x,c);
	else update(rs[p],mid+1,r,x,c);
	if(maxn[ls[p]]>=maxn[rs[p]])
		maxn[p] = maxn[ls[p]],maxno[p] = maxno[ls[p]];
	else 
		maxn[p] = maxn[rs[p]],maxno[p] = maxno[rs[p]];
	if(!maxn[p])maxno[p] =0;
}
int merge(int x,int y,int l,int r)
{
	if(!x||!y)return x+y;
	if(l==r)
	{
		maxn[x] = maxn[x]+maxn[y];
		maxno[x] = l;
		if(!maxn[x])maxno[x] =0;
		return x;
	}
	int mid = (l+r)>>1;
	ls[x] = merge(ls[x],ls[y],l,mid);
	rs[x] = merge(rs[x],rs[y],mid+1,r);
	if(maxn[ls[x]]>=maxn[rs[x]])
		maxn[x] = maxn[ls[x]],maxno[x] = maxno[ls[x]];
	else 
		maxn[x] = maxn[rs[x]],maxno[x] = maxno[rs[x]];
	if(!maxn[x])maxno[x] =0;
	return x;
}
int kind[N],Cnt,ans[N];
int find(int x)
{
	int l = 1,r = Cnt+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(kind[mid]<x)l = mid+1;
		else r = mid;
	}
	return l;
}
struct O
{int x,y,d;}opt[N];
void solve(int x)
{
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to!=fa[x][0])
		{
			solve(e[i].to);
			root[x] = merge(root[x],root[e[i].to],1,Cnt);
		}
	}
	ans[x] = kind[maxno[root[x]]];
}
void init()
{
	for(int j= 1;j<= 19;j++)
		for(int i = 1;i<= n;i++)
			fa[i][j] = fa[fa[i][j-1]][j-1];
}
int main()
{
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1,0);
	init();
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&opt[i].x,&opt[i].y,&opt[i].d);
		kind[++Cnt] = opt[i].d;
	}
	sort(kind+1,kind+Cnt+1);
	int tmp = Cnt;Cnt = 0;
	for(int i = 1;i<= tmp;i++)
		if(kind[i]!=kind[Cnt])
			kind[++Cnt] = kind[i];
	for(int i = 1;i<= m;i++)
	{
		int pos = find(opt[i].d);
		int lca = getlca(opt[i].x,opt[i].y);
		update(root[opt[i].x],1,Cnt,pos,1);
		update(root[opt[i].y],1,Cnt,pos,1);
		update(root[lca],1,Cnt,pos,-1);
		update(root[fa[lca][0]],1,Cnt,pos,-1);
	}
	solve(1);
	for(int i = 1;i<= n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
