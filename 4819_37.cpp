
#include <stdio.h>
#include <queue>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const double eps = 1e-7;
const int N = 205;
const int M = 3e4+5;
const double INF = 1e9;
struct E
{int next,to,f,from;double c;}e[M];
int head[N],tot=1;
int from[N],a[N][N],b[N][N],n;
void add(int x,int y,int f,double c)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;e[tot].f=f,e[tot].c=c;
	e[++tot].to=x;e[tot].next=head[y];head[y]=tot;e[tot].f=0,e[tot].c=-c;
	e[tot-1].from = x,e[tot].from = y;
}
double dis[N];
bool vis[N];
queue<int>Q;
bool spfa(int s,int t)
{
	for(int i = s;i<= t;i++)dis[i] = INF;
	dis[s] = 0;
	vis[s] = true;Q.push(s);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		vis[x] = false;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].f&&dis[e[i].to]>dis[x]+e[i].c)
			{
				dis[e[i].to] = dis[x]+e[i].c;
				from[e[i].to] = i;
				if(!vis[e[i].to])
				{
					Q.push(e[i].to);
					vis[e[i].to] = true;
				}
			}
	}
	return dis[t]!=INF;
}
double mcf(int s,int t)
{
	int x = INF;
	double ans = 0;
	for(int i = from[t];i;i=from[e[i].from])
		x = min(x,e[i].f);
	for(int i = from[t];i;i=from[e[i].from])
		e[i].f-=x,e[i^1].f+=x,ans+=e[i].c*x;
	return ans;
}
void rebuild(double mid)
{
	memset(head,0,sizeof(head));
	tot = 1;
	int s= 0,t = 2*n+1;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			add(i,j+n,1,mid*b[i][j]-a[i][j]);
	for(int i = 1;i<= n;i++)
		add(s,i,1,0),add(i+n,t,1,0);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
		scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
		scanf("%d",&b[i][j]);
	double l = 0,r = 10001;
	while(fabs(r-l)>eps)
	{
		double mid = (l+r)/2;
		rebuild(mid);
		double ans = 0;
		while(spfa(0,2*n+1))ans+=mcf(0,2*n+1);
		if(ans<eps)l = mid;
		else r = mid;
	}
	printf("%.6lf\n",l);
	return 0;
}
