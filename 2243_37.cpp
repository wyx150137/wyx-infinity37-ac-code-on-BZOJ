
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
struct E
{int next,to;}e[N<<1];
struct T
{int lc,rc,num,f;}t[N<<3];
int head[N],tot,n;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int deep[N],top[N],fa[N],son[N],size[N],w[N],c[N],cnt;
bool v[N];
void dfs1(int x,int dep)
{
	v[x] = true;
	size[x]++;
	deep[x] =dep;
	for(int i= head[x];i;i = e[i].next)
	{
		int tmp = e[i].to;
		if(!v[tmp])
		{
			dfs1(tmp,dep+1);
			size[x]+=size[tmp];
			if(size[tmp]>size[son[x]])son[x] = tmp;
			fa[tmp] = x;
		}
	}
}
void dfs2(int x,int tp)
{
	top[x] = tp;
	w[x] = ++cnt;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
}
void init(int no,int l,int r)
{
	t[no].f = -1;
	if(l==r)
	{
		t[no].num = 1;
		return ;
	}
	int mid= (l+r)>>1;
	init(no<<1,l,mid);
	init((no<<1)+1,mid+1,r);
	return ;
}
void push_down(int p)
{
	t[p<<1].num = t[(p<<1)+1].num = 1;
	t[p<<1].f = t[(p<<1)+1].f = t[p].f;
	t[p<<1].lc = t[(p<<1)+1].lc = t[p].lc;
	t[p<<1].rc = t[(p<<1)+1].rc = t[p].f;
	t[p].f = -1;
}
void update(int p,int l,int r,int a,int b,int c)
{
	if(t[p].f!=-1)push_down(p);
	if(l>=a&&r<=b)
		{t[p].lc = t[p].rc = t[p].f = c;t[p].num = 1;return ;}
	int mid = (l+r)>>1;
	if(a<=mid)
		update(p<<1,l,mid,a,b,c);
	if(b>mid)
		update((p<<1)+1,mid+1,r,a,b,c);
	if(t[p<<1].rc==t[(p<<1)+1].lc)t[p].num = t[p<<1].num+t[(p<<1)+1].num-1;
	else t[p].num = t[p<<1].num+t[(p<<1)+1].num;
	t[p].lc = t[p<<1].lc;t[p].rc = t[(p<<1)+1].rc;
}
T getans(int p,int l,int r,int a,int b)
{
	if(t[p].f!=-1)push_down(p);
	if(l>=a&&r<=b)
		return t[p];
	int mid = (l+r)>>1;
	T x,y,c;
	if(b<=mid)
		c = getans(p<<1,l,mid,a,b);
	else if(a>mid)
		c = getans((p<<1)+1,mid+1,r,a,b);
	else
	{
		x = getans(p<<1,l,mid,a,b);y = getans((p<<1)+1,mid+1,r,a,b);
		c.lc = x.lc;c.rc = y.rc;
		c.num = x.num+y.num;
		if(x.rc==y.lc)c.num--;
	}
	return c;
}
int t_ans;
void get_update(int x,int y,int c,int opt)
{
	T ta;
	while(top[x]!=top[y])
	{
		if(deep[top[x]]<deep[top[y]])swap(x,y);
		if(opt==1)update(1,1,n,w[top[x]],w[x],c);
		else
		{
			ta = getans(1,1,n,w[top[x]],w[x]);
			t_ans+=ta.num;
			if(ta.lc==getans(1,1,n,w[fa[top[x]]],w[fa[top[x]]]).lc)t_ans--;
		}
		x = fa[top[x]];
	}
	if(deep[x]<deep[y])swap(x,y);
	if(opt==1)update(1,1,n,w[y],w[x],c);
	else
	{
		ta = getans(1,1,n,w[y],w[x]);
		t_ans+=ta.num;
	} 
}
int main()
{
	int m,x,y,z;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&c[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	init(1,1,n);
	dfs1(1,1);
	dfs2(1,1);
	for(int i = 1;i<= n;i++)get_update(i,i,c[i],1);
	char j[3];
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",j);
		if(j[0]=='C')
		{
			scanf("%d%d%d",&x,&y,&z);
			get_update(x,y,z,1);
		}else
		{
			t_ans = 0;
			scanf("%d%d",&x,&y);
			get_update(x,y,0,0);
			printf("%d\n",t_ans);
		}
	}
	return 0;
}
