
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define M 800000+5
#define max(a,b) (a)>(b)?(a):(b);
using namespace std;
struct seg
{
	int l,r,mn;
}tr[M];
void build(int k,int l,int r)
{
	tr[k].l=l,tr[k].r=r;
	if(l==r)
	{
		tr[k].mn=0;
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tr[k].mn=0;
}
void change(int k,int pos,int x)
{
	if(tr[k].l==pos && tr[k].r==pos)
	{
		tr[k].mn=x;
		return;
	}
	int mid=(tr[k].l+tr[k].r)>>1;
	if(pos<=mid)
		change(k<<1,pos,x);
	else
		change(k<<1|1,pos,x);
	tr[k].mn=max(tr[k<<1].mn,tr[k<<1|1].mn);
}
int ask(int k,int l,int r)
{
	if(tr[k].l==l && tr[k].r==r)
		return tr[k].mn;
	int mid=(tr[k].l+tr[k].r)>>1;
	if(r<=mid)
		return ask(k<<1,l,r);
	else if(l>mid)
		return ask(k<<1|1,l,r);
	return max(ask(k<<1,l,mid),ask(k<<1|1,mid+1,r));
}
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
int ans;
int L;
int main()
{
	//freopen("03.in", "r", stdin);
	//freopen("03.out", "w", stdout);
	int m,d;
	cin>>m>>d;	
	build(1,1,m);
	while(m--)
	{
		char str[40];
		scanf("%s",str);
		int tmp=read();
		if(str[0]=='A')
		{
			tmp+=ans;
			tmp%=d;
			change(1,++L,tmp);
		}
		else
		{
			int s=L-tmp+1;
			ans=ask(1,s,L);
			printf("%d\n",ans);
		}
	}
}
