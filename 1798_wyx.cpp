
#include <stdio.h>
#include <string.h>

#include <iostream>

#include <algorithm>

using namespace std;
#define N 100000+5
#define M 400000+5

typedef long long LL;



inline int read()

{

	int x=0,f=1;char ch = getchar();

	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}

	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}

	return x*f;

}


struct seg
{
	LL addlazy,mullazy;
	LL mn;
}tr[M];

LL a[N],p;

inline void updata(int k)
{
	tr[k].mn = (tr[k<<1].mn + tr[k<<1|1].mn)%p;
}

void build(int k,int l,int r)
{
	tr[k].addlazy = 0, tr[k].mullazy = 1;
	if(l==r){tr[k].mn = a[l];return;}
	int mid = (l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	updata(k);
}

inline void down(int k,int l,int r)
{
	if(l==r)return;
	tr[k<<1].addlazy = (tr[k<<1].addlazy * tr[k].mullazy + tr[k].addlazy)%p;
	tr[k<<1|1].addlazy = (tr[k<<1|1].addlazy * tr[k].mullazy + tr[k].addlazy)%p;
	tr[k<<1].mullazy = (tr[k<<1].mullazy * tr[k].mullazy)%p;
	tr[k<<1|1].mullazy = (tr[k<<1|1].mullazy * tr[k].mullazy)%p;
	int mid = (l+r)>>1;
	tr[k<<1].mn = (tr[k<<1].mn * tr[k].mullazy + tr[k].addlazy * (mid-l+1))%p;
	tr[k<<1|1].mn = (tr[k<<1|1].mn * tr[k].mullazy + tr[k].addlazy * (r-mid))%p;
	tr[k].addlazy = 0 ,tr[k].mullazy = 1;
}

void change(int k,int l,int r,int x,int y,int op,LL c)
{
	down(k,l,r);
	if(l==x && r==y)
	{	
		if(op == 0)
		{
			(tr[k].addlazy += c) %= p;
			(tr[k].mn += (r-l+1)*c) %= p ;
		}
		else
		{
			tr[k].addlazy = (tr[k].addlazy * c)%p;
			tr[k].mullazy = (tr[k].mullazy * c)%p;
			tr[k].mn = (tr[k].mn * c)%p;
		}
		return;
	}
	int mid = (l+r)>>1;
	if(y<=mid)
		change(k<<1,l,mid,x,y,op,c);
	else if(x>mid)
		change(k<<1|1,mid+1,r,x,y,op,c);
	else
		change(k<<1,l,mid,x,mid,op,c),change(k<<1|1,mid+1,r,mid+1,y,op,c);
	updata(k);
}

LL ask(int k,int l,int r,int x,int y)
{
	down(k,l,r);
	if( l==x && r==y )
		return tr[k].mn;
	int mid = (l+r)>>1;
	if(y<=mid)
		return ask(k<<1,l,mid,x,y)%p;
	else if(x>mid)
		return ask(k<<1|1,mid+1,r,x,y)%p;
	else return (ask(k<<1,l,mid,x,mid)+ask(k<<1|1,mid+1,r,mid+1,y))%p;
}


int main()

{	

	int n = read();
	p = read();
	for(int i=1;i<=n;++i)
		a[i] = read();
	build(1,1,n);
	int tmp = read();
	while(tmp--)
	{
		int tt = read();
		if(tt==1)
		{
			int x = read() ,y = read() , c = read();
			change(1,1,n,x,y,1,c);
		}
		else if(tt==2)
		{
			int x = read(), y = read(), c = read() ;
			change(1,1,n,x,y,0,c);
		}
		else
		{
			int x = read() , y = read();
			printf("%lld\n",ask(1,1,n,x,y));
		}
	}
	

}
