
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2005;
const int mod =1e9+9;
typedef long long ll;
int n,k;
ll f[N][N];
ll c[N][N],fac[N],g[N];
void init()
{
	fac[0] = 1;
	for(int i = 1;i<N;i++)
		fac[i] = fac[i-1]*i%mod;
	c[0][0] = 1;
	for(int i = 1;i<N;i++)
	{
		c[i][0] = 1;
		for(int j = 1;j<N;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	}	
}
int a[N],b[N],next[N];
int main()
{
	init();
	int n,k;
	scanf("%d%d",&n,&k);
	if((n+k)&1){printf("0\n");return 0;}
	k=(k+n)/2;
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)scanf("%d",&b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	int j = 1;
	for(int i = 1;i<= n;i++)
	{
		while(b[j]<a[i]&&j<=n)j++;
		next[i]=j-1;
	}
	f[0][0] = 1;
	for(int i = 1;i<= n;i++)
	{
		f[i][0]=1;
		for(int j = 1;j<= i;j++)
			(f[i][j]+=f[i-1][j-1]*max(next[i]-j+1,0)+f[i-1][j])%=mod;
	}
	for(int i = n;i>=k;i--)
	{
		g[i] = (ll)f[n][i]*fac[n-i]%mod;
		for(int j = i+1;j<= n;j++)
			(g[i]+=mod-g[j]*c[j][i]%mod)%=mod;
	}
	printf("%lld\n",g[k]);
	return 0;
}
