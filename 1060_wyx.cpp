
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 500000+5
#define M 1000000+5
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
int head[N];
long long dis[N];
long long f[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
	return x*f;
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
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] =cnt;
}

void DFS(int x,long long d,int fa)
{
	dis[x] = d;
	for(int i=head[x]; i ;i=edge[i].next)
		if(edge[i].to!=fa)
			DFS(edge[i].to,d+edge[i].val,x);
}

void DFS2(int x,int fa)
{
	int MAX = 0;
	for(int i=head[x] ; i ; i =edge[i].next)
		if(edge[i].to!=fa)
		{
			DFS2(edge[i].to,x);
			MAX = max(dis[edge[i].to],MAX);
		}
	//printf("%d -> MAX = %d \n",x,MAX);
	for(int i=head[x] ; i ;i=edge[i].next)
		if(edge[i].to!=fa)
			f[x] += MAX - dis[edge[i].to],f[x] += f[edge[i].to];
	if(MAX)
		dis[x] = MAX;
}

int main()
{
	//freopen("synch.in","r",stdin);
	//freopen("synch.out","w",stdout);
	int n = read(),root = read();
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read(),z=read();
		add(x,y,z);
	}
	DFS(root,0ll,root);
	//for(int i=1;i<=n;++i)
	//{
	//	printf("dis[%d] = %d\n ",i,dis[i]);
	//}
	DFS2(root,root);
	cout<<f[root];
}
