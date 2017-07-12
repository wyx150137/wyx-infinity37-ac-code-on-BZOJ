
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int M = 100005;
const int N = 4005;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,val;}e[N<<1];
int head[N],tot,dis[N],dep[N],top[N],son[N],size[N],w[N],fa[N],cnt,n,m;
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val = f;
	head[x] = tot;
	e[++tot].to = x;
	e[tot].next = head[y];
	e[tot].val = f;
	head[y] = tot;
}
struct S
{int u,v,val;}b[M<<1];
int snum;
void add_s(int x,int y,int f)
{
	b[++snum].u = x;
	b[snum].v = y;
	b[snum].val = f;
}
void dfs1(int x,int f)
{
	fa[x] = f;
	size[x]++;
	dep[x] = dep[f]+1;
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to!=f)
		{
			dis[e[i].to] = dis[x]+e[i].val;
			dfs1(e[i].to,x);
			size[x]+=size[e[i].to];
			if(size[e[i].to]>size[son[x]])son[x] = e[i].to;
		}
	}
}
void dfs2(int x,int tp)
{
	w[x] = ++cnt;
	top[x] = tp;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
}
int minn[N<<2],lazy[N<<2];
void push_down(int l,int r,int p)
{
	if(l==r||lazy[p]==INF)return ;
	minn[p<<1] = min(minn[p<<1],lazy[p]);
	minn[p<<1|1] = min(minn[p<<1|1],lazy[p]);
	lazy[p<<1] = min(lazy[p<<1],lazy[p]);
	lazy[p<<1|1] = min(lazy[p<<1|1],lazy[p]);
	lazy[p] = INF;
}
void update(int p,int l,int r,int a,int b,int c)
{
	push_down(l,r,p);
	if(l>=a&&r<=b)
	{
		minn[p] = min(minn[p],c);
		lazy[p] = min(lazy[p],c);
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,c);
	if(b>mid) update(p<<1|1,mid+1,r,a,b,c);
	minn[p] = min(minn[p<<1],minn[p<<1|1]);
}
int getans(int p,int l,int r,int x)
{
	push_down(l,r,p);
	if(l==r)
		return minn[p];
	int mid = (l+r)>>1;
	if(x<=mid)return getans(p<<1,l,mid,x);
	else return getans(p<<1|1,mid+1,r,x);
}
int get_cut(int x,int y,int c,int opt)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		if(opt)update(1,1,n,w[top[x]],w[x],c);
		x = fa[top[x]];
	}
	if(x==y)return x;
	if(dep[x]<dep[y])swap(x,y);
	if(opt)update(1,1,n,w[y]+1,w[x],c);
	return y;
}
int main()
{
	int a,d,l,t;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&a,&d,&l,&t);
		if(t)add(a,d,l);
		else add_s(a,d,l);
	}
	dfs1(1,0);
	dfs2(1,1);
	memset(minn,0x3f,sizeof(minn));
	memset(lazy,0x3f,sizeof(lazy));
	for(int i = 1;i<= snum;i++)
	{
		int lca = get_cut(b[i].u,b[i].v,0,0);
		int tmp = dis[b[i].u]+b[i].val+dis[b[i].v];
		get_cut(b[i].v,lca,tmp,1);
		get_cut(b[i].u,lca,tmp,1);
	}
	for(int i = 2;i<=n;i++)
	{
		int tmp = getans(1,1,n,w[i]);
		if(tmp==INF)printf("-1 ");
		else printf("%d ",tmp-dis[i]);
	}
	return 0;
}
