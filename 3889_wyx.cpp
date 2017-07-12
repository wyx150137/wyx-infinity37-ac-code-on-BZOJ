
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const int N = 1000+5;
const int M = 5000005;
const LL inf = 1e14;
using namespace std;

int head[N];

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
	head[x] = cnt;
}

queue <int> q;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

LL dis[3][N];
bool in[N];
int s,t;

void spfa()
{
	for(int i=1;i<=2;++i)for(int j=0;j<N;++j)dis[i][j] = inf;
	q.push(s);in[s] = 1;dis[1][s] = dis[2][s] = 0;
	while(!q.empty())
	{
		int tt = q.front();
		q.pop();in[tt] = false;
		for(int i=head[tt];i;i=edge[i].next)
		{
			if(dis[1][edge[i].to] > dis[1][tt] + edge[i].val1 ||( dis[1][edge[i].to] == dis[1][tt] + edge[i].val1 &&dis[2][edge[i].to] > dis[2][tt] + edge[i].val2))
			{
				dis[1][edge[i].to] = dis[1][tt] + edge[i].val1;
				dis[2][edge[i].to] = dis[2][tt] + edge[i].val2;
				if(!in[edge[i].to])
				{
					in[edge[i].to] = 1;
					q.push(edge[i].to);
				} 
			}

		}
	}
}

int n;

int a[N];

int main()
{
	s = read(),t = read(), n = read();
	for(int i=1;i<=n;++i)
	{
		int c = read(), m = read();
		for(int j=1;j<=m;++j) a[j] = read();
		for(int j=1;j<m;++j) 
			for(int k=j+1;k<=m;++k)
				add(a[j],a[k],c,k-j);
 	}
 	spfa();
 	if(dis[1][t] >= inf )
 		puts("-1 -1");
 	else cout << dis[1][t] << " " << dis[2][t] << endl;
}
