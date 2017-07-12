
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
LL f[15][10][10];
LL p10[15],ans[10][2];
void solve(LL x,int opt)
{
	if(x==0)return ;
	int num[15] = {};
	int cnt = 0;
	LL tmp = x;
	while(x)
	{
		num[++cnt] = x%10;
		x/=10;
	}
	for(int i = 1;i<=num[cnt]-1;i++)
		for(int j = 0;j<= 9;j++)
			ans[j][opt]+=f[cnt][i][j];
	ans[num[cnt]][opt]+=tmp%p10[cnt-1]+1;
	for(int i = cnt-1;i>=1;i--)
		for(int j = 1;j<= 9;j++)
			for(int k = 0;k<= 9;k++)
				ans[k][opt]+=f[i][j][k];
	for(int i = cnt-1;i>=1;i--)
	{
		for(int j = 0;j<= num[i]-1;j++)
			for(int k = 0;k<= 9;k++)
				ans[k][opt]+=f[i][j][k];
		ans[num[i]][opt]+=tmp%p10[i-1]+1;
	}
	return ;
}
int main()
{
	p10[0] = 1;
	for(int i = 1;i<= 12;i++)p10[i] = p10[i-1]*10;
	LL a,b;
	scanf("%lld%lld",&a,&b);
	for(int i = 0;i<= 9;i++)
		for(int j = 0;j<=9;j++)
			if(i==j)f[1][i][j] = 1;
	for(int i = 2;i<= 12;i++)
		for(int j = 0;j<= 9;j++)
			for(int k = 0;k<= 9;k++)
			{
				for(int l = 0;l<= 9;l++)
					f[i][j][k]+=f[i-1][l][k];
				if(k==j)f[i][j][k]+=p10[i-1];		
			}
	solve(a-1,0);
	solve(b,1);
	for(int i = 0;i< 9;i++)printf("%lld ",ans[i][1]-ans[i][0]);
	printf("%lld\n",ans[9][1]-ans[9][0]);
	return 0;
}
