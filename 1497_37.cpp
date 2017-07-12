
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 6e4+5;
const int M = 4e5+5;
const int INF = 0x3f3f3f3f;
struct F
{int next,to,flow;}e[M];
int head[N],tot=1;
void add(int x,int y,int f)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;e[tot].flow=f;
	e[++tot].to=x;e[tot].next=head[y];head[y]=tot;e[tot].flow=0;
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
			if(d[e[i].to]==-1&&e[i^1].flow)
			{
				d[e[i].to]=d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[s]!=-1;
}
int get_maxflow(int s,int t,int mf)
{
	if(s==t)return mf;
	int last = mf;
	for(int i = head[s];i;i=e[i].next)
		if(d[e[i].to]==d[s]-1&&e[i].flow)
		{
			int tof = get_maxflow(e[i].to,t,min(last,e[i].flow));
			if(tof)
			{
				e[i].flow-=tof;
				e[i^1].flow+=tof;
				if(!(last-=tof))return mf;
			}
		}
	d[s]=-1;
	return mf-last;
}
int dinic(int s,int t)
{
	int ans = 0,nowflow;
	while(bfs(s,t))
		while((nowflow=get_maxflow(s,t,INF)))
			ans+=nowflow;
	return ans;
}
int p[N];
int main()
{
	int n,m,sum=0;
	scanf("%d%d",&n,&m);
	int s = 0,end = n+m+1;
	for(int i = 1;i<= n;i++)scanf("%d",&p[i]);
	int x,y,z;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		sum+=z;
		add(s,i+n,z);
		add(i+n,x,INF),add(i+n,y,INF);
	}
	for(int i = 1;i<= n;i++)
		add(i,end,p[i]);
	printf("%d\n",sum-dinic(s,end));
	return 0;
}
