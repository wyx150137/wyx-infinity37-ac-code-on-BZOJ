
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
typedef long long ll;
int prime[N],cnt;
ll Ans[10000005];
bool v[N];
void quick_prime()
{
	for(int i = 2;i<N;i++)
	{
		if(!v[i])
			prime[++cnt]=i;
		for(int j = 1;j<= cnt&&i*prime[j]<N;j++)
		{
			v[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
bool check_prime(int x)
{
	if(x==1)return false;
	for(int i = 1;prime[i]*prime[i]<= x;i++)
		if(x%prime[i]==0)return false;
	return true;
}
void getans(ll ans,int pos,ll left)
{
	if(left==1)
	{
		Ans[++Ans[0]]=ans;
		return ;
	}
	if(left-1>=prime[pos]&&check_prime(left-1))
		Ans[++Ans[0]] = ans*(left-1);
	for(int i = pos;prime[i]*prime[i]<=left;i++)
	{
		ll sum = 1+prime[i],powe = prime[i];
		for(;sum<=left;powe*=prime[i],sum+=powe)
			if(left%sum==0)
			{
				getans(ans*powe,i+1,left/sum);
			}
	}
}
int main()
{
	ll n;
	quick_prime();
	while(scanf("%lld",&n)!=EOF)
	{
		Ans[0] = 0;
		getans(1,1,n);
		sort(Ans+1,Ans+Ans[0]+1);
		printf("%lld\n",Ans[0]);
		for(int i = 1;i<= Ans[0];i++)
			printf("%lld%c",Ans[i],i==Ans[0]?'\n':' ');
	}
	return 0;
}
