
#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstdio>
#define M 2000000+5
#define N 500000+5
using namespace std;
struct data
{
       int lm,rm,mx,sum,l,r;
}tr[M];
int n,m,a[N];
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
void update(int k)
{
	tr[k].sum=tr[k<<1].sum+tr[k<<1|1].sum;
	tr[k].lm=max(tr[k<<1].lm,tr[k<<1].sum+tr[k<<1|1].lm);
	tr[k].rm=max(tr[k<<1|1].rm,tr[k<<1].rm+tr[k<<1|1].sum);
	tr[k].mx=max(max(tr[k<<1].mx,tr[k<<1|1].mx),tr[k<<1].rm+tr[k<<1|1].lm);
 }
void build(int k,int s,int t)
{
	tr[k].l=s;tr[k].r=t;
	if(s==t){tr[k].sum=tr[k].lm=tr[k].rm=tr[k].mx=a[s];return;}
	int mid=(s+t)>>1;
	build(k<<1,s,mid);
	build(k<<1|1,mid+1,t);
	update(k);
}
data ask(int k,int s,int t)
{
    data tmp1,tmp2,a;
    int l=tr[k].l,r=tr[k].r;
    if(l==s&&t==r)
    	return tr[k];
    int mid=(l+r)>>1;
    if(t<=mid) 
    	return ask(k<<1,s,t);
    else if(s>mid) 
    	return ask(k<<1|1,s,t);
    else
    {
	    tmp1=ask(k<<1,s,mid);
	    tmp2=ask(k<<1|1,mid+1,t);
	    a.mx=max(max(tmp1.mx,tmp2.mx),tmp1.rm+tmp2.lm);
	    a.rm=max(tmp2.sum+tmp1.rm,tmp2.rm);
	    a.lm=max(tmp1.lm,tmp1.sum+tmp2.lm);
	    return a;
   }
}
void change(int k,int x,int y)
{
     int l=tr[k].l,r=tr[k].r;
     if(l==r){tr[k].sum=tr[k].lm=tr[k].rm=tr[k].mx=y;return;}
     int mid=(l+r)>>1;
     if(x<=mid)
     	change(k<<1,x,y);
     else if(x>mid)
     	change(k<<1|1,x,y);
     update(k);
 }
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
       a[i]=read();
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int t,x,y;
        t=read(),x=read(),y=read();
        if(t==1)
        {
            if(x>y)swap(x,y);
            printf("%d\n",ask(1,x,y).mx);
        }
        if(t==2) 
        	change(1,x,y);
   	}
    return 0;
}
