
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int INF = 30005;
const int N = 30005;
struct E
{int next,to;}e[N<<1];
int head[N],tot,a[N],n;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int size[N],son[N],top[N],fa[N],dep[N];
void dfs1(int x)
{
	size[x] = 1;
	dep[x] = dep[fa[x]]+1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x])
		{
			fa[e[i].to]=x;
			dfs1(e[i].to);
			size[x]+=size[e[i].to];
			if(size[e[i].to]>size[son[x]])son[x] = e[i].to;
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
int sum[N<<2],mx[N<<2];
void Push_up(int p)
{
	sum[p] = sum[p<<1]+sum[p<<1|1];
	mx[p] = max(mx[p<<1],mx[p<<1|1]);
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		sum[p] = mx[p] = a[seq[l]];
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	Push_up(p);
}
void update(int p,int l,int r,int pos,int val)
{
	if(l==r)
	{
		mx[p] = val;
		sum[p] = val;
		return ;
	}
	int mid = (l+r)>>1;
	if(pos<=mid)update(p<<1,l,mid,pos,val);
	else update(p<<1|1,mid+1,r,pos,val);
	Push_up(p);
}
int Getsum(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return sum[p];
	int mid = (l+r)>>1,ans = 0;
	if(a<=mid)ans+=Getsum(p<<1,l,mid,a,b);
	if(b>mid)ans+=Getsum(p<<1|1,mid+1,r,a,b);
	return ans;
}
int Getmax(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return mx[p];
	int mid = (l+r)>>1;
	int ans = -INF;
	if(a<=mid)ans = max(ans,Getmax(p<<1,l,mid,a,b));
	if(b >mid)ans = max(ans,Getmax(p<<1|1,mid+1,r,a,b));
	return ans;
}
int getsum(int x,int y)
{
	int ans = 0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=Getsum(1,1,n,dfn[top[x]],dfn[x]);
		x = fa[top[x]];
	}
	if(dep[y]>dep[x])swap(x,y);
	ans += Getsum(1,1,n,dfn[y],dfn[x]);
	return ans;
}
int getmax(int x,int y)
{
	int ans = -INF;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans = max(ans,Getmax(1,1,n,dfn[top[x]],dfn[x]));
		x = fa[top[x]];
	}
	if(dep[y]>dep[x])swap(x,y);
	ans = max(ans,Getmax(1,1,n,dfn[y],dfn[x]));
	return ans;
}
int main()
{
	int x,y,q;
	scanf("%d",&n);
	for(int i = 1;i< n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	dfs1(1);
	dfs2(1,1);
	build(1,1,n);
	scanf("%d",&q);
	char opt[10];
	while(q--)
	{
		scanf("%s",opt);
		if(opt[0]=='C')
		{
			scanf("%d%d",&x,&y);
			update(1,1,n,dfn[x],y);
			a[x] = y;
		}
		else if(opt[1]=='M')
		{
			scanf("%d%d",&x,&y);
			printf("%d\n",getmax(x,y));
		}else
		{
			scanf("%d%d",&x,&y);
			printf("%d\n",getsum(x,y));
		}
	}
	return 0;
}
