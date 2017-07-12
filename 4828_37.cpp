
#include <stdio.h>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int N = 105;
const int B = 1e6;
int prime[N],cnt;
bool vis[N];
void get_prime()
{
	for(int i = 2;i<N;i++)
	{
		if(!vis[i])prime[cnt++] = i;
		for(int j = 0;j<cnt&&i*prime[j]<N;j++)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j]==0)break;
		}
	}
}
int S[B+5];
map<int,int>s;
int n,m,mc,k,dp[N][N];
int a[N],w[N],C[N],fl[N],maxc;
int Get(int x)
{
	if(x<=B)return S[x];
	else return s[x];
}
void Update(int x,int ans)
{
	if(x<=B)S[x] = ans;
	else s[x] = ans;
}
int calc(int n)
{
	if(n<0)return INF;
	if(n==0)return 0;
	if(n==1)return 1;
	int tmp = n,end = 1;
	for(int i = 0;i< cnt;i++)
		while(tmp%prime[i]==0)
			tmp/=prime[i],end = prime[i];
	if(tmp>1)return INF;
	if(Get(n))return Get(n);
	int lim = k+1;
	for(int i = end;i<lim-1;i++)if(n%i==0)
	{
		int t = i+1;
		tmp = n;
		for(int j = i;j>=2&&t<=lim&&tmp>1;j--)
			while(tmp%j==0)
				tmp/=j,t++;
		if(tmp==1)lim= min(lim,t);
	}
	Update(n,lim);
	return lim;
}
int tmp;
void solve(int x,int pos)
{
	if(tmp==m)return ;
	int t = calc(x);
	if(t>k/2)return ;
	for(int i = pos;i>=0;i--)if((ll)prime[i]*x<=maxc)solve(x*prime[i],i);
	for(int i = 0;i<= k-2*t;i++)
	{
		for(int j = 1;j<= m;j++)
			if(!fl[j])
			{
				int l = calc(C[j]-i-x);
				if(l+i+t<=k)fl[j]=1,tmp++;
			}
	}
}
int main()
{
	get_prime();
	scanf("%d%d%d",&n,&m,&mc);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)scanf("%d",&w[i]);
	for(int i = 1;i<= m;i++)scanf("%d",&C[i]),maxc = max(maxc,C[i]);
	memset(dp,-1,sizeof(dp));
	dp[0][0] = mc;
	for(int i = 0;i< n;i++)
	{
		for(int j = 0;j<= i;j++)if(dp[i][j]!=-1)
		{
			if(dp[i][j]<a[i+1])continue;
			dp[i+1][j] = min(mc,max(dp[i+1][j],dp[i][j]-a[i+1]+w[i+1]));
			dp[i+1][j+1] = min(mc,max(dp[i+1][j+1],dp[i][j]-a[i+1]));
		}
		for(int j = 0;j<= n;j++)if(dp[i+1][j]!=-1)k = max(k,j);
	}
	for(int i = 1;i<= m;i++)
	{
		for(int j =0;j<k&&j<C[i];j++)fl[i]|=(calc(C[i]-j)+j<=k);
		tmp+=fl[i];
	}
	solve(1,14);
	for(int i = 1;i<= m;i++)printf("%d\n",fl[i]);
	return 0;
}
