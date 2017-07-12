
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
struct Treap
{
	Treap *ls,*rs;
	int val,size,cnt,key;
	Treap(){}
	Treap(int x)
	{
		ls = rs = NULL;
		val = x;
		size = cnt = 1;
		key = rand();
	}
	void push_up()
	{
		size = cnt;
		if(ls)size+=ls->size;
		if(rs)size+=rs->size;
	}
}*root = NULL;
int DEC = 0,PER = 0,go_away;
void go_left(Treap *&x)
{
	Treap *y = x->rs;
	x->rs= y->ls;
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
	x= y;
	x->rs->push_up();
	x->push_up();
}
void Insert(Treap *&now,int x)
{
	if(!now) {now = new Treap(x);return ;}
	if(now->val==x)now->cnt++;
	else if(x<now->val)
	{
		Insert(now->ls,x);
		if(now->ls->key > now->key)
			go_right(now);
	}
	else 
	{
		Insert(now->rs,x);
		if(now->rs->key > now->key)
			go_left(now);
	}
	now->push_up();
}
int Delete(Treap *&now,int x)
{
	int ans = 0;
	if(!now)return 0;
	if(now->val+DEC>=x)
	{
		ans = Delete(now->ls,x);
		now->size-=ans;
	}
	else
	{
		if(now->ls)ans+=now->ls->size;
		ans+= now->cnt;
		now = now->rs;
		ans=ans+Delete(now,x);
	}		
	if(now)now->push_up();
	return ans;
}
int get_rank(Treap *x,int k)
{
	if(x->ls!=NULL&&k<=x->ls->size)return get_rank(x->ls,k);
	if(x->ls!=NULL)k-=x->ls->size;
	if(k<=x->cnt)return x->val;
	k-=x->cnt;
	return get_rank(x->rs,k);
}
int main()
{
	int n,Min,k;
	scanf("%d%d",&n,&Min);
	char ju[3];
	for(int i = 1;i<= n;i++)
	{
		scanf("%s%d",ju,&k);
		if(ju[0]=='I')
		{
			if(k>=Min)
				Insert(root,k-DEC);
		}else if(ju[0]=='A')DEC+=k;
		else if(ju[0]=='S')
		{
			DEC-=k;
			int tmp = Delete(root,Min);
			go_away+=tmp;
		}
		else 
		{
			if(root==NULL||k>root->size)printf("-1\n");
			else printf("%d\n",get_rank(root,root->size-k+1)+DEC);
		}
	}
	printf("%d\n",go_away);
	return 0;
}
