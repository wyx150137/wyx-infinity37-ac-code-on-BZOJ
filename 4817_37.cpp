
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
int n,m;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int Son[N],dfn[N],seq[N],top[N],size[N],dep[N],fa[N],Dfn;
void dfs1(int x)
{
	dep[x] = dep[fa[x]]+1;
	size[x] = 1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x])
		{
			fa[e[i].to] = x;
			dfs1(e[i].to);
			size[x]+=size[e[i].to];
			if(size[e[i].to]>size[Son[x]])Son[x] = e[i].to;
		}
}
void dfs2(int x,int tp)
{
	top[x] = tp;
	dfn[x] = ++Dfn;
	seq[Dfn] = x;
	if(Son[x])dfs2(Son[x],tp);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=Son[x])
			dfs2(e[i].to,e[i].to);
}
int getlca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x = fa[top[x]];
	}
	if(dep[x]<dep[y])return x;
	return y;
}
int mx[N<<2],lazy[N<<2];
void build(int p,int l,int r)
{
	lazy[p] = 0;
	if(l==r)
	{
		mx[p] = dep[seq[l]];
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	mx[p] = max(mx[p<<1],mx[p<<1|1]);
}
void Push_down(int p,int l,int r)
{
	if(l==r||!lazy[p])return ;
	mx[p<<1]+=lazy[p],mx[p<<1|1]+=lazy[p];
	lazy[p<<1]+=lazy[p],lazy[p<<1|1]+=lazy[p];
	lazy[p] = 0;
}
void Update(int p,int l,int r,int a,int b,int c)
{
	Push_down(p,l,r);
	if(l>=a&&r<=b){mx[p]+=c;lazy[p]+=c;return ;}
	int mid = (l+r)>>1;
	if(a<=mid)Update(p<<1,l,mid,a,b,c);
	if(b >mid)Update(p<<1|1,mid+1,r,a,b,c);
	mx[p] = max(mx[p<<1],mx[p<<1|1]);
}
int Getans(int p,int l,int r,int a,int b)
{
	Push_down(p,l,r);
	if(l>=a&&r<=b)return mx[p];
	int mid = (l+r)>>1;
	int ans = 0;
	if(a<=mid)ans = max(ans,Getans(p<<1,l,mid,a,b));
	if(b >mid)ans = max(ans,Getans(p<<1|1,mid+1,r,a,b));
	return ans;
}
int son[N][2],father[N],lx[N];
bool is_root(int x)
{
	return son[father[x]][0]!=x&&son[father[x]][1]!=x;
}
void update(int x)
{
	lx[x] = x;
	if(son[x][0])
		lx[x] = lx[son[x][0]];
}
void rotate(int x)
{
	int y = father[x],z = father[y];
	int d = son[y][1]==x;
	if(!is_root(y))
	{
		if(son[z][0]==y)son[z][0] = x;
		else son[z][1] = x;
	}
	father[y] = x,father[x] = z,father[son[x][d^1]] = y;
	son[y][d] = son[x][d^1];son[x][d^1] = y;
	update(x),update(y);
}
void splay(int x)
{
	while(!is_root(x))
	{
		int y = father[x],z = father[y];
		if(!is_root(y))
		{
			if((son[y][0]==x)!=(son[z][0]==y))rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	update(x);
}
void access(int x)
{
	int t = 0;
	while(x)
	{
		splay(x);
		if(son[x][1])
		{
			int y = lx[son[x][1]];
			Update(1,1,n,dfn[y],dfn[y]+size[y]-1,1);
		}
		son[x][1] = t;
		if(son[x][1])
		{
			int y = lx[son[x][1]];
			Update(1,1,n,dfn[y],dfn[y]+size[y]-1,-1);
		}
		update(x);
		t = x;x = father[x];
	}
}
int col(int x)
{
	splay(x);
	return lx[x];
}
int main()
{
	scanf("%d%d",&n,&m);
	int a,b;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b),add(b,a);
	}
	dfs1(1),dfs2(1,1);
	build(1,1,n);
	for(int i = 1;i<= n;i++)father[i]=fa[i];
	int opt;
	while(m--)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d",&a);
			access(a);
		}else if(opt==2)
		{
			scanf("%d%d",&a,&b);
			int lca = getlca(a,b);
			int flca = fa[lca];
			int valx = Getans(1,1,n,dfn[a],dfn[a]),valy = Getans(1,1,n,dfn[b],dfn[b]);
			int vall = 0;
			if(flca)
			{
				vall = Getans(1,1,n,dfn[flca],dfn[flca]);
				if(col(lca)==col(flca))
					vall--;
			}
			printf("%d\n",valx+valy-2*vall-1);
		}else
		{
			scanf("%d",&a);
			printf("%d\n",Getans(1,1,n,dfn[a],dfn[a]+size[a]-1));
		}
	}
	return 0;
}
