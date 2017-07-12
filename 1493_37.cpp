
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int Inv = 20000307;
int n,m;
struct col_seg
{
	int cnt,lc,rc;
	col_seg(int x)
	{
		cnt = 1;
		if(!x)
			cnt = 0;
		lc = rc = x;
	}
	col_seg();
	col_seg uni(col_seg x,col_seg y)
	{
		col_seg re(0);
		re.lc = x.lc?x.lc:y.lc;
		re.rc = y.rc?y.rc:x.rc;
		re.cnt = x.cnt+y.cnt-(x.rc==y.lc);
		return re;
	}
};
col_seg operator + (const col_seg x,const col_seg y)
{
	col_seg re(0);
	re.lc = x.lc?x.lc:y.lc;
	re.rc = y.rc?y.rc:x.rc;
	re.cnt = x.cnt+y.cnt-(x.rc==y.lc);
	return re;
}
struct Splay
{
	int num,size;
	Splay *ls,*rs,*fa;
	col_seg *col;
	int lazy_r,lazy_c;
	Splay(int x);
	void push_up();
	void push_down();
}*null = new Splay(0),*root = null;
Splay :: Splay(int x)
{
	ls = rs = fa = null;
	num = x;
	size = x?1:0;
	lazy_r = lazy_c = 0;
	col = new col_seg(x);
}
void Splay :: push_up()
{
	size = ls->size+rs->size+1;
	*col = (*ls->col)+col_seg(num)+(*rs->col);
}
void Splay :: push_down()
{
	if(lazy_r)
	{
		ls->lazy_r ^= 1;
		rs->lazy_r ^= 1;
		swap(ls->ls,ls->rs);
		swap(rs->ls,rs->rs);
		swap(ls->col->lc,ls->col->rc);
		swap(rs->col->lc,rs->col->rc);
		lazy_r = 0;
	}
	if(lazy_c)
	{
		if(ls!=null)
		{	
			ls->num = ls->lazy_c = lazy_c;
			*ls->col = col_seg(lazy_c);
		}
		if(rs!=null)
		{
			rs->num = rs->lazy_c = lazy_c;
			*rs->col = col_seg(lazy_c);
		}
		lazy_c = 0;
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
	if(y->fa->ls==y)
		y->fa->ls = x;
	else y->fa->rs = x;
	y->fa = x;
	y->push_up();
	if(y==root)root = x;
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
	if(y->fa->ls==y)
		y->fa->ls = x;
	else y->fa->rs = x;
	y->fa = x;
	y->push_up();
	if(y==root)root = x;
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
		x->push_down();
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
}
void R()
{
	int x;
	scanf("%d",&x);
	Find(root,n-x+1,null);
	Find(root,n+2,root);
	Splay *tmp = root->rs->ls;
	root->rs->ls = null;
	root->rs->push_up();
	root->push_up();
	Find(root,1,null);
	Find(root,2,root);
	root->rs->ls = tmp;
	tmp->fa = root->rs;
	root->rs->push_up();
	root->push_up();
}
void F()
{
	Find(root,2,null);
	Find(root,n+2,root);
	Splay *tmp = root->rs->ls;
	tmp->lazy_r ^= 1;
	swap(tmp->ls,tmp->rs);
	swap(tmp->col->lc,tmp->col->rc);
}
void S()
{
	int x,y;
	scanf("%d%d",&x,&y);
	if(x==y)return ;
	else if(x>y)swap(x,y);
	Find(root,x+1,null);
	Find(root,y+1,root);
	swap(root->rs->num,root->num);
}
void P()
{
	int x,y,z;
	scanf("%d%d%d",&x,&y,&z);
	if(x<=y)
	{
		Find(root,x,null);
		Find(root,y+2,root);
		Splay *tmp = root->rs->ls;
		tmp->num = tmp->lazy_c = z;
		*tmp->col = col_seg(z);
	}else
	{
		Find(root,x,null);
		Find(root,n+2,root);
		Splay *tmp = root->rs->ls;
		tmp->num = tmp->lazy_c = z;
		*tmp->col = col_seg(z);
		Find(root,1,null);
		Find(root,y+2,root);
		tmp = root->rs->ls;
		tmp->num = tmp->lazy_c = z;
		*tmp->col = col_seg(z);
	}
}
void C()
{
	Find(root,1,null);
	Find(root,n+2,root);
	Splay *tmp = root->rs->ls;
	int z = tmp->col->cnt-(tmp->col->lc==tmp->col->rc);
	if(!z)z++;
	printf("%d\n",z);
}
void CS()
{
	int x,y;
	scanf("%d%d",&x,&y);
	if(x<=y)
	{
		Find(root,x,null);
		Find(root,y+2,root);
		Splay *tmp = root->rs->ls;
		printf("%d\n",tmp->col->cnt);
	}
	else
	{
		Find(root,x,null);
		Find(root,n+2,root);
		Splay *tmp = root->rs->ls;
		col_seg stmp = *tmp->col;
		Find(root,1,null);
		Find(root,y+2,root);
		tmp = root->rs->ls;
		stmp = stmp+(*tmp->col);
		printf("%d\n",stmp.cnt);
	}
}
int main()
{
	int x,c;
	char opt[10];
	scanf("%d%d",&n,&c);
	Insert(root,Inv,null);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		Insert(root,x,null);
	}
	Insert(root,Inv,null);
	scanf("%d",&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",opt);
		if(opt[0]=='R')R();
		else if(opt[0]=='F')F();
		else if(opt[0]=='S')S();
		else if(opt[0]=='P')P();
		else if(opt[0]=='C'&&!opt[1])C();
		else CS();
	}
	return 0;
}
