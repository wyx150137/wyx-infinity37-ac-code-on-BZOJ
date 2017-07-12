
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
const int INF = 1e8+1;
int a[N],n,m;
struct Treap
{
	Treap *ls,*rs;
	int val,key,cnt,size;
	Treap();
	Treap(int v);
	void Push_up();
}*root[N<<2];
Treap :: Treap()
{
	ls = rs = NULL;
	val = 0;
	key = rand();
	cnt = size = 0;
}
Treap :: Treap(int v)
{
	ls = rs = NULL;
	val = v;
	key = rand();
	cnt = size = 1;
}
void Treap :: Push_up()
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
	x->ls->Push_up();
	x->Push_up();
}
void go_right(Treap *&x)
{
	Treap *y = x->ls;
	x->ls = y->rs;
	y->rs = x;
	x = y;
	x->rs->Push_up();
	x->Push_up();
}
void Insert(Treap *&x,int y)
{
	if(!x){x=new Treap(y);return ;}
	if(x->val==y)x->cnt++;
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
	x->Push_up();
}
void Delete(Treap *&x,int y)
{
	if(!x)return ;
	if(y<x->val)Delete(x->ls,y);
	else if(y>x->val)Delete(x->rs,y);
	else
	{
		if(x->cnt>1)x->cnt--;
		else if(!x->ls)x = x->rs;
		else if(!x->rs)x = x->ls;
		else
		{
			go_left(x);
			Delete(x->ls,y);
			if(x->ls&&x->ls->key>x->key)
				go_right(x);
		}
	}
	if(x)x->Push_up();
}
int rnk;
void get_rank(Treap *x,int y)
{
	if(!x)return ;
	if(x->val==y)
	{
		if(x->ls)rnk+=x->ls->size;
		return ;
	}else if(y<x->val)get_rank(x->ls,y);
	else
	{
		rnk+=x->cnt;
		if(x->ls)rnk+=x->ls->size;
		get_rank(x->rs,y);
	}
}
void get_rank(int p,int l,int r,int a,int b,int v)
{
	if(l>=a&&r<=b){get_rank(root[p],v);return ;}
	int mid = (l+r)>>1;
	if(a<=mid)get_rank(p<<1,l,mid,a,b,v);
	if(b >mid)get_rank(p<<1|1,mid+1,r,a,b,v);
}
void Insert(int p,int l,int r,int pos,int v)
{
	Insert(root[p],v);
	if(l==r)return ;
	int mid = (l+r)>>1;
	if(pos<=mid)Insert(p<<1,l,mid,pos,v);
	else Insert(p<<1|1,mid+1,r,pos,v);
}
void Delete(int p,int l,int r,int pos,int v)
{
	Delete(root[p],v);
	if(l==r)return ;
	int mid = (l+r)>>1;
	if(pos<=mid)Delete(p<<1,l,mid,pos,v);
	else Delete(p<<1|1,mid+1,r,pos,v);
}
int pre,sub;
void get_pre(Treap *x,int y)
{
	if(!x)return ;
	if(x->val>=y)get_pre(x->ls,y);
	else
	{
		pre = max(pre,x->val);
		get_pre(x->rs,y);
	}
}
void get_sub(Treap *x,int y)
{
	if(!x)return ;
	if(x->val<=y)get_sub(x->rs,y);
	else
	{
		sub = min(sub,x->val);
		get_sub(x->ls,y);
	}
}
void get_pre(int p,int l,int r,int a,int b,int v)
{
	if(l>=a&&r<=b){get_pre(root[p],v);return ;}
	int mid = (l+r)>>1;
	if(a<=mid)get_pre(p<<1,l,mid,a,b,v);
	if(b >mid)get_pre(p<<1|1,mid+1,r,a,b,v);
}
void get_sub(int p,int l,int r,int a,int b,int v)
{
	if(l>=a&&r<=b){get_sub(root[p],v);return ;}
	int mid = (l+r)>>1;
	if(a<=mid)get_sub(p<<1,l,mid,a,b,v);
	if(b >mid)get_sub(p<<1|1,mid+1,r,a,b,v);
}
void Get_rank(int l,int r,int k)
{
	rnk = 1;
	get_rank(1,1,n,l,r,k);
	printf("%d\n",rnk);
}
void Get_sub(int l,int r,int k)
{
	sub = INF;
	get_sub(1,1,n,l,r,k);
	printf("%d\n",sub);
}
void Get_pre(int l,int r,int k)
{
	pre = -INF;
	get_pre(1,1,n,l,r,k);
	printf("%d\n",pre);
}
void Get_number(int x,int y,int c)
{
	int l = 0,r = INF,ans;
	while(l<=r)
	{
		int mid = (l+r)>>1;
		rnk = 1;
		get_rank(1,1,n,x,y,mid);
		if(rnk<=c){l=mid+1,ans=mid;}
		else {r = mid-1;}
	}
	printf("%d\n",ans);
}
void update(int pos,int c)
{
	Delete(1,1,n,pos,a[pos]);
	Insert(1,1,n,pos,c);
	a[pos] = c;
}
int main()
{
	srand(200037);
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)Insert(1,1,n,i,a[i]);
	while(m--)
	{
		int opt,l,r,x,pos;
		scanf("%d",&opt);
		if(opt==3){scanf("%d%d",&pos,&x);}
		else {scanf("%d%d%d",&l,&r,&x);}
		if(opt==1)Get_rank(l,r,x);
		else if(opt==2)Get_number(l,r,x);
		else if(opt==3)update(pos,x);
		else if(opt==4)Get_pre(l,r,x);
		else Get_sub(l,r,x);
	}
	return 0;
}
