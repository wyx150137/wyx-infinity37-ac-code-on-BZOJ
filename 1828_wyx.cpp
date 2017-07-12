
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
#define M 400000+5
using namespace std;

struct tt
{
	int x,y;
	bool operator<(const tt &z)const
	{
		return x < z.x;
	}
}q[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int a[N];
int tr[M];
int lazy[M];

inline void updata(int k)
{
	tr[k] = min(tr[k<<1],tr[k<<1|1]);
}

inline void down(int k,int l,int r)
{
	int tmp = lazy[k];lazy[k] = 0;
	if(l==r || !tmp)return;
	lazy[k<<1] += tmp;
	lazy[k<<1|1]+=tmp;
	tr[k<<1] -= tmp;
	tr[k<<1|1] -= tmp; 
}

void build(int k,int l,int r)
{
	if(l==r){tr[k] = a[l];return;}
	int mid = (l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	updata(k);
}

void change(int k,int l,int r,int x,int y,int c)
{
	down(k,l,r);
	if(l==x && r==y){lazy[k]+=c;tr[k]-=c;return;}
	int mid = (l+r)>>1;
	if(y<=mid)change(k<<1,l,mid,x,y,c);
	else if(x>mid)change(k<<1|1,mid+1,r,x,y,c);
	else change(k<<1,l,mid,x,mid,c),change(k<<1|1,mid+1,r,mid+1,y,c);
	updata(k);
}

int ask(int k,int l,int r,int x,int y)
{
	down(k,l,r);
	if(l==x && r==y)return tr[k];
	int mid = (l+r)>>1;
	if(y<=mid)return ask(k<<1,l,mid,x,y);
	else if(x>mid)return ask(k<<1|1,mid+1,r,x,y);
	else return min(ask(k<<1,l,mid,x,mid),ask(k<<1|1,mid+1,r,mid+1,y));
}

int main()
{
	int n = read(),m=read();
	for(int i=1;i<=n;++i)
		a[i] = read();
	build(1,1,n);
	int ans = 0;
	for(int i=1;i<=m;++i)
		q[i].x=read(),q[i].y=read();
	sort(q+1,q+m+1);
	for(int i=m;i>=1;--i)
	{
		int tt = ask(1,1,n,q[i].x,q[i].y);
		if(tt > 0)
			change(1,1,n,q[i].x,q[i].y,1),ans ++;
	}
	cout<<ans;
}
