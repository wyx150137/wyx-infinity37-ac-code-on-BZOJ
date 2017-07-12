
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 305;
typedef long long ll;
const int sed = 107;
const int mod = 998244353;
double f[N][N],B[N],pw2[N];
int n,m,deg;
char s[N][N];
ll h[N][N],h0[N][N],pws[N],pw0[N];
int main()
{
	scanf("%d%d",&n,&m);
	deg = n+1;
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",s[i]+1);
		for(int j = 1;j<= m;j++)
		{
			h[i][j] = h[i][j-1]*sed+s[i][j];
			h0[i][j] = (h0[i][j-1]*sed+s[i][j])%mod;
		}
	}
	pw2[0] = pws[0] = pw0[0] = 1;
	for(int i = 1;i<= m;i++)
	{
		pw2[i] = pw2[i-1]*0.5;
		pws[i] = pws[i-1]*sed;
		pw0[i] = pw0[i-1]*sed%mod;
	}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			for(int k = 1;k<m;k++)
			if(h[i][k]==h[j][m]-h[j][m-k]*pws[k])
			{
				ll x0 = h0[i][k];
				ll x1 = (h0[j][m]-h0[j][m-k]*pw0[k]%mod+mod)%mod;
				if(x0==x1)
					f[i][j]+=pw2[m-k];
			}
	for(int i = 1;i<= n;i++)f[i][i]++,f[i][n+1]--,f[n+1][i]++;
	B[n+1] = 1;
	for(int i = 1,l;i<= deg;i++)
	{
		for(int j = (l=i)+1;j<=deg;j++)if(fabs(f[j][i])>fabs(f[l][i]))l = j;
		for(int j = i;j<= deg;j++)swap(f[i][j],f[l][j]);
		swap(B[i],B[l]);
		double t = f[i][i];
		for(int j = i;j<= deg;j++)f[i][j]/=t;
		B[i]/=t;
		for(int j = 1;j<= deg;j++)if(j!=i)
		{
			t = f[j][i];
			for(int k = i;k<= deg;k++)f[j][k]-=f[i][k]*t;
			B[j]-=B[i]*t;
		}
	}
	for(int i = 1;i<= n;i++)printf("%.10lf\n",B[i]);
	return 0;
}
