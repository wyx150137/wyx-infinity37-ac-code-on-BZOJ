
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int dep[N],size[N],son[N],top[N],fa[N],dfn[N],seq[N],Dfn,cnt;
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
			if(size[e[i].to]>size[son[x]])son[x]=e[i].to;
		}
}
void dfs2(int x,int tp)
{
	top[x]=tp;
	dfn[x] = ++Dfn;
	seq[Dfn] = x;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=son[x]&&e[i].to!=fa[x])
			dfs2(e[i].to,e[i].to);
}
struct Ask
{
	int x,y,c;
	int dat;
}ask[N];
int root[N],sum[N*100],TOT,ls[N*100],rs[N*100],val[N];
int mx = 2e5;
void update(int &p,int pre,int l,int r,int pos)
{
	p = ++TOT;
	sum[p]=sum[pre]+1;
	if(l==r)return ;
	ls[p]=ls[pre],rs[p]=rs[pre];
	int mid = (l+r)>>1;
	if(pos<=mid)update(ls[p],ls[pre],l,mid,pos);
	else update(rs[p],rs[pre],mid+1,r,pos);
}
int getans(int p1,int p2,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return sum[p2]-sum[p1];
	int mid = (l+r)>>1,ans = 0;
	if(a<=mid)ans+=getans(ls[p1],ls[p2],l,mid,a,b);
	if(b >mid)ans+=getans(rs[p1],rs[p2],mid+1,r,a,b);
	return ans;
}
int lth;
int getans(int x,int y,int c)
{
	int ans = 0;
	lth = dep[x]+dep[y];
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=getans(root[dfn[top[x]]-1],root[dfn[x]],0,mx,c,mx);
		x = fa[top[x]];
	}
	if(dep[y]<dep[x])swap(x,y);
	ans+=getans(root[dfn[x]-1],root[dfn[y]],0,mx,c,mx);
	lth-=dep[x]+dep[fa[x]];
	return ans;
}
int main()
{
	int n,m,rot;
	int k,x,y,c;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		if(!x)rot=i;
		else add(x,i);
	}
	dfs1(rot);
	dfs2(rot,rot);
	scanf("%d",&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&k,&x);
		if(k==1)
		{
			scanf("%d%d",&y,&c);
			cnt++;
			ask[cnt].x=x,ask[cnt].y=y,ask[cnt].c=c;ask[cnt].dat=i;
		}else
			val[x] = m-i;
	}
	for(int i = 1;i<= n;i++)
		update(root[i],root[i-1],0,mx,val[seq[i]]);
	for(int i = 1;i<= cnt;i++)
	{
		int ans2 = getans(ask[i].x,ask[i].y,ask[i].c+m-ask[i].dat+1);
		int ans1 = lth;
		printf("%d %d\n",ans1,ans2);
	}
	return 0;
}
