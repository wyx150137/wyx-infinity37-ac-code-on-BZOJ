
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define P 1000000007
#define GET (ch>='0'&&ch<='9')
#define MAXN 1000005
#define lchild rt<<1,l,mid
#define rchild rt<<1|1,mid+1,r
#define ln rt<<1
#define rn rt<<1|1
#define MAXINT 1000000
using namespace std;
int n;
int c[MAXN],d[MAXN],g[MAXN];
struct node
{
	int x,y;
	node()  {   x=y=0;  }
	node(int tx,int ty) {   x=tx;y=ty;  }
	inline node operator + (const node& b)
	{
		if (x<b.x)  return  b;
		if (x>b.x)  return  (node){x,y};
		return (node){x,(y+b.y)%P};
	}
	inline node operator + (int tx) {   return (node){x+tx,y};  }
	inline void operator +=(const node& b)  {   *this=*this+b;  }
}f[MAXN];
struct seg
{
	int l,r;
	int pos,vald;
	node f,flag;
}tree[(MAXN<<1)+(int)(1e5)];
inline void build1(int rt=1,int l=0,int r=n)
{
	tree[rt].l=l;tree[rt].r=r;
	if (l==r)   {   tree[rt].pos=l;tree[rt].vald=d[l];return;   }
	int mid=(l+r)>>1;build1(lchild);build1(rchild);
	tree[rt].pos=c[tree[ln].pos]>c[tree[rn].pos]?tree[ln].pos:tree[rn].pos;
	tree[rt].vald=min(tree[ln].vald,tree[rn].vald);
}
inline void build2(int rt=1,int l=0,int r=n)
{
	tree[rt].flag=(node){-MAXINT,0};
	if (l==r)   {   tree[rt].vald=d[l];tree[rt].f=f[l];return;  }
	int mid=(l+r)>>1;build2(lchild);build2(rchild);
	tree[rt].f=tree[ln].f+tree[rn].f;
	tree[rt].vald=min(tree[ln].vald,tree[rn].vald);
}
inline void modify_add(int rt,int l,int r,node delta)
{
	int L=tree[rt].l,R=tree[rt].r,mid=(L+R)>>1;
	if (l<=L&&R<=r) {   tree[rt].flag+=delta;return;    }
	if (r<=mid) modify_add(ln,l,r,delta);
	else    if (l>mid)  modify_add(rn,l,r,delta);
	else    modify_add(ln,l,mid,delta),modify_add(rn,mid+1,r,delta);
}
inline int query_c(int rt,int l,int r)
{
	int L=tree[rt].l,R=tree[rt].r,mid=(L+R)>>1;
	if (l<=L&&r>=R) return tree[rt].pos;
	if (r<=mid) return query_c(ln,l,r);
	if (l>mid)  return query_c(rn,l,r);
	int t1=query_c(ln,l,mid),t2=query_c(rn,mid+1,r);    
	return c[t1]>c[t2]?t1:t2;
}
inline int query_d(int rt,int l,int r)
{
	int L=tree[rt].l,R=tree[rt].r,mid=(L+R)>>1;
	if (l<=L&&r>=R) return tree[rt].vald;
	if (r<=mid) return query_d(ln,l,r);
	if (l>mid)  return query_d(rn,l,r);
	return min(query_d(ln,l,mid),query_d(rn,mid+1,r));
}
inline node query_f(int rt,int l,int r)
{
	if (l>r)    return node(-MAXINT,0);
	int L=tree[rt].l,R=tree[rt].r,mid=(L+R)>>1;
	if (l<=L&&r>=R) return tree[rt].f;
	if (r<=mid) return query_f(ln,l,r);
	if (l>mid)  return query_f(rn,l,r);
	return query_f(ln,l,mid)+query_f(rn,mid+1,r);
}
inline void modify_cov(int rt,int x,node delta)
{
	int L=tree[rt].l,R=tree[rt].r,mid=(L+R)>>1;
	if (L==R)   {   tree[rt].f=delta;return;    }
	if (x<=mid) modify_cov(ln,x,delta); else    modify_cov(rn,x,delta);
	tree[rt].f=tree[ln].f+tree[rn].f;
}
node ask(int x)
{
	int rt=1,L=tree[rt].l,R=tree[rt].r,mid=(L+R)>>1;
	node t=node(-MAXINT,0);
	while (L!=R)
	{
		t+=tree[rt].flag;
		mid=(L+R)>>1;rt<<=1;
		if (x>mid)  rt|=1;
		L=tree[rt].l,R=tree[rt].r;
	}
	t+=tree[rt].flag;
	return t;
}
inline void update(int l,int mid,int r)
{
	int i=max(c[mid]+l,mid);
	if (i>r||g[i]>=mid) return;
	int newl=max(l,g[i]),newr=i-c[mid];
	node tmp=query_f(1,newl,newr)+1;
	for (;i<=mid-1+c[mid]&&i<=r;i++)
	{
		if (g[i]>newl)
		{
			if (g[i]>=mid)  return;
			newl=g[i];tmp=query_f(1,newl,newr)+1;
		}
		f[i]+=tmp;newr++;
		if (newr>=newl) tmp+=f[newr]+1;
	}
	while (i<=r)
	{
		if (g[i]>newl)
		{
			if (g[i]>=mid)  return;
			newl=g[i];
		}
		tmp=query_f(1,newl,mid-1)+1;
		int t=query_d(1,newl+1,n);
		if (t>r)    {   modify_add(1,i,r,tmp);return;   }
		modify_add(1,i,t-1,tmp);i=t;
	}
}
void solve(int l,int r)
{
	if (l==r)
	{
		if (l)  modify_cov(1,l,f[l]=f[l]+ask(l));
		return;
	}
	int mid=query_c(1,l+1,r);
	solve(l,mid-1);update(l,mid,r);solve(mid,r);
}
int main()
{
	scanf("%d",&n);
	int i=0,j=0;
	for (i=1;i<=n;i++)scanf("%d%d",&c[i],&d[i]);	
	build1();
	for (i=0;i<=n;i++)  d[i]=n+1,f[i]=node(-MAXINT,0);
	f[0]=node(0,1);
	for (i=0;i<=n;i++)
	{
		while (j<i&&i-j>query_d(1,j+1,i))   j++;
		g[i]=j;
		if (d[g[i]]>n)  d[g[i]]=i;
	}
	build2();solve(0,n);
	printf(f[n].x>0?"%d %d\n":"NIE\n",f[n].x,f[n].y);
}
