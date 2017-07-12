
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
#define M 400000+5
typedef long long LL;
using namespace std;

LL tr[M],lazy[M];

inline void updata(int k)
{
	tr[k] = tr[k<<1]+tr[k<<1|1];
}

inline LL read()
{
	LL x=0ll,f=1ll;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

void down(int k,int l,int r)
{
	LL tmp = lazy[k];
	lazy[k] =0;
	if(!tmp || l==r)return;
	int mid = (l+r)>>1;
	lazy[k<<1]+=tmp;
	lazy[k<<1|1]+=tmp;
	tr[k<<1]+=(mid-l+1)*tmp;
	tr[k<<1|1]+=(r-mid)*tmp;
}

void change(int k,int l,int r,int x,int y,LL c)
{
	down(k,l,r);
	if(l==x && r==y){lazy[k]+=c;tr[k]+=(r-l+1)*c;return;}
	int mid = (l+r)>>1;
	if(y<=mid)change(k<<1,l,mid,x,y,c);
	else if(x>mid)change(k<<1|1,mid+1,r,x,y,c);
	else change(k<<1,l,mid,x,mid,c),change(k<<1|1,mid+1,r,mid+1,y,c);
	updata(k);
}

LL ask(int k,int l,int r,int x,int y)
{
	down(k,l,r);
	int mid = (l+r)>>1;
	if(l==x && r==y)return tr[k];
	if(y<=mid)return ask(k<<1,l,mid,x,y);
	else if(x>mid)return ask(k<<1|1,mid+1,r,x,y);
	else return ask(k<<1,l,mid,x,mid)+ask(k<<1|1,mid+1,r,mid+1,y);
}

int a[N];

void build(int k,int l,int r)
{
	if(l==r){tr[k] = a[l];return;}
	int mid = (l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	updata(k);
}

int main()
{
	int n = read();int Q = read();
	for(int i=1;i<=n;++i)
		a[i] = read();
	build(1,1,n);
	char ch[10];
	while(Q--)
	{
		scanf("%s",ch);
		if(ch[0] =='Q')
		{
			int x = read(),y=read();
			printf("%lld\n",ask(1,1,n,x,y));
		}
		else
		{
			int x = read(),y=read();
			LL z = read();
			change(1,1,n,x,y,z);
		}
	}	
}
