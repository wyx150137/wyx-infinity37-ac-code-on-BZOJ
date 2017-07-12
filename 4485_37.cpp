
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
const int M = 2e6+5;
const int INF = 0x3f3f3f3f;
struct E
{
	int next,to,f;
}e[M];
int head[N],tot = 1,n,m;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];e[tot].f = f;head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];e[tot].f = f;head[y] = tot;
}
int d[N];
queue<int>Q;
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
			if(d[e[i].to]==-1&&e[i^1].f)
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
		if(d[e[i].to]==d[s]-1&&e[i].f)
		{
			int tof = get_mxf(e[i].to,t,min(last,e[i].f));
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
inline int getid(int x,int y)
{
	return (x-1)*m+y;
}
int main()
{
	int d,sum = 0;
	scanf("%d%d",&n,&m);
	int S = 0,T = n*m+1;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
		{
			scanf("%d",&d);
			if(d>0)add(S,getid(i,j),d),sum+=d;
			else add(getid(i,j),T,-d),sum+=-d;
		}
	for(int i = 1;i<n;i++)
		for(int j = 1;j<= m;j++)
		{
			scanf("%d",&d);
			add(getid(i,j),getid(i+1,j),d);
		}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<m;j++)
		{
			scanf("%d",&d);
			add(getid(i,j),getid(i,j+1),d);
		}
	printf("%d\n",sum-dinic(S,T));
	return 0;
}
