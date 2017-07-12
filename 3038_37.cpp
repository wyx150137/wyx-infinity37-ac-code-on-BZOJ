
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
typedef long long LL;
LL sum[N<<2];
LL a[N];
int fa[N];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x] = x;
	else return fa[x] = getfa(fa[x]);
}
void update(int p,int l,int r,int x,LL c)
{
	if(l==r)
		{sum[p] = c;return ;}
	int mid = (l+r)>>1;
	if(x<=mid)update(p<<1,l,mid,x,c);
	else update(p<<1|1,mid+1,r,x,c);
	sum[p] = sum[p<<1]+sum[p<<1|1];
}
LL getans(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)
		return sum[p];
	LL ans = 0;
	int mid = (l+r)>>1;
	if(a<=mid)ans = ans+getans(p<<1,l,mid,a,b);
	if(b>mid)ans = ans+getans(p<<1|1,mid+1,r,a,b);
	return ans;
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		sum[p] = a[l];
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	sum[p] = sum[p<<1]+sum[p<<1|1];
}
int main()
{
	int n,m;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%lld",&a[i]);
	build(1,1,n);
	for(int i = 1;i<= n;i++)
	{
		if(a[i]>1)fa[i] = i;
		else fa[i] = i+1;
	}
	fa[n+1] = n+1;
	int x,y,opt;
	scanf("%d",&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&opt,&x,&y);
		if(x>y)swap(x,y);
		if(opt==0)
		{
			for(int t = getfa(x);t<= y;t= getfa(t))
			{
				a[t] = sqrt(a[t]);
				update(1,1,n,t,a[t]);
				if(a[t]<=1)
					fa[t] = t+1;
				t = t+1;
			}
		}else
			printf("%lld\n",getans(1,1,n,x,y));
	}
	return 0;
}
