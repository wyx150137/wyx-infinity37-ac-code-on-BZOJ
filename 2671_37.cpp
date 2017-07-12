
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
typedef long long ll;
int mu[N],prime[N],cnt;
bool v[N];
ll n,stack[N];
void quick_mu()
{
	mu[1] = 1;
	for(int i = 2;i<N;i++)
	{
		if(!v[i])
		{
			mu[i] = -1;
			prime[++cnt] = i;
		}
		for(int j=1;j<= cnt&&i*prime[j]<N;j++)
		{
			v[prime[j]*i]=true;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else 
			{
				mu[i*prime[j]]=0;
				break;
			}
		}
	}
}
void get_fac(ll x)
{
	stack[0]=0;
	for(ll i = 1;i*i<=x;i++)
		if(x%i==0)
		{
			stack[++stack[0]] = i;
			if(i*i!=x)stack[++stack[0]]=x/i;
		}
	sort(stack+1,stack+stack[0]+1);
}
ll calc()
{
	ll a,b,k,last,ans=0;
	for(b=1;b*(b+1)<=n;b++)
	{
		get_fac(b);
		for(a=1;a<b&&b*(a+b)<=n;a=last+1)
		{
			last=min(n/(n/b/(a+b))/b-b,b-1);
			ll cnt = 0;
			for(k=1;stack[k]<=last;k++)
				cnt+=(ll)mu[stack[k]]*(last/stack[k]-(a-1)/stack[k]);
			ans+=n/b/(a+b)*cnt;
		}
	}
	return ans;
}
int main()
{
	scanf("%lld",&n);
	quick_mu();
	printf("%lld\n",calc());
	return 0;
}
