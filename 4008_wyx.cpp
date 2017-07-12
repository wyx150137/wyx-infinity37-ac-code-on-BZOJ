
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 200+50;
using namespace std;
typedef long double ld;

ld F[N][N],ans;
ld p[N],d[N];

int main()
{
	int T; cin >> T;
	while(T--)
	{
		memset(F,0,sizeof F);
		int n,m; cin >> n >> m;
		for(int i=1;i<=n;++i)
		{
			double x,y;
			scanf("%lf%lf",&x,&y);
			p[i] = x,d[i] = y;
		}
		F[0][m] = 1 , ans = 0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
			{
				F[i][j] = F[i-1][j]*pow(1.0-p[i-1],j) + F[i-1][j+1]*(1.0-pow(1.0-p[i-1],j+1));
				ans += F[i][j] * (1.0-pow(1-p[i],j))*d[i];
			}
		printf("%.10lf\n",(double) ans);
	}
}
