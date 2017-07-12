
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 50000+5;
const int M = N << 2;

int cnt = 0;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1) + (x<<3) + ch - '0';ch = getchar();}
	return x*f;
}

struct Line 
{
	double k,b;
	int id;
	Line () {}
	Line (int x1,int y1,int x2,int y2,int I)
	:id(I){
		if(x1 == x2) k=0,b=max(y1,y2);
		else k = double (y2-y1)/(x2-x1),b = (double)y2 - k*x2;
	}
	double calc(double x )
	{
		return k*x+b;
	}
}tr[M];

bool cmp(Line &A,Line &B,double x)
{
	if(!A.id) return true;
	double tmp1 = A.calc(x),tmp2 = B.calc(x);
	return tmp1 != tmp2 ? tmp1 < tmp2 : A.id < B.id;
}

Line ask(int k,int l,int r,int pos)
{
	if(l==r)return tr[k];
	int mid = (l+r) >>1;
	Line tmp;
	if(pos <= mid)tmp = ask(k<<1,l,mid,pos);
	else tmp = ask(k<<1|1,mid+1,r,pos);
	return cmp(tr[k],tmp,pos) ? tmp : tr[k];
}

void solve(int k,int l,int r,Line x)
{
	if(!tr[k].id) tr[k] = x;
	if(cmp(tr[k],x,l)) swap(tr[k],x);
	if(l==r || tr[k].k == x.k) return;
	int mid = (l+r)>>1;
	double delta = (tr[k].b-x.b)/(x.k-tr[k].k);
	if(delta < l || delta > r) return;
	if(delta <= mid) solve(k<<1,l,mid,tr[k]),tr[k] = x;
	else solve(k<<1|1,mid+1,r,x);
}

void change(int k,int l,int r,int x,int y,Line tmp)
{
	if(x <= l && r <= y) {solve(k,l,r,tmp);return;}
	int mid = (l+r)>>1;
	if(x <= mid)change(k<<1,l,mid,x,y,tmp);
	if(y > mid) change(k<<1|1,mid+1,r,x,y,tmp);
}

const int p1 = 39989;
const int p2 = 1000000000;

int main()
{
	int q = read();
	const int n = 50000;
	int las = 0;
	while(q--)
	{
		int opt = read();
		if(opt == 0)
		{
			int x = read();
			x = (x+las-1) %p1+1;
			las = ask(1,1,n,x).id;
			printf("%d\n",las);
		}
		else
		{
			int x0 = read(),y0=read(),x1 = read(),y1 = read();
			x0=(x0+las-1)%p1+1;y0=(y0+las-1)%p2+1;x1=(x1+las-1)%p1+1;y1=(y1+las-1)%p2+1;
			if(x0 > x1) swap(x0,x1),swap(y0,y1);
			change(1,1,n,x0,x1,Line(x0,y0,x1,y1,++cnt));
		}
	}
}
