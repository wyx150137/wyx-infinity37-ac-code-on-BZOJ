
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>
#define inf 1000000000
#define N 1000005
using namespace std;
queue <int> q;	
int rt,cnt;
int sum[N],a[N],fa[N],id[N];
int mx[N],lx[N],rx[N],v[N],n,m;
int ch[N][2];
int size[N];
bool rev[N],lazy[N];
inline void updata(int k)
{
	int l=ch[k][0],r=ch[k][1];
	sum[k]=sum[l]+sum[r]+v[k];
	size[k]=size[l]+size[r]+1;
	mx[k]=max(mx[l],mx[r]);mx[k]=max(mx[k],rx[l]+v[k]+lx[r]);
	lx[k]=max(lx[l],sum[l]+lx[r]+v[k]);
	rx[k]=max(rx[r],sum[r]+rx[l]+v[k]);
}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void down(int k)
{
	int l=ch[k][0],r=ch[k][1];
	if(lazy[k])
	{
		rev[k]=lazy[k]=0;
		if(l){lazy[l]=1;v[l]=v[k];sum[l]=size[l]*v[k];}
		if(r){lazy[r]=1;v[r]=v[k];sum[r]=size[r]*v[k];}
		if(v[k]>=0)
		{
			if(l){lx[l]=rx[l]=mx[l]=sum[l];}
			if(r){lx[r]=rx[r]=mx[r]=sum[r];}
		}
		else
		{
			if(l){lx[l]=rx[l]=0;mx[l]=v[k];}
			if(r){lx[r]=rx[r]=0;mx[r]=v[k];}
		}
	}
	if(rev[k])
	{
		rev[k]^=1,rev[l]^=1,rev[r]^=1;
		swap(lx[l],rx[l]);
		swap(lx[r],rx[r]);
		swap(ch[l][0],ch[l][1]);swap(ch[r][0],ch[r][1]);
	}
}
void rotate(int x,int &k)
{
	int y=fa[x],z=fa[y];
	int l = (ch[y][1]==x), r = l^1;
	if(y==k)k=x;
	else ch[z][ch[z][1]==y]=x;
	fa[ch[x][r]]=y;
	fa[y]=x;
	fa[x]=z;
	ch[y][l]=ch[x][r];
	ch[x][r]=y;
	updata(y),updata(x);
}
void splay(int x,int &k)
{
	while(x!=k)
	{
		int y=fa[x],z=fa[y];
		if(y!=k)
		{
			if((ch[y][0]==x) ^ (ch[z][0]==y))rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
int find(int x,int rank)
{
	down(x);
	int l = ch[x][0] , r=ch[x][1];
	if(size[l]+1==rank)return x;
	if(size[l]>=rank)return find(l,rank);
	return find(r,rank-size[l]-1);
}
void rec(int x)
{
	if(!x)return;
	int l=ch[x][0],r=ch[x][1];
	rec(l),rec(r);
	q.push(x);
	fa[x]=ch[x][0]=ch[x][1]=0;
	lazy[x]=rev[x]=0;
}
int turn(int k,int tot)
{	
	int x=find(rt,k);
	int y=find(rt,tot+k+1);
	splay(x,rt),splay(y,ch[x][1]);
	return ch[y][0];
}
void query(int k,int tot)
{
	int tt = turn(k,tot);
	printf("%d\n",sum[tt]);
}
void change(int k,int tot,int val)
{
	int x=turn(k,tot),y=fa[x];
	v[x]=val;lazy[x]=1;sum[x]=size[x]*val;
	if(val>=0)mx[x]=rx[x]=lx[x]=sum[x];
	else lx[x]=rx[x]=0,mx[x]=val;
	updata(y),updata(fa[y]);
}
void rever(int k,int tot)
{
	int x=turn(k,tot),y=fa[x];
	if(!lazy[x])
	{
		rev[x]^=1;
		swap(ch[x][0],ch[x][1]);
		swap(lx[x],rx[x]);
		updata(y);updata(fa[y]);
	}
}
void erase(int k,int tot)
{
	int x=turn(k,tot),y=fa[x];
	rec(x);
	ch[y][0]=0;
	updata(y),updata(fa[y]);
}
void build(int l,int r,int f)
{
	if(l>r)return;
	int mid = (l+r)>>1;
	int now = id[mid] , last = id[f];
	if(l==r)
	{
		sum[now] = a[l];
		size[now] = 1;
		rev[now] = lazy[now] = 0;
		if(a[l]>=0) lx[now] = rx[now] = mx[now] = a[l];
		else lx[now] = rx[now] = 0,mx[now] = a[l]; 
	}
	else
	{
		build(l,mid-1,mid);
		build(mid+1,r,mid);
	}
	v[now] = a[mid];
	fa[now] = last;
	updata(now);
	ch[last][mid >= f] = now;
}
void insert(int k,int tot)
{
	for(int i=1;i<=tot;++i)a[i]=read();
	for(int i=1;i<=tot;++i)
		if(!q.empty())id[i]=q.front(),q.pop();
		else id[i]=++cnt;
	build(1,tot,0);
	int z=id[(1+tot)>>1];
	int x=find(rt,k+1),y=find(rt,k+2);
	splay(x,rt);splay(y,ch[x][1]);
	fa[z]=y;ch[y][0]=z;
	updata(y);updata(x);
}
int main()
{
	n=read(),m=read();
	mx[0]=a[1]=a[n+2]=-inf;
	for(int i=1;i<=n;++i)a[i+1]=read();
	for(int i=1;i<=n+2;++i)id[i]=i;
	build(1,n+2,0);
	rt = (n+3)>>1;
	cnt = n+2;
	int k,tot,val;
	char str[10];
	while(m--)
	{
		scanf("%s",str);
		if(str[0]!='M'||str[2]!='X')k=read(),tot=read();
		if(str[0]=='I')insert(k,tot);
		if(str[0]=='D')erase(k,tot);
		if(str[0]=='M')
		{
			if(str[2]=='X')printf("%d\n",mx[rt]);
			else val=read(),change(k,tot,val);
		}
		if(str[0]=='R')rever(k,tot);
		if(str[0]=='G')query(k,tot);
	}
	return 0;
}
