
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int mod = 1e9+7;
typedef long long LL;
int f[6][16][16][16][16][16];
bool used[6][16][16][16][16][16];
int cnt[6];
int dp(int last,int a,int b,int c,int d,int e)
{
	if(!a&&!b&&!c&&!d&&!e)return 1;
	if(a<0||b<0||c<0||d<0||e<0)return 0;
	if(used[last][a][b][c][d][e])return f[last][a][b][c][d][e];
	LL ans = 0;
	ans+=(LL)(a+(last==2?-1:0))*dp(1,a-1,b,c,d,e)%mod;
	ans+=(LL)(b+(last==3?-1:0))*dp(2,a+1,b-1,c,d,e)%mod;
	ans+=(LL)(c+(last==4?-1:0))*dp(3,a,b+1,c-1,d,e)%mod;
	ans+=(LL)(d+(last==5?-1:0))*dp(4,a,b,c+1,d-1,e)%mod;
	ans+=(LL)e*dp(5,a,b,c,d+1,e-1)%mod;
	ans = ans%mod;
	used[last][a][b][c][d][e] = true;
	f[last][a][b][c][d][e] = ans;
	return ans;
}
int main()
{
	int k,x;
	scanf("%d",&k);
	for(int i = 1;i<= k;i++)
	{
		scanf("%d",&x);
		cnt[x]++;
	}
	printf("%d\n",dp(0,cnt[1],cnt[2],cnt[3],cnt[4],cnt[5]));
	return 0;
}
