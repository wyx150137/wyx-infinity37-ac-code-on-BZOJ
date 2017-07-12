
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 40005;
typedef long long LL;
struct L
{int pos,h,f;}line[N<<1];
int cnt,id[N],x[N],y[N],v[N],tp[N];
bool cmp(L a,L b)
{
	return a.pos<b.pos;
}
bool cmi(int a,int b)
{
	return v[a]<v[b];
}
int sum[N<<2],lazy[N<<2];
void push_down(int p,int l,int r)
{
	if(!lazy[p]||l==r)return ;
	int mid = (l+r)>>1;
	lazy[p<<1]+=lazy[p];
	lazy[p<<1|1]+=lazy[p];
	sum[p<<1]+=lazy[p]*(mid-l+1);
	sum[p<<1|1]+=lazy[p]*(r-mid);
	lazy[p] = 0;
}
void update(int p,int l,int r,int a,int b,int c)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		sum[p]+=(r-l+1)*c;
		lazy[p]+=c;
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,c);
	if(b>mid)update(p<<1|1,mid+1,r,a,b,c);
	sum[p] = sum[p<<1]+sum[p<<1|1];
}
int getans(int p,int l,int r)
{
	push_down(p,l,r);
	if(l==r)
	{
		if(sum[p])return l;
		else return l-1;
	}
	int mid = (l+r)>>1;
	if(!sum[p<<1|1])return getans(p<<1,l,mid);
	else return getans(p<<1|1,mid+1,r);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i= 1;i<= n;i++)
	{
		scanf("%d%d%d",&x[i],&y[i],&v[i]);
		id[i] = i;
	}
	sort(id+1,id+n+1,cmi);
	for(int i = 1;i<= n;i++)
		tp[id[i]] = i;
	for(int i = 1;i<= n;i++)
	{
		line[++cnt].pos = x[i];line[cnt].h = tp[i];line[cnt].f = 1;
		line[++cnt].pos = y[i],line[cnt].h = tp[i];line[cnt].f =-1;
	}
	sort(line+1,line+cnt+1,cmp);
	int last = 0;
	LL ans = 0;
	for(int i = 1;i<= cnt;i++)
	{
		ans+=(LL)v[id[last]]*(line[i].pos-line[i-1].pos);
		update(1,1,n,1,line[i].h,line[i].f);
		last = getans(1,1,n);
	}
	printf("%lld\n",ans);
	return 0;
}
