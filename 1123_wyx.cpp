
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const int N = 100000+5;
const int M = 500000+5;
using namespace std;

struct graph
{
	graph *next;int to;
}edge[M<<1],*head[N];

inline void add(int x,int y)
{
	static graph *cnt = edge;
	++cnt; cnt -> to = y, cnt -> next = head[x], head[x] = cnt;
	++cnt; cnt -> to = x, cnt -> next = head[y], head[y] = cnt;
}

int DFN[N],low[N],size[N],cnt,n,m;
LL ans[N];

void DFS(int x,int fa)
{
	size[x] = 1;
	DFN[x] = low[x] = ++cnt;
	LL T = 0;
	for(graph *i = head[x]; i; i = i -> next) {
		int tt = i->to;
		if(tt != fa)
		{
			if(!DFN[tt])
			{
				DFS(tt,x); size[x] += size[tt];
				low[x] = min(low[tt],low[x]);
				if(low[tt] >= DFN[x]) ans[x] += T * size[tt], T += size[tt];
			}
			else if(DFN[tt] < DFN[x]) low[x] = min(low[x],DFN[tt]);
		}
	}
	ans[x] += (T)*(n-T-1) + n-1;
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
	n = read(), m = read();
	for(int i=1;i<=m;++i) add(read(),read());
	DFS(1,0);
	for(int i=1;i<=n;++i) printf("%lld\n",ans[i]*2);
}
