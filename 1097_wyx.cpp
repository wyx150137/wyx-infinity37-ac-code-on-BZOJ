
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 20000+5;
const int M = N * 20;
using namespace std;

queue <int> q;
int head[N];

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
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] = cnt;
}

bool in[N];
int dis[N];
int d[25][N],n;

void spfa(int s)
{
	memset(in,false,sizeof in);
	memset(dis,0x7f,sizeof dis);
	dis[s] = 0;in[s] = 1;q.push(s);
	while(!q.empty())
	{
		int tt = q.front();
		q.pop();in[tt] = false;
		for(int i=head[tt];i;i=edge[i].next)
			if(dis[edge[i].to] > dis[tt] + edge[i].val)
			{
				dis[edge[i].to] = dis[tt] + edge[i].val;
				if(!in[edge[i].to])
				{
					in[edge[i].to] = 1;
					q.push(edge[i].to);
				}
			}
	}
	for(int i=1;i<=n;++i) d[s][i] = dis[i];
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int ban[N];
int F[1<<21][25];

inline int Min(int x,int y)
{
	if(x == -1) return y;
	else return  x < y ? x : y;
}

int main(){
	n = read();
	int m = read(), k = read();
	for(int i=1,x,y,z;i<=m;++i)
	{
		x = read(), y = read(), z = read();
		add(x,y,z);
	}
	int tt = read();
	for(int i=1;i<=tt;++i)
	{
		int x = read(), y = read();
		ban[y] |= (1<<(x-2));
	}
	for(int i=1;i<=k+1;++i)spfa(i);
	memset(F,-1,sizeof F);
	F[0][1] = 0; int Max = (1<<k) - 1;

	for(int i=0;i<=Max;++i)
		for(int j=1;j<=k+1;++j)
			if(~F[i][j])
				for(int tmp=2;tmp<=k+1;++tmp)
					if((i&ban[tmp]) == ban[tmp])
					F[i|(1<<(tmp-2))][tmp] = Min(F[i|(1<<(tmp-2))][tmp],F[i][j]+d[j][tmp]);
	int ans = 0x7fffffff;

	for(int i=1;i<=k+1;++i)
		if(~F[Max][i])
			ans = min(ans,F[Max][i]+d[i][n]);
	cout << ans << endl;
}
