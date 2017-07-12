
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100005;
const int M = 100005;
int mod;
int mul_tag[N<<2],add_tag[N<<2];
int sum[N<<2];
void build(int p,int l,int r)
{
	mul_tag[p] = 1,add_tag[p] = 0;
	if(l==r)
	{
		scanf("%d",&sum[p]);
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	sum[p] = (sum[p<<1]+sum[p<<1|1])%mod;
}
void push_down(int p,int l,int r)
{
	if(l==r||(mul_tag[p]==1&&add_tag[p]==0))return ;
	int mid = (l+r)>>1;
	sum[p<<1] = ((LL)sum[p<<1]*mul_tag[p]%mod+(LL)add_tag[p]*(mid-l+1)%mod)%mod;
	sum[p<<1|1] = ((LL)sum[p<<1|1]*mul_tag[p]%mod+(LL)add_tag[p]*(r-mid)%mod)%mod;
	mul_tag[p<<1] = (LL)mul_tag[p<<1]*mul_tag[p]%mod;
	mul_tag[p<<1|1] = (LL)mul_tag[p<<1|1]*mul_tag[p]%mod;
	add_tag[p<<1] = ((LL)add_tag[p<<1]*mul_tag[p]+add_tag[p])%mod;
	add_tag[p<<1|1] = ((LL)add_tag[p<<1|1]*mul_tag[p]+add_tag[p])%mod;
	mul_tag[p] = 1;
	add_tag[p] = 0;	
}
void update(int p,int l,int r,int a,int b,int c,int opt)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		if(opt)
			{add_tag[p]+=c;sum[p] = (sum[p]+(LL)c*(r-l+1)%mod)%mod;}
		else
		{
			add_tag[p] = (LL)add_tag[p]*c%mod;
			mul_tag[p] = (LL)mul_tag[p]*c%mod;
			sum[p] = (LL)sum[p]*c%mod;
		}
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,c,opt);
	if(b>mid)update(p<<1|1,mid+1,r,a,b,c,opt);
	sum[p] = (sum[p<<1]+sum[p<<1|1])%mod;
}
int getans(int p,int l,int r,int a,int b)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
		return sum[p];
	int mid = (l+r)>>1;
	int ans = 0;
	if(a<=mid)ans = (ans+getans(p<<1,l,mid,a,b))%mod;
	if(b>mid)ans = (ans+getans(p<<1|1,mid+1,r,a,b))%mod;
	return ans;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&mod);
	build(1,1,n);
	int opt,l,r,c;
	scanf("%d",&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&opt);
		if(opt<=2)
		{
			opt--;
			scanf("%d%d%d",&l,&r,&c);
			update(1,1,n,l,r,c,opt);
		}else
		{
			scanf("%d%d",&l,&r);
			printf("%d\n",getans(1,1,n,l,r));
		}
	}
	return 0;
}
