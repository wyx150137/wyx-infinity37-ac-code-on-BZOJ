
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL INF = 1e18;
const int mod = 1e6;
struct Treap
{
	Treap *ls,*rs;
	int key,cnt,size;
	LL val;
	Treap(int x);
	void push_up();
}*root0,*root1;
Treap :: Treap(int x)
{
	ls = rs = NULL;
	key = rand();
	val = x;
	cnt = size = 1;
}
void Treap :: push_up()
{
	size = cnt;
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
void insert(Treap *&x,int y)
{
	if(!x){x = new Treap(y);return ;}
	if(x->val==y)x->cnt++;
	else if(y<x->val)
	{
		insert(x->ls,y);
		if(x->ls->key<x->key)
			go_right(x);
	}else
	{
		insert(x->rs,y);
		if(x->rs->key<x->key)
			go_left(x);
	}
	x->push_up();
}
void dele(Treap *&x,int y)
{
	if(y<x->val)
		dele(x->ls,y);
	else if(y>x->val)
		dele(x->rs,y);
	else
	{
		if(x->cnt>1)x->cnt--;
		else if(!x->ls)
			x = x->rs;
		else if(!x->rs)
			x = x->ls;
		else
		{
			go_left(x);
			dele(x->ls,y);
			if(x->ls && x->ls->key<x->key)
				go_right(x);
		}
	}
	if(x)x->push_up();
}
LL ans;
void ask_pro(Treap *x,int y)
{
	if(!x)return ;
	if(x->val<y)
	{
		ans = max(ans,x->val);
		ask_pro(x->rs,y);
	}
	else ask_pro(x->ls,y);
}
void ask_sub(Treap *x,int y)
{
	if(!x)return ;
	if(x->val>y)
	{
		ans = min(ans,x->val);
		ask_sub(x->ls,y);
	}
	else ask_sub(x->rs,y);
}
int main()
{
	int n,a,b;
	scanf("%d",&n);
	LL sum = 0;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&a,&b);
		if(a==0&&!root1)
			insert(root0,b);
		else if(a==1&&!root0)
			insert(root1,b);
		else
		{
			if(a==0)
			{
				ans = 0;
				ask_pro(root1,b);
				int tmp1 = ans;
				ans = INF;
				ask_sub(root1,b);
				int tmp2 = ans;
				if(tmp1==0){sum+=abs(b-tmp2);dele(root1,tmp2);}
				else if(tmp2==INF){sum+=abs(b-tmp1);dele(root1,tmp1);}
				else if(abs(b-tmp1)>abs(b-tmp2)){sum+=abs(b-tmp2);dele(root1,tmp2);}
				else if(abs(b-tmp1)<abs(b-tmp2)){sum+=abs(b-tmp1);dele(root1,tmp1);}
				else{sum+=abs(b-tmp1);dele(root1,tmp1);}
			}else
			{
				ans = 0;
				ask_pro(root0,b);
				int tmp1 = ans;
				ans = INF;
				ask_sub(root0,b);
				int tmp2 = ans;
				if(tmp1==0){sum+=abs(b-tmp2);dele(root0,tmp2);}
				else if(tmp2==INF){sum+=abs(b-tmp1);dele(root0,tmp1);}
				else if(abs(b-tmp1)>abs(b-tmp2)){sum+=abs(b-tmp2);dele(root0,tmp2);}
				else if(abs(b-tmp1)<abs(b-tmp2)){sum+=abs(b-tmp1);dele(root0,tmp1);}
				else{sum+=abs(b-tmp1);dele(root0,tmp1);}
			}
		}
	}
	printf("%lld\n",sum%mod);
	return 0;
}
