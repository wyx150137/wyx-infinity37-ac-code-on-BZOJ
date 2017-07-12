
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 105;
int n,m,s;
double p,ans,f[N][N],g[N][N],a[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		scanf("%lf",&a[i]);
	scanf("%d%lf",&s,&p);
	memset(f,0xc2,sizeof(f));
	for(int i = 1;i<= n;i++)
		f[i][i] = 0;
	int x,y;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		f[x][y] = a[y];
	}
	double pow = p;
	int T=70;
	while(T--)
	{
		memset(g,0xc2,sizeof(g));
		for(int k = 1;k<= n;k++)
			for(int i = 1;i<= n;i++)
				for(int j= 1;j<= n;j++)
					g[i][j]=max(g[i][j],f[i][k]+f[k][j]*pow);
		memcpy(f,g,sizeof(f));
		pow*=pow;
	}
	ans = 0;
	for(int i = 1;i<= n;i++)
		ans = max(ans,f[s][i]);
	printf("%.1lf",ans*p+a[s]);
	return 0;
}
