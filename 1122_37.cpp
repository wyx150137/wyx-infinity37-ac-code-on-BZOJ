
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1000005;
typedef long long LL;
int sum[N<<1],mn[N],Q[N<<1],l,r;
char opt[N];
LL Abs(LL x){return x>0?x:-x;}
int main()
{
	int n,p,q,x,y;
	scanf("%d%d%d%d%d",&n,&p,&q,&x,&y);
	scanf("%s",opt+1);
	for(int i = n*2;i>n;i--)
		sum[i] = sum[i+1]+(opt[i-n]=='+'?1:-1);
	for(int i = n;i>=1;i--)
		sum[i] = sum[i+1]+(opt[i]=='+'?1:-1);
	r = -1;
	for(int i = 2*n;i>=1;i--)
	{
		while(l<=r&&sum[i]>sum[Q[r]])r--;
		Q[++r] = i;
		while(l<=r&&Q[l]-i>=n)l++;
		if(i<=n)mn[i] = sum[i]-sum[Q[l]];
	}
	LL get = sum[n+1];
	LL cng = (q-p-get)/2;
	LL ans = 1e18;
	for(int i = 0;i<n;i++)
	{
		LL cost = Abs(cng)*x+(LL)y*i;
		if(i==0)
		{
			mn[1]+=p+max(cng,0ll)*2;
			if(mn[1]<0)cost += (LL)x*2*((1-mn[1])/2);
		}else
		{
			mn[n-i+1]+=p+max(cng,0ll)*2;
			if(mn[n-i+1]<0)cost += (LL)x*2*((1-mn[n-i+1])/2);
		}
		ans = min(ans,cost);
	}
	printf("%lld\n",ans);
	return 0;
}
