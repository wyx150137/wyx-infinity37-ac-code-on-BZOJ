
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
struct Treap{
	Treap *ls,*rs;
	int key,val,cnt,size;
	Treap(int x)
	{
		ls = rs = NULL;
		key = rand();
		cnt = size = 1;
		val = x;
	}
	void push_up()
	{
		size = cnt;
		if(ls)size+=ls->size;
		if(rs)size+=rs->size;
	}
}*root = NULL;
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
	else if(y>x->val)
	{
		Insert(x->rs,y);
		if(x->rs->key > x->key)
			go_left(x);
	}
	else
	{
		Insert(x->ls,y);
		if(x->ls->key > x->key)
			go_right(x);
	}
	x->push_up();
}
int get_pre(Treap *x,int y)
{
	if(!x)return -0x3f3f3f3f;
	if(x->val>y)return get_pre(x->ls,y);
	else return max(x->val,get_pre(x->rs,y));
}
int get_suc(Treap *x,int y)
{
	if(!x)return 0x3f3f3f3f;
	if(x->val<y)return get_suc(x->rs,y);
	else return min(x->val,get_suc(x->ls,y));
}
int main()
{
	int n,x,ans = 0;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		if(i==1){ans+=x;Insert(root,x);}
		else
		{
			int tmp = get_pre(root,x),minn = INF;
			if(tmp!=-INF) minn = x-tmp;
			tmp = get_suc(root,x);
			if(tmp!=INF)minn = min(minn,tmp-x);
			ans+=minn;
			Insert(root,x);
		}
	}
	printf("%d\n",ans);
	return 0;
}
