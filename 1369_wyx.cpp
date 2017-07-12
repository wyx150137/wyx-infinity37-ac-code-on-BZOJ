
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
#define M 200000+5
using namespace std;
const int inf = 0x7fffff;
int head[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
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
	head[y] = cnt;
}

int f[N][22];

void DFS(int x,int fa)
{
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
			DFS(edge[i].to,x);
	for(int j = 1; j <= 10; ++ j)
		f[x][j] = j;
	for(int j = 1; j <= 10; ++ j)
	{
		for(int i=head[x];i;i=edge[i].next)
		{
			int tmp = inf;
			if(edge[i].to!=fa)
			{
				for(int k = 1; k <= 10 ; ++ k)
					if(j ^ k)
						tmp = min(f[edge[i].to][k],tmp);
				f[x][j] += tmp;
			}
			
		}
	}
				
}

int main()
{	
	int n = read();
	for(int i=1;i<n;++i)
	{
		int x = read(),y = read();
		add(x,y);
	}
	DFS(1,1);
	int ans = inf;
	for(int i=1;i<=10;++i)
		ans = min(ans,f[1][i]);
	cout<<ans;
}

