
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e4+5;
const int M = 8e4+5;
const int INF = 0x3f3f3f3f;
struct F
{int next,to,flow;}e[M];
int head[N],tot=1;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];e[tot].flow = f;head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];e[tot].flow = 0;head[y] = tot;
}
queue<int>Q;
int d[N],st,end;
bool bfs(int s,int t)
{
	memset(d,-1,sizeof(d));
	d[s] = 0;
	Q.push(s);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(d[e[i].to]==-1&&e[i].flow)
			{
				d[e[i].to]=d[x]+1;
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
		if(d[e[i].to]==d[s]+1&&e[i].flow)
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
	int ans = 0;
	while(bfs(s,t))
		ans+=get_maxflow(s,t,INF);
	return ans;
}
int r[105],c[105],map[105][105];
int R[105],C[105];
int main()
{
	int m,n,k;
	scanf("%d%d%d",&m,&n,&k);
	int st = 0,end = n*m+1;
	for(int i = 1;i<= m;i++)r[i]=n,scanf("%d",&R[i]);
	for(int i = 1;i<= n;i++)c[i]=m,scanf("%d",&C[i]);
	int x,y;
	for(int i = 1;i<= k;i++)
	{
		scanf("%d%d",&x,&y);
		map[x][y]++;
		r[x]--;c[y]--;
	}
	int ans = 0;
	for(int i = 1;i<= m;i++)
		for(int j = 1;j<= n;j++)
			if(!map[i][j])
				ans++,add(i,j+m,1);
	for(int i = 1;i<=m;i++)if(r[i]<R[i]){printf("JIONG!\n");return 0;}
	for(int i = 1;i<=n;i++)if(c[i]<C[i]){printf("JIONG!\n");return 0;}
	for(int i = 1;i<=m;i++)add(st,i,r[i]-R[i]);
	for(int i = 1;i<=n;i++)add(i+m,end,c[i]-C[i]);
	ans-=dinic(st,end);
	//for(int i = head[0];i;i=e[i].next)
	//	if(e[i].flow)
	//		{printf("JIONG!\n");return 0;}
	printf("%d\n",ans);
	return 0;
}
