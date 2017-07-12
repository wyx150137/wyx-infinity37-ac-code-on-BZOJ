
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll pow2[64];
ll f[100][2][2][2],g[100][2][2][2];
ll mod;
void work()
{
	ll N,M,K;
	scanf("%lld%lld%lld%lld",&N,&M,&K,&mod);
	N--,M--;
	ll ans = 0;
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	f[0][1][1][1] = 1;
	for(int i=0;i<=63;i++)
		for(int a=0;a<2;a++)
		for(int b=0;b<2;b++)
		for(int c=0;c<2;c++)
			if(f[i][a][b][c])
			{
				int p = ((N&pow2[63-i])==0)?0:1;
				int q = ((M&pow2[63-i])==0)?0:1;
				int t = ((K&pow2[63-i])==0)?0:1;
				for(int x = 0;x<2;x++)
				{
					if(a&&x>p)continue;
					for(int y = 0;y<2;y++)
					{
						if(b&&y>q)continue;
						int z = x^y;
						if(c&&z<t)continue;
						int A = (a&&x==p);
						int B = (b&&y==q);
						int C = (c&&z==t);
						(f[i+1][A][B][C]+=f[i][a][b][c])%=mod;
						g[i+1][A][B][C]=(g[i+1][A][B][C]+g[i][a][b][c]+((z==0)?0:pow2[63-i]%mod)*f[i][a][b][c]%mod)%mod;
					}
				}
			}
	K%=mod;
	for(int a=0;a<2;a++)
		for(int b=0;b<2;b++)
			for(int c=0;c<2;c++)
		    	ans=(ans+g[64][a][b][c]-K*f[64][a][b][c]%mod+mod)%mod;
	printf("%lld\n",ans);
}
int main()
{
	pow2[0] = 1;
	for(int i = 1;i<64;i++)
		pow2[i] = pow2[i-1]*2;
	int t;
	scanf("%d",&t);
	while(t--)
		work();
	return 0;
}
