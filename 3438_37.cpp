
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e3+5;
const int M = 5e6+5;
const int INF = 0x3f3f3f3f;
struct F
{int next,to,flow;}e[M];
int head[N],tot = 1;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].flow = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].flow = 0;
}
int d[N];
queue<int>Q;
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
int a[N],b[N],c1[N],c2[N];
int main()
{
	int n;
	scanf("%d",&n);
	int st = 0,end = n+1;
	int id = n+1;
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)scanf("%d",&b[i]);
	int m,k,x,ans = 0;
	scanf("%d",&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&k,&c1[i],&c2[i]);
		ans+=c1[i]+c2[i];
		add(st,id+1,c1[i]),add(id+2,end,c2[i]);
		for(int j = 1;j<=k;j++)
		{
			scanf("%d",&x);
			add(id+1,x,INF);add(x,id+2,INF);
		}
		id+=2;
	}
	for(int i = 1;i<= n;i++)add(st,i,a[i]),ans+=a[i];
	for(int i = 1;i<= n;i++)add(i,end,b[i]),ans+=b[i];
	ans-=dinic(st,end);
	printf("%d\n",ans);
	return 0;
}
