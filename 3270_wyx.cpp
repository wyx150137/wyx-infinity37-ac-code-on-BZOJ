
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 20+2;
const int M = N * N + 4;
const double eps = 1e-13;
using namespace std;
int tot;
double p[N];
double a[M][M];
int table[N][N];
bool in[N][N];
int deg[N],n,m;

void build(int x1,int x2)
{
	a[table[x1][x2]][table[x1][x2]]--;
	for(int i=1;i<=n;++i)
		if(in[x1][i])
			for(int j=1;j<=n;++j)
				if(in[x2][j])
					if(i!=j)
					{
						if(i==x1 && j==x2) a[table[x1][x2]][table[i][j]] += p[i]*p[j];
						else if(i==x1) a[table[x1][x2]][table[i][j]] += p[i]*(1-p[j])/deg[j];
						else if(j==x2) a[table[x1][x2]][table[i][j]] += p[j]*(1-p[i])/deg[i];
						else a[table[x1][x2]][table[i][j]] += (1-p[i])*(1-p[j])/deg[i]/deg[j];
					}
}

int S,T;

int main()
{
	cin >> n >> m >> S >> T;
	for(int i=1,x,y;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		deg[x]++,deg[y]++;in[x][y] = in[y][x] = 1;
	}
	int cnt = 0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			table[i][j] = ++cnt;

	a[table[S][T]][cnt+1] = -1;
	for(int i=1;i<=n;++i) in[i][i] = 1;
	for(int i=1;i<=n;++i) scanf("%lf",&p[i]);

	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			build(i,j);

	for(int i=1;i<=cnt;++i)
	{
		int tt = i;
		for(int j=1;j<=cnt;++j)
			if(fabs(a[j][i]) > eps) tt = j;
		for(int j=1;j<=cnt+1;++j) swap(a[i][j],a[tt][j]);
		for(int j=1;j<=cnt;++j)
			if(j!=i && fabs(a[j][i]) > eps)
			{
				double tt = a[j][i] / a[i][i];
				for(int k=1;k<=cnt+1;++k)
					a[j][k] -= a[i][k]*tt;
			}
	}

	for(int i=1;i<=n;++i)
	{
		int tmp = table[i][i];
		printf("%.6lf ",a[tmp][cnt+1]/a[tmp][tmp]);
	}
}
