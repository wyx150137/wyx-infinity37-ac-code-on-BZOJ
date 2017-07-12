
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 8e4+5;
const int INF = 1e8+1;
struct E
{int next,to;}e[N<<1];
int head[N],tot,n,q;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int size[N],son[N],w[N],top[N],fa[N],cnt,id[N],d[N],dpt[N];
void dfs1(int x,int f)
{
	fa[x] = f;
	size[x] = 1;
	dpt[x] = dpt[f]+1;
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to==f)continue;
		dfs1(e[i].to,x);
		size[x]+=size[e[i].to];
		if(size[e[i].to]>size[son[x]])son[x] = e[i].to;
	}
}
void dfs2(int x,int tp)
{
	top[x] = tp;
	w[x] = ++cnt;
	id[cnt] = x;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
}
struct Treap
{
	Treap *ls,*rs;
	int cnt,val,key,size;
	Treap(int x);
	void push_up();
}*root[N<<2];
Treap :: Treap(int x)
{
	ls = rs = NULL;
	val = x;
	key = rand();
	cnt = size = 1;
}
void Treap :: push_up()
{
	size = cnt;
	if(ls)size+=ls->size;
	if(rs)size+=rs->size;
}
void go_left(Treap *&x)
{
	Treap *y = x->rs;
	x->rs = y->ls;
	y->ls = x;
	x = y;
	x->ls->push_up();
	x->push_up();
}
void go_right(Treap *&x)
{
	Treap *y = x->ls;
	x->ls = y->rs;
	y->rs = x;
	x = y;
	x->rs->push_up();
	x->push_up();
}
void Insert(Treap *&x,int y)
{
	if(!x){x = new Treap(y);return ;}
	if(x->val==y)x->cnt++;
	else if(y<x->val)
	{
		Insert(x->ls,y);
		if(x->ls->key>x->key)
			go_right(x);
	}else
	{
		Insert(x->rs,y);
		if(x->rs->key>x->key)
			go_left(x);
	}
	x->push_up();
}
void Delete(Treap *&x,int y)
{
	if(y<x->val)Delete(x->ls,y);
	else if(y>x->val)Delete(x->rs,y);
	else
	{
		if(x->cnt>1)x->cnt--;
		else if(!x->ls)x = x->rs;
		else if(!x->rs)x = x->ls;
		else
		{
			go_left(x);
			Delete(x->ls,y);
			if(x->ls&&x->ls->key>x->key)
				go_right(x);
		}
	}
	if(x)x->push_up();
}
int tmp;
void get_rank(Treap *x,int y)
{
	if(!x)return ;
	if(x->val==y)
	{
		if(x->ls)tmp+=x->ls->size;
		return ;
	}else if(y<x->val)get_rank(x->ls,y);
	else
	{
		tmp+=x->cnt;
		if(x->ls)tmp+=x->ls->size;
		get_rank(x->rs,y);
	}
}
void get_rank(int p,int l,int r,int a,int b,int y)
{
	if(l>=a&&r<=b){get_rank(root[p],y);return ;}
	int mid = (l+r)>>1;
	if(a<=mid)get_rank(p<<1,l,mid,a,b,y);
	if(b >mid)get_rank(p<<1|1,mid+1,r,a,b,y);
}
void build(int p,int l,int r,int pos,int num)
{
	Insert(root[p],num);
	if(l==r)return ;
	int mid = (l+r)>>1;
	if(pos<=mid)build(p<<1,l,mid,pos,num);
	else build(p<<1|1,mid+1,r,pos,num);
}
void build()
{
	for(int i = 1;i<=cnt;i++)
		build(1,1,cnt,i,d[id[i]]);
}
void get_rank(int x,int y,int k)
{
	while(top[x]!=top[y])
	{
		if(dpt[top[x]]<dpt[top[y]])swap(x,y);
		get_rank(1,1,n,w[top[x]],w[x],k);
		x = fa[top[x]];
	}
	if(dpt[x]<dpt[y])swap(x,y);
	get_rank(1,1,n,w[y],w[x],k);
}
void get_number(int x,int y,int k)
{
	int l = -INF,r = 1,ans;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		tmp = 1;
		get_rank(x,y,mid);
		if(tmp<=k){l = mid+1;ans= mid;}
		else r = mid-1;
	}
	if(ans!=1)printf("%d\n",-ans);
	else printf("invalid request!\n");
}
void change(int p,int l,int r,int pos,int a,int b)
{
	Delete(root[p],a);
	Insert(root[p],b);
	if(l==r)return ;
	int mid = (l+r)>>1;
	if(pos<=mid)change(p<<1,l,mid,pos,a,b);
	else change(p<<1|1,mid+1,r,pos,a,b);
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){scanf("%d",&d[i]);d[i] = -d[i];}
	int x,y;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs1(1,0);
	dfs2(1,1);
	build();
	int k,a,b;
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d%d",&k,&a,&b);
		if(k==0)
		{
			change(1,1,n,w[a],d[a],-b);
			d[a] = -b;
		}else
			get_number(a,b,k);
	}
	return 0;
}
