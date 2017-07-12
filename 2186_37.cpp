
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
const int Maxn = 10000000+5; 
long long fac[Maxn],ans[Maxn],rev[Maxn];
int prime[Maxn/10],t_p;
bool v[Maxn];
long long mod;
int n,m;
void quick_prime()
{
	for(int i = 2;i< Maxn;i++)
	{
		if(!v[i])
		{
			t_p++;
			prime[t_p] = i;
		}
		for(int j = 1;j<= t_p&&prime[j]*i<Maxn;j++)
		{
			v[i*prime[j]] = true;
			if(i%prime[j]==0)
				break;
		}
	}
	fac[1]=1; 
	int i; 
    for(i=2;i<=Maxn;i++)  
        fac[i]=fac[i-1]*i%mod;  
    rev[1]=1;  
    for(i=2;i<=Maxn&&i<mod;i++)  
        rev[i]=(mod-mod/i)*rev[mod%i]%mod;  
    ans[1]=1;  
    for(i=2;i<=Maxn;i++)  
    {  
        if(!v[i])  
            ans[i]=ans[i-1]*(i-1)%mod*rev[i%mod]%mod;  
        else  
            ans[i]=ans[i-1];  
    }
}
int main()
{
	int T;
	scanf("%d%lld",&T,&mod);
	quick_prime();
	while(T--)
	{
		scanf("%d%d",&n,&m);
		long long t_ans = fac[n];
		t_ans = t_ans*ans[m]%mod;
		printf("%lld\n",t_ans);
	}
	return 0;
}
