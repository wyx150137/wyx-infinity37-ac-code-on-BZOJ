
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 101;
const int INF = 1e9;
double g[N][N],f[N][N][N];
int l_k[N][N][N],l_j[N][N][N];
int main()
{
	double k1,k2;
	int n,m;
	scanf("%lf%lf%d%d",&k1,&k2,&m,&n);
	for(int i = 0;i<N;i++)
		for(int j = 0;j<N;j++)
			g[i][j] = INF;
	for(int i = 0;i<N;i++)
		for(int j = 0;j<N;j++)
			for(int k = 0;k<N;k++)
				f[i][j][k] = INF;
	g[0][0] = 0;
	for(int i = 1;i<= 100;i++)
		for(int j = 1;j<= i;j++)
			for(int k = j-1;k<i;k++)
				g[i][j] = min(g[i][j],g[k][j-1]+(double)(i-k)*(i-k)*k2);
	f[0][0][0] = 0;
	for(int k = 1;k<= 100;k++)
		for(int i = 1;i<= m;i++)
			for(int j = 1;j<= n;j++)
				for(int lk = l_k[k][i-1][j];lk<k;lk++)
					for(int lj = l_j[k][i-1][j];lj<j;lj++)
						if(f[lk][i-1][lj]+(k-lk)*(k-lk)*k1+g[k-lk][j-lj]<f[k][i][j])
						{
							f[k][i][j] = f[lk][i-1][lj]+(double)(k-lk)*(k-lk)*k1+g[k-lk][j-lj];
							l_k[k][i][j] = lk;
							l_j[k][i][j] = lj;
						}
	printf("%.1f\n",f[100][m][n]);
	return 0;
}
