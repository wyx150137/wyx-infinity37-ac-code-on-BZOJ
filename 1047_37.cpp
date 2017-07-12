
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int f[13][1005][1005];
int g[13][1005][1005];
int log[1005];
int a,b,n,ans = 0x3f3f3f3f;
void init()
{
	for(int j = 1;j<= 12;j++)
		for(int l = 1;l+(1<<j)-1<= a;l++)
			for(int i = 1;i+(1<<j)-1<= b;i++)
			{
				f[j][l][i] = max(max(f[j-1][l][i],f[j-1][l][i+(1<<(j-1))]),
								 max(f[j-1][l+(1<<(j-1))][i],f[j-1][l+(1<<(j-1))][i+(1<<(j-1))]));
				g[j][l][i] = min(min(g[j-1][l][i],g[j-1][l][i+(1<<(j-1))]),
								 min(g[j-1][l+(1<<(j-1))][i],g[j-1][l+(1<<(j-1))][i+(1<<(j-1))]));
			}
	log[1] = 0;
	for(int i = 2;i<= 1000;i++)
		log[i] = log[i>>1]+1;
}
void ask(int x,int y)
{
	int xl = x,xr = x+n-1;
	int yl = y,yr = y+n-1;
	int m_ans = 0,n_ans = 0x3f3f3f3f;
	m_ans = max(f[log[n]][xl][yl],f[log[n]][xl][yr-(1<<log[n])+1]);
	m_ans = max(m_ans,max(f[log[n]][xr-(1<<log[n])+1][yl],f[log[n]][xr-(1<<log[n])+1][yr-(1<<log[n])+1]));
	n_ans = min(g[log[n]][xl][yl],g[log[n]][xl][yr-(1<<log[n])+1]);
	n_ans = min(n_ans,min(g[log[n]][xr-(1<<log[n])+1][yl],g[log[n]][xr-(1<<log[n])+1][yr-(1<<log[n])+1]));
	ans = min(ans,m_ans-n_ans);
}
int main()
{
	memset(g,0x3f,sizeof(g));
	int x;
	scanf("%d%d%d",&a,&b,&n);
	for(int i = 1;i<= a;i++)
	{
		for(int j = 1;j<= b;j++)
		{
			scanf("%d",&x);
			f[0][i][j] = g[0][i][j] = x;
		}
	}
	init();
	for(int i = 1;i<= a-n+1;i++)
		for(int j = 1;j<= b-n+1;j++)
			ask(i,j);
	printf("%d",ans);
	return 0;
}
