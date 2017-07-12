
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 105;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int f[N][N],g[N][N],m,n;
void dfs(int x,int fa)
{
	f[x][0] = g[x][0] = 1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
		{
			dfs(e[i].to,x);
			for(int j = m;~j;j--)
				for(int k = 0;k<=j-1;k++)
				{
					if(j-k-2>=0)f[x][j] = max(f[x][j],f[e[i].to][k]+f[x][j-k-2]);
					g[x][j] = max(g[x][j],g[e[i].to][k]+f[x][j-k-1]);
					if(j-k-2>=0)g[x][j] = max(g[x][j],f[e[i].to][k]+g[x][j-k-2]);
				}
		}
	for(int i = 0;i<m;i++)f[x][i+1] = max(f[x][i],f[x][i+1]);
	for(int i = 0;i<m;i++)g[x][i+1] = max(g[x][i],g[x][i+1]);
}
int main()
{
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 2;i<= n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(0,0);
	printf("%d\n",g[0][m]);
	return 0;
}
