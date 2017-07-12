
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 40005;
struct E
{
	int next,to;
}e[N<<1];
int head[N],tot,ans,n,m;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int son[N][2],sum[N],fa[N],size[N],lazy[N],val[N],s[N],d[N];
bool rev[N];
inline bool is_root(int x)
{
	return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;
}
inline void reverse(int x)
{
	rev[x]^=1;
	swap(son[x][0],son[x][1]);
}
inline void init(int x,int f)
{
	fa[x] = f;
	son[x][0] = son[x][1] = val[x] = lazy[x] = 0;
	sum[x] = s[x] = d[x] = 0;size[x] = 1;
}
inline void Push_up(int x)
{
	if(!x)return ;
	size[x] =size[son[x][0]]+1+size[son[x][1]];
}
inline void Add(int x,int y)
{
	if(!x)return ;
	val[x]+=y;
	lazy[x]+=y;
}
inline void update(int x,int S,int D)
{
	if(!x)return ;
	sum[x]+=S+size[son[x][1]]*D;
	s[x]+=S,d[x]+=D;
}
inline void Push_down(int x)
{
	int ls = son[x][0],rs = son[x][1];
	if(rev[x])
	{
		reverse(ls);
		reverse(rs);
		rev[x] = 0;
	}
	if(lazy[x])
	{
		Add(ls,lazy[x]),Add(rs,lazy[x]);
		lazy[x] = 0;
	}
	if(d[x])
	{
		update(ls,s[x]+(size[rs]+1)*d[x],d[x]);
		update(rs,s[x],d[x]);
		s[x] = d[x] = 0;
	}
}
void rotate(int x)
{
	int y = fa[x],z = fa[y];
	int d = son[y][1]==x;
	if(!is_root(y))
	{
		if(y==son[z][0])son[z][0] = x;
		else son[z][1] = x;
	}
	fa[y] = x,fa[x] = z,fa[son[x][d^1]] = y;
	son[y][d] = son[x][d^1],son[x][d^1] = y;
	Push_up(x),Push_up(y);
}
int stack[N],top;
void splay(int x)
{
	top = 0;
	stack[++top] = x;
	for(int i = x;!is_root(i);i = fa[i])stack[++top] = fa[i];
	while(top)Push_down(stack[top--]);
	while(!is_root(x))
	{
		int y = fa[x],z = fa[y];
		if(!is_root(y))
		{
			if((son[y][0]==x)!=(son[z][0]==y))rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access(int x)
{
	int t = 0;
	while(x)
	{
		splay(x);
		son[x][1] = t;
		Push_up(x);
		t = x;
		x = fa[x];
	}
}
void move_to_root(int x)
{
	access(x);
	splay(x);
	reverse(x);
}
void link(int x,int y)
{
	move_to_root(x);
	fa[x] = y;
}
int find(int x)
{
	access(x);
	splay(x);
	while(son[x][0])
		x = son[x][0];
	return x;
}
void insert(int f,int x)
{
	init(x,f);
	f = find(f);access(x);splay(f);
	Add(f,1);
	update(f,0,1);
	x = son[f][1];
	while(son[x][0])
		x = son[x][0];
	splay(x);
	int v1 = val[f],v2= val[x];
	if(v2*2>v1)
	{
		val[x] = v1,val[f]-=v2;
		sum[f]-=sum[x]+v2;sum[x]+=sum[f]+v1-v2;
		access(x);splay(f);
		son[f][0] = x;son[f][1] = 0;
	}
}
void dfs(int x,int f)
{
	insert(f,x);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=f)dfs(e[i].to,x);
}
void Link(int x,int y)
{
	add(x,y),add(y,x);
	int p = find(x),q = find(y);
	ans-=sum[p]+sum[q];
	if(val[p]<val[q])swap(x,y);
	dfs(y,x);
	ans+=sum[find(x)];
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)val[i]=size[i]=1;
	char opt[3];
	int a,b;
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",opt);
		if(opt[0]=='A'){scanf("%d%d",&a,&b);Link(a,b);}
		else printf("%d\n",ans);
	}
	return 0;
}
