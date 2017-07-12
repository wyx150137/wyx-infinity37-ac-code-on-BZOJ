
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
const int mod = 1e9+7;
int prime[N],cnt;
bool v[N];
void quick_prime(int n)
{
	for(int i = 2;i<= n;i++)
	{
		if(!v[i])
			prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
		{
			v[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
int main()
{
	int n;
	long long ans = 1;
	scanf("%d",&n);
	quick_prime(n);
	for(int i = 1;i<= cnt;i++)
	{
		int tmp = n;
		long long cnt = 0;
		while(tmp)
		{
			cnt+=tmp/prime[i];
			tmp/=prime[i];
		}
		cnt = (cnt<<1|1)%mod;
		ans = ans*cnt%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
