
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 400000+5
#define M 400000+5
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch <'0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0'&& ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N],n,m;

struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y)
{
	static int cnt = 0 ;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

int fa[N];

int find(int x)
{
	return fa[x]^x?fa[x]=find(fa[x]) : fa[x];
}

int q[N];
int cut[N],tot;
int ans[N];

bool used[N];

void DFS(int x)
{
	int tt = find(x);
	for(int i=head[x];i;i=edge[i].next)
		if(used[edge[i].to])
		{
			int q = find(edge[i].to);
			if(q ^ tt)
			{
				tot --;
				fa[q] = tt;
			}
		}
}

int main()
{
	n = read() , m = read();
	for(int i=0;i<n;++i)
		fa[i] = i;
	for(int i=1;i<=m;++i)
	{
		int x = read();
		int y = read();
		add(x,y);
	}
	int tmp = read();
	for(int i=1;i<=tmp;++i)
		q[i] = read(),cut[q[i]] = 1;
	for(int i=0;i<n;++i)
		if(!cut[i])
			DFS(i),tot++,used[i] = 1;
	ans[tmp+1] = tot;
	for(int i=tmp;i>=1;--i)
	{
		tot++;
		DFS(q[i]);
		used[q[i]] = 1;
		ans[i] = tot;
	}
	for(int i=1;i<=tmp+1;++i)
		printf("%d\n",ans[i]);
}
