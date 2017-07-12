
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <queue>
#define N 1000000+5
#define M 10000000+5
#define inf 0x7fffff
using namespace std;
int head[N],depth[N];
struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];
queue <int >Q;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
inline void add(int x,int y,int z)
{
	static int cnt = 1;
	edge[++cnt]=graph(head[x],y,z);
	head[x]=cnt;
	edge[++cnt]=graph(head[y],x,z);
	head[y]=cnt;
}
bool BFS(int S,int T)
{
	memset(depth,-1,sizeof depth);
	depth[S]=0;
	Q.push(S);
	while(!Q.empty())
	{
		int tt=Q.front();
		Q.pop();
		for(int i=head[tt];i;i=edge[i].next)
			if(depth[edge[i].to]<0 && edge[i].val)
				depth[edge[i].to]=depth[tt]+1,Q.push(edge[i].to);
	}
	if(depth[T]<0)
		return false;
	return true;
}
int T,S;
int DFS(int x,int f)
{
	if(x==T)
		return f;
	int used=0,w;
	for(int i=head[x];i;i=edge[i].next)
		if(depth[edge[i].to]==depth[x]+1&&edge[i].val)
		{
			w=f-used;
			w=DFS(edge[i].to,min(edge[i].val,w));
			edge[i].val-=w;
			edge[i^1].val+=w;
			used+=w;
			if(used==f)
				return f;
		}
	if(!used)
		depth[x]=-1;
	return used;
}
int main()
{
	int n,m;
	n=read(),m=read();
	S=1,T=m*n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;++j)
		{
			int kk=read();
			add((i-1)*m+j,(i-1)*m+j+1,kk);
		}
	for(int i=1;i<n;++i)
		for(int j=1;j<=m;++j)
		{
			int kk=read();
			add((i-1)*m+j,i*m+j,kk);
		}
	for(int i=1;i<n;++i)
		for(int j=1;j<m;++j)
		{
			int kk=read();
			add((i-1)*m+j,(i*m)+j+1,kk);
		}
	int ans=0 ;
	while(BFS(S,T))
		ans += DFS(S,inf);
	printf("%d",ans);
}
