
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 10000000+5
using namespace std;

int prime[N],cnt;
bool f[N];
int phi[N];
long long sum[N];
int n;
void init()
{
	phi[1]=1;
	register int i,j;
	for(i=2;i<=n;++i)
	{
		if(!f[i])
		{
			prime[++cnt] = i;
			phi[i] = i-1;
		}
		for(j=1;(long long)prime[j]*i <= n; ++j)
		{
			f[prime[j]*i] = 1;
			if(i%prime[j]==0)
			{
				phi[prime[j]*i] = phi[i] * prime[j];
				break;
			}
			else
				phi[prime[j]*i] = phi[i] * (prime[j]-1);
		}
	}
}

int main()
{
	cin>>n;
	init();
//	for(int i=1;i<=10;++i)
//s		cout<<phi[i]<<" ";
	for(int i=1;i<=n;++i)
		sum[i] = sum[i-1] + phi[i];
	long long ans = 0;
	for(int i=1;i<=cnt;++i)
		ans += sum[n/prime[i]]*2-1;//1 1 ->-1
	cout<<ans;
}	
