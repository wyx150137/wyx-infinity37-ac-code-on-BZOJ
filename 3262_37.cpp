
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
struct Treap
{
	Treap *ls,*rs;
	int cnt,size,val,key;
	Treap(int x);
	void push_up();
}*root[N];
Treap :: Treap(int x)
{
	ls = rs = NULL;
	val = x;
	cnt = size = 1;
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
	else if(y>x->val)
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
int get_rank(Treap *x,int y)
{
	if(!x)return 0;
	int tmp;
	if(!x->ls)tmp = 0;else tmp = x->ls->size;
	if(x->val==y)return tmp+x->cnt;
	else if(y>x->val)return tmp+x->cnt+get_rank(x->rs,y);
	else return get_rank(x->ls,y);
}
void update(int x,int y)
{
	for(int i = x;i<N;i+=i&(-i))
		Insert(root[i],y);
}
int getans(int x,int y)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=get_rank(root[i],y);
	return ans;
}
struct F
{int s,c,m,no;}flower[N];
bool cmp1(const F &a,const F &b)
{
	return a.s<b.s;
}
int id[N],cnt;
int find(int x)
{
	int l = 1,r = cnt+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(id[mid]<x)l = mid+1;
		else r = mid;
	}
	return l;
}
int ans[N],no[N];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d%d",&flower[i].s,&flower[i].c,&flower[i].m);
		id[i] = flower[i].c;
		flower[i].no = i;
	}
	sort(flower+1,flower+n+1,cmp1);
	cnt = 0;
	sort(id+1,id+n+1);
	for(int i = 1;i<= n;i++)
		if(id[i]!=id[cnt])
			id[++cnt] = id[i];
	int st,end;
	for(int i = 1;i<= n;i=end+1)
	{
		st = i,end = i;
		while(flower[end].s==flower[st].s&&end<=n)end++;
		end--;
		for(int j = st;j<=end;j++)
		{
			int pos = find(flower[j].c);
			update(pos,flower[j].m);
		}
		for(int j = st;j<= end;j++)
		{
			int pos = find(flower[j].c);
			int rank = getans(pos,flower[j].m)-1;
			ans[rank]++;
			no[flower[j].no] = rank;
		}
		/*int pos = find(flower[i].c);
		int rank = getans(pos,flower[i].m);
		ans[rank]++;
		update(pos,flower[i].m);*/
	}
	//for(int i= 1;i<= n;i++)
	//	printf("%d : %d\n",i,no[i]);
	for(int i = 0;i< n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
