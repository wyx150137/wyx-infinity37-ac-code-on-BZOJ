
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
long long sum_oula[10000005];
long long oula[10000005];
int prime[1000005],t_p,n;
bool v[10000005];
void quick_oula()
{
	oula[1] = 1;
	for(int i = 2;i<= n;i++)
	{
		if(!v[i])
		{
			t_p++;
			prime[t_p] = i;
			oula[i] = i - 1;
		}
		for(int j = 1;j<= t_p&&i*prime[j]<=n;j++)
		{
			v[i*prime[j]] = true;
			if(i%prime[j]==0)
			{
				oula[i*prime[j]] = oula[i]*prime[j];
				break;
			}
			else 
				oula[i*prime[j]] = oula[i]*(prime[j]-1);
		}
	}
	for(int i = 1;i<= n;i++)
		sum_oula[i] = sum_oula[i-1]+oula[i];
}
int main()
{
	memset(prime,0x3f,sizeof(prime));
	scanf("%d",&n);
	quick_oula();
	int j = 1;long long ans = 0;
	while(prime[j]<=n)
	{
		ans +=sum_oula[n/prime[j]];
		j++;
	}
	ans = ans*2-j+1;
	printf("%lld",ans);
	return 0;
}
