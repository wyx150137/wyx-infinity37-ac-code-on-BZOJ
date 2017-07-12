
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e3+5;
const int M = 2e6+5;
const int INF = 0x3f3f3f3f;
struct F
{int next,to,flow;}e[M];
int head[N],tot=1,ind[N],d[N],f[N];
int ans,m,n,st,end;
bool Can[N];
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];e[tot].flow = f;head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];e[tot].flow = 0;head[y] = tot;
	ind[x]++;
}
queue<int>Q;
bool bfs(int s,int t)
{
	memset(d,-1,sizeof(d));
	d[s] = 0;Q.push(s);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(e[i].flow&&d[e[i].to]==-1&&Can[e[i].to])
			{
				d[e[i].to] = d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[t]!=-1;
}
int dinic(int s,int t,int mf)
{
	if(s==t)return mf;
	int last = mf;
	for(int i = head[s];i;i=e[i].next)
		if(d[e[i].to]==d[s]+1&&e[i].flow&&last)
		{
			int tof = dinic(e[i].to,t,min(e[i].flow,last));
			if(tof)
			{
				e[i].flow-=tof;
				e[i^1].flow+=tof;
				if(!(last-=tof))return mf;
			}else d[e[i].to]=-1;
		}
	d[s] = -1;
	return mf-last;
}
int get_maxflow(int s,int t)
{
	int ans = 0;
	while(bfs(s,t))
		ans+=dinic(s,t,INF);
	return ans;
}
void topo()
{
	for(int i = st;i<=end;i++)
		if(!ind[i])
			Q.push(i);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		if(f[x]>0)ans+=f[x];
		Can[x] = true;
		for(int i=head[x];i;i=e[i].next)
			if(i&1)
				if(!--ind[e[i].to])
					Q.push(e[i].to);
	}
}
void debug()
{
	for(int i = st;i<= end;i++)
	{
		printf("%d:",i);
		for(int j = head[i];j;j=e[j].next)
			printf("%d(%d) ",e[j].to,e[j].flow);
		printf("\n");
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	st = 0,end = n*m+1;
	for(int i = 1;i<end;i++)
	{
		scanf("%d",&f[i]);
		if(f[i]>0)add(st,i,f[i]);
		else add(i,end,-f[i]);
		int k,r,c;
		scanf("%d",&k);
		while(k--)
		{
			scanf("%d%d",&r,&c);
			add(r*m+c+1,i,INF);
		}
		if(i%m)
			add(i,i+1,INF);
	}
	topo();
	ans-=get_maxflow(st,end);
	printf("%d\n",ans);
	return 0;
}
