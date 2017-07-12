
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
int n,m,s,t,a[N];
char opt[N];
struct Seg
{
	int x,y,z,s1,s2,t1,t2;
	void init(int i)
	{
		x = y = i;z = 1;
		s1 = t1 = i?-1:0;
		s2 = t2 = -1;
	}
	friend Seg operator +(const Seg &a,const Seg &b)
	{
		Seg res={a.x,b.y,a.z+b.z};
		int j = (a.y||b.x)?-1:0;
		if(b.s1==j)res.s1=a.s1,res.s2=a.s2;
		else 
			res.s1 = b.s1+a.z,res.s2=(b.s2!=j)?b.s2+a.z:a.s1;
		if(a.t1==j)res.t1=b.t1,res.t2=b.t2;
		else
			res.t1 = a.t1+b.z,res.t2=(a.t2!=j)?a.t2+b.z:b.t1;
		return res;
	}
}tr[N<<3];
int cal(int i)
{
	int s = i%n,t=(s+n-1)%n;
	if(opt[s]=='+')return (a[s]+a[t])%10;
	else return a[s]*a[t]%10;
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		tr[p].init(cal(l));
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	tr[p]=tr[p<<1]+tr[p<<1|1];
}
void update(int p,int l,int r,int pos,int val)
{
	if(l==r)
	{
		tr[p].init(val);
		return ;
	}
	int mid = (l+r)>>1;
	if(pos<=mid)update(p<<1,l,mid,pos,val);
	else update(p<<1|1,mid+1,r,pos,val);
	tr[p] = tr[p<<1]+tr[p<<1|1];
}
Seg getans(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return tr[p];
	int mid = (l+r)>>1;
	if(b<=mid)return getans(p<<1,l,mid,a,b);
	else if(a>mid)return getans(p<<1|1,mid+1,r,a,b);
	else return getans(p<<1,l,mid,a,b)+getans(p<<1|1,mid+1,r,a,b);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 0;i<n;i++)
		scanf("%d %c",&a[i],&opt[i]);
	build(1,0,2*n-1);
	int s,t;
	while(m--)
	{
		scanf("%d%d",&s,&t);
		if(s==1)
		{
			scanf("%d %c",&a[t],&opt[t]);
			update(1,0,2*n-1,t,cal(t));
			update(1,0,2*n-1,t+n,cal(t));
			update(1,0,2*n-1,t+1,cal(t+1));
			if(t!=n-1)
				update(1,0,2*n-1,t+n+1,cal(t+1));
		}else
		{
			update(1,0,2*n-1,t,a[t]);
			Seg a=getans(1,0,2*n-1,t,t+(n-1)/2);
			Seg b=getans(1,0,2*n-1,t+(n+1)/2,t+n-1);
			if(~b.t1&&(a.x||b.t1))++b.t1;
            if(~b.t2&&(a.x||b.t2))++b.t2;
            printf("%d\n",a.y||b.x?max(a.s1,b.t1):max(max(a.s2,b.t2),min(a.s1,b.t1)));
            update(1,0,2*n-1,t,cal(t));
		}
	}
	return 0;
}
