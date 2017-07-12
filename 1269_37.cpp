
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
struct splay
{
	splay *ls,*rs,*fa;
	bool rev;
	int size;char c;
	splay(char c);
	void push_up();
	void push_down();
	void reverse();
}*null=new splay(0),*root=null;
splay :: splay(char C)
{
	ls = rs = fa = null;
	rev = false;
	size = C?1:0;
	c = C;
}
void splay :: push_up()
{
	size = ls->size+(c!=0)+rs->size;
}
void splay :: push_down()
{
	if(rev)
	{
		ls->reverse();
		rs->reverse();
		rev = false;
	}
}
void splay :: reverse()
{
	rev^=1;
	swap(ls,rs);
}
void go_left(splay *x)
{
	splay *y = x->fa;
	y->push_down();
	x->push_down();
	y->rs = x->ls;
	x->ls->fa = y;
	x->ls = y;
	x->fa=y->fa;
	if(y==y->fa->ls)
		y->fa->ls = x;
	else if(y==y->fa->rs)
		y->fa->rs = x;
	y->fa = x;
	y->push_up();
	if(root==y)root=x;
}
void go_right(splay *x)
{
	splay *y = x->fa;
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
	y->push_up();
	if(root==y)root=x;
}
void Splay (splay *x,splay *tar)
{
	while(true)
	{
		splay *y = x->fa,*z = x->fa;
		if(y==tar)break;
		if(z==tar)
		{
			if(y==x->ls)go_right(x);
			else go_left(x);
			break;
		}else
		{
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
}
void find(splay *x,int y,splay *z)
{
	while(true)
	{
		x->push_down();
		if(y<=x->ls->size)
			x = x->ls;
		else
		{
			y-=x->ls->size;
			if(y==1)break;
			y--;x=x->rs;
		}
	}
	Splay(x,z);
}
char s[1<<21];
void build(splay *&x,int l,int r)
{
	if(l>r)return ;
	int mid = (l+r)>>1;
	x = new splay(s[mid]);
	build(x->ls,l,mid-1);
	build(x->rs,mid+1,r);
	if(x->ls!=null)x->ls->fa=x;
	if(x->rs!=null)x->rs->fa=x;
	x->push_up();
}
int pointer;
int main()
{
	char opt[20];
	int m,lth;
	scanf("%d",&m);
	root=new splay('\n');
	root->rs=new splay('\n');
	root->rs->fa= root;
	root->push_up();
	while(m--)
	{
		scanf("%s",opt);
		if(opt[0]=='M')
			scanf("%d",&pointer);
		else if(opt[0]=='I')
		{
			scanf("%d",&lth);
			do s[0]=getchar();while(s[0]=='\n'||s[0]=='\r');
			if(lth^1)gets(s+1);
			find(root,pointer+1,null);
			find(root,pointer+2,root);
			build(root->rs->ls,0,lth-1);
			root->rs->ls->fa=root->rs;
			root->rs->push_up();
			root->push_up();
		}else if(opt[0]=='D')
		{
			scanf("%d",&lth);
			find(root,pointer+1,null);
			find(root,pointer+lth+2,root);
			root->rs->ls=null;
			root->rs->push_up();
			root->push_up();
		}else if(opt[0]=='R')
		{
			scanf("%d",&lth);
			find(root,pointer+1,null);
			find(root,pointer+lth+2,root);
			root->rs->ls->reverse();
		}else if(opt[0]=='G')
		{
			find(root,pointer+2,null);
			printf("%c\n",root->c);
		}else if(opt[0]=='P')
			pointer--;
		else pointer++;
	}
	return 0;
}
