
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const int M = 4e6+5;
const int INF = 0x3f3f3f3f;
struct F
{int next,to,flow;}e[M];
int head[N],tot=1;
void add(int x,int y,int f)
{
	e[++tot].to=y;e[tot].next=head[x];e[tot].flow=f;head[x]=tot;
	e[++tot].to=x;e[tot].next=head[y];e[tot].flow=0;head[y]=tot;
}
queue<int>Q;
int d[N];
bool bfs(int s,int t)
{
	memset(d,-1,sizeof(d));
	d[t]=0;
	Q.push(t);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i=head[x];i;i=e[i].next)
			if(d[e[i].to]==-1&&e[i^1].flow)
			{
				d[e[i].to]=d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[s]!=-1;
}
int get_mf(int s,int t,int mf)
{
	if(s==t)return mf;
	int last = mf;
	for(int i = head[s];i;i=e[i].next)
		if(d[e[i].to]==d[s]-1&&e[i].flow)
		{
			int tof = get_mf(e[i].to,t,min(last,e[i].flow));
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
	int ans = 0,nf;
	while(bfs(s,t))
		while((nf=get_mf(s,t,INF)))
			ans+=nf;
	return ans;
}
int main()
{
	int n,x,sum=0;
	scanf("%d",&n);
	int st = 0,end = n*n+n+1,id = n;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
		{
			id++;
			scanf("%d",&x);
			add(i,id,INF),add(j,id,INF);
			add(id,end,x);
			sum+=x;
		}
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		add(st,i,x);
	}
	printf("%d\n",sum-dinic(st,end));

	return 0;
}
