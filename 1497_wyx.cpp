
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 500000+5
#define M 500000
#define inf 0x7fffffff
using namespace std;
int head[N],depth[N],q[N],n,m;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];
inline void add(int x,int y,int z)
{
	static int cnt  = 1;
	edge[++cnt]=graph(head[x],y,z);
	head[x]=cnt;
	edge[++cnt]=graph(head[y],x,0);
	head[y]=cnt;
}
bool BFS(int S, int T) 
{	
	int h=0,t=1;
	memset(depth,-1,sizeof depth);
	q[h]=S;
	depth[S]=0;
	while(h<t)
	{
		int now=q[h++];
		for(int i=head[now];i;i=edge[i].next)
			if(depth[edge[i].to]<0&&edge[i].val)
			{
				depth[edge[i].to]=depth[now]+1;
				q[t++]=edge[i].to;
			}
	}
	if(depth[T]<0)return false;
	return true;
}	
int DFS(int x,int f)
{
	if(x==n+m+1)
		return f;
	int used = 0,w;
	for(int i=head[x];i;i=edge[i].next)
	{
		if(depth[edge[i].to]==depth[x]+1 && edge[i].val)
		{
			w=f-used;
			w=DFS(edge[i].to,min(w,edge[i].val));
			edge[i].val-=w;
			edge[i^1].val+=w;
			used+=w;
			if(used==f)
				return f;
		}
	}
	if(!used)
		depth[x]=-1;
	return used;
}
int main()
{
	int ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		int tmp=read();
		add(0,i,tmp);
	}
	for(int i=1;i<=m;++i)
	{
		int tmp1=read(),tmp2=read(),tmp3=read();
		add(tmp1,n+i,inf);
		add(tmp2,n+i,inf);
		add(n+i,n+m+1,tmp3);
		ans += tmp3;
	}
	while(BFS(0,n+m+1))
		ans-=DFS(0,inf);
	cout<<ans;
}
