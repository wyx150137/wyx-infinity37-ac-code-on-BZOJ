
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 505;
const int S = 1<<8;
int prime[N],cnt;
bool vis[N];
void quick_prime()
{
	for(int i = 2;i<=500;i++)
	{
		if(!vis[i])
			prime[cnt++] = i;
		for(int j = 0;j<cnt&&i*prime[j]<=500;j++)
		{
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
struct Num
{
	int l,p,i;
	bool operator <(const Num &s)const
	{
		return p<s.p;
	}
}num[N];
int f[S][S],dp[S][S][2];
void calc(int x)
{
	int tmp = x;
	for(int i = 0;i<8;i++)
		if(tmp%prime[i]==0)
		{
			num[x].l|=1<<i;
			while(tmp%prime[i]==0)tmp/=prime[i];
		}
	num[x].p = tmp;
}
int main()
{
	int n,mod;
	quick_prime();
	scanf("%d%d",&n,&mod);
	for(int i = 2;i<= n;i++)
		calc(i);
	sort(num+2,num+n+1);
	f[0][0] = 1;
	int end = (1<<8)-1,i,j,k;
	for(i = 2;i<= n;i++)
	{
		if(i==2||num[i].p==1||num[i-1].p!=num[i].p)
			for(j = end;j>=0;j--)
				for(k = end;k>=0;k--)
					dp[j][k][0]=dp[j][k][1]=f[j][k];
		for(j = end;j>=0;j--)
			for(k = end;k>=0;k--)
			{
				if((j&num[i].l)==0)
					(dp[j][k|num[i].l][1]+=dp[j][k][1])%=mod;
				if((k&num[i].l)==0)
					(dp[j|num[i].l][k][0]+=dp[j][k][0])%=mod;
			}
		if(i==n||num[i].p==1||num[i].p!=num[i+1].p)
			for(j = end;j>=0;j--)
				for(k = end;k>=0;k--)
				{
					f[j][k] = dp[j][k][0]+dp[j][k][1]-f[j][k];
					f[j][k] = (f[j][k]%mod+mod)%mod;
				}
	}
	int ans = 0;
	for(j = 0;j<=end;j++)
		for(k = 0;k<=end;k++)
			if((j&k)==0)(ans+=f[j][k])%=mod;
	printf("%d\n",ans);
	return 0;
}
