
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const double eps = 1e-5;
const int N = 105;
const int S = 8e4+5;
int sl[N][N],sr[N][N];
struct E
{int next,to;double dis,a,b;}e[S];
int head[S],tot;
void add(int x,int y,double a,double b)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[tot].a = a,e[tot].b = b;
}
bool inq[S];
double dis[S];
bool dfs(int x)
{
	inq[x] = true;
	for(int i = head[x];i;i=e[i].next)
		if(dis[e[i].to]>dis[x]+e[i].dis)
		{
			dis[e[i].to]=dis[x]+e[i].dis;
			if(inq[e[i].to])return true;
			if(dfs(e[i].to))return true;
		}
	inq[x] = false;
	return false;
}
int cnt,id[N][N];
bool check(double mid)
{
	memset(dis,0,sizeof(dis));
	memset(inq,0,sizeof(inq));
	for(int i = 1;i<= tot;i++)
		e[i].dis = -(e[i].a-mid*e[i].b);
	for(int i = 1;i<= cnt;i++)
		if(dfs(i))return true;
	return false;
}
int main()
{
	int n,m,x;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
		{
			scanf("%d",&x);
			sl[i][j] = sl[i][j-1]+x;
			sr[i][j] = sr[i-1][j]+x;
		}
	for(int i = 0;i<= n;i++)
		for(int j = 0;j<= m;j++)
			id[i][j] = ++cnt;
	for(int i = 0;i<= n;i++)
		for(int j = 1;j<= m;j++)
		{
			scanf("%d",&x);
			add(id[i][j-1],id[i][j],sr[i][j],x);
			add(id[i][j],id[i][j-1],-sr[i][j],x);
		}
	for(int i = 1;i<= n;i++)
		for(int j = 0;j<= m;j++)
		{
			scanf("%d",&x);
			add(id[i-1][j],id[i][j],-sl[i][j],x);
			add(id[i][j],id[i-1][j],sl[i][j],x);
		}
	double l = 0,r = 1e9;
	while(fabs(l-r)>eps)
	{
		double mid = (l+r)/2;
		if(check(mid))l=mid;
		else r = mid;
	}
	printf("%.3lf\n",l/2);
	return 0;
}
