
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
typedef long long ll;
using namespace std;
const int N = 5e4+5;
const int M = 2e7+5;
int root[N<<2];
int ls[M],rs[M],lazy[M];
ll sum[M];
int tot,n,m;
void push_down(int p,int l,int r)
{
	if(!lazy[p]||l==r)return ;
	if(!ls[p])ls[p] = ++tot;
	if(!rs[p])rs[p] = ++tot;
	lazy[ls[p]]+=lazy[p];
	lazy[rs[p]]+=lazy[p];
	int mid = (l+r)>>1;
	sum[ls[p]]+=(mid-l+1)*lazy[p];
	sum[rs[p]]+=(r-mid)*lazy[p];
	lazy[p] = 0;
}
void update(int &p,int l,int r,int a,int b)
{
	if(!p)p = ++tot;
	push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		sum[p]+=r-l+1;
		lazy[p]++;
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(ls[p],l,mid,a,b);
	if(b >mid)update(rs[p],mid+1,r,a,b);
	sum[p] = sum[ls[p]]+sum[rs[p]];
}
ll getans(int p,int l,int r,int a,int b)
{
	if(!p)return 0;
	push_down(p,l,r);
	if(l>=a&&r<=b)return sum[p];
	int mid = (l+r)>>1;ll ans = 0;
	if(a<=mid)ans+=getans(ls[p],l,mid,a,b);
	if(b >mid)ans+=getans(rs[p],mid+1,r,a,b);
	return ans;
}
void insert(int a,int b,int c)
{
	int l = 1,r = n,p = 1;
	while(l!=r)
	{
		int mid=(l+r)>>1;
		update(root[p],1,n,a,b);
		if(c<=mid)r = mid,p = p<<1;
		else l = mid+1,p = p<<1|1;
	}
	update(root[p],1,n,a,b);
}
int solve(int a,int b,ll c)
{
	int l = 1,r = n,p = 1;
	while(l!=r)
	{
		int mid = (l+r)>>1;
		ll tmp = getans(root[p<<1],1,n,a,b);
		if(tmp>=c)r = mid,p = p<<1;
		else l = mid+1,p = p<<1|1,c-=tmp;
	}
	return l;
}
int main()
{
	scanf("%d%d",&n,&m);
	int opt,a,b,c;
	for(int i= 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&opt,&a,&b,&c);
		if(opt==1)
			insert(a,b,n-c+1);
		else
			printf("%d\n",n-solve(a,b,c)+1);
	}
	return 0;
}
