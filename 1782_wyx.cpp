
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define lowbit(x) ((x)&(-x))
#define N 100000+5
#define M 200000+5
using namespace std;
int n;
int head[N];
int size[N],depth[N];
int top[N],fa[N];
int w[N],sz;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
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
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] =cnt;
}
void DFS1(int x)
{
	size[x] = 1;
	for(int i=head[x] ; i ; i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			depth[edge[i].to ] =depth[x]+1;
			fa[edge[i].to] = x;
			DFS1(edge[i].to);
			size[x] += size[edge[i].to];
		}
}	
void DFS2(int x,int chain)
{
	top[x] = chain;w[x] = ++sz;
	int k = 0;
	for(int i=head[x] ; i ; i=edge[i].next)
		if(edge[i].to!=fa[x]&&size[k] < size[edge[i].to])
			k = edge[i].to;
	if(!k)return;
	DFS2(k,chain);
	for(int i=head[x] ; i ; i=edge[i].next)
		if(edge[i].to!=fa[x]&&edge[i].to!=k)
			DFS2(edge[i].to,edge[i].to);
}
int T[N];
void updata(int x,int num)
{
	while(x<=n)
	{
		T[x] += num;
		x += lowbit(x);
	}
}
int ask(int x)
{
	int ans = 0;
	while(x)
	{
		ans += T[x];
		x -= lowbit(x);
	}
	return ans;
}	
int solveask(int x,int y)
{
	int ans = 0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]] < depth[top[y]])swap(x,y);
		ans += ask(w[x])-ask(w[top[x]]-1);
		//cout<<w[x] << " " << w[top[x]]-1<<endl;
		x = fa[top[x]];
	}
	if(depth[x] > depth[y])swap(x,y);
	ans += ask(w[y])-ask(w[x]-1);
	return ans;
}
int main()
{
	n = read();
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read();
		add(x,y);
	}
	DFS1(1);
	DFS2(1,1);
	for(int i=1;i<=n;++i)
	{
		int x = read();
		printf("%d\n",solveask(x,1));
		updata(w[x],1);
	}
}
