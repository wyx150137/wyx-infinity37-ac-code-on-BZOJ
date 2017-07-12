
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int M = (500000+5) << 2;
using namespace std;

int n;

struct data
{
	int l,r;
	int sum;
}tr[M];

int lazy[M];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x= (x<<1) + (x<<3) + ch - '0' ; ch = getchar();}
	return x*f;
}

data merge(const data &a,const data &b)
{
	data tmp;
	tmp.l = a.l,tmp.r = b.r,tmp.sum = a.sum + b.sum - (a.r == b.l);
	return tmp;
}

void updata(int k)
{
	tr[k] = merge(tr[k<<1],tr[k<<1|1]);
}

void down(int k,int l,int r)
{
	int tmp = lazy[k];
	lazy[k] = 0;
	if(!tmp || l == r) return;
	lazy[k<<1] = lazy[k<<1|1] = tmp;
	tr[k<<1].sum = tr[k<<1|1].sum = 1;
	tr[k<<1].l = tr[k<<1].r = tr[k<<1|1].l = tr[k<<1|1].r = tmp;
	return;
}

void change(int k,int L,int R,int x,int y,int val)
{
	if(x <= L && R <= y)
	{
		tr[k].l = tr[k].r = lazy[k] = val;
		tr[k].sum = 1;
		return;
	}
	int mid = (L+R) >> 1;
	down(k,L,R);
	if(x <= mid)change(k<<1,L,mid,x,y,val);
	if(y > mid) change(k<<1|1,mid+1,R,x,y,val);
	updata(k);
}

data ask(int k,int L,int R,int x,int y)
{
	if(L == x && R == y) return tr[k];
	down(k,L,R);
	int mid = (L+R) >> 1;
	if(y <= mid) return ask(k<<1,L,mid,x,y);
	else if(x > mid) return ask(k<<1|1,mid+1,R,x,y);
	else return merge(ask(k<<1,L,mid,x,mid),ask(k<<1|1,mid+1,R,mid+1,y));
}

void build(int k,int L,int R)
{
	if(L==R)
	{
		tr[k].l = tr[k].r = read();
		tr[k].sum = 1;
		return;
	}
	int mid = (L+R) >> 1;
	build(k<<1,L,mid);
	build(k<<1|1,mid+1,R);
	updata(k);
}

bool rev;
int delta;

inline void calc(int &x,int &y)
{
	if(rev)
	{
		x = ((n + 2 - delta - x) % n + n )%n,
		y = ((n + 2 - delta - y) % n + n )%n;
		swap(x,y);
	}
	else
	{
		x = (( x - delta) % n + n)% n,
		y = (( y - delta) % n + n)% n;
	}
	if(x == 0) x = n;
	if(y == 0) y = n;
}

int main()
{
	n = read();
	scanf("%*d");
	build(1,1,n);
	int Q = read();
	char str[10];
	data tmp,now;
	while(Q--)
	{
		scanf("%s",str);
		if(strlen(str) == 1)
		{
			if(str[0] == 'R')
			{
				int x = read();
				if(rev)
					delta=(delta+n-x)%n;
				else delta=(delta+x)%n;
			}
			else if(str[0] == 'F')
				rev ^= 1;
			else if(str[0]=='S')
			{
				int x = read(), y = read(),tmp1,tmp2;
				calc(x,y);
				tmp = ask(1,1,n,x,x);
				tmp1 = tmp.l;
				tmp = ask(1,1,n,y,y);
				tmp2 = tmp.l;
				change(1,1,n,x,x,tmp2);
				change(1,1,n,y,y,tmp1);
			}
			else if(str[0]=='P')
			{
				int x = read(), y = read(), z = read();
				calc(x,y);
				if (x <= y)
					change(1,1,n,x,y,z);
				else change(1,1,n,x,n,z),change(1,1,n,1,y,z);
			}
			else
			{
				int tmp1 = tr[1].sum;
				if(tr[1].l == tr[1].r) tmp1 --;
				if(tmp1 == 0) tmp1 = 1;
				printf("%d\n",tmp1);
			}
		}
		else
		{
			int x = read(), y = read();
			calc(x,y);
			if(x <= y) printf("%d\n",ask(1,1,n,x,y).sum);
			else 
			{
				tmp = ask(1,1,n,x,n);
				now = ask(1,1,n,1,y);
				printf("%d\n",tmp.sum+now.sum-(tmp.r == now.l));
			}
		}
	}
}
