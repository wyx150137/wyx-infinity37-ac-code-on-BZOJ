
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const double INF = 1e9+1;
double dp[35][35][35];
int rt[35][35][35];
int d[35],n;
double k,c;
double dfs(int l,int r,int dep)
{
	if(l==r)
		return (k*(dep+1)+c)*d[l];
	if(r<l)return 0;
	if(dp[l][r][dep]<1e9+1)return dp[l][r][dep];
	for(int i = l;i<= r;i++)
	{
		double tmp1 = dfs(l,i-1,dep+1);
		double tmp2 = dfs(i+1,r,dep+1);
		if(tmp1+tmp2+(k*(dep+1)+c)*d[i]<dp[l][r][dep])
		{
			dp[l][r][dep] = tmp1+tmp2+(k*(dep+1)+c)*d[i];
			rt[l][r][dep] = i;
		}
	}
	return dp[l][r][dep];
}
/*void print(int l,int r,int dep)
{
	if(l==r)
	{
		printf("%d")
	}
	int t = rt[l][r][dep];

}*/
int main()
{
	int sum = 0;
	for(int i = 0;i<= 31;i++)
		for(int j = 0;j<= 31;j++)
			for(int k = 0;k<= 31;k++)
				dp[i][j][k] = INF;
	scanf("%d%lf%lf",&n,&k,&c);
	for(int i = 1;i<= n;i++)
		{scanf("%d",&d[i]);sum+=d[i];}
	double ans = dfs(1,n,0);
	ans = ans/(double)sum;
	printf("%.3f",ans);
	//print(1,n,0);
	return 0;
}
