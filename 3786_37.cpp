
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100005;
const int Inv = 20000307;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
struct Splay
{
	Splay *ls,*rs,*fa;
	int pos,neg,sta,lazy;
	LL num,sum;
	Splay(LL x,int s);
	void push_up();
	void push_down();
	void Add(LL x);
}*null = new Splay(0,0),*root,*tree[N][2];
Splay :: Splay(LL x,int s)
{
	ls = rs = fa = null;
	num = x*(s==1?1:-1);
	sta = s;
	neg = pos = 0;
	if(sta==1)pos++;
	if(sta==2)neg++;
	lazy = 0;
}
void Splay :: push_up()
{
	sum = ls->sum+rs->sum+num;
	pos = ls->pos+rs->pos+(sta==1);
	neg = ls->neg+rs->neg+(sta==2);
}
void Splay :: push_down()
{
	if(lazy)
	{
		ls->Add(lazy);
		rs->Add(lazy);
		lazy = 0;
	}
}
void Splay :: Add(LL x)
{
	if(this==null)return ;
	num+=x*(sta==1?1:-1);
	sum+=x*(pos-neg);
	lazy+=x;
}
void Push_down(Splay *x)
{
	static Splay *stack[N<<1];
	static int top = 0;
	for(;x!=null;x = x->fa)
		stack[++top] = x;
	while(top)
		stack[top--]->push_down();
}
void go_left(Splay *x)
{
	Splay *y = x->fa;
	y->rs = x->ls;
	x->ls->fa = y;
	x->ls = y;
	x->fa = y->fa;
	if(y->fa->ls==y)
		y->fa->ls = x;
	else y->fa->rs = x;
	y->fa = x;
	y->push_up();
	if(y==root)
		root = x;
}
void go_right(Splay *x)
{
	Splay *y = x->fa;
	y->ls = x->rs;
	x->rs->fa = y;
	x->rs = y;
	x->fa = y->fa;
	if(y->fa->ls==y)
		y->fa->ls = x;
	else y->fa->rs = x;
	y->fa = x;
	y->push_up();
	if(y==root)
		root = x;
}
void splay(Splay *x,Splay *target)
{
	Push_down(x);
	while(true)
	{
		Splay *y = x->fa;Splay *z = y->fa;
		if(y==target)break;
		if(z==target)
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
Splay* Insert(LL x,int s)
{
	Splay *y = root;
	while(y->rs!=null)
		y = y->rs;
	y->rs = new Splay(x,s);
	y->rs->fa = y;
	y->push_up();
	splay(y->rs,null);
	return root;
}
Splay* find_min(Splay *x)
{
	while(x->ls!=null)
		x = x->ls;
	return x;
}
Splay* find_max(Splay *x)
{
	while(x->rs!=null)
		x = x->rs;
	return x;
}
void move_to_root(Splay *x,Splay *y)
{
	splay(x,null);
	Splay *tmp1 = find_max(root->ls);
	splay(y,null);
	Splay *tmp2 = find_min(root->rs);
	splay(tmp1,null);
	splay(tmp2,root);
}
LL a[N];
void dfs(int x)
{
	tree[x][0] = Insert(a[x],1);
	for(int i = head[x];i;i = e[i].next)
		dfs(e[i].to);
	tree[x][1] = Insert(a[x],2);
}
int main()
{
	int n,f;
	LL x,y;
	scanf("%d",&n);
	for(int i = 2;i<= n;i++)
	{
		scanf("%d",&f);
		add(f,i);
	}
	for(int i = 1;i<= n;i++)scanf("%lld",&a[i]);
	root = new Splay(Inv,3);
	dfs(1);
	Insert(Inv,4);
	int m;
	scanf("%d",&m);
	char opt[10];
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",opt);
		if(opt[0]=='Q')
		{
			scanf("%lld",&x);
			move_to_root(tree[1][0],tree[x][0]);
			printf("%lld\n",root->rs->ls->sum);
		}else if(opt[0]=='C')
		{
			scanf("%lld%lld",&x,&y);
			move_to_root(tree[x][0],tree[x][1]);
			Splay *tmp = root->rs->ls;
			root->rs->ls = null;
			root->rs->push_up();
			root->push_up();
			splay(tree[y][0],null);
			splay(find_min(root->rs),root);
			root->rs->ls = tmp;
			tmp->fa = root->rs;
			root->rs->push_up();
			root->push_up();
		}
		else
		{
			scanf("%lld%lld",&x,&y);
			move_to_root(tree[x][0],tree[x][1]);
			root->rs->ls->Add(y);
		}
	}
	return 0;
}
