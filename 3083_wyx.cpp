
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 100000+5
#define M 400000+5
const long long inf = 10000000000ll;
using namespace std;
int head[N];
inline long long read()
{
    int x=0,f=1;char ch =getchar();
    while(ch <'0' || ch >'9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0'&& ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}
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
	edge[++cnt] = graph(head[x],y);
	head[x]=cnt;
	edge[++cnt] = graph(head[y],x);
	head[y]=cnt;
}
int fa[N],size[N],w[N],top[N],depth[N],sz,last[N];
void DFS1(int x)
{
	size[x]=1;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			fa[edge[i].to]=x;
			depth[edge[i].to]=depth[x]+1;
			DFS1(edge[i].to);
			size[x]+=size[edge[i].to];
		}
}
void DFS2(int x,int chain)
{
	top[x]=chain,w[x]=last[x]=++sz;
	int k = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&size[k]<size[edge[i].to])
			k=edge[i].to;
	if(!k)return;
	DFS2(k,chain);last[x]=max(last[x],last[k]);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&edge[i].to!=k)
			DFS2(edge[i].to,edge[i].to),last[x]=max(last[x],last[edge[i].to]);
}
struct seg
{
	int l,r;
	long long mn;
	long long lazy;
}tr[M];
void build(int k,int l,int r)
{
	tr[k].l=l,tr[k].r=r,tr[k].lazy=inf;
	if(l==r)return;
	int mid = (l+r)>>1;
	build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
inline void updata(int k)
{
	tr[k].mn = min(tr[k<<1].mn,tr[k<<1|1].mn);
}
inline void down(int k)
{
	long long tmp = tr[k].lazy;tr[k].lazy=inf;
	if(tr[k].l==tr[k].r || tmp==inf)return;
	tr[k<<1].lazy=tr[k<<1|1].lazy=tr[k<<1].mn=tr[k<<1|1].mn=tmp;
}
void change(int k,int l,int r,long long x)
{
	down(k);
	if(tr[k].l==l && tr[k].r==r){tr[k].mn=tr[k].lazy=x;return;}
	int mid = (tr[k].l+tr[k].r)>>1;
	if(r<=mid)change(k<<1,l,r,x);
	else if(l>mid)change(k<<1|1,l,r,x);
	else change(k<<1,l,mid,x),change(k<<1|1,mid+1,r,x);
	updata(k);
}
long long ask(int k,int l,int r)
{
	down(k);
	if(l==tr[k].l && r==tr[k].r)return tr[k].mn;
	int mid = (tr[k].l+tr[k].r)>>1;
	if(r<=mid)return ask(k<<1,l,r);
	else if(l>mid)return ask(k<<1|1,l,r);
	else return min(ask(k<<1,l,mid),ask(k<<1|1,mid+1,r));
}
int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return depth[x]<depth[y]?x:y;
}
void solvechange(int x,int y,long long z)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])swap(x,y);
		change(1,w[top[x]],w[x],z); x=fa[top[x]];
	}
	if(depth[x]>depth[y])swap(x,y);
	change(1,w[x],w[y],z);
}
long long val[N];
int main()
{
	int n=read(),m=read();
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read();
		add(x,y);
	}
	DFS1(1);
	DFS2(1,1);
	build(1,1,n);
	for(int i=1;i<=n;++i)
		val[i]=read();
	int tt=read();
	for(int i=1;i<=n;++i)
		change(1,w[i],w[i],val[i]);
	for(int i=1;i<=m;++i)
	{
		int op = read();
		if(op==1)
			tt=read();
		else if(op==2)
		{
			int x=read(),y=read(),z=read();
			solvechange(x,y,z);
		}
		else
		{
			int x=read();
			int L = lca(x,tt);
			if(x==tt)
			{
				printf("%lld\n",tr[1].mn);
			}
			else if(L!=x)
			{
				printf("%lld\n",ask(1,w[x],last[x]));
			}
			else
			{
				int v;
				for(int i=head[x];i;i=edge[i].next)
					if(w[tt]>=w[edge[i].to]&&w[tt]<=last[edge[i].to]&&edge[i].to!=fa[x])
						v=edge[i].to;
				long long ans = inf;
				if(w[v]>=2)
					ans = min(ans,ask(1,1,w[v]-1));
				if(last[v]<n)
					ans = min(ans,ask(1,last[v]+1,n));
				printf("%lld\n",ans);
			}
		}
	}
}
