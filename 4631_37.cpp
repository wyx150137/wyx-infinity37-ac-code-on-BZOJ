
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int pre[N],nxt[N];
struct C
{int l,r,i;}cld[N];
bool operator <(const C &a,const C &b)
{return a.r<b.r;}
int tr[N<<2],a[N],c[N],n,m;
inline int Push_up(int x,int y)
{
	return cld[x].l>cld[y].l?x:y;
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		tr[p] = l;
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);build(p<<1|1,mid+1,r);
	tr[p] = Push_up(tr[p<<1],tr[p<<1|1]);
}
void update(int p,int l,int r,int pos)
{
	if(l==r){tr[p]=0;return ;}
	int mid = (l+r)>>1;
	if(pos<=mid)update(p<<1,l,mid,pos);
	else update(p<<1|1,mid+1,r,pos);
	tr[p] = Push_up(tr[p<<1],tr[p<<1|1]);
}
int getans(int p,int l,int r,int d)
{
	if(r<=d)return tr[p];
	int mid = (l+r)>>1,t = getans(p<<1,l,mid,d);
	if(d>mid)t = Push_up(t,getans(p<<1|1,mid+1,r,d));
	return t;
}
int ans = 0;
void Delete(int x)
{
	a[x]--;if(a[x])return ;
	int l = pre[x],r = nxt[x];
	pre[r] = l,nxt[l] = r;r = c[r-1];
	if(!r)return ;
	while(true)
	{
		int t = getans(1,1,m,r);
		if(cld[t].l<=l)return ;
		ans++;update(1,1,m,t);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]),pre[i]=i-1,nxt[i]=i+1;
	int lastans = 0;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&cld[i].l,&cld[i].r);
		cld[i].i=i;
	}
	sort(cld+1,cld+m+1);
	for(int i = 1;i<= m;i++)
		if(cld[i].r!=cld[i-1].r)
			for(int j = cld[i-1].r;j<cld[i].r;j++)c[j] = i-1;
	for(int i = cld[m].r;i<= n;i++)c[i]=m;
	build(1,1,m);
	int Q,x;
	scanf("%d",&Q);
	while(Q--)
	{
		scanf("%d",&x);x = (x+ans-1)%n+1;
		Delete(x);printf("%d\n",ans);
	}
	return 0;
}
