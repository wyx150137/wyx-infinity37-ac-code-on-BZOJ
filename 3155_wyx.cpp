
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 100000+5
#define M 400000+5

long long tr[M];
long long lazy[M];
long long sum[N];

inline void updata(int k)
{
	tr[k] = tr[k<<1]+tr[k<<1|1];
}

void build(int k,int l,int r)
{
	if(l==r){tr[k]=sum[l];return;}
	int mid = (l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	updata(k);
}

inline void down(int k,int l,int r)
{
	long long tmp = lazy[k];lazy[k] = 0;
	if(l==r || !tmp)return;
	int mid = (l+r)>>1;
	lazy[k<<1]+=tmp;
	lazy[k<<1|1]+=tmp;
	tr[k<<1]+=(mid-l+1)*tmp;
	tr[k<<1|1]+=(r-mid)*tmp;
}

void change(int k,int l,int r,int x,int y,long long c)
{
	down(k,l,r);
	if(l==x && r==y){
		tr[k]+=(r-l+1)*c;
		lazy[k]+=c;
		return;		
	}
	int mid = (l+r)>>1;
	if(y<=mid)change(k<<1,l,mid,x,y,c);
	else if(x>mid)change(k<<1|1,mid+1,r,x,y,c);
	else change(k<<1,l,mid,x,mid,c),change(k<<1|1,mid+1,r,mid+1,y,c);
	updata(k);
}

long long ask(int k,int l,int r,int x,int y)
{
	down(k,l,r);
	if(l==x && r==y)return tr[k];
	int mid = (l+r)>>1;
	if(y<=mid)return ask(k<<1,l,mid,x,y);
	else if(l>mid)return ask(k<<1|1,mid+1,r,x,y);
	else return ask(k<<1,l,mid,x,mid)+ask(k<<1|1,mid+1,r,mid+1,y);
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}
long long a[N];

int main()
{
	int n = read(),m=read();
	for(int i=1;i<=n;++i)a[i] = read(),sum[i]+=sum[i-1]+a[i];
	build(1,1,n);
	for(int i=1;i<=m;++i)
	{
		char ch[10];
		scanf("%s",ch);
		if(ch [0]== 'Q')
		{
			int x = read();
			printf("%lld\n",ask(1,1,n,1,x));
		}
		else
		{
			int pos = read(),x=read();
			int tmp = x - a[pos];
			change(1,1,n,pos,n,tmp);
			a[pos] = x;
		}
	}
}
