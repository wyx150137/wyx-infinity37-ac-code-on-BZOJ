
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
#define M N
using namespace std;

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
}

int a[N][500+5];
int len[N];
int ans[N];

void DFS(int x)
{
	a[x][0] = 1;
	for(int i=head[x];i;i=edge[i].next)
	{
		DFS(edge[i].to);
		for(int j=0;j<=len[x];++j)
			for(int k=0;k<=len[edge[i].to];++k)
				ans[j^(k+1)] += a[x][j] * a[edge[i].to][k];
		len[x] = max(len[x],len[edge[i].to]+1);
		for(int j=0;j<=len[edge[i].to];++j)
			a[x][j+1] += a[edge[i].to][j];
	}
}

int main()
{
	int n = read();
	register int i=2;
	for(int tmp;i<=n;++i)
		tmp = read(),add(tmp,i);
	DFS(1);
	i = 0;
	while(1)
		if(ans[i])
			printf("%d\n",ans[i++]);
		else
			break;
	
}
