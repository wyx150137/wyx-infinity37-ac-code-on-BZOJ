
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 55;
const int M = 2005;
int kind[N],num[N],cost[N],power[N],ind[N];
int f[N][M][N*2];
int g[N][M];
struct E
{
	int val,next,to;
}e[N<<1];
int head[N],tot,n,m;
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val  = f;
	head[x] = tot;
}
void dfs(int x)
{
	if(head[x]==0)
	{
		num[x] = min(num[x],m/cost[x]);
		for(int j = 0;j<=num[x];j++)
			for(int k = 0;k<= j;k++)
				f[x][j*cost[x]][k] = power[x]*(j-k);
		return ;
	}
	num[x] = 105;
	for(int i = head[x];i;i = e[i].next)
	{
		dfs(e[i].to);
		num[x] = min(num[x],num[e[i].to]/e[i].val);
		cost[x] += cost[e[i].to]*e[i].val;
	}
	num[x] = min(num[x],m/cost[x]);
	int cnt = 0;
	memset(g,-0x3f,sizeof(g));
    g[0][0]=0;	
	for(int l = num[x];l>= 0;l--)
	{
		cnt=0;
		for(int i = head[x];i;i = e[i].next)
		{
			cnt++;
			for(int j = 0;j<= m;j++)
				for(int k = 0;k<=j;k++)
					if(l*e[i].val<=num[e[i].to])
						g[cnt][j] = max(g[cnt][j],g[cnt-1][j-k]+f[e[i].to][k][l*e[i].val]);
		}
		for(int k = 0;k<= l;k++)
			for(int j = 0;j<= m;j++)
				f[x][j][k] = max(f[x][j][k],g[cnt][j]+power[x]*(l-k));
	}	
}
int main()
{
	memset(f,-0x3f,sizeof(f));
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&power[i]);
		char ju[3];
		scanf("%s",ju);
		if(ju[0]=='B')
			scanf("%d%d",&cost[i],&num[i]);
		else
		{
			int num,x,y;
			scanf("%d",&num);
			for(int	j = 1;j<= num;j++)
			{
				scanf("%d%d",&x,&y);
				add(i,x,y);ind[x]++;
			}
		}
	}
	int ans = 0;
	for(int i = 1;i<= n;i++)
		if(!ind[i])
		{
			dfs(i);
			for(int j = 0;j<= m;j++)
				for(int k = 0;k<= num[i];k++)
					ans = max(ans,f[i][j][k]);
		}
	printf("%d\n",ans);
	return 0;
}
