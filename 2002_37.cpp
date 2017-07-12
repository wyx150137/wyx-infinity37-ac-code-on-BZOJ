
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
const int M = 2e5+5;
struct Splay{
	Splay *fa,*ls,*rs;
	int size;
	void push_up();
	Splay();
}*null = new Splay(),tree[M];
void Splay :: push_up()
{
	size = ls->size+rs->size+1;
}
Splay :: Splay()
{
	ls = rs = fa = null;
	size = 1;
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
	while(x==x->fa->ls||x==x->fa->rs)
	{
		y = x->fa,z = y->fa;
		if(x==y->ls)
		{
			if(y==z->ls)go_right(y);
			go_right(x);
		}else
		{
			if(y==x->rs)go_left(y);
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
void link(Splay *x,Splay *y)
{
	access(x);
	splay(x);
	x->ls->fa = null;
	x->ls = null;
	x->fa = y;
	x->push_up();
}
int main()
{
	null->ls = null->rs = null->fa = null;
	null ->size = 0;
	int n,x;
	Splay *root;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		if(i+x<=n)
			tree[i].fa = &tree[i+x];
	}
	int m,p,y;
	scanf("%d",&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&p);
		if(p==1)
		{
			scanf("%d",&x);x++;
			access(&tree[x]);
			splay(&tree[x]);
			printf("%d\n",tree[x].size);
		}else
		{
			scanf("%d%d",&x,&y);x++;
			if(x+y<=n)root = &tree[x+y];
			else root = null;
			link(&tree[x],root);
		}
	}
	return 0;
}
