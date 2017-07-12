
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const double beta = 0.75;
const int N = 7e4;
const int M = 1e7+5;
struct seg
{int l,r,sum;}a[M];
vector<int>rec,T,P;
int root[140005],ls[140005],rs[140005],v[140005],dfn[140005];
int n,m,size,lastans,tmp,Root;
int newnode()
{
	if(!rec.size())return ++size;
	else
	{
		int k = rec.back();rec.pop_back();
		return k;
	}
}
void Free(int &x)
{
	if(!x)return ;
	rec.push_back(x);
	Free(a[x].l),Free(a[x].r);
	a[x].sum =0;x = 0;
}
void Insert(int &p,int l,int r,int pos,int num)
{
	if(!p)p = newnode();
	if(l==r){a[p].sum+=num;return ;}
	int mid=(l+r)>>1;
	if(pos<=mid)Insert(a[p].l,l,mid,pos,num);
	else Insert(a[p].r,mid+1,r,pos,num);
	a[p].sum = a[a[p].l].sum+a[a[p].r].sum;
	if(!a[p].sum)Free(p);
}
void build(int &p,int l,int r)
{
	if(l>r)return ;
	if(l==r)
	{
		p = dfn[l];
		Insert(root[p],0,N,v[p],1);
		return ;
	}
	int mid=(l+r)>>1;
	p = dfn[mid];
	build(ls[p],l,mid-1);build(rs[p],mid+1,r);
	for(int i = l;i<=r;i++)
		Insert(root[p],0,N,v[dfn[i]],1);
}
void del(int &x)
{
	if(!x)return ;
	Free(root[x]);
	del(ls[x]);P.push_back(x);del(rs[x]);
	x = 0;
}
void rebuild(int &x)
{
	del(x);
	int s1 = P.size();
	for(int i = 1;i<= s1;i++)dfn[i] = P[i-1];
	build(x,1,s1);
	P.clear();
}
int update(int p,int x,int val)
{
	Insert(root[p],0,N,val,1);
	int t,lsize = a[root[ls[p]]].sum;
	if(x==lsize+1){t=v[p];v[p] = val;}
	else if(lsize>=x)t=update(ls[p],x,val);
	else t=update(rs[p],x-lsize-1,val);
	Insert(root[p],0,N,t,-1);
	return t;
}
void getans(int p,int l,int r)
{
	int L = a[root[ls[p]]].sum,R = a[root[p]].sum;
	if(l==1&&R==r){T.push_back(root[p]);return ;}
	if(l<=L+1&&r>=L+1)P.push_back(v[p]);
	if(r<=L)getans(ls[p],l,r);
	else if(l>L+1)getans(rs[p],l-L-1,r-L-1);
	else
	{
		if(l<=L)getans(ls[p],l,L);
        if(R>L+1)getans(rs[p],1,r-L-1);
	}
}
int Getans(int L,int R,int K)
{
	getans(Root,L,R);
	K--;
	int l = 0,r = N;
	int s1=T.size(),s2 = P.size();
	while(l<r)
	{
		int mid = (l+r)>>1,sum=0;
		for(int i = 0;i<s1;i++)sum+=a[a[T[i]].l].sum;
		for(int i = 0;i<s2;i++)
			if(P[i]>=l&&P[i]<=mid)
				sum++;
		if(K<sum)
		{
			for(int i = 0;i<s1;i++)T[i]=a[T[i]].l;
			r=mid;
		}else
		{
			for(int i = 0;i<s1;i++)T[i]=a[T[i]].r;
			l = mid+1;K-=sum;
		}
	}
	T.clear();P.clear();
	return l;
}
void Insert(int &p,int x,int val)
{
	if(!p)
	{
		p=++n;
		Insert(root[p],0,N,val,1);
		v[p] =val;
		return ;
	}
	Insert(root[p],0,N,val,1);
	int lsize = a[root[ls[p]]].sum;
	if(x<=lsize)Insert(ls[p],x,val);
	else Insert(rs[p],x-lsize-1,val);
	if(a[root[p]].sum*beta>max(a[root[ls[p]]].sum,a[root[rs[p]]].sum))
	{
		if(tmp)
		{
			if(ls[p]==tmp)rebuild(ls[p]);
			else rebuild(rs[p]);
			tmp = 0;
		}
	}else tmp = p;  
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&v[i]);
	for(int i = 1;i<= n;i++)dfn[i] = i;
	build(Root,1,n);
	scanf("%d",&m);
	int x,y,K;char opt[3];
	while(m--)
	{
		scanf("%s%d%d",opt,&x,&y);
		x = x^lastans,y = y^lastans;
		switch(opt[0])
		{
			case 'Q':scanf("%d",&K);K = K^lastans;lastans = Getans(x,y,K);printf("%d\n",lastans);break;
			case 'M':update(Root,x,y);break;
			case 'I':tmp = 0;Insert(Root,x-1,y);if(tmp){tmp = 0;rebuild(Root);}break;
		}
		//printf("%d %d ",x,y);
		//if(opt[0]=='Q')printf("%d\n",K);
		//else printf("\n");
	}
	return 0;
}
