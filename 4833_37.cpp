
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e6+5;
ll f[N],g[N];
int n,p;
int quick_pow(int x,int y)
{
	int res = 1;
	while(y)
	{
		if(y&1)res=(ll)res*x%p;
		x = (ll)x*x%p;
		y>>=1;
	}
	return res;
}
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%d%d",&n,&p);
		f[1] = g[1] = 1,f[2] = g[2] = 2;
		for(int i = 3;i<= n;i++)
			f[i] = ((f[i-1]<<1)+f[i-2])%p,g[i] = f[i];
		for(int i = 1;i<= n;i++)
		{
			int inv = quick_pow(g[i],p-2);
			for(int j = i+i;j<= n;j+=i)
				g[j] = (ll)g[j]*inv%p;
		}
		ll lcm = 1,ans = 0;
		for(int i = 1;i<= n;i++)
			lcm = (ll)lcm*g[i]%p,(ans+=lcm*i%p)%=p;
		printf("%lld\n",ans);
	}
}
