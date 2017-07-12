
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int Inv = 20000307;
struct Splay 
{
	Splay *ls,*rs,*fa;
	int lazy_add,max_val,val;
	int size;
	bool lazy_rev;
	Splay(int x);
	void push_down();
	void push_up();
}*null = new Splay(0xefefefef),*root = null;
Splay :: Splay (int x)
{
	ls = rs = fa = null;
	lazy_add = lazy_rev = 0;
	max_val = val = x;
	size = null?1:0;
}
void Splay :: push_up()
{
	size = ls->size+rs->size+1;
	max_val = max(max(ls->max_val,rs->max_val),val);
}
void Splay :: push_down()
{
	if(this==null)return ;
	if(lazy_add)
	{
		if(ls!=null)
		{
			ls->lazy_add += lazy_add;
			ls->max_val+=lazy_add;
			ls->val+=lazy_add;
		}
		if(rs!=null)
		{
			rs->lazy_add += lazy_add;
			rs->max_val+=lazy_add;
			rs->val+=lazy_add;
		}
		lazy_add = 0;
	}
	if(lazy_rev)
	{
		swap(ls->ls,ls->rs);
		swap(rs->ls,rs->rs);
		ls->lazy_rev^=1;
		rs->lazy_rev^=1;
		lazy_rev = 0;
	}
}
void go_left(Splay *x)
{
	Splay *y = x->fa;
	x->push_down();
	y->push_down();
	y->rs = x->ls;
	x->ls->fa = y;
	x->ls = y;
	x->fa = y->fa;
	if(y==y->fa->ls)
		y->fa->ls = x;
	else y->fa->rs = x;
	y->fa = x;
	y->push_up();
	if(root==y)root = x;
}
void go_right(Splay *x)
{
	Splay *y = x->fa;
	x->push_down();
	y->push_down();
	y->ls = x->rs;
	x->rs->fa = y;
	x->rs = y;
	x->fa = y->fa;
	if(y==y->fa->ls)
		y->fa->ls = x;
	else y->fa->rs = x;
	y->fa = x;
	y->push_up();
	if(root==y)root = x;
}
void splay(Splay *x,Splay *tar)
{
	while(true)
	{
		Splay *y = x->fa;Splay *z = y->fa;
		if(y==tar)break;
		if(z==tar)
		{
			if(x==y->ls)go_right(x);
			else go_left(x);
			break;
		}
		if(x==y->ls)
		{
			if(y==z->ls)go_right(y);
			go_right(x);
		}else
		{
			if(y==z->rs)go_left(y);
			go_left(x);
		}
	}
	x->push_up();
}
void Find(Splay *x,int y,Splay *tar)
{
	while(true)
	{
		x->push_down();
		if(y<=x->ls->size)
			x = x->ls;
		else
		{
			y = y-x->ls->size;
			if(y==1)
				break;
			y--;
			x = x->rs;
		}
	}
	splay(x,tar);
}
void update()
{
	int l,r,c;
	scanf("%d%d%d",&l,&r,&c);
	Find(root,l,null);
	Find(root,r+2,root);
	root->rs->ls->val+=c;
	root->rs->ls->max_val+=c;
	root->rs->ls->lazy_add+=c;
	//root->rs->push_up();
	//root->push_up();
}
void reverse()
{
	int l,r;
	scanf("%d%d",&l,&r);
	Find(root,l,null);
	Find(root,r+2,root);
	Splay *tmp = root->rs->ls;
	tmp->lazy_rev^=1;
	swap(tmp->ls,tmp->rs);
}
void get_max()
{
	int l,r;
	scanf("%d%d",&l,&r);
	Find(root,l,null);
	Find(root,r+2,root);
	printf("%d\n",root->rs->ls->max_val);
}
/*
void Insert(Splay *&x,int y,Splay *from)
{
	if(x==null)
	{
		x = new Splay(y);
		x->fa = from;
		splay(x,null);
		return ;
	}
	x->push_down();
	Insert(x->rs,y,x);
}*/
void build(Splay *&x,int l,int r)
{
	if(r<l)return ;
	int mid = (l+r)>>1;
	x = new Splay(0);
	build(x->ls,l,mid-1);
	build(x->rs,mid+1,r);
	if(x->ls!=null)x->ls->fa = x;
	if(x->rs!=null)x->rs->fa = x;
	x->push_up();
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int opt;
	root = new Splay(Inv);
	root->rs = new Splay(Inv);
	build(root->rs->ls,1,n);
	root->rs->ls->fa = root->rs;
	root->rs->fa =root;
	root->rs->push_up();
	root->push_up();
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&opt);
		if(opt==1)update();
		else if(opt==2)reverse();
		else get_max();
	}
	return 0;
}
