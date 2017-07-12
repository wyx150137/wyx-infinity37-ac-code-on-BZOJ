
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 20005;
struct Seg
{
	ll p[61];
	Seg(){memset(p,0,sizeof(p));}
	void init()
	{
		memset(p,0,sizeof(p));
	}
}tr[N<<2];
struct E
{int next,to;}e[N<<1];
int head[N],tot,n,Q;
ll val[N];
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int dep[N],top[N],size[N],son[N],dfn[N],Dfn,seq[N],fa[N];
void dfs1(int x)
{
	size[x] = 1;
	dep[x] = dep[fa[x]]+1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x])
		{
			fa[e[i].to] = x;
			dfs1(e[i].to);
			size[x]+=size[e[i].to];
			if(size[e[i].to]>size[son[x]])son[x] = e[i].to;
		}
}
void dfs2(int x,int tp)
{
	top[x] = tp;
	seq[++Dfn] = x;
	dfn[x] = Dfn;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
}
void insert(Seg &a,ll x)
{
	for(int i = 60;i>=0;i--)
		if((x>>i)&1)
		{
			if(!a.p[i]){a.p[i] = x;break;}
			else x^=a.p[i];
		}
}
void merge(Seg &a,Seg &b,Seg &c)
{
	for(int i = 0;i<= 60;i++)a.p[i]=b.p[i];
	for(int i = 60;i>=0;i--)if(c.p[i])insert(a,c.p[i]);
}
ll getans(const Seg &ans)
{
	ll Ans = 0;
	for(int i = 60;i>=0;i--)if((Ans^ans.p[i])>Ans)Ans = Ans^ans.p[i];
	return Ans;
}
void Build(int p,int l,int r)
{
	if(l==r)
	{
		tr[p].init();
		insert(tr[p],val[seq[l]]);
		return ;
	}
	int mid = (l+r)>>1;
	Build(p<<1,l,mid);
	Build(p<<1|1,mid+1,r);
	merge(tr[p],tr[p<<1],tr[p<<1|1]);
}
Seg ret;
void Getans(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)
		{merge(ret,ret,tr[p]);return ;}
	int mid = (l+r)>>1;
	if(a<=mid)Getans(p<<1,l,mid,a,b);
	if(b >mid)Getans(p<<1|1,mid+1,r,a,b);
}
ll Getans(int x,int y)
{
	ret.init();
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		Getans(1,1,n,dfn[top[x]],dfn[x]);
		x = fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	Getans(1,1,n,dfn[y],dfn[x]);
	return getans(ret);
}
int main()
{
	scanf("%d%d",&n,&Q);
	for(int i = 1;i<= n;i++)
		scanf("%lld",&val[i]);
	int x,y;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs1(1);
	dfs2(1,1);
	Build(1,1,n);
	while(Q--)
	{
		scanf("%d%d",&x,&y);
		printf("%lld\n",Getans(x,y));
	}
	return 0;
}
