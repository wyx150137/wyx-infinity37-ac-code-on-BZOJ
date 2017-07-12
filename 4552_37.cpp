
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int sum[N<<2],cov[N<<2];
int a[N];
int MID;
void build(int p,int l,int r)
{
	cov[p] = -1;
	if(l==r)
	{
		sum[p] = a[l]>=MID;
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	sum[p] = sum[p<<1]+sum[p<<1|1];
}
inline void Push_down(int p,int l,int r)
{
	if(cov[p]==-1)return ;
	int mid = (l+r)>>1;
	if(cov[p]==1)
	{
		sum[p<<1] = mid-l+1;sum[p<<1|1] = r-mid;
		cov[p<<1] = cov[p],cov[p<<1|1] = cov[p];
	}else
	{
		sum[p<<1] = sum[p<<1|1] = cov[p<<1] = cov[p<<1|1] = 0;
	}
	cov[p] = -1;
}
void Update(int p,int l,int r,int a,int b,int v)
{
	if(a>b)return ;
	if(l>=a&&r<=b)
	{
		sum[p] = (r-l+1)*v;
		cov[p] = v;
		return ;
	}
	Push_down(p,l,r);
	int mid = (l+r)>>1;
	if(a<=mid)Update(p<<1,l,mid,a,b,v);
	if(b >mid)Update(p<<1|1,mid+1,r,a,b,v);
	sum[p] = sum[p<<1]+sum[p<<1|1];
}
int Getsum(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return sum[p];
	Push_down(p,l,r);
	int mid = (l+r)>>1,ans = 0;
	if(a<=mid)ans+=Getsum(p<<1,l,mid,a,b);
	if(b >mid)ans+=Getsum(p<<1|1,mid+1,r,a,b);
	return ans;
}
int opt[N],l[N],r[N];
int n,m,q;
bool check(int mid)
{
	MID = mid;
	build(1,1,n);
	for(int i = 1;i<= m;i++)
	{
		int tmp = Getsum(1,1,n,l[i],r[i]);
		int lth = r[i]-l[i]+1;
		if(!opt[i])
		{
			Update(1,1,n,l[i],l[i]+lth-tmp-1,0);
			Update(1,1,n,l[i]+lth-tmp,r[i],1);
		}else
		{
			Update(1,1,n,l[i],l[i]+tmp-1,1);
			Update(1,1,n,l[i]+tmp,r[i],0);
		}
	}
	return Getsum(1,1,n,q,q)==1;
}
int main()
{
	//freopen("x.in","r",stdin);
	//freopen("x.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= m;i++)
		scanf("%d%d%d",&opt[i],&l[i],&r[i]);
	scanf("%d",&q);
	int L = 1,R = n+1;
	while(L<R)
	{
		int mid = (L+R)>>1;
		if(check(mid))L = mid+1;
		else R = mid;
	}
	printf("%d\n",L-1);
	return 0;
}
