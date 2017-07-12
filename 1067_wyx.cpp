
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 50000+5
#define M 200000+5
using namespace std;
int year[N],a[N],n;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
struct data
{	
	int l,r,mn;
}tr[M];
void build(int k,int l,int r)
{	
	tr[k].l=l,tr[k].r=r;
	if(l==r){tr[k].mn=a[l];return;}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tr[k].mn=max(tr[k<<1].mn,tr[k<<1|1].mn);
}
int ask(int k,int s,int t)
{
	if(s>t)return -1;
    int l=tr[k].l,r=tr[k].r;
    if(s==l && t==r)return tr[k].mn;
    int mid=(l+r)>>1;
    if(t<=mid)return ask(k<<1,s,t);
    if(s>mid)return ask(k<<1|1,s,t);
    return max(ask(k<<1,s,mid),ask(k<<1|1,mid+1,t));
}
int main()
{
//	freopen("rains.in", "r", stdin);
//	freopen("rains.out", "w", stdout);
	cin>>n;
	for(int i=1;i<=n;++i)
		year[i]=read(),a[i]=read();
	build(1,1,n);
	/*for(int i=1;i<=n;++i)
	printf("y[%d]=%d  a[%d]=%d\n",i,year[i],i,a[i]);*/
	int q;cin>>q;
	while(q--)
	{
		int A=read(),B=read();
		int l=lower_bound(year+1,year+n+1,A)-year;
		int r=lower_bound(year+1,year+n+1,B)-year;
		if(year[l]==A && year[r]==B)
		{
			if(a[l]<a[r] || ask(1,l+1,r-1) >= a[r])
				puts("false");
			else if(B-A == r-l)
				puts("true");
			else
				puts("maybe");
		}
		else if(year[l]!=A && year[r]!=B)
			puts("maybe");
		else if(year[r] != B)
		{
			if(ask(1,l+1, r-1) >= a[l])
				puts("false");
			else
				puts("maybe");
		}
		else
		{
			if(ask(1,l, r-1) >= a[r])
				puts("false");
			else
				puts("maybe");
		}
	}
}	
