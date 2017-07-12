
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e7+5;
const int mod = 1e9+7;
bool v[N];
int f[N],g[N],prime[N],e[N],d[N],cnt;
int main()
{
	int q1,a,b,c;
	int q;
	scanf("%d%d%d%d%d",&q,&q1,&a,&b,&c);
	f[1] = g[1] = 1;
	for(int i = 2;i<= c;i++)
	{
		if(!v[i])
		{
			prime[++cnt] = i;
			e[i] = d[i] = 1;
			g[i] = 2;
			f[i]=((LL)i*i+1)%mod;
		}
		int k;
		for(int j = 1;j<= cnt&&(k=i*prime[j])<=c;j++)
		{
			v[k] = true;
			if(i%prime[j]==0)
			{
				e[k] = e[i]+1;
				g[k] = (g[i]/e[k])*(e[k]+1);
				d[k] = d[i];
				f[k] = ((LL)f[i]*prime[j]%mod*prime[j]%mod+f[d[i]])%mod;
				break;
			}else
			{
				e[k] = 1;
				d[k] = i;
				g[k] = g[i]*2;
				f[k] = (LL)f[i]*((LL)prime[j]*prime[j]%mod+1)%mod;
			}
		}
	}
	int ans1 = 0,ans2 = 0;
	for(int i = 1;i<= q;i++)
	{
		(ans1+=g[q1]+(q1&1))%=mod;
		(ans2+=f[q1]+4*(q1&1))%=mod;
		q1 = ((LL)q1*a+b)%c+1;
	}
	printf("%d\n%d\n",ans1,ans2);
	return 0;
}
