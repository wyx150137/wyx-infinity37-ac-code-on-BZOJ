
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int mx[N<<2],lmx[N<<2],rmx[N<<2];
int F[N<<2];
void Push_up(int p)
{
	lmx[p] = lmx[p<<1];
	rmx[p] = rmx[p<<1|1];
	mx[p] = max(mx[p<<1],mx[p<<1|1]);
}
int sa[N],sb[N],sc[N],a[N],b[N],c[N],pb[N],pc[N],K[N],f[N];
void update(int p,int r,int v)
{
	lmx[p] = rmx[p] = F[p] = v;
	mx[p] = v+sb[r];
}
void build(int p,int l,int r)
{
	F[p] = -1;
	if(l==r)
	{
		lmx[p] = rmx[p] = f[l];
		mx[p] = f[l]+sb[l];
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	Push_up(p);
}
void Update(int p,int l,int r,int a,int b,int v)
{
	if(l>=a&&r<=b)
	{
		if(lmx[p]<=v)return ;
		if(rmx[p]>=v){update(p,r,v);return ;}
	}
	int mid = (l+r)>>1;
	if(F[p]!=-1)
		update(p<<1,mid,F[p]),update(p<<1|1,r,F[p]),F[p]=-1;
	if(a<=mid)Update(p<<1,l,mid,a,b,v);
	if(b >mid)Update(p<<1|1,mid+1,r,a,b,v);
	Push_up(p);
}
int main()
{
	char opt[3];
	scanf("%s",opt);
	int cas,i;
	scanf("%d",&cas);
	while(cas--)
	{
		int n;
		scanf("%d",&n);
		for(i = 1;i<= n;i++)scanf("%d",&K[i]);
		for(i = 1;i<= n;i++)scanf("%d",&a[i]);
		for(i = 1;i<= n;i++)scanf("%d",&b[i]),pb[b[i]]=i;
		for(i = 1;i<= n;i++)scanf("%d",&c[i]),pc[c[i]]=i;
		for(i = 1;i<= n;i++)scanf("%d",&sa[i]),sa[i]+=sa[i-1];
		for(i = 1;i<= n;i++)scanf("%d",&sb[i]),sb[i]+=sb[i-1];
		for(i = 1;i<= n;i++)scanf("%d",&sc[i]),sc[i]+=sc[i-1];
		f[0] = sc[n];
		for(int i = 1;i<= n;i++)
			if(K[b[i]]==1)
				f[i] = min(f[i-1],sc[pc[b[i]]-1]);
			else
				f[i] = f[i-1];
		build(1,0,n);
		int ans = mx[1];
		for(int i = 1;i<= n;i++)
		{
			if(K[a[i]]==1)
			{
				Update(1,0,n,pb[a[i]],n,-1<<30);
				Update(1,0,n,0,n,sc[pc[a[i]]-1]);
			}else
				Update(1,0,n,pb[a[i]],n,sc[pc[a[i]]-1]);
			ans = max(ans,sa[i]+mx[1]);
		}
		printf("%d",ans);
		puts("");
	}
	return 0;
}
