
#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 1000000000
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,rt,sz;
int c[80005][2],fa[80005],deep[80005];
int a[80005],size[80005],v[80005],pos[80005];
void update(int k)
{
	size[k]=size[c[k][0]]+size[c[k][1]]+1;
}
void rotate(int x,int &k)
{
	int y=fa[x],z=fa[y],l,r;
	if(c[y][0]==x)l=0;else l=1;r=l^1;
	if(y==k)k=x;
	else {if(c[z][0]==y)c[z][0]=x;else c[z][1]=x;}
	fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
	c[y][l]=c[x][r];c[x][r]=y;
	update(y);update(x);
}
void splay(int x,int &k)
{
	while(x!=k)
	{
		int y=fa[x],z=fa[y];
		if(y!=k)
		{	
			if(c[y][0]==x^c[z][0]==y)
				rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
void build(int l,int r,int f)
{
	if(l>r)return;
	int now=l,last=f;
	if(l==r)
	{
		v[now]=a[l];size[now]=1;fa[now]=last;
		if(l<f)c[last][0]=now;
		else c[last][1]=now;
		return;
	}
	int mid=(l+r)>>1;now=mid;
	build(l,mid-1,mid);build(mid+1,r,mid);
	v[now]=a[mid];fa[now]=last;update(now);
	if(mid<f)c[last][0]=now;
	else c[last][1]=now;
}
int find(int k,int rank)
{
	int l=c[k][0],r=c[k][1];
	if(size[l]+1==rank)return k;
	else if(size[l]>=rank)return find(l,rank);
	else return find(r,rank-size[l]-1);
}
void del(int k)
{
	int x,y,z;
	x=find(rt,k-1);y=find(rt,k+1);
	splay(x,rt);splay(y,c[x][1]);
	z=c[y][0];c[y][0]=0;fa[z]=size[z]=0;
	update(y);update(x);
}
void move(int k,int val)
{
	int x,y,z=pos[k],rank;
	splay(z,rt);rank=size[c[z][0]]+1;
	del(rank);
	if(val==inf)x=find(rt,n),y=find(rt,n+1);
	else if(val==-inf)x=find(rt,1),y=find(rt,2);
	else x=find(rt,rank+val-1),y=find(rt,rank+val);
	splay(x,rt);splay(y,c[x][1]);
	size[z]=1;fa[z]=y;c[y][0]=z;
	update(y);update(x);
}
int main()
{
	n=read();m=read();
	for(int i=2;i<=n+1;i++)
		a[i]=read(),pos[a[i]]=i;
	build(1,n+2,0);
	rt=(3+n)>>1;
	char ch[10];int S,T;
	for(int i=1;i<=m;i++)
	{
		scanf("%s",ch);S=read();
		switch(ch[0])
		{
		case 'T':move(S,-inf);break;
		case 'B':move(S,inf);break;
		case 'I':T=read();move(S,T);break;
		case 'A':splay(pos[S],rt);printf("%d\n",size[c[pos[S]][0]]-1);break;
		case 'Q':printf("%d\n",v[find(rt,S+1)]);break;
		}
	}
	return 0;
}
