
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10000000 +10;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int root[500000+10];
int sz,n,m;
int ls[N],rs[N];
int tr[N];

void add(int l,int r,int x,int &y, int dat)
{
	y = ++sz;
	tr[y] = tr[x] + 1;
	if(l==r)return;
	ls[y] = ls[x];
	rs[y] = rs[x];
	int mid = (l + r)>>1;
	if(dat <= mid)add(l,mid,ls[x],ls[y],dat);
	else add(mid+1,r,rs[x],rs[y],dat);
}

int ask(int l,int r)
{
	int L = 1;
	int R = n;
	int len = (r - l + 1) >> 1;
	int x = root[l - 1],y = root[r];
	while(L != R)
	{
		if(tr[y] - tr[x] <= len) return 0;
		int mid = (L+R)>>1;
		if(tr[ls[y]] - tr[ls[x]] > len)
		{
			R = mid;
			x = ls[x];
			y = ls[y];
		}
		else if(tr[rs[y]] - tr[rs[x]] > len)
		{
			L = mid + 1;
			x = rs[x];
			y = rs[y];
		}
		else return 0;
	}
	return L;	
}


int main()  
{  

	n = read(), m =read();
	for(int i=1;i<=n;++i)
	{
		int x = read();
		add(1,n,root[i-1],root[i],x);
	}
	for(int i=1;i<=m;++i)
	{
		int x = read(), y = read();
		printf("%d\n",ask(x,y));
	}

}  
