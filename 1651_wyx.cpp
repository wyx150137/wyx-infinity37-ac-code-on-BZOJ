
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define M 3000000+5
using namespace std;

int tr[M];
int lazy[M];

inline void down(int k,int l,int r)
{
	int tmp = lazy[k];lazy[k] = 0;
	if(!tmp||l==r)return;
	lazy[k<<1] += tmp;
	lazy[k<<1|1] += tmp;
	tr[k<<1] += tmp;
	tr[k<<1|1] += tmp;
	return; 
}

inline void updata(int k)
{	
	tr[k] = max(tr[k<<1],tr[k<<1|1]);
}

void change(int k,int l,int r,int x,int y,int c)
{
	down(k,l,r);
	if(l==x && r==y)
	{tr[k]++;lazy[k]++;return;}
	int mid = (l+r)>>1;
	if(y<=mid)change(k<<1,l,mid,x,y,c);
	else if(x>mid)change(k<<1|1,mid+1,r,x,y,c);
	else change(k<<1,l,mid,x,mid,c),change(k<<1|1,mid+1,r,mid+1,y,c);
	updata(k);
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	int n = read();
	for(int i=1;i<=n;++i)
	{
		int x = read(),y=read();
		change(1,1,1000000,x,y,1);
	}
	cout<<tr[1];
}
