
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 4e4+5;
const int M = 2e6+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,f;}e[M];
int head[N],tot=1;
queue<int>Q;
int d[N];
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].f = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].f = 0;
}
bool bfs(int s,int t)
{
	memset(d,-1,sizeof(d));
	d[t] = 0;
	Q.push(t);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(e[i^1].f&&d[e[i].to]==-1)
			{
				d[e[i].to] = d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[s]!=-1;
}
int get_mxf(int s,int t,int mx)
{
	if(s==t)return mx;
	int last = mx;
	for(int i = head[s];i;i=e[i].next)
		if(e[i].f&&d[e[i].to]==d[s]-1)
		{
			int tof = get_mxf(e[i].to,t,min(e[i].f,last));
			if(tof)
			{
				e[i].f-=tof;
				e[i^1].f+=tof;
				if(!(last-=tof))return mx;
			}
		}
	d[s] = -1;
	return mx-last;
}
int dinic(int s,int t)
{
	int ans = 0;
	while(bfs(s,t))
		ans+=get_mxf(s,t,INF);
	return ans;
}
int in[N],out[N];
int main()
{
	int node = 0;
	int S = 0,T;
	int n,m,F,sum=0;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)in[i]=++node;
	for(int i = 1;i<= n;i++)out[i]=++node;
	T = ++node;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&F);sum+=F;
		add(S,in[i],F),add(out[i],T,F);
	}
	int u,v;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&u,&v,&F);
		add(in[u],out[v],F);
	}
	printf("%d\n",sum-dinic(S,T));
	return 0;
}
