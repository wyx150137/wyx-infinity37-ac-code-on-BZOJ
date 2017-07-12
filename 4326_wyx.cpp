
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 300000+5
#define M 1200000+5
using namespace std;
int head[N],top[N],fa[N],depth[N];
int sz,size[N],n,m;
int dis[N];
int op[N][3];
int cost[N];
int tmpdis[N];
int w[N];
struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];
inline void add(int x,int y,int z)
{
	static int cnt = 0;
	edge[++cnt] = graph (head[x], y,z);
	head[x]=cnt;
	edge[++cnt] = graph (head[y], x,z);
	head[y]=cnt;
}
void DFS1(int x,int val)
{	
	dis[x]=val;
	size[x]=1;w[++sz]=x;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			fa[edge[i].to]=x;
			depth[edge[i].to]=depth[x]+1;
			DFS1(edge[i].to,val+edge[i].val);
			size[x]+=size[edge[i].to];
			tmpdis[edge[i].to]=edge[i].val;
		}	
}
void DFS2(int x,int chain)
{
	top[x]=chain;
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
int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	return depth[x]<depth[y] ? x : y;
}
inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch <'0' || ch>'9'){if(ch =='-')f=-1;ch = getchar();}
	while(ch >='0'&& ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
int cha[N];

bool check(int x)
{
	int cnt = 0;
	int lim = 0;
	for(int i=1;i<=n;++i)
		cha[i]=0;
	for(int i=1;i<=m;++i)
		if(cost[i]>x)
		{
			++cha[op[i][1]],++cha[op[i][2]];
			cha[op[i][0]] -= 2;
			lim = max(lim,cost[i]-x);
			++cnt;
		}
	if(!cnt)return 1;
	for(int i=n;i>1;--i)cha[fa[w[i]]]+=cha[w[i]];
	for(int i=2;i<=n;++i)if(tmpdis[i]>=lim&&cha[i]==cnt)return 1;
		return false;
}

int main()
{
	int l = 0 ,r = 0 ;
	int ans = 0;
	cin>>n>>m;
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read(),z=read();
		add(x,y,z);
		r+=z;
	}
	DFS1(1,0);DFS2(1,1);
	for(int i=1;i<=m;++i)
	{
		op[i][1]=read(),op[i][2]=read();
		op[i][0] = lca(op[i][1],op[i][2]);
		cost[i] = dis[op[i][1]]+dis[op[i][2]] - 2*dis[op[i][0]];
	}
	while(l<=r)
	{
		int mid = (l+r)>>1;
		if(check(mid))
		{
			ans = mid ;
			r = mid -1;
		}
		else
			l = mid + 1;
	}
	cout<<ans;
}
