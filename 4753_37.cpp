
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2505;
const double eps = 1e-8;
const double INF = 1e9;
struct E
{
	int next,to;
}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
double dp[N][N],ans,p[N],s[N],size[N],g[N];
int K;
void dfs(int x)
{
	size[x] = 0;
	dp[x][0] = 0;
	for(int i = head[x];i;i=e[i].next)
	{
		dfs(e[i].to);
		for(int j = 0;j<= size[x]+size[e[i].to];j++)g[j] = -INF;
		for(int j = 0;j<= size[x];j++)
			for(int k = 0;k<= size[e[i].to];k++)
				g[j+k] = max(g[j+k],dp[x][j]+dp[e[i].to][k]);
		for(int j = 0;j<= size[x]+size[e[i].to];j++)dp[x][j] = max(dp[x][j],g[j]);
		size[x]+=size[e[i].to];
	}
	for(int j = size[x];j>= 0;j--)
		dp[x][j+1]=dp[x][j]+p[x]-s[x]*ans;
	dp[x][0] = 0;
	size[x]++;
}
int main()
{
	int n,fa;
	scanf("%d%d",&K,&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%lf%lf%d",&s[i],&p[i],&fa);
		add(fa,i);
	}
	double l = 0,r = 10001;
	while(fabs(l-r)>0.0001)
	{
		double mid = (l+r)/2;
		ans = mid;
		for(int i = 0;i<= n;i++)
			for(int j = 0;j<=n;j++)dp[i][j]=-INF;
		dfs(0);
		if(dp[0][K+1]>0)l=mid;
		else r = mid;
	}
	printf("%.3lf\n",l);
	return 0;
}
