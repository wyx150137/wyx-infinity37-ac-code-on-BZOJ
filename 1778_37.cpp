
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 305;
const double eps = 1e-9;
double f[N][N],cnt[N],ans[N];
int n,m,x,y;
double p,q;
void swapn(int x,int y)
{
	for(int i = 1;i<= n+1;i++)
		swap(f[x][i],f[y][i]);
	return ;
}
void work()
{
	for(int i = 1;i<= n;i++)
	{
		int xn = i;
		while(fabs(f[xn][i])<eps)xn++;
		if(xn!=i)swapn(xn,i);
		for(int line = i+1;line<=n;line++)
		{
			double tmp = f[line][i]/f[i][i];
			for(int j = i;j<= n+1;j++)
				f[line][j]-=f[i][j]*tmp;
		}
	}
	for(int i = n;i>= 1;i--)
	{
		for(int j = n;j>i;j--)
			f[i][n+1]-=f[i][j]*ans[j];
		ans[i] = f[i][n+1]/f[i][i];
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%lf%lf",&p,&q);
	double rate = p/q;
	if(rate>1)rate = 1;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		f[x][y]+=1;f[y][x]+=1;
		cnt[x]+=1;cnt[y]+=1;
	}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			if(fabs(cnt[j])>eps)
				f[i][j]/=cnt[j];
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			f[i][j]*=rate-1;
	for(int i = 1;i<= n;i++)
		f[i][i]+=1;
	f[1][n+1] = rate;
	work();
	for(int i = 1;i<= n;i++)
		printf("%.9f\n",fabs(ans[i]));	
	return 0;
}
