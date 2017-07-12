
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int mx[N<<2],lazy[N<<2],dep[N];
struct E
{int next,to;}e[N<<1];
int head[N],tot,in[N],out[N],Dfn;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
void dfs(int x,int fa)
{
	in[x] = ++Dfn;
	dep[x] = dep[fa]+1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
			dfs(e[i].to,x);
	out[x] = Dfn;
}
inline int merge(int x,int y)
{
	return dep[x]>dep[y]?x:y;
}
inline void Push_down(int p)
{
	if(!lazy[p])return ;
	mx[p<<1] = merge(mx[p<<1],lazy[p]),mx[p<<1|1] = merge(mx[p<<1|1],lazy[p]);
	lazy[p<<1] = merge(lazy[p<<1],lazy[p]),lazy[p<<1|1] = merge(lazy[p<<1|1],lazy[p]);
	lazy[p] = 0;
}
void build(int p,int l,int r)
{
	lazy[p] = 0;
	if(l==r){mx[p]=1;return ;}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);build(p<<1|1,mid+1,r);
	mx[p] = merge(mx[p<<1],mx[p<<1|1]);
}
void update(int p,int l,int r,int a,int b,int id)
{
	if(l>=a&&r<=b)
	{
		mx[p] = merge(mx[p],id);lazy[p] = merge(lazy[p],id);
		return ;
	}
	Push_down(p);
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,id);
	if(b >mid)update(p<<1|1,mid+1,r,a,b,id);
	mx[p] = merge(mx[p<<1],mx[p<<1|1]);
}
int getans(int p,int l,int r,int pos)
{
	if(l==r)return mx[p];
	Push_down(p);
	int mid = (l+r)>>1;
	if(pos<=mid)return getans(p<<1,l,mid,pos);
	else return getans(p<<1|1,mid+1,r,pos);
}
int main()
{
	//freopen("x.in","r",stdin);
	int n,q,x,y;
	scanf("%d%d",&n,&q);
	for(int i = 1;i< n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,0);
	build(1,1,n);
	char opt[3];
	while(q--)
	{
		scanf("%s%d",opt,&x);
		if(opt[0]=='Q')printf("%d\n",getans(1,1,n,in[x]));
		else update(1,1,n,in[x],out[x],x);
	}
	return 0;
}
