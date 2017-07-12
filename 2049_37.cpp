
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 200005;
struct Splay
{
	Splay *ls,*rs,*fa;
	bool rev;
	Splay();
	void reverse();
	void push_down();
}*null = new Splay(),tree[N];
void Splay :: push_down()
{
	if(fa->ls==this||fa->rs==this)
		fa->push_down();
	if(rev)
	{
		swap(ls->ls,ls->rs);
		swap(rs->ls,rs->rs);
		ls->rev^=1;
		rs->rev^=1;
		rev = 0;
	}
}
Splay :: Splay()
{
	ls = rs = fa = null;
	rev = false;
}
void Splay :: reverse()
{
	swap(ls,rs);
	rev^=1;
}
void go_left(Splay *x)
{
	Splay *y = x->fa;
	y->push_down();
	x->push_down();
	y->rs = x->ls;
	x->ls->fa = y;
	x->ls = y;
	x->fa = y->fa;
	if(y==y->fa->ls)
		y->fa->ls = x;
	else if(y==y->fa->rs)
		y->fa->rs = x;
	y->fa = x;
}
void go_right(Splay *x)
{
	Splay *y = x->fa;
	y->push_down();
	x->push_down();
	y->ls = x->rs;
	x->rs->fa = y;
	x->rs = y;
	x->fa = y->fa;
	if(y==y->fa->ls)
		y->fa->ls = x;
	else if(y==y->fa->rs)
		y->fa->rs = x;
	y->fa = x;
}
void splay(Splay *x)
{
	x->push_down();
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
			if(y==z->rs)go_left(y);
			go_left(x);
		}
	}
}
void access(Splay *x)
{
	Splay *y = null;
	while(x!=null)
	{
		splay(x);
		x->rs = y;
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
	while(x->fa!=null)
		x = x->fa;
	return x;
}
void link(Splay *x,Splay *y)
{
	move_to_root(x);
	x->fa = y;
}
void cut(Splay *x,Splay *y)
{
	move_to_root(x);
	access(y);
	splay(y);
	x->fa = null;
	y->ls = null;
}
int main()
{
	null->ls = null->rs = null->fa = null;
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	char opt[10];
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",opt);
		scanf("%d%d",&x,&y);
		if(opt[0]=='C')link(&tree[x],&tree[y]);
		else if(opt[0]=='D')cut(&tree[x],&tree[y]);
		else
		{
			Splay *tmp = find_root(&tree[x]);
			if(tmp==find_root(&tree[y]))printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
}
