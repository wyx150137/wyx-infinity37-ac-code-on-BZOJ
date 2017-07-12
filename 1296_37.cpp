
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int map[55][55];
int stack[55],top;
int f[2501];
int g[55][55][55][2];
int w[55][55];
int main()
{
	int n,m,t;
	scanf("%d%d%d",&n,&m,&t);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			scanf("%1d",&map[i][j]);
	for(int x = 1;x<= n;x++)
		for(int y = 1;y<= m;y++)
		{
			for(int i = min(m,t);i>=1;i--)
			{
				g[x][y][i][0] = max(g[x][y][i][0],g[x][y-1][i][0]+(map[x][y]==0));
				g[x][y][i][0] = max(g[x][y][i][0],g[x][y-1][i-1][1]+(map[x][y]==0));
				g[x][y][i][1] = max(g[x][y][i][1],g[x][y-1][i][1]+(map[x][y]==1));
				g[x][y][i][1] = max(g[x][y][i][1],g[x][y-1][i-1][0]+(map[x][y]==1));
			}
		}
	for(int x = 1;x<=n;x++)
		for(int i = 1;i<= min(m,t);i++)
		{
			int num = 0;
			for(int y = 1;y<= m;y++)
			{
				num = max(num,g[x][y][i][0]);
				num = max(num,g[x][y][i][1]);
			}
			w[x][i] = num;
		}
	for(int x = 1;x<=n;x++)
		for(int j = t;j>=0;j--)
			for(int i = 1;i<= min(m,t);i++)
				if(j>=i)f[j] = max(f[j],f[j-i]+w[x][i]);
	printf("%d\n",f[t]);
	return 0;
}
