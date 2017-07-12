
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
struct pas_seq
{
	int sum,lmax,rmax,lmin,rmin;
	void exc()
	{
		sum = -sum;
		swap(lmax,lmin);
		swap(rmax,rmin);
		lmax=-lmax,rmax=-rmax;
		lmin=-lmin,rmin=-rmin;
	}
	void rev()
	{
		swap(lmax,rmax);
		swap(lmin,rmin);
	}
	pas_seq(int x,int siz)
	{
		sum =siz*x;
		if(x==1)
			lmax=rmax=sum,lmin=rmin=0;
		else 
			lmin=rmin=sum,lmax=rmax=0;
	}
	friend pas_seq operator+(const pas_seq &a,const pas_seq &b)
	{
		pas_seq res(0,0);
		res.sum = a.sum+b.sum;
		res.lmax = max(a.lmax,a.sum+b.lmax);
		res.rmax = max(b.rmax,b.sum+a.rmax);
		res.lmin = min(a.lmin,a.sum+b.lmin);
		res.rmin = min(b.rmin,b.sum+a.rmin);
		return res;
	}
};
struct Splay
{
	Splay *ls,*rs,*fa;
	int cng,exc,size,val;
	bool rev;
	pas_seq *seq;
	Splay(int x);
	void push_up();
	void push_down();
}*null = new Splay(0),*root=null;
Splay :: Splay(int x)
{
	ls = rs = fa = null;
	cng = exc = rev = 0;
	val = x,size = (val==0?0:1);
	seq = new pas_seq(x,size);
}
void Splay :: push_up()
{
	size = ls->size+(val==0?0:1)+rs->size;
	*seq = (*ls->seq)+pas_seq(val,1)+(*rs->seq);
}
void Splay :: push_down()
{
	if(cng)
	{
		ls->val = ls->cng = cng;
		rs->val = rs->cng = cng;
		*ls->seq = pas_seq(cng,ls->size);
		*rs->seq = pas_seq(cng,rs->size);
		ls->rev = ls->exc = 0;
		rs->rev = rs->exc = 0;
		cng = 0;
	}
	if(rev)
	{
		ls->rev^=1;
		rs->rev^=1;
		ls->seq->rev();
		rs->seq->rev();
		swap(ls->ls,ls->rs);
		swap(rs->ls,rs->rs);
		rev = 0;
	}
	if(exc)
	{
		ls->exc^=1;
		rs->exc^=1;
		ls->val=-ls->val;
		rs->val=-rs->val;
		ls->seq->exc();
		rs->seq->exc();
		exc = 0;
	}
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
	y->fa= x;
	y->push_up();
	if(root==y)root=x;
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
	y->push_up();
	if(root==y)root=x;
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
void find(Splay *x,int y,Splay *z)
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
void Insert(Splay *&x,int y,Splay *z)
{
	if(x==null)
	{
		x = new Splay(y);
		x->fa = z;
		x->push_up();
		splay(x,null);
		return ;
	}
	x->push_down();
	Insert(x->rs,y,x);
}
char s[N];
int main()
{
	int n,m,l,r;
	char opt[10];
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	Insert(root,-2,null);
	for(int i = 1;i<= n;i++)
		Insert(root,s[i]=='('?1:-1,null);
	Insert(root,2,null);
	while(m--)
	{
		scanf("%s%d%d",opt,&l,&r);
		find(root,l,null);
		find(root,r+2,root);
		Splay *tmp = root->rs->ls;
		if(opt[0]=='R')
		{
			scanf("%s",opt);
			int v = opt[0]=='('?1:-1;
			tmp->cng = tmp->val = v;
			*tmp->seq = pas_seq(v,tmp->size);
			tmp->exc = tmp->rev = 0;
		}else if(opt[0]=='S')
		{
			tmp->rev^=1;
			swap(tmp->ls,tmp->rs);
			tmp->seq->rev();
		}else if(opt[0]=='I')
		{
			tmp->exc^=1;
			tmp->val=-tmp->val;
			tmp->seq->exc();
		}else
		{
			l=(int)ceil(abs(tmp->seq->lmin)/2.0);
	           	r=(int)ceil(abs(tmp->seq->rmax)/2.0);
            		printf("%d\n",l+r);
		}
	}
	return 0;
}
