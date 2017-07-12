
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int mod = 1e9+7;
const int S = 1<<15;
char let[]={'A','C','G','T'};
char s[20];
int f[2][S],trs[S][4],cnt[S],n,m,ans[20];
void init()
{
	for(int i = 0;i<1<<n;i++)
	{
		static int f[20],g[20];
		for(int j = 1;j<= n;j++)
			f[j] = f[j-1]+((i&(1<<(j-1)))?1:0);
		cnt[i] = f[n];
		for(int k = 0;k<4;k++)
		{
			for(int j = 1;j<= n;j++)
			{
				g[j] =max(g[j-1],f[j]);
				if(let[k]==s[j])
					g[j] = max(f[j-1]+1,g[j]);
			}
			trs[i][k] = 0;
			for(int j = 1;j<= n;j++)
				if(g[j]-g[j-1]==1)
					trs[i][k]|=1<<(j-1);
		}
	}
}
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%s%d",s+1,&m);
		n = strlen(s+1);
		init();
		int pre = 0,now = 1;
		memset(f,0,sizeof(f));
		f[pre][0] = 1;
		for(int i = 1;i<= m;i++)
		{
			memset(f[now],0,sizeof(f[now]));
			for(int j = 0;j<1<<n;j++)
				for(int k = 0;k<4;k++)
					(f[now][trs[j][k]]+=f[pre][j])%=mod;
			swap(now,pre);
		}
		memset(ans,0,sizeof(ans));
		for(int i = 0;i<1<<n;i++)
			(ans[cnt[i]]+=f[pre][i])%=mod;
		for(int i = 0;i<= n;i++)
			printf("%d\n",ans[i]);
	}
	return 0;
}
