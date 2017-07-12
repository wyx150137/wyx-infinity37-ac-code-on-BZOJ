
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int Mn = 86399+5;
const int N = 1e4+5;
const LL INF = 1e18;
struct C
{int s,t,c;}cl[N];
bool cmp(C a,C b)
{
	return a.s<b.s;
}
LL f[Mn],t[Mn<<2];
void build(int p,int l,int r)
{
	t[p] = INF;
	if(l==r)
	{
		f[l] = INF;
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
void push_down(int p,int l,int r)
{
	if(t[p]==INF)return ;
	if(l==r){f[l] = min(f[l],t[p]);t[p] = INF;return ;}
	t[p<<1] = min(t[p],t[p<<1]);
	t[p<<1|1] = min(t[p],t[p<<1|1]);
	t[p] = INF;
}
void update(int p,int l,int r,int a,int b,LL c)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		t[p] = min(t[p],c);
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,c);
	if(b>mid)update(p<<1|1,mid+1,r,a,b,c);
	return ;
}
LL getans(int p,int l,int r,int x)
{
	push_down(p,l,r);
	if(x<=0)return 0;
	if(l==r)return f[l];
	int mid = (l+r)>>1;
	if(x<=mid)return getans(p<<1,l,mid,x);
	else return getans(p<<1|1,mid+1,r,x);
}
int main()
{
	int n,m,e;
	scanf("%d%d%d",&n,&m,&e);
	m++,e++;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d%d",&cl[i].s,&cl[i].t,&cl[i].c);
		cl[i].s++;cl[i].t++;
	}
	sort(cl+1,cl+n+1,cmp);
	build(1,1,e);
	update(1,1,e,1,m,0);
	for(int i = 1;i<= n;i++)
	{
		int s = cl[i].s,t = cl[i].t,v = cl[i].c;
		LL tmp = getans(1,1,e,s-1);
		if(tmp>=INF){printf("-1\n");return 0;}
		update(1,1,e,s,t,tmp+v);
	}
	printf("%lld\n",getans(1,1,e,e));
	return 0;
}
