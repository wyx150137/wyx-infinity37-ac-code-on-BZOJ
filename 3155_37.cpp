
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
typedef long long LL;
LL sum[N<<2],lazy[N<<2];
LL pre[N],a[N];
void build(int p,int l,int r)
{
	if(l==r){sum[p] = pre[l];return ;}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	sum[p] = sum[p<<1]+sum[p<<1|1];
}
void push_down(int p,int l,int r)
{
	if(l==r){lazy[p] = 0;return ;}
	int mid = (l+r)>>1;
	lazy[p<<1] += lazy[p];
	lazy[p<<1|1] +=lazy[p];
	sum[p<<1] += lazy[p]*(mid+1-l);
	sum[p<<1|1]+=lazy[p]*(r-mid);
	lazy[p] = 0;
}
void update(int p,int l,int r,int a,int b,LL dec)
{
	if(lazy[p])push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		lazy[p]+=dec;
		sum[p] = sum[p]+dec*(r-l+1);
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,dec);
	if(b>mid)update(p<<1|1,mid+1,r,a,b,dec);
	sum[p] = sum[p<<1]+sum[p<<1|1];
}
LL get_ans(int p,int l,int r,int a,int b)
{
	if(lazy[p])push_down(p,l,r);
	if(l>=a&&r<=b)
		return sum[p];
	LL ans = 0;
	int mid = (l+r)>>1;
	if(a<=mid)ans+=get_ans(p<<1,l,mid,a,b);
	if(b>mid)ans+=get_ans(p<<1|1,mid+1,r,a,b);
	//sum[p] = sum[p<<1]+sum[p<<1|1];
	return ans;
}
int main()
{
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%lld",&a[i]);
		pre[i] = pre[i-1]+a[i];
	}
	build(1,1,n);
	char ju[10];
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",ju);
		if(ju[0]=='M')
		{
			scanf("%d%d",&x,&y);
			LL dec = y-a[x];
			update(1,1,n,x,n,dec);
			a[x] = y;
		}else
		{
			scanf("%d",&x);
			printf("%lld\n",get_ans(1,1,n,1,x));
		}
	}
	return 0;
}
