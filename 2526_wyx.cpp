
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000010;
const int M = N << 1;
typedef long long LL;
using namespace std;

int head[N];
int fa[N];

struct graph
{
	int next,to,;
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
	head[y] = cnt;
}

int fir[N],sec[N];
int mx[N],size[N];
LL tot[N];

void DFS1(int x)
{
	size[x] = 1;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			fa[edge[i].to] = x;
			DFS1(edge[i].to);
			tot[x] += size[edge[i].to] + tot[edge[i].to];
			size[x] += size[edge[i].to];
			sec[x] = max(sec[x],fir[edge[i].to]+1);
			if(fir[x] < sec[x]) swap(fir[x],sec[x]);
			mx[x] = max(mx[x],size[edge[i].to]);
 		}
}

int n;
LL ans[N];

void DFS2(int x,int lg,LL tmp)
{
	if(max(mx[x],n-size[x]) > n/2) ans[x] = -1;
	else if(max(mx[x],n-size[x]) == n/2 && (n%2) == 0)
	{
		if(n-size[x] == n/2) ans[x] = 2*tot[x]+tmp-lg;
		else
			for(int i=head[x];i;i=edge[i].next)
				if(size[edge[i].to] == mx[x])
					ans[x] = 2*tot[x] + tmp - fir[edge[i].to] - 1;
	}
	else
		ans[x] = 2*tot[x]+tmp-max(fir[x],lg);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			if(fir[x] == fir[edge[i].to] + 1)
				DFS2(edge[i].to,max(sec[x],lg)+1,tmp+2*(tot[x]-tot[edge[i].to]+n-2*size[edge[i].to]));
			else
				DFS2(edge[i].to,max(fir[x],lg)+1,tmp+2*(tot[x]-tot[edge[i].to]+n-2*size[edge[i].to]));
		}
} 

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	n = read();
	for(int i=1;i<n;++i)
	{
		int x = read(),y = read();
		add(x,y);
	}

	DFS1(1);
	DFS2(1,0,0);
	for(int i=1;i<=n;++i) 
		printf("%lld\n",ans[i]);
}
