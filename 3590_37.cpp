
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int S = 1<<12;
const int N = 13;
const int M = 85;
const int INF = 5e8;
struct E
{int next,to,val;}e[M];
int head[N],tot;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];e[tot].val = f;head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];e[tot].val = f;head[y] = tot;
}
int g[S][N][N],h[S][N][2],n,m;
int f[S];
void graph_init()
{
	memset(head,0,sizeof(head));
	tot = 0;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
}
void edge_init()
{
	for(int i = 0;i<1<<n;i++)for(int j = 0;j<= n;j++)for(int k = 0;k<= n;k++)
		g[i][j][k] = INF;
	for(int i = 0;i<1<<n;i++)for(int j = 0;j<= n;j++)for(int k = 0;k<= 1;k++)
		h[i][j][k] = INF;
	for(int i = 0;i<n;i++)
		g[i<<1][i+1][i+1] = 0;
	for(int i = 1;i<=n;i++)
		for(int j = head[i];j;j = e[j].next)
		{
			int l = i,r = e[j].to;
			int s = (1<<(l-1))|(1<<(r-1));
			g[s][l][r] = min(g[s][l][r],e[j].val);
		}
	for(int s = 0;s<1<<n;s++)
	{
		for(int l = 1;l<= n;l++)
			for(int r = 1;r<= n;r++)
				if((s|(1<<(l-1))|(1<<(r-1)))==s)
					for(int p = head[r];p;p=e[p].next)
					{
						int nr = e[p].to;
						if((s|(1<<(nr-1)))!=s)
							g[s|(1<<(nr-1))][l][nr] = 
							min(g[s|(1<<(nr-1))][l][nr],g[s][l][r]+e[p].val);
					}
	}
	for(int s = 0;s<1<<n;s++)
		for(int i = 1;i<= n;i++)
			if((s|(1<<(i-1)))==s)
				for(int j = head[i];j;j = e[j].next)
				{
					int to = e[j].to;
					if((s|(1<<(to-1)))!=s)
					{
						if(e[j].val<=h[s][to][0])
						{
							h[s][to][1] = h[s][to][0];
							h[s][to][0] = e[j].val;
						}else if(e[j].val<h[s][to][1])
							h[s][to][1] = e[j].val;
					}
				}
}
int calc_sta(int x)
{
	int sta = 1;
	for(x = x&(x-1);x;x = x&(x-1))
		sta++;
	return sta;
}
void dp()
{
	for(int i = 1;i<1<<n;i++)
		f[i] = INF;
	for(int i = 0;i<n;i++)
		f[1<<i] = 0;
	for(int i = 1;i<1<<n;i++)
		if(calc_sta(i)>=2)
			for(int s = i&(i-1);s;s = (s-1)&i)
			{
				int t = i-s;
				for(int l = 1;l<= n;l++)
					for(int r = 1;r<= n;r++)
						if((s|(1<<(l-1)))==s&&(s|(1<<(r-1)))==s)
						{
							if(l==r)
								f[i] = min(f[i],f[t]+g[s][l][r]+h[t][l][0]+h[t][l][1]);
							else 
								f[i] = min(f[i],f[t]+g[s][l][r]+h[t][l][0]+h[t][r][0]);
						}

			}
	if(f[(1<<n)-1]<INF)printf("%d\n",f[(1<<n)-1]);
	else printf("impossible\n");
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		graph_init();
		edge_init();
		dp();
	}
	return 0;
}
