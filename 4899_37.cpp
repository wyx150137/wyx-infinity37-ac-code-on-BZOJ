
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 705;
const int P = 705;
const int M = 1505;
struct E
{int next,to;}e[M];
int head[M],tot;
void add(int x,int y){e[++tot].to=y;e[tot].next=head[x];head[x]=tot;}
double g[M],dis[N][N],f[N][P];
int d[M],n,m,p;
void dfs(int x)
{
	g[x] = 1;
	for(int i = head[x];i;i=e[i].next)
	{
		dfs(e[i].to);
		g[x]+=g[e[i].to]/d[x];
	}
}
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		int x,y;
		scanf("%d%d%d",&n,&m,&p);
		for(int i = 1;i<= m-n;i++)
		{
			scanf("%d%d",&x,&y);
			add(x,y);d[x]++;
		}
		for(int i = 1;i<= n;i++)dfs(i);
		for(int i = 1;i<= n;i++)
			for(int j = i+1;j<= n;j++)
				dis[i][j] = 
			(dis[i][j-1]+1.0/(d[j-1]+1)+1.0*d[j-1]/(d[j-1]+1)*g[j-1])*(d[j-1]+1);
		for(int i = 1;i<= n;i++)
			for(int j = 1;j<= p;j++)
				f[i][j]=1e18;
		f[1][1] = 0;
		int lim = (n+p-1)/p+1;
		for(int i = 1;i<= n;i++)
			for(int j = 1;j< p;j++)
				for(int k = i+1;k<= i+lim&&k<= n;k++)
					f[k][j+1] = min(f[k][j+1],f[i][j]+dis[i][k]);
		printf("%.4f\n",f[n][p]);tot=0;
		for(int i = 1;i<= m;i++)d[i]=0,head[i]=0,g[i]=0;
	}
	return 0;
}
