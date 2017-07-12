
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000+5;
const int M = N << 1;
const double eps = 1e-8;
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
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

int dis[N],step[N][N],deg[N];
double F[N][N];
bool in[N];

queue <int> q;

void spfa(int sta)
{
	memset(in,false,sizeof in);
	memset(dis,0x3f,sizeof dis);
	q.push(sta);in[sta] = 1;dis[sta] = 0;
	while(!q.empty())
	{
		int tt = q.front();q.pop();in[tt] = false;
		for(int i=head[tt];i;i=edge[i].next)
			if(dis[edge[i].to]>dis[tt]+1||(dis[edge[i].to]==dis[tt]+1&&tt<step[sta][edge[i].to]) )
			{
				dis[edge[i].to] = dis[tt] + 1;
				step[sta][edge[i].to] = tt;
				if(!in[edge[i].to])
				{
					in[edge[i].to] = 1;
					q.push(edge[i].to);
				}
			}
	}
}

double DFS(int x,int y)
{
	if(x == y) return F[x][y] = 0.0;
	if(F[x][y] > eps) return F[x][y];
	if(step[y][x] == y || step[y][step[y][x]] == y) return F[x][y] = 1.0;
	int tmp = step[y][step[y][x]];
	double ans = DFS(tmp,y);
	for(int i=head[y];i;i=edge[i].next)ans += DFS(tmp,edge[i].to);
	ans = ans / (double)(deg[y]+1) + 1;
	return F[x][y] = ans;
}

int main()
{
	int n = read(), E = read(), c = read() ,m = read() , x , y;
	for(int i=1;i<=E;++i)
	{
		x = read(), y = read();
		add(x,y); deg[x] ++, deg[y] ++;
	}
	for(int i=1;i<=n;++i) spfa(i);
	memset(F,0xc2,sizeof(F));
	printf("%.3lf\n",DFS(c,m));
}
