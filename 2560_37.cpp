
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int S = 1<<16;
const int mod = 1e9+7;
int c[20][20];
int f[S],g[S],n;
int main()
{
	int now;
	scanf("%d",&n);
	for(int i = 0;i<n;i++)
		for(int j = 0;j<n;j++)
			scanf("%d",&c[i][j]);
	int end = 1<<n;
	for(int i = 1;i<end;i++)
	{
		g[i] = 1;
		for(int j = 0;j<n;j++)if(i&(1<<j))
			for(int k = j+1;k<n;k++)if(i&(1<<k))
				g[i] = (ll)g[i]*(c[j][k]+1)%mod;
		for(int j = n-1;j>= 0;j--)
			if(i&(1<<j)){now = j;break;}
		f[i] = g[i];
		now = i^(1<<now);
		for(int j = now;j;j=(j-1)&now)
			(f[i]+=mod-(ll)g[j]*f[i^j]%mod)%=mod;
	}
	printf("%d\n",f[end-1]);
	return 0;
}
