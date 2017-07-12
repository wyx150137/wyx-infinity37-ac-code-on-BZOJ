
#include<iostream>
#include<cstdio>
#include<algorithm>
#define inf 0x7fffffff
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n,m,cnt,k=0;
int a[200005],b[200005],sg[200005],ans[200005],next[200005],last[200005];
int ls[600005],rs[600005],mn[600005];
bool mark[200005];
struct data{int l,r,id;}q[200005];
bool cmp(data a,data b)
{return a.l<b.l;}
int find(int x)
{
	int l=1,r=cnt;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(b[mid]<x)l=mid+1;
		else r=mid-1;
	}
	return l;
}
void build(int k,int l,int r)
{
     ls[k]=l;rs[k]=r;mn[k]=inf;
     if(l==r){mn[k]=sg[l];return;}
     int mid=(l+r)>>1;
     build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
void pushdown(int k)
{
     int l=ls[k],r=rs[k];
     if(l==r)return;
     mn[k<<1]=min(mn[k],mn[k<<1]);
     mn[k<<1|1]=min(mn[k],mn[k<<1|1]);
}
int ask(int k,int x)
{
    if(mn[k]!=inf)pushdown(k);
    int l=ls[k],r=rs[k];
    if(l==r)return mn[k];
    int mid=(l+r)>>1;
    if(x<=mid)return ask(k<<1,x);
    return ask(k<<1|1,x);
}
void update(int k,int x,int y,int val)
{
     if(mn[k]!=inf)pushdown(k);
     int l=ls[k],r=rs[k];
     if(l==x&&y==r){mn[k]=min(mn[k],val);return;}
     int mid=(l+r)>>1;
     if(y<=mid)update(k<<1,x,y,val);
     else if(x>mid)update(k<<1|1,x,y,val);
     else {update(k<<1,x,mid,val);update(k<<1|1,mid+1,y,val);}
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
		a[i]=b[i]=read();
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	    if(b[i]!=b[i-1]||i==1)b[++cnt]=b[i];
	for(int i=1;i<=n;i++)
	{
		int t=find(a[i]);
		mark[t]=1;
		if(a[i]==k)
			while(mark[t])
			    {
				    k++;
				    if(b[++t]!=k)break;
				}
		sg[i]=k;
	}
	build(1,1,n);
	for(int i=n;i>0;i--)
	    next[i]=last[find(a[i])],last[find(a[i])]=i;
	for(int i=1;i<=m;i++)
	{
		q[i].l=read();q[i].r=read();
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	int now=1;
	for(int i=1;i<=m;i++)
	{
		while(now<q[i].l)
		{
			if(!next[now])next[now]=n+1;
			update(1,now,next[now]-1,a[now]);
			now++;
		}
		ans[q[i].id]=ask(1,q[i].r);
	}
	for(int i=1;i<=m;i++)
	    printf("%d\n",ans[i]);
	return 0;
}
