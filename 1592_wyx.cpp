
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 2000+5
using namespace std;
const long long inf = 0x7fffffff;
int a[N],b[N];
long long dp[N][N];//第i个数改为b中第j个数的花费
#define min(a,b) ((a)<(b)?(a):(b))
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;++i)scanf("%d",a+i),b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;++i)
	{
		long long tmp = inf;
		for(int j=1;j<=n;++j)
		{
			tmp = min(tmp,dp[i-1][j]);
			dp[i][j] = abs(a[i]-b[j])+tmp;
		}
	}
	long long ans = inf;
	for(int i=1;i<=n;++i)
		ans = min(ans,dp[n][i]);
	cout<<ans;
}	
