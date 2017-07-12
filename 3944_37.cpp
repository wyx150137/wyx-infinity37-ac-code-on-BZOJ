
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int M = 2e6+5;
const int N = 1e5+5;
const int m = 2e6;
bool v[M];
int prime[M],cnt,n;
ll mu[M],phi[M],p[N],q[N];
bool vis[N];
void quick_shai()
{
	phi[1] = mu[1] = 1;
	for(int i = 2;i<M;i++)
	{
		if(!v[i])
		{
			phi[i] = i-1;
			mu[i] = -1;
			prime[++cnt] = i;
		}
		for(int j = 1;j<= cnt&&prime[j]*i<M;j++)
		{
			v[i*prime[j]] = true;
			if(i%prime[j])
			{
				mu[i*prime[j]] = -mu[i];
				phi[i*prime[j]] = phi[i]*(prime[j]-1);
			}else
			{
				mu[i*prime[j]] = 0;
				phi[i*prime[j]] = phi[i]*prime[j];
				break;
			}
		}
	}
	for(int i = 1;i<M;i++)
		phi[i]+=phi[i-1],mu[i]+=mu[i-1];
}
ll getp(int x)
{
	if(x<=m)return phi[x];
	else return p[n/x];
}
ll getq(int x)
{
	if(x<=m)return mu[x];
	else return q[n/x];
}
void solve(int x)
{
	if(x<=m)return ;
	int i,j = 1,t=n/x;
	if(vis[t])return ;
	vis[t] = true;
	p[t] = ((ll)x+1)*x/2;q[t] = 1;
	while(j<x)
	{
		i = j+1;
		j = x/(x/i);
		solve(x/i);
		q[t]-=getq(x/i)*(j-i+1);
		p[t]-=getp(x/i)*(j-i+1);
	}
}
int main()
{
	quick_shai();
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(vis,0,sizeof(vis));
		scanf("%d",&n);
		if(n<=m)printf("%lld %lld\n",phi[n],mu[n]);
		else
		{
			solve(1ll*n);
			printf("%lld %lld\n",p[1],q[1]);
		}
	}
	return 0;
}
