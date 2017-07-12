
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100005;
const int M = 1<<12;
const int INF = 1e8;
const LL mod = 1000000001;
bool v[N];
int a[20][13],b[20],p2[20],n;
int f[20][M];
LL calc(int x)
{
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	a[1][1] = x;
	for(int i = 2;i<= 18;i++)
	{
		if((a[i-1][1]<<1)<=n)
			a[i][1] = a[i-1][1]<<1;
		else a[i][1] = INF;
	}
	for(int i = 1;i<= 18;i++)
		for(int j = 2;j<= 12;j++)
		{
			if(a[i][j-1]*3<=n)
				a[i][j] = a[i][j-1]*3;
			else a[i][j] = INF;
		}
	for(int i = 1;i<= 18;i++)
		for(int j = 1;j<= 12;j++)
			if(a[i][j]<=n)
			{
				v[a[i][j]] = true;
				b[i]+=p2[j-1];
			}
	memset(f,0,sizeof(f));
	f[0][0] = 1;
	for(int i = 1;i<= 18;i++)
		for(int j = 0;j<=b[i-1];j++)
		{
			if(((j<<1)&j)||((j>>1)&j))continue;
			for(int k = 0;k<= b[i];k++)
			{
				if(((k<<1)&k)||((k>>1)&k)||(j&k))continue;
				f[i][k]=(f[i][k]+f[i-1][j])%mod;
			}
		}
	long long ans = 0;
	for(int i = 0;i<=b[18];i++)
		ans = (ans+f[18][i])%mod;
	return ans;
}
int main()
{
	for(int i = 0;i<=18;i++)
		p2[i] = 1<<i;
	scanf("%d",&n);
	LL ans = 1;
	for(int i = 1;i<= n;i++)
		if(!v[i])ans = ans*calc(i)%mod;
	printf("%lld\n",ans);
	return 0;
}
