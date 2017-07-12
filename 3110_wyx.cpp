
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const int N = 50000+5;
const int M = N << 2;
const int inf = 0x7fffffff;
#define updata(k) tr[k] = tr[k<<1] + tr[k<<1|1]
using namespace std;

LL tr[M],add[M];
bool lazy[M];
int n,m;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void down(int k,int l,int r)
{
	if(l==r) return;
	if(lazy[k])
	{
		lazy[k] = 0;
		tr[k<<1] = tr[k<<1|1] = add[k<<1] = add[k<<1|1] = 0;
		lazy[k<<1] = lazy[k<<1|1] = 1; 
	}
	if(add[k])
	{
		LL tmp = add[k]; add[k] = 0;
		int mid = (l+r) >> 1; 
		tr[k<<1] += (mid - l + 1) * tmp;
		tr[k<<1|1] += (r-mid) * tmp;
		add[k<<1] += tmp ;add[k<<1|1]  += tmp;
	}
}

void change(int k,int l,int r,int x,int y)
{
	down(k,l,r);
	if(l==x && r==y)
	{
		tr[k] += r-l+1;
		add[k] ++;
		return ;
	}
	int mid = (l+r) >> 1;
	if(y <= mid) change(k<<1,l,mid,x,y);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y);
	else change(k<<1,l,mid,x,mid), change(k<<1|1,mid+1,r,mid+1,y);
	updata(k);
}

LL ask(int k,int l,int r,int x,int y)
{
	down(k,l,r);
	if(l==x && r==y)return tr[k];
	int mid = (l+r) >> 1;
	if(y <= mid) return ask(k<<1,l,mid,x,y);
	else if(x > mid) return ask(k<<1|1,mid+1,r,x,y);
	else return ask(k<<1,l,mid,x,mid) + ask(k<<1|1,mid+1,r,mid+1,y);
}

struct data
{
	int opt,l,r,v,k,times;
	bool operator < (const data &z)const
	{
		return k ^ z.k ? k < z.k : times < z.times;
	}
}q[N];

int ans[N];

void solve(LL L,LL R,int l,int r)
{
	if(l > r) return;
	if(L == R)
	{
		for(int i=l;i<=r;++i)
			if(q[i].opt == 2)
				ans[q[i].times] = L;
		return;
	}
	tr[1] = add[1] = 0 , lazy[1] = 1;
	int mid = (L+R) >> 1, tt = l-1;
	for(int i=l;i<=r;++i)
	{
		if(q[i].opt == 1)
		{
			if(q[i].v > mid)
				change(1,1,n,q[i].l,q[i].r),q[i].k = 1;
			else
				tt ++ , q[i].k = 0;
		}
		else
		{
			LL tmp = ask(1,1,n,q[i].l,q[i].r);
			if(q[i].v <= tmp) q[i].k = 1;
			else tt ++, q[i].k = 0,q[i].v -= tmp;
		}
	}
	sort(q+l,q+r+1);
	solve(L,mid,l,tt);
	solve(mid+1,R,tt+1,r);
}

int main()
{
	int Min = inf, Max = -inf;
	n = read(), m = read();
	for(int i=1;i<=m;++i)
	{
		q[i].opt = read(), q[i].l = read(), q[i].r = read(), q[i].v = read();
		q[i].times = i; 
		if(q[i].opt == 1)
		{
			Min = min(Min,q[i].v);
			Max = max(Max,q[i].v);
		}
	}
	memset(ans,-1,sizeof ans);
	solve(Min,Max,1,m);
	for(int i=1;i<=m;++i)
		if(~ans[i])
			printf("%d\n",ans[i]);
}

