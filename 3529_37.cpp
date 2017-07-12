
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
typedef long long ll;
const ll mod = (1ll<<31)-1;
bool vis[N];
int mu[N],prime[N],cnt;
ll G[N],g[N];
struct To
{int no;ll val;}g_no[N];
bool cmp(const To &a,const To &b){return a.val<b.val;}
void quick_mu()
{
	mu[1] = 1;
	for(int i = 2;i<N;i++)
	{
		if(!vis[i])
		{
			prime[++cnt] =i;
			mu[i] = -1;
		}
		for(int j = 1;j<=cnt&&i*prime[j]<N;j++)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j])mu[i*prime[j]] = -mu[i];
			else
			{
				mu[i*prime[j]] = 0;
				break;
			}
		}
	}
	for(int i = 1;i<N;i++)
		for(int j = 1;j*i<N;j++)
			g[i*j]=(g[i*j]+i)&mod;
	for(int i = 1;i<N;i++)
		g_no[i].val = g[i],g_no[i].no = i;
	sort(g_no+1,g_no+N,cmp);
}
void update(int x,int y)
{
	for(int i = x;i<N;i+=i&(-i))
		G[i]=(G[i]+y)&mod;
}
ll getans(int x)
{
	ll ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans=(ans+G[i])&mod;
	return ans;
}
struct A
{int a,no,n,m;}ask[N];
bool cmpask(const A &a,const A &b){return a.a<b.a;}
ll ans_no[N];
void solve(int n,int m,int no)
{
	ll ans = 0;
	int last;
	for(int i = 1;i<=n&&i<=m;i =last+1)
	{
		last = min(n/(n/i),m/(m/i));
		ans = (ans+(ll)(n/i)*(m/i)*((getans(last)-getans(i-1))%(mod+1)+mod+1))&mod;
	}
	ans_no[no] = ans;
}
int main()
{
	int q;
	scanf("%d",&q);
	quick_mu();
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d%d",&ask[i].n,&ask[i].m,&ask[i].a);
		ask[i].no = i;
	}
	sort(ask+1,ask+q+1,cmpask);
	int r = 1;
	for(int i = 1;i<= q;i++)
	{
		while(g_no[r].val<=ask[i].a&&r<N)
		{
			for(int j = 1;j*g_no[r].no<N;j++)
				update(j*g_no[r].no,g_no[r].val*mu[j]);
			r++;
		}
		solve(ask[i].n,ask[i].m,ask[i].no);
	}
	for(int i=1;i<= q;i++)
		printf("%lld\n",ans_no[i]);
	return 0;
}
