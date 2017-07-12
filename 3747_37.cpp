
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
typedef long long LL;
int w[N],f[N],next[N],last[N];
LL maxn[N<<2],lazy[N<<2];
void push_down(int p,int l,int r)
{
	if(lazy[p]==0||l==r)return ;
	maxn[p<<1]+=lazy[p];
	maxn[p<<1|1]+=lazy[p];
	lazy[p<<1]+=lazy[p];
	lazy[p<<1|1]+=lazy[p];
	lazy[p] = 0;
}
void update(int p,int l,int r,int a,int b,int c)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		lazy[p]+=c;
		maxn[p]+=c;
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,c);
	if(b>mid)update(p<<1|1,mid+1,r,a,b,c);
	maxn[p] = max(maxn[p<<1],maxn[p<<1|1]);
}
/*LL getans(int p,int l,int r,int a,int b)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
		return maxn[p];
	LL ans = 0;
	int mid = (l+r)>>1;
	if(a<=mid)ans = max(ans,getans(p<<1,l,mid,a,b));
	if(b>mid)ans = max(ans,getans(p<<1|1,mid+1,r,a,b));
	maxn[p] = max(maxn[p<<1],maxn[p<<1|1]);
	return ans;
}*/
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		scanf("%d",&f[i]);
	for(int i = 1;i<= m;i++)
		scanf("%d",&w[i]);
	for(int i = n;i>=1;i--)
	{
		next[i] = last[f[i]];
		last[f[i]] = i;
	}
	for(int i = 1;i<= m;i++)
		if(last[i])
		{
			if(!next[last[i]])update(1,1,n,last[i],n,w[i]);
			else update(1,1,n,last[i],next[last[i]]-1,w[i]);
		}
	LL ans = 0;
	for(int i = 1;i<= n;i++)
	{
		ans = max(ans,maxn[1]);
		int t = next[i];
		if(t)
		{
			update(1,1,n,i,t-1,-w[f[i]]);
			if(next[t])update(1,1,n,t,next[t]-1,w[f[i]]);
			else update(1,1,n,t,n,w[f[i]]);
		}else update(1,1,n,i,n,-w[f[i]]);
	}
	printf("%lld",ans);
	return 0;
}
