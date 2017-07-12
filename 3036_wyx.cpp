
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 100000+5;
const int M = N << 1;
using namespace std;

int deg[N];
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
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,int z)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt; deg[x] ++;
}

bool vis[N];
double F[N];

void DFS(int x)
{
	if(vis[x]) return; vis[x] ++;
	for(int i=head[x];i;i=edge[i].next)
		DFS(edge[i].to),F[x] += F[edge[i].to] + edge[i].val;
	if(deg[x]) F[x] = F[x] / deg[x];
}


int main()
{
	int n = read(), m = read(),x,y,z;
	for(int i=1;i<=m;++i) {
		x = read(), y = read(), z = read();
		add(x,y,z);
	}
	DFS(1); printf("%.2lf\n",F[1]);
}
