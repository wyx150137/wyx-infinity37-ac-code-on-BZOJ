
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
int dp[105][105];
char str[105];
int calc(int x)
{
	int cnt = 0;
	while(x)
	{
		x/=10;
		cnt++;
	}
	return cnt;
}
int Dp(int l,int r)
{
	if(r==l)return 1;
	if(dp[l][r]!=INF)return dp[l][r];
	for(int k = l;k< r;k++)
		dp[l][r] = min(dp[l][r],min(r-l+1,Dp(l,k)+Dp(k+1,r)));
	for(int k = 1;l+k<=r;k++)
	{
		bool flag = true;
		if((r-l+1)%k==0)
		{
			for(int t = 1;t<(r-l+1)/k;t++)
			{
				for(int p = 0;p<k;p++)
					if(str[l+p]!=str[l+t*k+p])
						{flag = false;break;}
				if(!flag)break;
			}
		}else continue;
		if(flag)dp[l][r] = min(dp[l][r],Dp(l,l+k-1)+2+calc((r-l+1)/k));
	}
	return dp[l][r];
}
int main()
{
	scanf("%s",str+1);
	int n = strlen(str+1);
	memset(dp,0x3f,sizeof(dp));
	printf("%d\n",Dp(1,n));
	return 0;
}
