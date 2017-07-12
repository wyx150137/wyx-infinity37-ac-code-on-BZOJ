
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 105;
double map[N][N],sol[N][N];
double imp[N];
int main()
{
	for(int i = 1;i<N;i++)
		for(int j = 1;j<N;j++)
			map[i][j] = 1e9;
	int n,m,x,y,c;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x,&y,&c);
		map[x][y] = map[y][x] = c;
		sol[x][y] = sol[y][x] = 1;
	}
	for(int k = 1;k<= n;k++)
		for(int i = 1;i<= n;i++)
			for(int j = 1;j<= n;j++)
			{
				if(i==j||j==k||i==k)continue;
				if(map[i][k]+map[k][j]<map[i][j])
				{
					map[i][j] = map[i][k]+map[k][j];
					sol[i][j] = sol[i][k]*sol[k][j];
				}else if(map[i][k]+map[k][j]==map[i][j])
					sol[i][j]+=sol[i][k]*sol[k][j];
			}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			for(int v = 1;v<= n;v++)
			{
				if(i==j||j==v||i==v)continue;
				if(map[i][v]+map[v][j]!=map[i][j]||sol[i][j]<=0)continue;
				imp[v] += sol[i][v]*sol[v][j]/sol[i][j];
			}
	for(int i = 1;i<= n;i++)
		printf("%.3f\n",imp[i]);
	return 0;
}
