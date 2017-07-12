
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 3005;
int t,vis[N];
ll l,r,n,m;
ll a[N];
ll gcd(ll x,ll y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
void getnum(ll x,ll y)
{
	if(y>r)
		return ;
	if(x>1)
		a[++m]=y;
	if(x>t)
		return ;
	getnum(x+1,y*10+2);
	getnum(x+1,y*10+9);
}
ll ans;
void dfs(ll x,ll y,ll z)
{
	if(x>n)
	{
		if(y&1)
			ans+=r/z-(l-1)/z;
		else
			if(y)
				ans-=r/z-(l-1)/z;
		return ;
	}
	dfs(x+1,y,z);
	ll next = a[x]*z/gcd(a[x],z);
	if(next<=r)
		dfs(x+1,y+1,next);
	return ;
}
int b[N];
int main()
{
	scanf("%lld%lld",&l,&r);
	t = (int)(log10(r)+1);
	getnum(1,0);
	sort(a+1,a+m+1);
	for(int i = 1;i<= m;i++)
		if(!vis[i])
		{
			b[++n] = a[i];
			for(int j = i+1;j<= m;j++)
				if(a[j]%a[i]==0)
					vis[j] = 1;
		}
	for(int i = 1;i<= n;i++)
		a[n-i+1]=b[i];
	dfs(1,0,1);
	printf("%lld\n",ans);
	return 0;
}
