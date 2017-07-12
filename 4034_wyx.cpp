
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100005
#define M 400000+5
using namespace std;
int head[N],top[N],w[N],size[N],fa[N],n,m;
long long v[N];
int mx[N];
int sz;
struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];
inline void add(int x,int y)
{
	static int cnt = 0;
	edge[++cnt]=graph(head[x],y);
	head[x]=cnt;
	edge[++cnt]=graph(head[y],x);
	head[y]=cnt;
}
void DFS1(int x)
{
	size[x]=1;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			fa[edge[i].to]=x;
			DFS1(edge[i].to);
			size[x]+=size[edge[i].to];
		}
}
void DFS2(int x,int chain)
{
	top[x]=chain;
	int k=0;
	mx[x]=w[x]=++sz;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&size[edge[i].to]>size[k])
			k=edge[i].to;
	if(!k)return;
	DFS2(k,chain);mx[x]=max(mx[x],mx[k]);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&edge[i].to!=k)
			DFS2(edge[i].to,edge[i].to),mx[x]=max(mx[x],mx[edge[i].to]);
}
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
struct seg
{
	int l,r;
	long long mn;
	long long lazy;
}tr[M];
void build(int k,int l,int r)
{
	tr[k].l=l,tr[k].r=r;
	if(l==r)return;
	int mid=(tr[k].l+tr[k].r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
inline void down(int k)
{
	if(tr[k].l==tr[k].r)return;
	long long tmp = tr[k].lazy;
	tr[k].lazy=0;
	tr[k<<1].lazy+=tmp;
	tr[k<<1|1].lazy+=tmp;
	tr[k<<1].mn+=(tr[k<<1].r-tr[k<<1].l+1)*tmp;
	tr[k<<1|1].mn+=(tr[k<<1|1].r-tr[k<<1|1].l+1)*tmp;
}
inline void updata(int k)
{
	tr[k].mn=tr[k<<1].mn+tr[k<<1|1].mn;
}
long long ask(int k,int l,int r)
{
	if(tr[k].lazy)
		down(k);
	if(l==tr[k].l&&r==tr[k].r)return tr[k].mn;
	int mid=(tr[k].l+tr[k].r)>>1;
	if(r<=mid)
		return ask(k<<1,l,r);
	else if(l>mid)
		return ask(k<<1|1,l,r);
	else
		return ask(k<<1,l,mid)+ask(k<<1|1,mid+1,r);
}
void change(int k,int l,int r,long long c)
{
	if(tr[k].lazy)down(k);
	if(l==tr[k].l&&r==tr[k].r)
	{
		tr[k].lazy+=c;
		tr[k].mn+=(tr[k].r-tr[k].l+1)*c;
		return ;
	}
	int mid=(tr[k].l+tr[k].r)>>1;
	if(r<=mid)
		change(k<<1,l,r,c);
	else if(l>mid)
		change(k<<1|1,l,r,c);
	else
		change(k<<1,l,mid,c),change(k<<1|1,mid+1,r,c);
	updata(k);
}
long long solveask(int x)
{	
	long long ans = 0;
	while(top[x]^1)
	{
		ans+=ask(1,w[top[x]],w[x]);
		x=fa[top[x]];
	}
	ans+=ask(1,1,w[x]);
	return ans;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		v[i]=read();
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read();
		add(x,y);
	}
	DFS1(1);
	DFS2(1,1);
	build(1,1,n);
	for(int i=1;i<=n;++i)
		change(1,w[i],w[i],v[i]);
	for(int i=1;i<=m;++i)
	{
		int tmp=read();
		int x=read();
		if(tmp==1)
		{
			int a=read();
			change(1,w[x],w[x],a);
		}
		else if(tmp==2)
		{
			int a=read();
			change(1,w[x],mx[x],a);
		}
		else if(tmp==3)
		{
			long long t = solveask(x);
			printf("%lld\n",t);
		}
	}
}
