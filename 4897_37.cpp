
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 55;
const int INF = 1e9;
int dp[N][N],dp1[N][N][N];
int mx[N][N],mn[N][N];
int n,a,b,w[N];
void DP(int l,int r)
{
	register int i,j,k,o;
	for(i = l;i<= r;i++)
		for(j = l;j<= r;j++)
			for(k = l;k<= r;k++)
				dp1[i][j][k] = INF;
	dp1[l][l][l] = 0;
	for(i = l;i<= r;i++)
	{
		if(i!=l)dp1[i][i][i] = min(dp1[i][i][i],dp[l][i-1]);
		for(j = l;j<= r;j++)
			for(k = l;k<= r;k++)
			{
				if(dp1[i][j][k]==INF)continue;
				dp1[i+1][w[j]>w[i+1]?j:i+1][w[k]<w[i+1]?k:i+1] = min(dp1[i+1][w[j]>w[i+1]?j:i+1][w[k]<w[i+1]?k:i+1] ,dp1[i][j][k]);
				for ( o = i + 1 ; o <= r ; o++ )
                	dp1[o][j][k] = min ( dp1[o][j][k] , dp1[i][j][k] + dp[i+1][o] );  
			}
	}
}
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	for(int i = 1;i<= n;i++)scanf("%d",&w[i]);
	for(int i = 1;i<= n;i++)
	{
		mx[i][i] = mn[i][i] = w[i]; 
		for(int j = i+1;j<= n;j++)
			mx[i][j] = max(mx[i][j-1],w[j]),
			mn[i][j] = min(mn[i][j-1],w[j]);
	}
	for(int l = 1;l<= n;l++)
	{
		for(int i = 1;i<= n-l+1;i++)
		{
			int j = i+l-1;
			dp[i][j] = a+b*(mx[i][j]-mn[i][j])*(mx[i][j]-mn[i][j]);
			DP(i,j);
			for (int k = i ; k <= j ; k++ ) 
				for (int o = i ; o <= j ; o++ ) 
				{  
                	if ( w[k] < w[o] ) continue;  
                	dp[i][j] = min ( dp[i][j] , dp1[j][k][o] + a + b * (w[k]-w[o]) * (w[k]-w[o]) );  
            	}  
		}
	}
	printf ("%d\n",dp[1][n]);  
	return 0;
}
