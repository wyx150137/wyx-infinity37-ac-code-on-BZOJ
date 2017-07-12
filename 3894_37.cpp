
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 30005;
const int M = 1000005;
const int INF = 0x3f3f3f3f;
struct F
{int next,to,flow;}e[M];
int head[N],tot=1;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];e[tot].flow = f;head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];e[tot].flow = 0;head[y] = tot;
}
int d[N];
queue<int>Q;
bool bfs(int s,int t)
{
	memset(d,-1,sizeof(d));
	d[s] = 0;
	Q.push(s);
	int x;
	while(!Q.empty())
	{
		x = Q.front();Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(d[e[i].to]==-1&&e[i].flow!=0)
			{
				d[e[i].to] = d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[t]!=-1;
}
int get_maxflow(int s,int t,int mf)
{
	if(s==t)return mf;
	int last = mf;
	for(int i = head[s];i;i=e[i].next)
		if(e[i].flow!=0&&d[e[i].to]==d[s]+1)
		{
			int tof = get_maxflow(e[i].to,t,min(e[i].flow,last));
			if(tof)
			{
				e[i].flow-=tof;
				e[i^1].flow+=tof;
				if(!(last-=tof))return mf;
			}
		}
	d[s] = -1;
	return mf-last;
}
int dinic(int s,int t)
{
	int ans = 0;
	while(bfs(s,t))
		ans+=get_maxflow(s,t,INF);
	return ans;
}
int id,n,m;
inline int getid(int x,int y)
{
	return (x-1)*m+y;
}
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int main()
{
	int sum = 0,x;
	scanf("%d%d",&n,&m);
	id = n*m+1;
	int st = 0,end = id;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);
			add(0,getid(i,j),x);sum+=x;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);
			add(getid(i,j),id,x);sum+=x;
		}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
		{
			++id;
			scanf("%d",&x);
			add(0,id,x);sum+=x;
			add(id,getid(i,j),INF);
			for(int k = 0;k<4;k++)
			{
				int tx = i+dx[k],ty = j+dy[k];
				if(tx&&ty&&tx<=n&&ty<=m)add(id,getid(tx,ty),INF);
			}
		}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
		{
			++id;
			scanf("%d",&x);
			add(id,end,x);sum+=x;
			add(getid(i,j),id,INF);
			for(int k = 0;k<4;k++)
			{
				int tx = i+dx[k],ty = j+dy[k];
				if(tx&&ty&&tx<=n&&ty<=m)add(getid(tx,ty),id,INF);
			}
		}
	sum = sum-dinic(st,end);
	printf("%d\n",sum);
	return 0;
}
