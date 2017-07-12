
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int S = 1<<5;
const int N = 1e4+5;
int f[N][S],g[N][S],n,C;
bool ok[N*5][S];
struct P
{
	int pos;
	int f,l;
	int fear,love;
}c[N*5];
int mod(int x)
{
	return (x%n+n)%n;
}
int main()
{
	int x;
	scanf("%d%d",&n,&C);
	for(int i = 1;i<= C;i++)
	{
		scanf("%d%d%d",&c[i].pos,&c[i].f,&c[i].l);
		for(int j = 1;j<=c[i].f;j++)
		{
			scanf("%d",&x);
			c[i].fear|=(1<<mod(x-c[i].pos));
		}
		for(int j = 1;j<=c[i].l;j++)
		{
			scanf("%d",&x);
			c[i].love|=(1<<mod(x-c[i].pos));
		}
		for(int j = 0;j<S;j++)
			if((j&c[i].fear)||((31^j)&c[i].love))
				ok[i][j] = true,g[c[i].pos][j]++;
	}
	int ans = 0;
	for(int i = 0;i<1<<4;i++)
	{
		memset(f[0],200,sizeof(f[0]));
		f[0][i<<1] = 0;
		for(int j = 1;j<= n;j++)
			for(int k = 0;k<1<<5;k++)
				f[j][k] = max(f[j-1][(k&15)<<1],f[j-1][(k&15)<<1|1])+g[j][k];
		ans = max(ans,max(f[n][i<<1],f[n][i<<1|1]));
	}
	printf("%d\n",ans);
	return 0;
}
