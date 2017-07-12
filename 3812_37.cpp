
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int S = 1<<15;
const LL mod = 1e9+7;
LL c[250][250];
LL f[S],g[S],h[S],power_2[S];
int in[S],out[S],dig[S];
int Count(int x)
{
	return dig[x>>8] + dig[x&255] ;
}
int main()
{
	int n,m,x,y,i;
	scanf("%d%d",&n,&m);
	for(i = 1;i<1<<8;i++)
		dig[i] = dig[i>>1]+(i&1);
	for(power_2[0]=1,i=1;i<=m;i++)
		power_2[i]=(power_2[i-1]<<1)%mod;
	for(i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		//add(x,y);
		//f[(1<<(x-1))|(1<<(y-1))]+=1;
		out[1<<(x-1)]|=1<<(y-1);
		in[1<<(y-1)]|=1<<(x-1);
	}
	for(i = 1;i<1<<n;i++)
	{
		int one = i&(-i),sta = i^one;
		h[i] = h[sta]+Count(in[one]&sta)+Count(out[one]&sta);
		for(int j = sta;j;j = (j-1)&sta)
			(g[i]+=mod-f[i^j]*g[j]%mod)%=mod;
		static int w[1<<15];
		f[i] = power_2[h[i]];
		for(int j = i;j;j = (j-1)&i)
		{
			if(j==i)w[j] = 0;
			else
			{
				int tmp = (i^j)&(-(i^j));
				w[j] = w[j^tmp]-Count(out[tmp]&(i^j))+Count(j&in[tmp]);
			}
			(f[i]+=mod-power_2[h[i^j]+w[j]]*g[j]%mod)%=mod;
		}
		(g[i]+=f[i])%=mod;
	}
	printf("%lld\n",f[(1<<n)-1]);
	return 0;
}
