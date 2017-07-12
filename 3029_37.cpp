
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 201;
double f[2][N][N<<1];
int w[N];
double p[N];
int main()
{
	int n,l,K;
	scanf("%d%d%d",&n,&l,&K);
	if(K>n)K = n;
	f[0][0][K+200] = 1;
	for(int i = 1;i<= n;i++)
	{
		scanf("%lf",&p[i]);
		p[i]/=100.0;
	}
	for(int i = 1;i<= n;i++)
		scanf("%d",&w[i]);
	for(int i = 0;i< n;i++)
	{
		int next = (i+1)&1,now = i&1;
		for(int j = 0;j<=i;j++)
			for(int k = -i;k<= n;k++)
			{
				f[next][j][k+200] += (1.0-p[i+1])*f[now][j][k+200];
				int tmp = k+w[i+1];
				if(tmp>n)tmp = n;
				f[next][j+1][tmp+200] += p[i+1]*f[now][j][k+200];
			}
		memset(f[now],0,sizeof(f[now]));
	}
	double ans = 0;
	for (int i=0;i<=n;i++) 
	  for (int j=l;j<=n;j++) 
	    ans+=f[n&1][j][i+200];
	printf("%.6f\n",ans);
	return 0;
}
