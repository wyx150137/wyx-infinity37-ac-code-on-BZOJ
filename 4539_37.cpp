
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 2e5+5;
const int M = 2e6+5;
ll N;
int idx,n,m,q,root[maxn],from[maxn];
namespace seg
{
	int sz[M],ls[M],rs[M],root[maxn],tot;
	void Insert(int &p,int pre,int l,int r,int v)
	{
		p = ++tot;
		sz[p] = sz[pre]+1;
		if(l==r)return ;
		int mid = (l+r)>>1;
		ls[p] = ls[pre],rs[p] = rs[pre];
		if(v<=mid)Insert(ls[p],ls[pre],l,mid,v);
		else Insert(rs[p],rs[pre],mid+1,r,v);
	}
	void insert(int idx,int x)
	{
		Insert(root[idx],root[idx-1],1,n,x);
	}
	int calc(int x,int y,int k)
	{
		x = root[x-1],y = root[y];
		int l= 1,r = n;
		while(l<r)
		{
			int mid = (l+r)>>1;
			if(sz[ls[y]]-sz[ls[x]]>=k)r=mid,y = ls[y],x = ls[x];
			else k-=sz[ls[y]]-sz[ls[x]],l=mid+1,y = rs[y],x = rs[x];
		}
		return l;
	}
}
int size[maxn],dfn[maxn],last[maxn];
struct Gragh
{
	struct E
	{int next,to;ll val;}e[maxn<<1];
	int head[maxn],tot;
	void add(int x,int y,ll f)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].val = f;
		e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].val = f;
	}
	int dep[maxn],fa[maxn][18],Dfn;
	ll dis[maxn];
	void dfs1(int x)
	{
		dep[x] = dep[fa[x][0]]+1;
		for(int i = 1;i<= 17;i++)
			fa[x][i] = fa[fa[x][i-1]][i-1];
		for(int i = head[x];i;i=e[i].next)if(e[i].to!=fa[x][0])
		{
			dis[e[i].to] = dis[x]+e[i].val;
			fa[e[i].to][0] = x;
			dfs1(e[i].to);
		}
	}
	void dfs2(int x)
	{
		dfn[x] = ++Dfn;
		seg::insert(Dfn,x);
		size[x] = 1;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=fa[x][0])
			{
				dfs2(e[i].to);
				size[x] += size[e[i].to];
			}
		last[x] = Dfn;
	}
	int go_up(int x,int d)
	{
		for(int i = 17;i>= 0;i--)
			if((d>>i)&1)x=fa[x][i];
		return x;
	}
	int getlca(int x,int y)
	{
		if(dep[x]<dep[y])swap(x,y);
		for(int i =17;i>= 0;i--)
			if(dep[fa[x][i]]>=dep[y])
				x = fa[x][i];
		if(x==y)return x;
		for(int i = 17;i>= 0;i--)
			if(fa[x][i]!=fa[y][i])
				x = fa[x][i],y = fa[y][i];
		return fa[x][0];
	}
	ll getdis(int x,int y)
	{
		return dis[x]+dis[y]-dis[getlca(x,y)]*2;
	}
	int find(int x,int v)
	{
		return go_up(x,dep[x]-dep[v]-1);
	}
}G[2];
ll list[maxn];
int getpos(ll x)
{
	return lower_bound(list+1,list+idx+1,x)-list;
}
int main()
{
	ll x,y;
	scanf("%d%d%d",&n,&m,&q);
	for(int i = 1;i<n;i++)
	{
		scanf("%lld%lld",&x,&y);
		G[0].add(x,y,1);
	}
	G[0].dfs1(1);
	G[0].dfs2(1);
	N = n,idx = 1;
	root[1] = 1;
	list[1] = N;
	for(int i = 1;i<= m;i++)
	{
		scanf("%lld%lld",&x,&y);
		int t = getpos(y),r=root[t],yy=seg::calc(dfn[r],last[r],y-list[t-1]);
		G[1].add(t,idx+1,G[0].dis[yy]-G[0].dis[r]+1);
		N+=size[x],root[++idx] = x,list[idx] = N,from[idx] = yy;
	}
	G[1].dfs1(1);
	for(int i = 1;i<= q;i++)
	{
		scanf("%lld%lld",&x,&y);
		int tx = getpos(x),rx = root[tx],xx = seg::calc(dfn[rx],last[rx],x-list[tx-1]);
		int ty = getpos(y),ry = root[ty],yy = seg::calc(dfn[ry],last[ry],y-list[ty-1]);
		int lca = G[1].getlca(tx,ty);
		ll ans = G[0].dis[xx]+G[0].dis[yy]-G[0].dis[rx]-G[0].dis[ry]+G[1].getdis(tx,ty);
		if(tx==ty)
		{
			printf("%lld\n",G[0].getdis(xx,yy));
		}else if(tx==lca)
		{
			int fry = from[G[1].find(ty,lca)];
			printf("%lld\n",ans-(G[0].dis[xx]+G[0].dis[fry]-G[0].getdis(xx,fry)-2*G[0].dis[rx]));
		}else if(ty==lca)
		{
			int frx = from[G[1].find(tx,lca)];
			printf("%lld\n",ans-(G[0].dis[yy]+G[0].dis[frx]-G[0].getdis(yy,frx)-2*G[0].dis[ry]));
		}else
		{
			int frx = from[G[1].find(tx,lca)];
			int fry = from[G[1].find(ty,lca)];
			printf("%lld\n",ans-(G[0].dis[frx]+G[0].dis[fry]-G[0].getdis(frx,fry)-2*G[0].dis[root[lca]]));
		}
	}
	return 0;
}
