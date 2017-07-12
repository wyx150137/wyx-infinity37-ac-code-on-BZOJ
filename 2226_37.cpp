
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int phi[1000005],a[100005],tot;
long long f[1000005];
bool not_prime[1000005];
void oula(int n)
{
	for(int i = 2;i<= n;i++)
	{
		if(!not_prime[i])
		{
			a[++tot] = i;
			phi[i] = i-1;
		}
		for(int j = 1;j<= tot&&a[j]*i<=n;j++)
		{
			not_prime[i*a[j]] = true;
			if(i%a[j]==0){phi[i*a[j]] = phi[i]*a[j];break;}
			else phi[i*a[j]] = phi[i]*(a[j]-1);
		}
	}
}
long long ans(int i)
{
	long long re = 0;
	for(int j = 1;j*j<= i;j++)
	{
		if(i%j==0&&j*j!=i)
			{re+=f[i/j]+f[j];}
		else if(j*j==i)
			re+=f[j];
	}
	return re;
}
int main()
{
	int T,x;
	scanf("%d",&T);
	oula(1000001);
	f[1] = 1;
	for(int i = 1;i<= 1000001;i++)
		if(i!=1)f[i] = (long long)i*phi[i]/2;
	for(int i = 1;i<= T;i++)
	{
		scanf("%d",&x);
		printf("%lld\n",ans(x)*x);
	}
	return 0;
}
