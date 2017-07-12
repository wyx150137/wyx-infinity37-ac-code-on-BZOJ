
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e4+5;
const int C = 1e6+5;
const int INF = 0x3f3f3f3f;
int n,m;
struct Treap
{
	Treap *ls,*rs;
	int cnt,val,size,key;
	Treap(int x);
	void push_up();
}*root[N<<2],*col[C];
Treap :: Treap(int x)
{
	ls = rs = NULL;
	cnt = size = 1;
	val = x;
	key = rand();
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
	if(!x)return ;
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
void get_less(Treap *x,int y)
{
	if(!x)return ;
	if(x->val==y)
	{
		if(x->ls)tmp+=x->ls->size;
		return ;
	}else if(y<x->val)get_less(x->ls,y);
	else
	{
		if(x->ls)tmp+=x->ls->size;
		tmp+=x->cnt;
		get_less(x->rs,y);
	}
}
void get_less(int p,int l,int r,int a,int b,int y)
{
	if(l>=a&&r<=b){get_less(root[p],y);return ;}
	int mid = (l+r)>>1;
	if(a<=mid)get_less(p<<1,l,mid,a,b,y);
	if(b >mid)get_less(p<<1|1,mid+1,r,a,b,y);
}
int tt;
void get_pre(Treap *x,int y)
{
	if(!x)return ;
	if(x->val>=y)get_pre(x->ls,y);
	else
	{
		tt = max(tt,x->val);
		get_pre(x->rs,y);
	}
}
void get_sub(Treap *x,int y)
{
	if(!x)return ;
	if(x->val<=y)get_sub(x->rs,y);
	else
	{
		tt = min(tt,x->val);
		get_sub(x->ls,y);
	}
}
int pre[N],last[C],color[N];
void build(int p,int l,int r,int pos,int val)
{
	Insert(root[p],val);
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(pos<=mid)build(p<<1,l,mid,pos,val);
	else build(p<<1|1,mid+1,r,pos,val);
}
void change(int p,int l,int r,int pos,int a,int b)
{
	Delete(root[p],a);
	Insert(root[p],b);
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(pos<=mid)change(p<<1,l,mid,pos,a,b);
	else change(p<<1|1,mid+1,r,pos,a,b);
}
int main()
{
	scanf("%d%d",&n,&m);
	int cc = 0;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&color[i]);
		pre[i] = last[color[i]];
		last[color[i]] = i;
		Insert(col[color[i]],i);
		cc = max(cc,color[i]);
	}
	for(int i = 1;i<= n;i++)
		build(1,1,n,i,pre[i]);
	for(int i=1;i<=1000000;i++)
		Insert(col[i],0),Insert(col[i],n+1);
	char opt[2];
	int x,y;
	while(m--)
	{
		scanf("%s%d%d",opt,&x,&y);
		if(opt[0]=='Q'){tmp = 0;get_less(1,1,n,x,y,x);printf("%d\n",tmp);}
		else
		{
			tt = INF;get_sub(col[color[x]],x);
			int nextA = tt;
			tt = 0;get_pre(col[y],x);
			int lastB = tt;
			tt = INF;get_sub(col[y],x);
			int nextB = tt;
			if(nextA!=n+1)change(1,1,n,nextA,x,pre[x]);
			change(1,1,n,x,pre[x],lastB);
			if(nextB!=n+1)change(1,1,n,nextB,lastB,x);
			Delete(col[color[x]],x);Insert(col[y],x);
			color[x] = y;
			if(nextA!=n+1)pre[nextA] = pre[x];
			pre[x] =lastB;
			if(nextB!=n+1)pre[nextB] = x;
		}
	}
	return 0;
}
