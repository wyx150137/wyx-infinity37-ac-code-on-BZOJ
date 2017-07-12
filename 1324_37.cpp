
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e4+5;
const int M = 2e5+5;
const int INF = 0x3f3f3f3f;
struct F
{int next,to,flow;}e[M];
int head[N],tot=1;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];e[tot].flow = f;head[x]=tot;
	e[++tot].to = x;e[tot].next = head[y];e[tot].flow = 0;head[y]=tot;
}
int d[N],n,m;
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
int get_MF(int s,int t,int mf)
{
	if(s==t)return mf;
	int last = mf;
	for(int i = head[s];i;i=e[i].next)
		if(e[i].flow&&d[e[i].to]==d[s]-1)
		{
			int tof = get_MF(e[i].to,t,min(last,e[i].flow));
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
	int ans = 0,NF;
	while(bfs(s,t))
		while((NF=get_MF(s,t,INF)))
			ans+=NF;
	return ans;
}
int getid(int x,int y)
{
	return (x-1)*m+y;
}
int main()
{
	int x,sum=0;
	scanf("%d%d",&n,&m);
	int st = 0,end = n*m+1;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
		{
			scanf("%d",&x);
			sum+=x;
			if((i+j)&1)add(getid(i,j),end,x);
			else
			{
				add(st,getid(i,j),x);
				if(i!=1)add(getid(i,j),getid(i-1,j),INF);
				if(j!=1)add(getid(i,j),getid(i,j-1),INF);
				if(i!=n)add(getid(i,j),getid(i+1,j),INF);
				if(j!=m)add(getid(i,j),getid(i,j+1),INF);
			}
		}
	printf("%d\n",sum-dinic(st,end));
	return 0;
}
