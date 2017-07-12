
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 200000+5;
const int M = N << 2;
const int inf = 0x7ffffff;
using namespace std;

int a[N],b[N];
int tr1[M],tr2[M];

inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1; ch = getchar();}
	while(ch >='0' && ch <='9'){x= (x<<1) + (x<<3) + ch - '0';ch = getchar();}
	return x*f;
}

inline void updata(int k,int l,int r)
{
	int mid = (l+r) >> 1;
	if(a[mid+1] >= tr1[k<<1]) tr1[k] = tr1[k<<1|1];
	else if(b[mid+1] >= tr1[k<<1]) tr1[k] = tr2[k<<1|1];
	else tr1[k] = inf;
	if(a[mid+1] >= tr2[k<<1]) tr2[k] = tr1[k<<1|1];
	else if(b[mid+1] >= tr2[k<<1]) tr2[k] = tr2[k<<1|1];
	else tr2[k] = inf;
}

void build(int k,int l,int r)
{
	if(l==r)
	{
		tr1[k] = a[l];
		tr2[k] = b[l];
		return ;
	}
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	updata(k,l,r);
}

void change(int k,int l,int r,int pos)
{
	if(l==r)
	{
		tr1[k] = a[l];
		tr2[k] = b[l];
		return ;
	}
	int mid = (l+r) >> 1;
	if(pos <= mid) change(k<<1,l,mid,pos);
	else change(k<<1|1,mid+1,r,pos);
	updata(k,l,r);
}

int main()
{
	int n = read();
	for(int i=1;i<=n;++i)
	{
		a[i] = read(), b[i] = read();
		if(a[i] > b[i]) swap(a[i],b[i]);
	}
	build(1,1,n);
	int T = read();
	while(T--)
	{
		int x = read(),y = read();
		swap(a[x],a[y]);
		swap(b[x],b[y]);
		change(1,1,n,x);
		change(1,1,n,y);
		if(tr1[1] == inf)  puts("NIE");
		else puts("TAK");
	}
}
