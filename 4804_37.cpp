
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e7+5;
int prime[N/10],cnt;
bool vis[N];ll F[N];
void quick_shai()
{
	F[1] = 1;
	for(int i = 2;i< N;i++)
	{
		if(!vis[i])
		{
			prime[++cnt] = i;
			F[i] = i-2;
		}
		for(int j = 1;j<= cnt&&(ll)i*prime[j]<N;j++)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j]==0)
			{
				if((i/prime[j])%prime[j]!=0)
					F[i*prime[j]] = F[i/prime[j]]*(prime[j]-1)*(prime[j]-1);
				else 
					F[i*prime[j]] = F[i]*prime[j];
				break;
			}
			else 
				F[i*prime[j]] = F[i]*F[prime[j]];
		}
	}
	for(int i = 1;i<N;i++)F[i]+=F[i-1];
}
ll Solve(int n)
{
	int l,r,t; 
	ll ret=0;
	for(l = 1;l*l<= n;l++)
		t=n/l,ret+=(ll)t*t*(F[l]-F[l-1]);
	for(t = n/l;l<= n;l=r+1,t--)
		r=n/t,ret+=(ll)t*t*(F[r]-F[l-1]);
	return ret;
}
int main()
{
	int cas,n;
	quick_shai();
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%d",&n);
		printf("%lld\n",Solve(n));
	}
	return 0;
}
