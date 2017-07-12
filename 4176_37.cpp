
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e7+5;
const int mod = 1e9+7;
int n,S;
int mu[N],prime[N/10],cnt,sum2[N];
bool v[N];
void quick_mu()
{
	mu[1] = 1;
	for(int i = 2;i<=S;i++)
	{
		if(!v[i])
		{
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j = 1;j<= cnt&&prime[j]*i<=S;j++)
		{
			v[i*prime[j]] = true;
			if(i%prime[j])
				mu[prime[j]*i] = -mu[i];
			else {mu[prime[j]*i]=0;break;}
		}
	}
}
int Get_Sum(int n)
{
	int i,ans=0,last;
	for(i=1;i<=n;i=last+1)
	{
		last = n/(n/i);
		(ans+=(ll)(last-i+1)*(n/i)%mod)%=mod;
	}
	return ans;
}
int get_sum(int x)
{
	if(x<=S)return mu[x];
	else return sum2[n/x];
}
void init()
{
	quick_mu();
	for(int i = 2;i<=S;i++)
		mu[i]+=mu[i-1];
	int i,j,last;
	for(i=1;n/i>S;i++);
	for(j=i;j;j--)
	{
		int n = ::n/j;
		sum2[j] = 1;
		for(i=2;i<=n;i=last+1)
		{
			last = n/(n/i);
			(sum2[j]-=(ll)(last-i+1)*get_sum(n/i)%mod)%=mod;
		}
	}
}
int main()
{
	int i,last,ans =0;
	scanf("%d",&n);
	S = ceil(pow(n,0.75)-1e-7)+1e-7;
	init();
	for(i=1;i<=n;i=last+1)
	{
		last = n/(n/i);
		ll tmp = Get_Sum(n/i);
		(ans+=(get_sum(last)-get_sum(i-1))*tmp%mod*tmp%mod)%=mod;
	}
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
