
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 500005;
const double eps = 1e-6;
struct E{int next,to;double p;}e[N<<2];
int head[N],tot;
void add(int x,int y,double val)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].p = val;
	head[x] = tot;
}
double g[N],f[N],q[N];
void dfs(int x,int fa)
{
	double tmp = 1;
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to!=fa)
		{
			dfs(e[i].to,x);
			tmp*=(1.0-e[i].p*f[e[i].to]);
		}	
	}
	f[x] = 1.0-tmp*(1.0-q[x]);	
}
void dfs2(int x,int fa)
{
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to==fa)continue;
		double tmp = 1-f[e[i].to]*e[i].p;
		if(fabs(tmp)<eps)g[e[i].to] = 1;
		else
		{
			double y = (g[x]-f[e[i].to]*e[i].p)/(1-f[e[i].to]*e[i].p);
			g[e[i].to] = f[e[i].to]+y*e[i].p-f[e[i].to]*y*e[i].p;
		}
		dfs2(e[i].to,x);
	}
}
int main()
{
	int n,x,y;
	double p;
	scanf("%d",&n);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%lf",&x,&y,&p);
		add(x,y,p/100.0);
		add(y,x,p/100.0);
	}
	for(int i = 1;i<= n;i++)
		{scanf("%lf",&q[i]);q[i]/=100.0;}
	dfs(1,0);
	g[1] = f[1];
	dfs2(1,0);
	double ans = 0;
	for(int i = 1;i<= n;i++)
		ans+=g[i];
	printf("%.6f",ans);
	return 0;
}
