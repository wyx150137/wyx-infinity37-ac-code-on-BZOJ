
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
typedef long long ll;
const ll INF = 123456789123456789ll;
struct E
{int next,to,val;}e[N<<1];
int head[N],tot;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];e[tot].val = f;head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];e[tot].val = f;head[y] = tot;
}
int dep[N],top[N],size[N],son[N],fa[N],n,m;
ll dis[N];
void dfs1(int x)
{
	dep[x] = dep[fa[x]]+1;
	size[x] = 1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x])
		{
			fa[e[i].to] = x;
			dis[e[i].to] = dis[x]+e[i].val;
			dfs1(e[i].to);
			if(size[e[i].to]>size[son[x]])son[x] = e[i].to;
			size[x]+=size[e[i].to];
		}
}
int dfn[N],seq[N],Dfn;
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
struct Seg
{ll a,b,mn;}tr[N<<2];
void build(int p,int l,int r)
{
	tr[p].a=0,tr[p].b=INF,tr[p].mn = INF;
	if(l==r)return;
	int mid = (l+r)>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
}
ll calc(ll a,ll b,ll x)
{
	return a*dis[seq[x]]+b;
}
void Update(int p,int l,int r,ll a,ll b)
{
	ll xl = calc(tr[p].a,tr[p].b,l);
	ll xr = calc(tr[p].a,tr[p].b,r);
	ll yl = calc(a,b,l),yr = calc(a,b,r);
	if(xl<=yl&&xr<=yr)return ;
	if(xl>=yl&&xr>=yr){tr[p].a=a,tr[p].b=b;return ;}
	int mid = (l+r)>>1;
	ll xm = calc(tr[p].a,tr[p].b,mid);
	ll ym = calc(a,b,mid);
	if(xm>=ym)
	{
		swap(a,tr[p].a),swap(b,tr[p].b);
		swap(xl,yl),swap(xr,yr),swap(xm,ym);
	}
	if(xl>=yl)Update(p<<1,l,mid,a,b);
	else Update(p<<1|1,mid+1,r,a,b);
}
void update(int p,int l,int r,int a,int b,ll A,ll B)
{
	tr[p].mn = min(tr[p].mn,min(calc(A,B,a),calc(A,B,b)));
	if(l>=a&&r<=b){Update(p,l,r,A,B);return ;}
	int mid = (l+r)>>1;
	if(b<=mid)update(p<<1,l,mid,a,b,A,B);
	else if(a >mid)update(p<<1|1,mid+1,r,a,b,A,B);
	else update(p<<1,l,mid,a,mid,A,B),update(p<<1|1,mid+1,r,mid+1,b,A,B);
}
ll ans;
void getans(int p,int l,int r,int a,int b)
{
	ans = min(ans,min(calc(tr[p].a,tr[p].b,a),calc(tr[p].a,tr[p].b,b)));
	if(l>=a&&r<=b){ans = min(ans,tr[p].mn);return ;}
	int mid = (l+r)>>1;
	if(b<=mid)getans(p<<1,l,mid,a,b);
	else if(a >mid)getans(p<<1|1,mid+1,r,a,b);
	else getans(p<<1,l,mid,a,mid),getans(p<<1|1,mid+1,r,mid+1,b);
	return ;
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
void update(int f,int x,ll a,ll b)
{
	while(top[x]!=top[f])
	{
		update(1,1,n,dfn[top[x]],dfn[x],a,b);
		x = fa[top[x]];
	}
	update(1,1,n,dfn[f],dfn[x],a,b);
}
void getans(int f,int x)
{
	while(top[x]!=top[f])
	{
		getans(1,1,n,dfn[top[x]],dfn[x]);
		x = fa[top[x]];
	}
	getans(1,1,n,dfn[f],dfn[x]);
}
int main()
{
	int x,y;
	ll z;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%lld",&x,&y,&z);
		add(x,y,z);
	}
	dfs1(1);
	dfs2(1,1);
	build(1,1,n);
	int opt;
	while(m--)
	{
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1)
		{
			ll a,b;
			scanf("%lld%lld",&a,&b);
			int lca = getlca(x,y);
			update(lca,x,-a,a*dis[x]+b);
			update(lca,y,a,a*(dis[x]-dis[lca]*2)+b);
		}else
		{
			int lca = getlca(x,y);
			ans = INF;
			getans(lca,x);
			getans(lca,y);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
