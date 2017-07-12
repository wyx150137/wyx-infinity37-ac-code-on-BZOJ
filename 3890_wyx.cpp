
#include <queue>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100+5;
const int M = N * N / 2;
bitset<10001> F[N],G[N];

int head[N],in[N];

struct graph
{
	int next,to;
	int val1,val2;
	graph () {}
	graph (int _next,int _to,int _val1,int _val2)
	:next(_next),to(_to),val1(_val1),val2(_val2){}
}edge[M];

inline void add(int x,int y,int z1,int z2)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z1,z2);
	head[x] = cnt; in[y] ++;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1) + (x<<3)+ch - '0';ch = getchar();}
	return x*f;
}

int main()
{
	int n = read(), m = read();
	for(int i=1;i<=m;++i){
		int x = read(), y = read(),z1 = read(),z2 = read();
		add(x,y,z1,z2);
	}
	G[1][0] = F[1][0] = 1; queue <int> q;
	for(int i=1;i<=n;++i) if(!in[i]) q.push(i);
	while(!q.empty())
	{
		int tt = q.front();
		q.pop();
		for(int i=head[tt];i;i=edge[i].next)
		{
			--in[edge[i].to]; F[edge[i].to] |= F[tt]<<edge[i].val1,G[edge[i].to] |= G[tt] << edge[i].val2; 
			if(!in[edge[i].to]) q.push(edge[i].to);
		}
	}
	for(int i=0;i<=100000;++i)
		if(F[n][i] && G[n][i])
		{
			cout << i << endl;
			return 0;
		}
	puts("IMPOSSIBLE");
}
