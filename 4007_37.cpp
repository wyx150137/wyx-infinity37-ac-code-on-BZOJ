
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = (1<<10)+5;
int dp[N][N],w[N][12],f[N][12],n,m;
void dfs(int x,int y,int sta,int cnt)
{
	for(int i = 0;i<= cnt;i++)dp[x][i] = 0;
	if(y==n-1)
	{
		for(int i = 0;i<y;i++)
			if(sta&(1<<i))dp[x][1]+=w[x-(1<<y)][i];
			else dp[x][0]+=f[x-(1<<y)][i];
		return ;
	}
	dfs(x<<1,y+1,sta,cnt>>1),dfs(x<<1|1,y+1,sta,cnt>>1);
	for(int i = 0;i<= cnt>>1;i++)
		for(int j = 0;j<= cnt>>1;j++)
			dp[x][i+j]=max(dp[x][i+j],dp[x<<1][i]+dp[x<<1|1][j]);
	dfs(x<<1,y+1,sta|(1<<y),cnt>>1),dfs(x<<1|1,y+1,sta|(1<<y),cnt>>1);
	for(int i = 0;i<= cnt>>1;i++)
		for(int j = 0;j<= cnt>>1;j++)
			dp[x][i+j]=max(dp[x][i+j],dp[x<<1][i]+dp[x<<1|1][j]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 0;i< 1<<(n-1);i++)
		for(int j = n-2;j>=0;j--)
			scanf("%d",&w[i][j]);
	for(int i = 0;i< 1<<(n-1);i++)
		for(int j = n-2;j>=0;j--)
			scanf("%d",&f[i][j]);
	dfs(1,0,0,1<<(n-1));
	int ans = 0;
	for(int i = 0;i<= m;i++)ans = max(ans,dp[1][i]);
	printf("%d\n",ans);
}
