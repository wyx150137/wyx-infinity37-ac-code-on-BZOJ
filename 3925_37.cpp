
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1<<10;
typedef long long ll;
double f[50][N],g[50][N];
int sz[N],cnt[N];
ll c[50][50];
int e[11];
int main()
{
	int n,m,u,v;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&u,&v);
		u--,v--;
		e[u]|=1<<v;
		e[v]|=1<<u;
	}
	c[0][0] = 1;
	for(int i = 1;i<50;i++)
	{
		c[i][0] = 1;
		for(int j = 1;j<50;j++)
			c[i][j] = c[i-1][j-1]+c[i-1][j];
	}
	for(int s = 1;s<1<<n;s++)
	{
		sz[s] = sz[s>>1]+(s&1);
		if(sz[s]==1)
		{
			g[0][s] = 1;
			continue;
		}
		for(int i = 0;i<n;i++)
			if(s&(1<<i))
				cnt[s]+=sz[s&e[i]];
		cnt[s]/=2;
		int lb = s&(-s);
		for(int k = (s-1)&s;k;k = s&(k-1))
			if(k&lb)
				for(int i = 0;i<=cnt[k];i++)
					for(int j = 0;j<=cnt[s^k];j++)
						f[i+j][s]+=g[i][k]*c[cnt[s^k]][j];
		for(int i = 0;i<=cnt[s];i++)
			g[i][s] = c[cnt[s]][i]-f[i][s];
	}
	double ans = 0;
	int end = (1<<n)-1;
	for(int i = 0;i<= m;i++)
		ans+=(double)f[i][end]/(double)c[cnt[end]][i];
	ans/=(double)(m+1);
	printf("%.6lf\n",ans);
	return 0;
}
