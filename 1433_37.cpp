
#include <stdio.h>
#include <queue>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 105;
const int M = 2e4+5;
const int INF = 0x3f3f3f3f;
struct F
{int next,to,flow;}e[M];
int head[N],tot=1;
void add(int x,int y,int f)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;e[tot].flow=f;
	e[++tot].to=x;e[tot].next=head[y];head[y]=tot;e[tot].flow=0;
}
queue<int>Q;
int d[N],map[N][N];
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
	d[s] = -1;
	return mf-last;
}
int dinic(int s,int t)
{
	int ans=0,nowflow;
	while(bfs(s,t))
		while((nowflow=get_maxflow(s,t,INF)))
			ans+=nowflow;
	return ans;
}
int is_sch[N];
void debug()
{
	for(int i = 0;i<=7;i++)
	{
		printf("%d:",i);
		for(int j = head[i];j;j=e[j].next)
			printf("%d(%d) ",e[j].to,e[j].flow);
		printf("\n");
	}
}
void init()
{
	memset(head,0,sizeof(head));
	tot = 1;
}
void work()
{
	init();
	int n,x,num=0;
	scanf("%d",&n);
	int st = 0,end = 2*n+1;
	for(int i = 1;i<= n;i++)scanf("%d",&is_sch[i]);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		if(is_sch[i])
			{if(!x)add(st,i,1),num++;}
		else if(!is_sch[i])add(st,i,1),num++;
	}
	for(int i = 1;i<= n;i++)if(is_sch[i])add(i+n,end,1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&map[i][j]);
			if((map[i][j]&&is_sch[j])||(i==j&&is_sch[i]))
				add(i,j+n,1);
		}
	int ans = dinic(st,end);
	if(ans>=num)printf("^_^\n");
	else printf("T_T\n");
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		work();
	return 0;
}
