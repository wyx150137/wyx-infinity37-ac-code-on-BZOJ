
#include <stdio.h>
#include <queue>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int n,m;

struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;
	e[++tot].to=x;e[tot].next=head[y];head[y]=tot;
}
int son[N],size[N],dfn[N],top[N],Dfn,fa[N],dep[N];
void dfs1(int x)
{
	size[x] = 1;
	dep[x] =dep[fa[x]]+1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x])
		{
			fa[e[i].to] = x;
			dfs1(e[i].to);
			size[x]+=size[e[i].to];
			if(size[e[i].to]>=size[son[x]])son[x]=e[i].to;
		}
}
void dfs2(int x,int tp)
{
	top[x] = tp;
	dfn[x] = ++Dfn;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
}

struct Heap
{
	priority_queue<int>a,b;
	void del(int val){b.push(val);}
	void push(int val){a.push(val);}
	int top()
	{
		while(!b.empty()&&a.top()==b.top()) a.pop(),b.pop();
        if(a.empty()) return -1;
        return a.top();
	}
}t[270005];
void update(int p,int l,int r,int a,int b,int val,bool flag)
{
	if(a>b)return ;
	if(l>=a&&r<=b)
	{
		if(!flag)t[p].push(val);
		else t[p].del(val);
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,val,flag);
	if(b >mid)update(p<<1|1,mid+1,r,a,b,val,flag);
}
int getans(int p,int l,int r,int pos)
{
	if(l==r)
		return t[p].top();
	int mid = (l+r)>>1;
	if(pos<=mid)return max(t[p].top(),getans(p<<1,l,mid,pos));
	else return max(t[p].top(),getans(p<<1|1,mid+1,r,pos));
}

vector<pair<int,int> >stack;
void Update(int x,int y,int val,bool flag)
{
	stack.clear();
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		stack.push_back(make_pair(dfn[top[x]],dfn[x]));
		x = fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	stack.push_back(make_pair(dfn[y],dfn[x]));
	sort(stack.begin(),stack.end());
	x = 1;
	int sz = stack.size();
	for(int i = 0;i<sz;i++)
	{
		update(1,1,n,x,stack[i].first-1,val,flag);
		x = stack[i].second+1;
	}
	update(1,1,n,x,n,val,flag);
	return ;
}

int X[N<<1],Y[N<<1],Z[N<<1];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&X[0],&Y[0]);
		add(X[0],Y[0]);
	}
	int root = rand()%n+1;
	dfs1(root);
	dfs2(root,root);
	int tp;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&tp);
		if(tp==0)
		{
			scanf("%d%d%d",&X[i],&Y[i],&Z[i]);
			Update(X[i],Y[i],Z[i],(bool)tp);
		}else if(tp==1)
		{
			scanf("%d",&X[i]);
			Update(X[X[i]],Y[X[i]],Z[X[i]],(bool)tp);
		}else
		{
			scanf("%d",&X[i]);
			printf("%d\n",getans(1,1,n,dfn[X[i]]));
		}
	}
	return 0;
}
