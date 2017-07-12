
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 25;
const int M = N*N;
const double eps = 1e-8;
struct E{int next,to;}e[2*M];
int id[N][N],Cnt,tot,head[N],n,m;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
double f[M][M],cnt[N],p[N],ans[M];
void work()
{
	for(int i = 1;i<= n*n;i++)
	{
		int xn = i;
		while(fabs(f[xn][i])<eps)xn++;
		if(xn!=i)swap(f[xn],f[i]);
		for(int line = i+1;line<= n*n;line++)
		{
			double tmp = f[line][i]/f[i][i];
			for(int j = i;j<=n*n+1;j++)
				f[line][j]-=f[i][j]*tmp;
		}
	}
	for(int i = n*n;i>= 1;i--)
	{
		for(int j = i+1;j<= n*n;j++)
			f[i][n*n+1]-=f[i][j]*ans[j];
		ans[i] = f[i][n*n+1]/f[i][i];
	}
}
int main()
{
	int x,y,a,b;
	scanf("%d%d%d%d",&n,&m,&a,&b);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
		cnt[x]+=1.0,cnt[y]+=1.0;
	}
	for(int i = 1;i<= n;i++)
		scanf("%lf",&p[i]);
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<= n;j++)
			id[i][j] = ++Cnt;
	for(int i = 1;i<= n;i++)
	{
		for(int j = 1;j<= n;j++)
		{
			if(i!=j)
			{
				f[id[i][j]][id[i][j]] -= p[i]*p[j];
				for(int t = head[i];t;t = e[t].next)
					f[id[i][j]][id[e[t].to][j]] -= p[j]*(1-p[i])/cnt[i];
				for(int t = head[j];t;t = e[t].next)
					f[id[i][j]][id[i][e[t].to]] -= p[i]*(1-p[j])/cnt[j];
				for(int t1 = head[i];t1;t1 = e[t1].next)
					for(int t2 = head[j];t2;t2 = e[t2].next)
						f[id[i][j]][id[e[t1].to][e[t2].to]] -= (1-p[i])*(1-p[j])/cnt[i]/cnt[j];
			}
		}
	}
	for(int i = 1;i<= n*n;i++)
		for(int j=1;j<i;j++)
			swap(f[i][j],f[j][i]);
	for(int i = 1;i<= n*n;i++)
		f[i][i]+=1;
	f[id[a][b]][n*n+1] = 1;
	work();
	for(int i = 1;i<= n;i++)
		printf("%.6f ",ans[id[i][i]]);
	return 0;
}
