
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define N 5000+5
#define M 10000+5
typedef long long LL;
int head[N];

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

int tmp[N],f[N],g[N];

void DFS(int x,int fa,int depth)
{
	tmp[depth]++;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
			DFS(edge[i].to,x,depth+1);
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
	int n = read();
	for(int i=1;i<n;++i)
	{
		int x = read(),y =read();
		add(x,y);
	}
	LL ans = 0;
	for(int i=1;i<n;++i)
	{
		memset(f,0,sizeof f);
		memset(g,0,sizeof g);
		for(int j=head[i];j;j=edge[j].next)
		{
			memset(tmp,0,sizeof tmp);
			DFS(edge[j].to,i,1);
			for(int k=1;k<=n;++k)
			{
				ans += (LL)(g[k])*tmp[k];
				g[k] +=(LL)f[k] * tmp[k];
				f[k] += tmp[k];
			}
		}
	}
	cout<<ans<<endl;
}
