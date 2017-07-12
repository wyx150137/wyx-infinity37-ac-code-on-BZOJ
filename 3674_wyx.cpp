
#include<cstdio>
#include<iostream>
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch>'9'||ch<'0')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n,m,sz,last;
int root[200005],ls[10000005],rs[10000005],v[10000005],deep[10000005];
void build(int &k,int l,int r)
{
	if(!k)k=++sz;
	if(l==r){v[k]=l;return;}
	int mid=(l+r)>>1;
	build(ls[k],l,mid);
	build(rs[k],mid+1,r);
}
void modify(int l,int r,int x,int &y,int pos,int val)
{
	y=++sz;
	if(l==r){v[y]=val;deep[y]=deep[x];return;}
	ls[y]=ls[x];rs[y]=rs[x];
	int mid=(l+r)>>1;
	if(pos<=mid)
		modify(l,mid,ls[x],ls[y],pos,val);
	else modify(mid+1,r,rs[x],rs[y],pos,val);
}
int query(int k,int l,int r,int pos)
{
	if(l==r)return k;
	int mid=(l+r)>>1;
	if(pos<=mid)return query(ls[k],l,mid,pos);
	else return query(rs[k],mid+1,r,pos);
}
void add(int k,int l,int r,int pos)
{
	if(l==r){deep[k]++;return;}
	int mid=(l+r)>>1;
	if(pos<=mid)add(ls[k],l,mid,pos);
	else add(rs[k],mid+1,r,pos);
}
int find(int k,int x)
{
    int p=query(k,1,n,x);
	if(x==v[p])return p;
    int t=find(k,v[p]);
    modify(1,n,k,k,v[p],t);
	return t;
}
int main()
{
	n=read();m=read();
	build(root[0],1,n);
	int f,k,a,b;
	for(int i=1;i<=m;i++)
	{
		f=read();
		if(f==1)
		{
			root[i]=root[i-1];
			a=read();b=read();a=a^last;b=b^last;
			int p=find(root[i],a),q=find(root[i],b);
			if(v[p]==v[q])continue;
			if(deep[p]>deep[q])swap(p,q);
			modify(1,n,root[i-1],root[i],v[p],v[q]);
			if(deep[p]==deep[q])add(root[i],1,n,v[q]);
		}
		if(f==2)
		{k=read();k=k^last;root[i]=root[k];}
		if(f==3)
		{
			root[i]=root[i-1];
			a=read();b=read();a=a^last;b=b^last;
		    int p=find(root[i],a),q=find(root[i],b);
			if(v[p]==v[q])last=1;
			else last=0;
			printf("%d\n",last);
		}
	}
	return 0;
}
