
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1<<16;
const int INF = 0x3f3f3f3f;
int d[105],c[105][20];
int f[105][N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&d[i]);
		for(int j = 1;j<= m;j++)
			scanf("%d",&c[i][j]);
	}
	memset(f,0x3f,sizeof(f));
	f[0][0] = 0;
	for(int i = 1;i<= n;i++)
	{
		for(int sta = 0;sta<1<<m;sta++)
			f[i][sta] = f[i-1][sta]+d[i];
		for(int sta = 0;sta<1<<m;sta++)
		{
			if(f[i][sta]==INF)continue;
			for(int k = 0;k<m;k++)
			{
				if(sta&(1<<k))continue;
				f[i][sta|(1<<k)] = min(f[i][sta|(1<<k)],f[i][sta]+c[i][k+1]);
			}
		}
		for(int sta = 0;sta<1<<m;sta++)
			f[i][sta] = min(f[i-1][sta],f[i][sta]);
	}
	printf("%d\n",f[n][(1<<m)-1]);
	return 0;
}
