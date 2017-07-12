
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int INF = 1e8+1;
struct Treap
{
	Treap *ls,*rs;
	int cnt,val,size,key;
	Treap(int x);
	void push_up();
};
Treap :: Treap(int x)
{
	ls = rs = NULL;
	cnt = size = 1;
	val = x;
	key = rand();
}
void Treap :: push_up()
{
	size =cnt;
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
	if(x==NULL)
		x = new Treap(y);
	else if(x->val==y)
		x->cnt++;
	else if(y<x->val)
	{
		Insert(x->ls,y);
		if(x->ls->key>x->key)
			go_right(x);
	}
	else
	{
		Insert(x->rs,y);
		if(x->rs->key>x->key)
			go_left(x);
	}
	x->push_up();
}
void Delete(Treap *&x,int y)
{
	if(x==NULL)return ;
	else if(x->val==y)
	{
		if(x->cnt>1)x->cnt--;
		else if(!x->ls)x= x->rs;
		else if(!x->rs)x= x->ls;
		else
		{
			go_left(x);
			Delete(x->ls,y);
			if(x->ls&&x->ls->key>x->key)
				go_right(x);
		}
	}else if(y<x->val)
		Delete(x->ls,y);
	else Delete(x->rs,y);
	if(x)x->push_up();
}
int get_rank(Treap *x,int y)
{
	if(x==NULL)return 0;
	if(x->val==y)
	{
		if(x->ls)return x->ls->size;
		else return 0;
	}else if(y<x->val)
		return get_rank(x->ls,y);
	else
	{
		int tmp = x->cnt;
		if(x->ls)tmp+=x->ls->size;
		return tmp+get_rank(x->rs,y);
	}
}
int get_num(Treap *x,int y)
{
    if(!x)return 0;
    int tmp = 0;
    if(x->ls)tmp+=x->ls->size;
	if(y<=tmp)
		return get_num(x->ls,y);
    else if(y>tmp+x->cnt)
		return get_num(x->rs,y-tmp-x->cnt);
    else return x->val;
}
int pre,sub;
void get_pre(Treap *x,int y)
{
	if(x==NULL)return ;
	else if(y<=x->val)get_pre(x->ls,y);
	else
	{
		pre = max(pre,x->val);
		get_pre(x->rs,y);
	}
}
void get_sub(Treap *x,int y)
{
	if(x==NULL)return ;
	else if(y<x->val)
	{
		sub = min(sub,x->val);
		get_sub(x->ls,y);
	}else get_sub(x->rs,y);
}
int main()
{
	int n,opt,x;
	scanf("%d",&n);
	Treap *root = NULL;
	while(n--)
	{
		scanf("%d%d",&opt,&x);
		if(opt==1)Insert(root,x);
		else if(opt==2)Delete(root,x);
		else if(opt==3)printf("%d\n",get_rank(root,x)+1);
		else if(opt==4)printf("%d\n",get_num(root,x));
		else if(opt==5)pre = -INF,get_pre(root,x),printf("%d\n",pre);
		else sub = INF,get_sub(root,x),printf("%d\n",sub);
	}
	return 0;
}
