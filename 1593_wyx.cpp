
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
struct seg
{
	int l,r;
	int ls,rs,mn;
	int sum;
	int lazy;
}tr[200000+5];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch=='-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

void build(int k,int l,int r)
{
	tr[k].l=l,tr[k].r=r;
	tr[k].ls = tr[k].rs = tr[k].sum = tr[k].mn = r - l + 1;
	if(l==r)return;
	int mid = (tr[k].l+tr[k].r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}

void updata(int k)
{
	if(tr[k<<1].mn==tr[k<<1].sum)
		tr[k].ls = tr[k<<1].sum + tr[k<<1|1].ls;
	else tr[k].ls = tr[k<<1].ls;
	if(tr[k<<1|1].mn==tr[k<<1|1].sum)
		tr[k].rs = tr[k<<1|1].sum + tr[k<<1].rs;
	else tr[k].rs = tr[k<<1|1].rs;
	tr[k].mn = max(tr[k<<1].mn,tr[k<<1|1].mn);
	tr[k].mn = max(tr[k].mn,tr[k<<1].rs + tr[k<<1|1].ls);
}

void down(int k)
{
	int tmp = tr[k].lazy;
	tr[k].lazy = 0;
	if(tr[k].l==tr[k].r) return;
	if(tmp==1)
	{
		tr[k<<1].ls = tr[k<<1].rs = tr[k<<1].mn = tr[k<<1].sum;
		tr[k<<1|1].ls = tr[k<<1|1].rs = tr[k<<1|1].mn = tr[k<<1|1].sum;
		tr[k<<1].lazy = tr[k<<1|1].lazy = 1;
	}
	else if(tmp==2)
	{
		tr[k<<1].ls = tr[k<<1].rs = tr[k<<1].mn = 0;
		tr[k<<1|1].ls = tr[k<<1|1].rs = tr[k<<1|1].mn = 0;
		tr[k<<1].lazy = tr[k<<1|1].lazy = 2;
	}
}

void change(int k,int x,int y,int f)
{
	down(k);
	if(tr[k].l==x && tr[k].r == y)
	{
		if(f==1) tr[k].mn = tr[k].ls = tr[k].rs = tr[k].sum;
		else tr[k].mn = tr[k].ls = tr[k].rs = 0;
		tr[k].lazy = f;
		return ;
	}
	int mid = (tr[k].l+tr[k].r)>>1;
	if(y<=mid)
		change(k<<1,x,y,f);
	else if(x>mid)
		change(k<<1|1,x,y,f);
	else change(k<<1,x,mid,f),change(k<<1|1,mid+1,y,f);
	updata(k);
}

int ask(int k,int x)
{
	down(k);
	if (tr[k].l==tr[k].r) return tr[k].l;
	int mid = (tr[k].l+tr[k].r)>>1;
	if(tr[k<<1].mn >= x)return ask(k<<1,x);
	if(tr[k<<1].rs + tr[k<<1|1].ls >= x)return mid - tr[k<<1].rs + 1;
	else return ask(k<<1|1,x);

}

int n,m;

int main()
{
	cin >> n >> m;
	build(1,1,n);
	for(int i=1;i<=m;++i)
	{
		int f=read();
		if(f==1)
		{
			int x=read();
			if(tr[1].mn<x)puts("0");
			else 
			{
				int pos = ask(1,x);
				printf("%d\n",pos);
				change(1,pos,pos+x-1,2);
			}
		}
		else
		{
			int x=read(),y=read();
			change(1,x,x+y-1,1);
		}
	}
}
