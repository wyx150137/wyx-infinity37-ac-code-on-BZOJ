
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 300005;
struct Splay
{
	Splay *ls,*rs,*fa;
	int val,sum;
	bool rev;
	Splay(int x);
	void reverse();
	void push_up();
	void push_down();
}*null = new Splay(0),*tree[N];
Splay :: Splay(int x)
{
	ls = rs = fa = null;
	val = x;sum = x;
	rev = false;
}
void Splay :: reverse()
{
	swap(ls,rs);
	rev ^=1;
}
void Splay :: push_down()
{
	if(this==fa->ls||this==fa->rs)
		fa->push_down();
	if(rev)
	{
		ls->reverse();
		rs->reverse();
		rev = 0;
	}
}
void Splay :: push_up()
{
	sum = ls->sum ^ rs->sum ^ val;
}
void go_left(Splay *x)
{
	Splay *y = x->fa;
	y->rs = x->ls;
	x->ls->fa = y;
	x->ls = y;
	x->fa = y->fa;
	if(y==y->fa->ls)
		y->fa->ls = x;
	else if(y==y->fa->rs)
		y->fa->rs = x;
	y->fa = x;
	y->push_up();
}
void go_right(Splay *x)
{
	Splay *y = x->fa;
	y->ls = x->rs;
	x->rs->fa = y;
	x->rs = y;
	x->fa = y->fa;
	if(y==y->fa->ls)
		y->fa->ls = x;
	else if(y==y->fa->rs)
		y->fa->rs = x;
	y->fa = x;
	y->push_up();
}
void splay(Splay *x)
{
	Splay *y,*z;
	x->push_down();
	while(x==x->fa->ls||x==x->fa->rs)
	{
		y = x->fa,z = y->fa;
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
void access(Splay *x)
{
	Splay *y = null;
	while(x!=null)
	{
		splay(x);
		x->rs = y;
		x->push_up();
		y = x;
		x = x->fa;
	}
}
void move_to_root(Splay *x)
{
	access(x);
	splay(x);
	x->reverse();
}
Splay* find_root(Splay *x)
{
	while(x->fa!=null)x = x->fa;
	return x;
}
void link(Splay *x,Splay *y)
{
	if(find_root(x)==find_root(y))return ;
	move_to_root(x);
	x->fa = y;
}
void cut(Splay *x,Splay *y)
{
	if(x==y||find_root(x)!=find_root(y))return ;
	move_to_root(x);
	access(y);
	splay(y);
	if(y->ls!=x)return ;
	x->fa = null;
	y->ls = null;
	y->push_up();
}
void change(Splay *x,int y)
{
	splay(x);
	x->val = y;
	x->push_up();
}
void qurey(Splay *x,Splay *y)
{
	move_to_root(x);
	access(y);
	splay(y);
	printf("%d\n",y->sum);
}
int main()
{
	int n,m,x,y,c;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		tree[i] = new Splay(x);
	}
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&c,&x,&y);
		switch(c)
		{
			case 0:qurey(tree[x],tree[y]);break;
			case 1:link(tree[x],tree[y]);break;
			case 2:cut(tree[x],tree[y]);break;
			case 3:change(tree[x],y);break;
		}
	}
	return 0;
}
