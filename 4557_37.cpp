
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to;}e[N<<1];
int head[N],tot,n,d,m;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int f[N][25],g[N][25];
int w[N];bool need[N];
void dfs(int x,int fa)
{
	f[x][0] = g[x][0] = need[x]?w[x]:0;
	for(int i = 1;i<= d;i++)g[x][i]=w[x];
	g[x][d+1] = INF; 
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
		{
			dfs(e[i].to,x);
			for(int j = 0;j<= d;j++)
				g[x][j] = min(g[x][j]+f[e[i].to][j],g[e[i].to][j+1]+f[x][j+1]);
			for(int j = d;j>=0;j--)g[x][j] = min(g[x][j+1],g[x][j]);
			f[x][0]=g[x][0];
			for(int j = 1;j<=d;j++)f[x][j]+=f[e[i].to][j-1];
			for(int j = 1;j<=d;j++)f[x][j] = min(f[x][j-1],f[x][j]);
		}
}
int main()
{
	scanf("%d%d",&n,&d);
	for(int i = 1;i<= n;i++)
		scanf("%d",&w[i]);
	scanf("%d",&m);
	for(int i = 1;i<= m;i++)
	{
		int x;
		scanf("%d",&x);
		need[x] = true;
	}
	int x,y;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,0);
	printf("%d\n",f[1][0]);
	return 0;
}
