
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 405;
const int mod = 1e9+7;
int dp[2][N][N],ans[N][N],A[N][N];
int a[N],idx[N],y[N],num[N];
int n,Q;
void solve(int l,int r,int pos)
{
	int i,j;
	for(i = l;i<= r;i++)
		for(j = l;j<= r;j++)
			dp[0][i][j]=dp[1][i][j]=0;
	int now = 1,pre = 0;
	ll k1;
	dp[0][l][r] = 1;
	for(int t = 1;t<= Q;t++)
	{
		for(i = l;i<= r;i++)
		{
			k1 = 0;
			for(j = r;j>= i;j--)
				dp[now][i][j] = k1%mod,k1 += 1ll*dp[pre][i][j]*(n-j);
		}
		for(j = l;j<= r;j++)
		{
			k1 = 0;
			for(i = l;i<= j;i++)
				dp[now][i][j]= (dp[now][i][j]+k1)%mod,k1 += 1ll*dp[pre][i][j]*(i-1);
		}
		for(j = l;j<= r;j++)
			for(i = l;i<= j;i++)
				dp[now][i][j]=(dp[now][i][j]+1ll*dp[pre][i][j]*A[i][j])%mod;
		pre^=1,now^=1;
	}
	for(i = l;i<= r;i++)
	{
		k1 = 0;
		for(j = r;j>= i;j--)
		{
			k1 += dp[pre][i][j];
			ans[j][y[pos]] = (ans[j][y[pos]]+k1)%mod;
		}
	}
}
bool cmp(int x,int y)
{
	return a[x]<a[y];
}
int main()
{
	scanf("%d%d",&n,&Q);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)idx[i]=i;
	sort(idx+1,idx+n+1,cmp);
	for(int i = 1;i<= n;i++)y[idx[i]]=i;
	for(int i = 1;i<= n;i++)num[i] = (i*(i+1))>>1;
	for(int i = 1;i<= n;i++)
		for(int j = i;j<= n;j++)A[i][j] = num[i-1]+num[j-i+1]+num[n-j];
	int l,r,Ans;
	for(int i = 1;i<= n;i++)
	{
		l = i,r = i;
		while(l&&a[l]<=a[i])l--;
		while(r<=n&&a[r]<=a[i])r++;
		solve(l+1,r-1,i);
	}
	int i,j,k;
	for(i = 1;i<= n;i++)
	{
		Ans = 0;
		for(j = 1;j<= n;j++)
		{
			if(!ans[i][j])continue;
			for(k = 1;k<j;k++)
				ans[i][j] = (ans[i][j]-ans[i][k]+mod)%mod;
			Ans = (Ans+1ll*a[idx[j]]*ans[i][j])%mod;
		}
		printf("%d",Ans);
		if(i!=n)printf(" ");
	}
	return 0;
}
