
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e5+5;
const int sed = 37;
#define is(x) (son[fa[x]][1]==x)
typedef unsigned long long LL;
char start[N];
int digit[N];
LL power[N]={1};
struct node
{
	int root,n;
	LL hash[N];
	int val[N],fa[N],son[N][2],size[N];
	inline void update(int p)
	{
		size[p]=size[son[p][0]]+size[son[p][1]]+1;
		hash[p]=hash[son[p][0]]*power[size[son[p][1]]+1]+val[p]*power[size[son[p][1]]]+hash[son[p][1]];
	}
	inline void Build(int l,int r,int mid)
	{
		if(l<mid)		{
			int lmid=l+mid-1>>1;
			Build(l,mid-1,lmid);
			fa[lmid]=mid;
			son[mid][0]=lmid;
		}
		if(mid<r)
		{
			int rmid=mid+1+r>>1;
			Build(mid+1,r,rmid);
			fa[rmid]=mid;
			son[mid][1]=rmid;
		}
		val[mid]=digit[mid],update(mid);
	}
	inline void link(int x,int y,int d){son[y][d]=x;fa[x]=y;}
	inline void Rotate(int x)
	{
		int y=fa[x],z=fa[y],id=is(x),t=son[x][!id];
		if(t)fa[t]=y;son[y][id]=t;
		link(x,z,is(y));
		link(y,x,!id);
		update(y);
	}
	inline void Splay(int x,int k)
	{
		int y,z;
		while(fa[x]!=k)
		{
			y=fa[x];
			z=fa[y];
			if(z==k){Rotate(x);break;}
			if(is(x)==is(y))Rotate(y),Rotate(x);
			else Rotate(x),Rotate(x);
		}
		update(x);
		if(!k)root=x;
	}
	inline int Select(int rank,int k)
	{
		if(size[root]<rank)return -1;
		int x=root;
		while(size[son[x][0]]+1!=rank)
		{
			if(size[son[x][0]]+1>rank)x=son[x][0];
			else rank=rank-size[son[x][0]]-1,x=son[x][1];
		}
		Splay(x,k);
		return x;
	}
	inline void newnode(int &x,int y,int w)
	{
		x=++n;
		son[x][0]=son[x][1]=0;
		val[x]=w;
		fa[x]=y;
		size[x]=1;
	}
	inline void Insert(int x,int p)
	{
		int l=Select(x,0),r=Select(x+1,l);
		newnode(son[r][0],r,p);
		Splay(n,0);
	}
	inline void Change(int x,int p){x=Select(x,0),val[x]=p,Splay(x,0);}
	inline bool check(int a,int b,int len)
	{
		int x;
		Select(a-1,0);x=Select(a+len,root);
		if(x==-1)return 0;
		LL hash1=hash[son[x][0]];
		Select(b-1,0);x=Select(b+len,root);
		if(x==-1)return 0;
		LL hash2=hash[son[x][0]];
		return hash1==hash2;
	}
}tree;
char s[N];
int main()
{
	scanf("%s",s+1);
	int m,n=strlen(s+1);
	for(int i = 1;i<N;i++)power[i] = power[i-1]*sed;
	tree.n=n+2;
	for(int i = 2;i<= n+1;i++)
		digit[i] = s[i-1]-'a'+1;
	tree.root=(1+tree.n)>>1;
	tree.Build(1,tree.n,1+tree.n>>1);
	scanf("%d",&m);
	char a[10];
	int l,r;
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",a);
		if(a[0]=='Q')
		{
			scanf("%d%d",&l,&r);
			int L = 0,R = tree.n,ans = 0;
			while(L<=R)
			{
				int mid = (L+R)>>1;
				if(tree.check(l+1,r+1,mid))L=mid+1,ans=mid;
				else R=mid-1;
			}
			printf("%d\n",ans);
		}else if(a[0]=='R')
		{
			scanf("%d%s",&l,a);
			tree.Change(l+1,a[0]-'a'+1);
		}else
		{
			scanf("%d%s",&l,a);
			tree.Insert(l+1,a[0]-'a'+1);
		}
	}
	return 0;
}
