
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int INF = 0x3f3f3f3f;
int mn[N<<2],lazy[N<<2];
struct Q
{
	int l,r;
}ask[N];
bool cmp(Q a,Q b)
{
	return a.r<b.r;
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		scanf("%d",&mn[p]);
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	mn[p] = min(mn[p<<1],mn[p<<1|1]);
}
void push_down(int p,int l,int r)
{
	if(!lazy[p]||l==r)return ;
	mn[p<<1] = mn[p<<1]+lazy[p];
	mn[p<<1|1] = mn[p<<1|1]+lazy[p];
	lazy[p<<1]+=lazy[p];
	lazy[p<<1|1]+=lazy[p];
	lazy[p] = 0;
}
void update(int p,int l,int r,int a,int b)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		mn[p]--;
		lazy[p]--;
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b);
	if(b>mid)update(p<<1|1,mid+1,r,a,b);
	mn[p] = min(mn[p<<1],mn[p<<1|1]);
}
int getans(int p,int l,int r,int a,int b)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
		return mn[p];
	int mid = (l+r)>>1;
	int ans = INF;
	if(a<=mid)ans = min(ans,getans(p<<1,l,mid,a,b));
	if(b>mid)ans = min(ans,getans(p<<1|1,mid+1,r,a,b));
	mn[p] = min(mn[p<<1],mn[p<<1|1]);
	return ans;
}
int main()
{
	int n,m,ans = 0;
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for(int i = 1;i<= m;i++)
		scanf("%d%d",&ask[i].l,&ask[i].r);
	sort(ask+1,ask+m+1,cmp);
	for(int i = 1;i<= m;i++)
	{
		if(getans(1,1,n,ask[i].l,ask[i].r)>=1)
		{
			update(1,1,n,ask[i].l,ask[i].r);
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
