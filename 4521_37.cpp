
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;

ll f[20][2][10][10][4][2];
ll pow10[20];
int sta(int a,int b)
{
	return ((a==8||b==8)<<1)|((a==4||b==4));
}
ll dp(ll x)
{
	if(x<pow10[10])return 0;
	int s[20]={};
	int cnt = 0;
	while(x){s[11-cnt]=x%10;x/=10;cnt++;}
	memset(f,0,sizeof(f));
	int ap = sta(s[1],s[2]),fg = 0;
	f[2][0][s[1]][s[2]][ap][0]=1;
	for(int i = 1;i<= s[1];i++)
		for(int j = 0;j<= 9;j++)
		{
			if(i==s[1]&&j>=s[2])continue;
			f[2][1][i][j][sta(i,j)][0]=1;
		}
	for(int i = 3;i<= 11;i++)
	{
		ap|=sta(s[i],s[i]),fg|=(s[i]==s[i-1]&&s[i-1]==s[i-2]);
		if(ap!=3)f[i][0][s[i-1]][s[i]][ap][fg] = 1;
		for(int j = 0;j<= 9;j++)
		for(int k = 0;k<= 9;k++)
		for(int a = 0;a<= 2;a++)
			for(int b = 0;b<= 9;b++)
			{	
				int t1 = a|sta(b,b),t2 = j==k&&k==b;
				if(t1==3)continue;
				f[i][1][k][b][t1][1]+=(b<s[i])*f[i-1][0][j][k][a][1]+f[i-1][1][j][k][a][1];
				f[i][1][k][b][t1][t2]+=(b<s[i])*f[i-1][0][j][k][a][0]+f[i-1][1][j][k][a][0];
			}
	}
	ll ans = 0;
	for(int i = 0;i<= 9;i++)for(int j = 0;j<= 9;j++)
	for(int a = 0;a<= 2;a++)for(int b = 0;b<= 1;b++)
		ans+=f[11][b][i][j][a][1];
	return ans;
}

int main()
{
	ll l,r;
	scanf("%lld%lld",&l,&r);
	pow10[0]=1;
	for(int i = 1;i<= 11;i++)pow10[i]=pow10[i-1]*10;
	printf("%lld\n",dp(r)-dp(l-1));
	return 0;
}
