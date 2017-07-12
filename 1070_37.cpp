
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 605;
const int M = 1e5+5;
const int INF = 0x3f3f3f3f;
struct F
{int next,to,f,c,from;}e[M];
int head[N],tot=1,st,end;
void add(int x,int y,int f,int c)
{
	e[++tot].to=y;e[tot].next=head[x];e[tot].f=f;e[tot].c=c;head[x]=tot;
	e[++tot].to=x;e[tot].next=head[y];e[tot].f=0;e[tot].c=-c;head[y]=tot;
	e[tot-1].from=x;e[tot].from=y;
}
int dis[N],from[N];
bool v[N];
queue<int>Q;
bool spfa()
{
	for(int i = st;i<= end;i++)dis[i]=INF;
	Q.push(st);dis[st]=0;v[st]=true;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		v[x]=false;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].f&&dis[x]+e[i].c<dis[e[i].to])
			{
				dis[e[i].to]=dis[x]+e[i].c;
				from[e[i].to]=i;
				if(!v[e[i].to])
				{
					Q.push(e[i].to);
					v[e[i].to] = true;
				}
			}
	}
	return dis[end]!=INF;
}
double ans;
void mcf()
{
	int x = INF;
	for(int i = from[end];i;i=from[e[i].from])
		x = min(e[i].f,x);
	for(int i = from[end];i;i=from[e[i].from])
		{e[i].f-=x;e[i^1].f+=x;ans+=e[i].c*x;}
}
int ti[61][10];
int main()
{
	int m,n;
	scanf("%d%d",&m,&n);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			scanf("%d",&ti[i][j]);
	st=0,end=n*(m+1)+1;
	for(int i = 1;i<= n*m;i++)
		add(st,i,1,0);
	for(int i = n*m+1;i<=n*m+n;i++)
		add(i,end,1,0);
	for(int i = 1;i<= m;i++)
		for(int j = 1;j<= n;j++)
			for(int k = 1;k<= n;k++)
				add((i-1)*n+j,n*m+k,1,ti[k][i]*j);
	while(spfa())mcf();
	printf("%.2f",ans/(double)n);
	return 0;
}
