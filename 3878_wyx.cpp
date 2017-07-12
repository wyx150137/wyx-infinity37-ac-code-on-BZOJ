
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const int N = 100000+5;
const int M = N << 2;
using namespace std;

#define updata(k) tr[k].Min = min(tr[k<<1].Min,tr[k<<1|1].Min),tr[k].Max = max(tr[k<<1].Max,tr[k<<1|1].Max)

LL L,R;
int n;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct seg
{
	LL Min,Max;
	LL k, b, c;
}tr[M];

struct data
{
	LL x;
	int pos;
}a[N];

bool cmp1(const data &a,const data &b)
{
	return a.x < b.x;
}

bool cmp2(const data &a,const data &b)
{
	return a.pos < b.pos;
}

void build(int k,int l,int r)
{
	tr[k].c = 1, tr[k].k = 0 ,tr[k].b = 0;
	if(l==r)
	{
		tr[k].Min = tr[k].Max = a[l].x;
		return;
	}
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	updata(k);
}

void solve(int tmp,int l,int r,LL c,LL k,LL b)
{
	tr[tmp].Min = tr[tmp].Min * c + k * a[l].x + b;
	tr[tmp].Max = tr[tmp].Max * c + k * a[r].x + b;
	tr[tmp].c *= c,tr[tmp].k *= c,tr[tmp].b *= c;
	tr[tmp].k += k, tr[tmp].b += b;
}

void down(int k,int l,int r)
{
	int mid = (l+r) >> 1;
	solve(k<<1,l,mid,tr[k].c,tr[k].k,tr[k].b);
	solve(k<<1|1,mid+1,r,tr[k].c,tr[k].k,tr[k].b);
	tr[k].c = 1, tr[k].k = 0 , tr[k].b = 0;
}

void solve_smaller(int k,int l,int r)
{
	if(l==r)
	{
		solve(k,l,r,0,0,L);
		return ;
	}
	int mid = (l+r) >> 1;
	down(k,l,r);
	if(tr[k<<1|1].Min < L)
	{
		solve(k<<1,l,mid,0,0,L);
		solve_smaller(k<<1|1,mid+1,r);
	}
	else solve_smaller(k<<1,l,mid);
	updata(k);
}

void solve_bigger(int k,int l,int r)
{
	if(l==r)
	{
		solve(k,l,r,0,0,R);
		return ;
	}
	int mid = (l+r) >> 1;
	down(k,l,r);
	if(tr[k<<1].Max > R)
	{
		solve(k<<1|1,mid+1,r,0,0,R);
		solve_bigger(k<<1,l,mid);
	}
	else solve_bigger(k<<1|1,mid+1,r);
	updata(k);
}

void Final(int k,int l,int r)
{
	if(l==r)
	{
		a[l].x = tr[k].Max;
		return;
	}
	int mid = (l+r) >> 1;
	down(k,l,r);
	Final(k<<1,l,mid);
	Final(k<<1|1,mid+1,r);
}

struct opt
{
	char str[10];
	LL x;
}q[N];

int main()
{
	int Q = read();
	L = read(),R = read();
	for(int i=1;i<=Q;++i) scanf("%s",q[i].str),q[i].x = read();
	n = read();
	for(int i=1;i<=n;++i) a[i].x = read(), a[i].pos = i;
	sort(a+1,a+n+1,cmp1);
	build(1,1,n);
	for(int i=1;i<=Q;++i)
	{
		if(q[i].str[0] == '+') solve(1,1,n,1,0,q[i].x);
		else if(q[i].str[0] == '-') solve(1,1,n,1,0,-q[i].x);
		else if(q[i].str[0] == '*') solve(1,1,n,q[i].x,0,0);
		else solve(1,1,n,1,q[i].x,0);
		if(tr[1].Min < L) solve_smaller(1,1,n);
		if(tr[1].Max > R) solve_bigger(1,1,n);
	}
	Final(1,1,n);
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;++i)
		printf("%d\n",a[i].x);
}
