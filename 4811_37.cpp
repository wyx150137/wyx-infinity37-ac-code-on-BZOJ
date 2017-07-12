
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
typedef unsigned long long ull;
int Opt[N],n,m,k;ull Val[N];
struct Seg
{
	ull v0,v1;
	Seg(){}
	Seg(int opt,ull x)
	{
		if(opt==1)
		{
			v0 = 0&x;
			v1 = (~0)&x;
		}else if(opt==2)
		{
			v0 = 0|x;
			v1 = (~0)|x;
		}else
		{
			v0 = 0^x;
			v1 = (~0)^x;
		}
	}
	Seg operator +(const Seg &s)const
	{
		Seg ans;
		ans.v0 = (v0&s.v1)|((~v0)&s.v0);
		ans.v1 = (v1&s.v1)|((~v1)&s.v0);
		return ans;
	}
}trl[N<<2],trr[N<<2];
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int dep[N],fa[N],top[N],son[N],size[N];
void dfs1(int x)
{
	size[x] = 1;
	dep[x] = dep[fa[x]]+1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x])
		{
			fa[e[i].to] = x;
			dfs1(e[i].to);
			if(size[e[i].to]>size[son[x]])son[x]=e[i].to;
			size[x]+=size[e[i].to];
		}
}
int Dfn,dfn[N],seq[N];
void dfs2(int x,int tp)
{
	top[x] = tp;
	dfn[x] = ++Dfn;
	seq[Dfn] = x;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		trl[p] = trr[p] = Seg(Opt[seq[l]],Val[seq[l]]);
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	trl[p] = trl[p<<1]+trl[p<<1|1];
	trr[p] = trr[p<<1|1]+trr[p<<1];
}
void Update(int p,int l,int r,int pos,ull val)
{
	if(l==r)
	{
		trl[p] = trr[p] = Seg(Opt[seq[pos]],val);
		Val[seq[pos]] = val;
		return ;
	}
	int mid = (l+r)>>1;
	if(pos<=mid)Update(p<<1,l,mid,pos,val);
	else Update(p<<1|1,mid+1,r,pos,val);
	trl[p] = trl[p<<1]+trl[p<<1|1];
	trr[p] = trr[p<<1|1]+trr[p<<1];
}
Seg getansL(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return trl[p];
	int mid = (l+r)>>1;
	if(b<=mid)return getansL(p<<1,l,mid,a,b);
	else if(a>mid)return getansL(p<<1|1,mid+1,r,a,b);
	else return getansL(p<<1,l,mid,a,b)+getansL(p<<1|1,mid+1,r,a,b);
}
Seg getansR(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return trr[p];
	int mid = (l+r)>>1;
	if(b<=mid)return getansR(p<<1,l,mid,a,b);
	else if(a>mid)return getansR(p<<1|1,mid+1,r,a,b);
	else return getansR(p<<1|1,mid+1,r,a,b)+getansR(p<<1,l,mid,a,b);
}
Seg getans(int x,int y)
{
	Seg vx(3,0),vy(3,0);
	while(top[x]!=top[y])
	{
		if(dep[top[x]]>=dep[top[y]])
		{
			vx = vx+getansR(1,1,n,dfn[top[x]],dfn[x]);
			x = fa[top[x]];
		}else
		{
			vy = getansL(1,1,n,dfn[top[y]],dfn[y])+vy;
			y = fa[top[y]];
		}
	}
	if(dep[x]>dep[y])
		return vx+getansR(1,1,n,dfn[y],dfn[x])+vy;
	else return vx+getansL(1,1,n,dfn[x],dfn[y])+vy;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<= n;i++)
		scanf("%d%llu",&Opt[i],&Val[i]);
	int opt,x,y;
	ull z;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs1(1);
	dfs2(1,1);
	build(1,1,n);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%llu",&x,&y,&z);
			Seg ans = getans(x,y);
			ull Ans = 0,now = 0;
			for(int j = k-1;j>=0;j--)
			{
				if((ans.v0>>j)&1)
					Ans+=1ull<<j;
				else if(((ans.v1>>j)&1)&&(now+(1ull<<j))<=z)
					Ans+=1ull<<j,now+=1ull<<j;
			}
			printf("%llu\n",Ans);
		}else
		{
			scanf("%d%d%llu",&x,&y,&z);
			Opt[x] = y;
			Update(1,1,n,dfn[x],z);
		}
	}
	return 0;
}
