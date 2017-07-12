
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
struct Splay
{
	Splay *ls,*rs,*fa;
	char c;
	int size;
	Splay(char S);
	void push_up();
}*null =new Splay(0),*root = null;
Splay :: Splay (char S)
{
	ls = rs = fa = null;
	c = S;
	size = c?1:0;
}
void Splay :: push_up()
{
	size = ls->size+rs->size+1;
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
	else y->fa->rs = x;
	y->fa = x;
	y->push_up();
	if(root==y)root = x;
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
	else y->fa->rs = x;
	y->fa = x;
	y->push_up();
	if(root==y)root = x;
}
void splay(Splay *x,Splay *tar)
{
	while(true)
	{
		Splay *y = x->fa,*z = y->fa;
		if(y==tar)break;
		if(z==tar)
		{
			if(x==y->ls)go_right(x);
			else go_left(x);
			break;
		}
		if(x==y->ls)
		{
			if(y==z->ls)
				go_right(y);
			go_right(x);
		}else
		{
			if(y==z->rs)
				go_left(y);
			go_left(x);
		}
	}
	x->push_up();
}
void Find(Splay *x,int y,Splay *z)
{
	while(true)
	{
		if(y<=x->ls->size)
			x = x->ls;
		else
		{
			y-=x->ls->size;
			if(y==1)break;
			y--;
			x = x->rs;
		}
	}
	splay(x,z);
}
char s[1<<21];
void build(Splay *&x,int l,int r)
{
	if(r<l)return ;
	int mid = (l+r)>>1;
	x = new Splay(s[mid]);
	build(x->ls,l,mid-1);
	build(x->rs,mid+1,r);
	if(x->ls!=null)
		x->ls->fa = x;
	if(x->rs!=null)
		x->rs->fa = x;
	x->push_up();
}
int now;
void print(Splay *x)
{
	if(x==null)return ;
	print(x->ls);
	putchar(x->c);
	print(x->rs);
}
int main()
{
	int m,x;
	char opt[105];
	scanf("%d",&m);
	root = new Splay('\n');
	root->rs = new Splay('\n');
	root->rs->fa = root;
	root->push_up();
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",opt);
		if(opt[0]=='I')
		{
			scanf("%d",&x);
			for(int j= 0;j<x;j++)
			{
				do s[j] = getchar();while(s[j]<32||s[j]>126);
			}
			Find(root,now+1,null);
			Find(root,now+2,root);
			build(root->rs->ls,0,x-1);
			root->rs->ls->fa = root->rs;
			root->rs->push_up();
			root->push_up();
		}
		else if(opt[0]=='D')
		{
			scanf("%d",&x);
			Find(root,now+1,null);
			Find(root,min(now+2+x,root->size),root);
			root->rs->ls = null;
			root->rs->push_up();
			root->push_up();
		}
		else if(opt[0]=='G')
		{
			scanf("%d",&x);
			Find(root,now+1,null);
			Find(root,min(now+2+x,root->size),root);
			print(root->rs->ls);
			puts("");
		}
		else if(opt[0]=='M')
			scanf("%d",&now);
		else if(opt[0]=='P')
			now--;
		else now++;
	}
	return 0;
}
