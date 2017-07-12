
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
const int N = 10000000;
using namespace std;

int prime[N+5],cnt;
int ans[N];
bool f[N+5];
int rev[N+5];
long long mod;
int fac[N];

void init()
{
	for(int i=2;i<=N;++i)
	{
		if(!f[i])
			prime[++cnt] = i;
		for(int j=1;i*prime[j]<=N;++j)
		{
			f[i*prime[j]] = 1;
			if(i%prime[j] == 0)
				break;
		}
	}
	fac[1] = 1;
	for(int i=2;i<=N;++i)
		fac[i] = ((long long)fac[i-1]* i)%mod;
	rev[1] = 1;
	for(int i=2;i<=N && i<mod;++i)
		rev[i] = (mod - mod/i)*(long long)rev[mod%i]%mod;
	ans[1] = 1;
	for(int i=2;i<=N;++i)
		if(!f[i])
			ans[i] = (long long)ans[i-1]*(i-1)%mod * (long long)rev[i%mod] % mod;
		else
			ans[i] = ans[i-1];

}

int main()
{
	int T;
	cin>>T>>mod;
	init();
	while(T--)
	{
		int n,m;
		cin>>n>>m;
		long long tmp = fac[n];
		printf("%lld\n",tmp*ans[m]%mod);
	}
}	
