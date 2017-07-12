
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 10005;
const int INF = 1e9+1;
int n,m;
struct Treap
{
	Treap *ls,*rs;
	int cnt,val,key,size;
	Treap(int x);
	void push_up();
}*root[N<<2];
Treap :: Treap(int x)
{
	ls = rs = NULL;
	val = x;
	key = rand();
	size = cnt = 1;
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
void Insert(Treap *&x,int y)
{
	if(!x){x = new Treap(y);return ;}
	if(x->val==y)x->cnt++;
	else if(x->val<y)
	{
		Insert(x->rs,y);
		if(x->rs->key>x->key)
			go_left(x);
	}else
	{
		Insert(x->ls,y);
		if(x->ls->key>x->key)
			go_right(x);
	}
	x->push_up();
}
void Delete(Treap *&x,int y)
{
	if(y<x->val)
		Delete(x->ls,y);
	else if(y>x->val)
		Delete(x->rs,y);
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
	if(x)x->push_up();
}
void build(int p,int l,int r,int pos,int num)
{
	Insert(root[p],num);
	if(l==r)return ;
	int mid = (l+r)>>1;
	if(pos<=mid)build(p<<1,l,mid,pos,num);
	else build(p<<1|1,mid+1,r,pos,num);
}
int tmp;
void get_rank(Treap *x,int y)
{
	if(!x)return ;
	if(x->val==y)
	{
		if(x->ls)
			tmp+=x->ls->size;
		return ;
	}else if(y<x->val)get_rank(x->ls,y);
	else
	{
		tmp+=x->cnt;
		if(x->ls)tmp+=x->ls->size;
		get_rank(x->rs,y);
	}
}
void get_rank(int p,int l,int r,int a,int b,int y)
{
	if(l>=a&&r<=b){get_rank(root[p],y);return ;}
	int mid=(l+r)>>1;
	if(a<=mid)get_rank(p<<1,l,mid,a,b,y);
	if(b >mid)get_rank(p<<1|1,mid+1,r,a,b,y);
}
void get_number(int x,int y,int c)
{
	int l = 0,r = INF;int ans;
	while(l<=r)
	{
		int mid = (l+r)>>1;
		tmp = 1;
		get_rank(1,1,n,x,y,mid);
		if(tmp<=c){l = mid+1;ans = mid;}
		else r = mid-1;
	}
	printf("%d\n",ans);
}
void change(int p,int l,int r,int pos,int a,int b)
{
	Delete(root[p],a);
	Insert(root[p],b);
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(pos<=mid)change(p<<1,l,mid,pos,a,b);
	else change(p<<1|1,mid+1,r,pos,a,b);
}
int a[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)build(1,1,n,i,a[i]);
	char opt[3];int x,y,k;
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",opt);
		if(opt[0]=='Q')
		{
			scanf("%d%d%d",&x,&y,&k);
			get_number(x,y,k);
		}else
		{
			scanf("%d%d",&x,&k);
			change(1,1,n,x,a[x],k);
			a[x] = k;
		}
	}
	return 0;
}
