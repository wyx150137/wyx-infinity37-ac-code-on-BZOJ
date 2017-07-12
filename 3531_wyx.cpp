
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 100003
#define M 10000005
using namespace std;
int head[N],top[N],w[N],size[N];
int depth[N],fa[N],sz,tree,root[N],n,m;
int a[N],b[N];
inline int read()
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
void DFS1(int x)
{
	size[x]=1;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			depth[edge[i].to]=depth[x]+1;
			fa[edge[i].to]=x;
			DFS1(edge[i].to);
			size[x]+=size[edge[i].to];
		}
}
void DFS2(int x,int chain)
{
	top[x]=chain;
	w[x]=++sz;
	int k = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&size[k]<size[edge[i].to])
			k=edge[i].to;
	if(!k)return;
	DFS2(k,chain);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&edge[i].to!=k)
			DFS2(edge[i].to,edge[i].to);
}
struct seg
{
	int lson,rson;
	int mx,mn;
}tr[M];
inline void updata(int k)
{
	tr[k].mn = tr[tr[k].lson].mn + tr[tr[k].rson].mn;
	tr[k].mx = max(tr[tr[k].rson].mx,tr[tr[k].lson].mx);
}
void change(int &k,int l,int r,int x,int v)
{
	if(!k)k=++tree;
	if(l==r){tr[k].mn = tr[k].mx = v;return;}
	int mid = (l+r)>>1;
	if(x<=mid)change(tr[k].lson,l,mid,x,v);
	else change(tr[k].rson,mid+1,r,x,v);
	updata(k);
}
int asksum(int k,int l,int r,int x,int y)
{
	if(!k)return 0;
	if(l==x && r==y)return tr[k].mn;
	int mid = (l+r)>>1;
	if(y<=mid)return asksum(tr[k].lson,l,mid,x,y);
	else if(x>mid)return asksum(tr[k].rson,mid+1,r,x,y);
	else return asksum(tr[k].lson,l,mid,x,mid)+asksum(tr[k].rson,mid+1,r,mid+1,y);
}
int askmax(int k,int l,int r,int x,int y)
{
	if(!k)return 0;
	if(l==x && r==y)return tr[k].mx;
	int mid = (l+r)>>1;
	if(y<=mid)return askmax(tr[k].lson,l,mid,x,y);
	else if(x>mid)return askmax(tr[k].rson,mid+1,r,x,y);
	else return max(askmax(tr[k].lson,l,mid,x,mid),askmax(tr[k].rson,mid+1,r,mid+1,y));
}
int lca(int x,int y)
{
	while(top[x]^top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	return depth[x]<depth[y]?x:y;
}
int solvemax(int k,int x,int y)
{
	int MAX = 0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])swap(x,y);
		MAX = max(MAX, askmax(k,1,n,w[top[x]],w[x]) );
		x=fa[top[x]];
	}
	if(depth[x]>depth[y])swap(x,y);
	MAX = max(MAX,askmax(k,1,n,w[x],w[y]));
	return MAX;
}
int solvesum(int k,int x,int y)
{
	int sum = 0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])swap(x,y);
		sum += asksum(k,1,n,w[top[x]],w[x]);
		x=fa[top[x]];
	}
	if(depth[x]>depth[y])swap(x,y);
	sum += asksum(k,1,n,w[x],w[y]);
	return sum;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i)a[i]=read(),b[i]=read();
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read();
		add(x,y);
	}
	depth[1]=1;
	DFS1(1);
	DFS2(1,1);
	for(int i=1;i<=n;++i)
		change(root[b[i]],1,n,w[i],a[i]);
	for(int i=1;i<=m;++i)
	{
		char str[40];scanf("%s",str);
		int x=read(),y=read();
		if(str[1]=='C')
		{
			change(root[b[x]],1,n,w[x],0);
			b[x]=y;
			change(root[b[x]],1,n,w[x],a[x]);
		}
		else if(str[1]=='S')
		{
			printf("%d\n",solvesum(root[b[x]],x,y));
		}
		else if(str[1]=='W')
		{
			change(root[b[x]],1,n,w[x],y);
			a[x]=y;
		}
		else
		{
			printf("%d\n",solvemax(root[b[x]],x,y));
		}
	}
}
