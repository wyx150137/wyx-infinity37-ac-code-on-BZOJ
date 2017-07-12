
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int fa[300005],top[300005],son[300005],size[300005],w[300005],deep[300005],id[300005];
struct E
{int next,to;}e[600005];
int head[300005],tot,n;
bool v[300005];
int me = (300000<<1)+1;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
void dfs1(int x,int dep)
{
	v[x] = true;
	size[x]++;
	deep[x] = dep;
	for(int i = head[x];i;i = e[i].next)
	{
		int t = e[i].to;
		if(!v[t])
		{
			dfs1(t,dep+1);
			size[x]+=size[t];
			if(size[t]>size[son[x]])son[x] = t;
			fa[t] = x;
		}
	}
}
int cnt;
void dfs2(int x,int tp)
{
	top[x] = tp;
	w[x] = ++cnt;
	id[cnt] = x;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
}
int num[300005],ans[300005];
int f[300005<<2];
void push_down(int p)
{
	f[p<<1]+=f[p];
	f[(p<<1)+1]+=f[p];
	f[p] = 0;
}
void update(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b){f[p]++;return ;}
	if(f[p])push_down(p);
	int mid = (l+r)>>1;
	if(a<=mid)
		update(p<<1,l,mid,a,b);
	if(b>mid)
		update((p<<1)+1,mid+1,r,a,b);
	return ;
}
void getans(int p,int l,int r)
{
	if(l==r){ans[id[l]] = f[p];return ;}
	if(f[p])push_down(p);
	int mid = (l+r)>>1;
	getans(p<<1,l,mid);
	getans((p<<1)+1,mid+1,r);
}
void get_cut(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(deep[top[x]]<deep[top[y]])swap(x,y);
		update(1,1,n,w[top[x]],w[x]);
		x = fa[top[x]];
	}
	if(deep[x]<deep[y])swap(x,y);
	update(1,1,n,w[y],w[x]);
}
int main()
{
	int x,y;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&num[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs1(1,1);
	dfs2(1,1);
	for(int i = 1;i<n;i++)
		get_cut(num[i],num[i+1]);
	getans(1,1,n);
	for(int i = 1;i<= n;i++)
	{
		if(num[1]!=i)printf("%d\n",ans[i]-1);
		else printf("%d\n",ans[i]);
	}
	return 0;
}
