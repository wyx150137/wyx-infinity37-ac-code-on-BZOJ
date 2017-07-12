
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define inf 10000000000
using namespace std;
inline ll read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,bg,ed;
struct seg{int l,r;ll tag,mn;}t[400005];
struct data{int t1,t2,c;}a[10005];
inline bool operator<(data a,data b)
{
	return a.t1<b.t1;
}
void pushdown(int k)
{
	if(t[k].l==t[k].r)return;
    ll tag=t[k].tag;t[k].tag=inf;
	if(tag!=inf)
	{
		t[k<<1].tag=min(t[k<<1].tag,tag);
		t[k<<1|1].tag=min(t[k<<1|1].tag,tag);
		t[k<<1].mn=min(t[k<<1].mn,tag);
		t[k<<1|1].mn=min(t[k<<1|1].mn,tag);
	}
}
void build(int k,int l,int r)
{
	t[k].l=l;t[k].r=r;t[k].mn=inf;t[k].tag=inf;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
ll query(int k,int x)
{
	pushdown(k);
	if(x<bg)return 0;
	int l=t[k].l,r=t[k].r;
	if(l==r)return t[k].mn;
	int mid=(l+r)>>1;
	if(x<=mid)return query(k<<1,x);
	else return query(k<<1|1,x);
}
void update(int k,int x,int y,ll val)
{
	pushdown(k);
	int l=t[k].l,r=t[k].r;
	if(x==l&&y==r)
	{
		t[k].tag=val;
		t[k].mn=min(t[k].mn,val);
		return;
	}
	int mid=(l+r)>>1;
	if(y<=mid)update(k<<1,x,y,val);
	else if(x>mid)update(k<<1|1,x,y,val);
	else 
	{
		update(k<<1,x,mid,val);
		update(k<<1|1,mid+1,y,val);
	}
}
int main()
{
	n=read();bg=read();ed=read();
    build(1,bg,ed);
	for(int i=1;i<=n;i++)
		a[i].t1=read(),a[i].t2=read(),a[i].c=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		int t1=a[i].t1,t2=a[i].t2,c=a[i].c;
		ll tmp=query(1,t1-1);
		if(tmp==inf){puts("-1");return 0;}
		update(1,t1,t2,tmp+c);
	}
	ll ans=query(1,ed);
	if(ans<inf)printf("%lld",ans);
	else puts("-1");
	return 0;
}
