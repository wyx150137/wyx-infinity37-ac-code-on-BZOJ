
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1<<12;
const int mod = 100000000;
int f[13][N];
int map[13];
int main()
{
	int n,m,x;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		for(int j = 0;j<m;j++)
		{
			scanf("%d",&x);
			map[i] |= (x^1)<<j;
		}
	f[0][0] = 1;
	for(int i = 1;i<= n;i++)
	{
		for(int last = 0;last< 1<<m;last++)
		{
			if((last&map[i-1])||(last&(last<<1))||(last&(last>>1)))continue;
			for(int now = 0;now<1<<m;now++)
			{
				if((now&map[i])||(now&(now<<1))||(now&(now>>1)))continue;
				if(now&last)continue;
				f[i][now] = (f[i][now]+f[i-1][last])%mod;
			}
		}
	}
	int ans = 0;
	for(int i = 0;i<1<<m;i++)
		ans = (ans+f[n][i])%mod;
	printf("%d\n",ans);
	return 0;
}
