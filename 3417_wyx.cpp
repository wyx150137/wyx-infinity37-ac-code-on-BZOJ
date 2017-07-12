
#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 5000+5;
const int M = 10000+5;
const int inf = 0x3f3f3f3f;
const int MAXN = 1000000+5;
using namespace std;

int head[N];
bool in[N];

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

int dis[N][2];

void spfa(int x)
{
	queue <int> q;
	memset(dis,0x3f,sizeof dis);
	dis[x][0] = 0; in[x] = 1;q.push(x);
	while(!q.empty())
	{
		int tt = q.front();q.pop();in[tt] = false;
		for(int i=head[tt];i;i=edge[i].next)
		{
			if(dis[edge[i].to][1] > dis[tt][0] + 1)
			{
				dis[edge[i].to][1] = dis[tt][0] + 1;
				if(!in[edge[i].to])
				{
					in[edge[i].to] = 1;
					q.push(edge[i].to);
				}
			}

			if(dis[edge[i].to][0] > dis[tt][1] + 1)
			{
				dis[edge[i].to][0] = dis[tt][1] + 1;
				if(!in[edge[i].to])
				{
					in[edge[i].to] = 1;
					q.push(edge[i].to) ;
				}
			}
		}
	}
}

struct Lux
{
	int s,t,d,id,ans;
	Lux () {}
	Lux (int a,int b):t(a),d(b){} 
}q[MAXN];

bool cmp1(const Lux &a,const Lux &b)
{
	return a.s < b.s;
}

bool cmp2(const Lux &a,const Lux &b)
{
	return a.id < b.id;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
	return x*f;
}

int main()
{

	int n = read(),m = read(),k = read(),x,y;

	for(int i=1;i<=m;++i)
	{	
		x = read(), y = read();
		add(x,y);
	}

	for(int i=1;i<=k;++i)
	{
		q[i].s = read(),q[i].t = read(),
		q[i].d = read(),q[i].id = i;
		if(q[i].s > q[i].t) swap(q[i].s,q[i].t);
	}

	sort(q+1,q+k+1,cmp1);
	int j = 1;

	for(int i=1;i<=n;++i)
	{
		if(q[j].s == i) spfa(i);
		else continue;
		while(q[j].s == i)
		{
			if(q[j].s == q[j].t) 
				if(!head[i] && q[j].d != 0){q[j].ans = false,j ++;continue; }
			if(dis[q[j].t][q[j].d&1] > q[j].d) q[j].ans = 0;
			else if(dis[q[j].t][q[j].d&1] == q[j].d) q[j].ans = 1;
			else q[j].ans = ((dis[q[j].t][q[j].d&1] != inf)&((dis[q[j].t][q[j].d&1]&1) == (q[j].d & 1)));
			j ++;
		}
		if(j == k+1) break;
	}	

	sort(q+1,q+k+1,cmp2);

	for(int i=1;i<=k;++i)
		printf("%s\n",q[i].ans ? "TAK" : "NIE");
}
