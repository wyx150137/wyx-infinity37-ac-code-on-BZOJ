
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e4+5;
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
	cnt = size = 1;
	val = x;
	key = rand();
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
	else if(y<x->val)
	{
		Insert(x->ls,y);
		if(x->ls->key>x->key)
			go_right(x);
	}else
	{
		Insert(x->rs,y);
		if(x->rs->key>x->key)
			go_left(x);
	}
	x->push_up();
}
void Delete(Treap *&x,int y)
{
	if(!x)return ;
	if(y<x->val)Delete(x->ls,y);
	else if(y>x->val)Delete(x->rs,y);
	else
	{
		if(x->cnt>1)x->cnt--;
		else if(!x->rs)x = x->ls;
		else if(!x->ls)x = x->rs;
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
int get_less(Treap *x,int y)
{
	int tmp = 0;
	if(!x)return tmp;
	if(x->val==y)
	{
		if(x->ls)tmp+=x->ls->size;
		return tmp;
	}else if(y<x->val)return get_less(x->ls,y);
	else
	{
		tmp+=x->cnt;
		if(x->ls)tmp+=x->ls->size;
		return tmp+get_less(x->rs,y);
	}
}
int get_lessnqul(Treap *x,int y)
{
	int tmp = 0;
	if(!x)return tmp;
	if(x->val==y)
	{
		if(x->ls)tmp+=x->ls->size;
		tmp+=x->cnt;
		return tmp;
	}else if(y<x->val)return get_lessnqul(x->ls,y);
	else 
	{
		tmp+=x->cnt;
		if(x->ls)tmp+=x->ls->size;
		return tmp+get_lessnqul(x->rs,y);
	}
}
int get_bigger(int p,int l,int r,int a,int b,int y)
{
	if(a>b)return 0;
	if(l>=a&&r<=b)return r-l+1-get_lessnqul(root[p],y);
	int mid = (l+r)>>1;
	int ans = 0;
	if(a<=mid)ans+=get_bigger(p<<1,l,mid,a,b,y);
	if(b >mid)ans+=get_bigger(p<<1|1,mid+1,r,a,b,y);
	return ans;
}
int get_smaller(int p,int l,int r,int a,int b,int y)
{
	if(a>b)return 0;
	if(l>=a&&r<=b)return get_less(root[p],y);
	int mid=(l+r)>>1;
	int ans = 0;
	if(a<=mid)ans+=get_smaller(p<<1,l,mid,a,b,y);
	if(b >mid)ans+=get_smaller(p<<1|1,mid+1,r,a,b,y);
	return ans;
}
void update(int p,int l,int r,int pos,int a,int b)
{
	Delete(root[p],a);
	Insert(root[p],b);
	if(l==r)return ;
	int mid = (l+r)>>1;
	if(pos<=mid)update(p<<1,l,mid,pos,a,b);
	else update(p<<1|1,mid+1,r,pos,a,b);
}
void build(int p,int l,int r,int pos,int num)
{
	Insert(root[p],num);
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(pos<=mid)build(p<<1,l,mid,pos,num);
	else build(p<<1|1,mid+1,r,pos,num);
}
int a[N];
int main()
{
	int n,m;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		build(1,1,n,i,a[i]);
	int ans = 0;
	for(int i=1;i<=n;i++)
		ans+=get_bigger(1,1,n,1,i-1,a[i]);
	int x,y;
	scanf("%d",&m);
	while(m--)
	{
		printf("%d\n",ans);
		scanf("%d%d",&x,&y);
		if(a[x]==a[y]||x==y)continue;
		int flag =((x<y&&a[x]>a[y])||(x>y&&a[x]<a[y]));
		ans+=flag;
		ans-=get_bigger(1,1,n,1,x-1,a[x])+get_smaller(1,1,n,x+1,n,a[x]);
		ans-=get_bigger(1,1,n,1,y-1,a[y])+get_smaller(1,1,n,y+1,n,a[y]);
		update(1,1,n,x,a[x],a[y]);update(1,1,n,y,a[y],a[x]);
		swap(a[x],a[y]);
		ans+=get_bigger(1,1,n,1,x-1,a[x])+get_smaller(1,1,n,x+1,n,a[x]);
		ans+=get_bigger(1,1,n,1,y-1,a[y])+get_smaller(1,1,n,y+1,n,a[y]);
		ans-=(1-flag);
	}
	printf("%d\n",ans);
	return 0;
}
