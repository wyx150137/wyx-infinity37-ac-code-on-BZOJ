
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const double eps = 1e-5;
const int N = 5005;
const int M = 6005;
struct Road
{int x,y,a,b,c,d;}r[M];
struct E
{int next,to;double val;}e[M];
int head[N],tot,n,m;
void add(int x,int y,double f)
{e[++tot].to=y;e[tot].next=head[x];head[x]=tot;e[tot].val=f;}
bool vis[N];double dis[N];
bool flag;
void dfs(int x)
{
	vis[x] = true;
	for(int i = head[x];i;i=e[i].next)
	{
		if(dis[e[i].to]>dis[x]+e[i].val)
		{
			if(vis[e[i].to])flag = true;
			else
			{
				dis[e[i].to] = dis[x]+e[i].val;
				dfs(e[i].to);
			}
		}
	}
	vis[x] = false;
}
void init()
{
	memset(head,0,sizeof(head));
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis));
	flag = false;tot = 0;
}
bool check(double ans)
{
	init();
	for(int i = 1;i<= m;i++)
	{
		add(r[i].x,r[i].y,r[i].b+r[i].d+ans);
		if(r[i].c)add(r[i].y,r[i].x,r[i].a-r[i].d+ans);
	}
	for(int i = 1;i<= n && !flag;i++)
		dfs(i);
	return flag;
}
int main()
{
	scanf("%d%d",&n,&m);
	n+=2;
	for(int i = 1;i<= m;i++)
		scanf("%d%d%d%d%d%d",&r[i].x,&r[i].y,&r[i].a,&r[i].b,&r[i].c,&r[i].d);
	double l = 0,r = 1e8;
	while(fabs(r-l)>eps)
	{
		double mid = (l+r)/2;
		if(check(mid))l=mid;
		else r = mid;
	}
	printf("%.2lf\n",l);
	return 0;
}
