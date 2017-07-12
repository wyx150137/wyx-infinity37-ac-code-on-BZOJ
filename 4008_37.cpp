
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 220+5;
const int R = 132+5;
double f[N][R],Pow[N][R];
double p[N];
int w[N];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(f,0,sizeof(f));
		memset(Pow,0,sizeof(Pow));
		int n,r;
		scanf("%d%d",&n,&r);
		for(int i = 1;i<= n;i++)
			scanf("%lf%d",&p[i],&w[i]);
		for(int i = 1;i<= n;i++)
		{
			Pow[i][0] = 1;
			for(int j = 1;j<=r;j++)
				Pow[i][j] = Pow[i][j-1]*(1.0-p[i]);
		}
		f[0][r] = 1;
		double ans = 0;
		for(int i = 0;i<n;i++)
		{
			for(int j = 0;j<=r;j++)
			{
				f[i+1][j] += f[i][j]*Pow[i+1][j];
				if(j-1>=0)
				{
					f[i+1][j-1] += f[i][j]*(1.0-Pow[i+1][j]);
					ans += f[i][j]*(1.0-Pow[i+1][j])*w[i+1];
				}
			}
		}
		printf("%.10f\n",ans);
	}
	return 0;
}
