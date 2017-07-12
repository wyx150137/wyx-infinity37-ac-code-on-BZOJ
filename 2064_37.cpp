
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int M = 1<<10;
const int INF = 0x3f3f3f3f;
int cnt[M];
int f[M][M],logn[15];
int a[15],b[15],suma[M],sumb[M];
void dfs(int k,int state,int *t,int s,int *ans)
{
    if(k==t[0]+1)return ;
    ans[state<<(t[0]-k)]=s;
    dfs(k+1,state*2+1,t,s+t[k+1],ans);
    dfs(k+1,state*2,t,s,ans);
}
void init()
{
	for(int i = 0;i<M;i++)
	{
		int tmp = i;
		while(tmp)
		{
			tmp-=tmp&(-tmp);
			cnt[i]++;
		}
	}
	for(int i = 2;i<= 10;i++)
		logn[i] = logn[i>>1]+1;
	dfs(0,0,a,0,suma);
    dfs(0,0,b,0,sumb);
}
int main()
{
	//memset(f,0x3f,sizeof(f));
	scanf("%d",&a[0]);
	for(int i = 1;i<= a[0];i++)
		scanf("%d",&a[i]);
	scanf("%d",&b[0]);
	for(int i = 1;i<= b[0];i++)
		scanf("%d",&b[i]);
	init();
	for(int i = 1;i<1<<a[0];i++)
	{
		for(int j = 1;j<1<<b[0];j++)
		{
			for(int k = 1;k<= a[0];k++)
			{
				int tmp = 1<<(k-1);
				if((i&tmp)>0)f[i][j] = max(f[i][j],f[i-tmp][j]);
			}
			for(int k = 1;k<= b[0];k++)
			{
				int tmp = 1<<(k-1);
				if((j&tmp)>0)f[i][j] = max(f[i][j],f[i][j-tmp]);
			}
			if(suma[i]==sumb[j])f[i][j]++;
		}
	}
	printf("%d\n",a[0]+b[0]-2*f[(1<<a[0])-1][(1<<b[0])-1]);
	return 0;
}
