
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
const int M = 4e5+5;
struct List
{int next,to,opt;}e[M];
struct data
{
	int t,ca,x,y,z,ans;
	bool operator <(const data &s)const
	{return t<s.t;}
}ask[N],zlt;
int head[N],TOT;
void add(int x,int y,int o)
{e[++TOT].to=y;e[TOT].next=head[x];e[TOT].opt=o;head[x]=TOT;}
int fa[M],ch[M][2],size[M],sum[M],val[M],pp[M],sta[M],tot,top;
int lt[N],rt[N],gs[N],b[M],n,m;
bool rev[M];
inline int pd(int x)
{return ch[fa[x]][1]==x;}
inline void Push_up(int p)
{sum[p]=sum[ch[p][0]]+val[p]+sum[ch[p][1]];}
void rotate(int x)
{
	int y = fa[x];
	int d = ch[y][1]==x;
	fa[x] = fa[y];
	if(fa[y])ch[fa[y]][pd(y)] = x;
	ch[y][d]=ch[x][d^1];
	if(ch[x][d^1])fa[ch[x][d^1]] = y;
	ch[x][d^1] = y;
	fa[y] = x;
	Push_up(y);Push_up(x);
	if(pp[y])pp[x]=pp[y],pp[y]=0;
}
void Push_down(int p)
{
	if(rev[p])
	{
		if(ch[p][0])rev[ch[p][0]]^=1;
		if(ch[p][1])rev[ch[p][1]]^=1;
		swap(ch[p][0],ch[p][1]);
		rev[p] = false;
	}
}
void relax(int x,int y)
{
	top = 0;
	while(x!=y)
	{
		sta[++top] = x;
		x = fa[x];
	}
	while(top)
	{
		x = sta[top--];
		Push_down(x);
	}
}
void splay(int x,int y)
{
	relax(x,y);
	while(fa[x]!=y)
	{
		if(fa[fa[x]]!=y)
		{
			if(pd(x)==pd(fa[x]))rotate(fa[x]);
			else rotate(x);
		}
		rotate(x);
	}
}
int access(int x)
{
	int y,z,p = x;
	splay(x,0);
	z = ch[x][1];
	ch[x][1] = 0;
	if(z)
	{
		fa[z] = 0;
		pp[z] = x;
	}
	Push_up(x);
	while(pp[x])
	{
		p = y = pp[x];
		splay(y,0);
		z = ch[y][1];
		if(z)
		{
			fa[z] = 0;
			pp[z] = y;
		}
		ch[y][1] = x;
		fa[x] = y;pp[x] = 0;
		Push_up(y);
		splay(x,0);
	}
	return p;
}
void make_root(int x)
{
	access(x);
	splay(x,0);
	rev[x]^=1;
}
void Link(int x,int y)
{
	make_root(y);
	splay(y,0);
	pp[y] = x;
}
void Cut(int x)
{
	make_root(1);
	access(x);
	splay(x,0);
	int y = ch[x][0];
	ch[x][0] = 0;
	if(y)
	{
		fa[y] = pp[y] = 0;
	}
	Push_up(x);
}
void Insert1(int x)
{
	int j = b[ask[x].y-1],k = b[ask[x].y];
	Cut(k);
	Link(k,ask[x].x);
}
void Delete1(int x)
{
	int j = b[ask[x].y-1],k = b[ask[x].y];
	Cut(k);
	Link(k,j);
}
void Insert0(int x)
{
	int j = gs[ask[x].x];
	val[ask[x].x] = 1;
	Push_up(ask[x].x);
	Link(ask[x].x,b[j]);
}
void Delete0(int x)
{
	Cut(ask[x].x);
}

int main()
{
	int l,r,x,y,ans;
	scanf("%d%d",&n,&m);
	tot = top = 1;
	lt[1] = 1,rt[1] = n;
	for(int i = 1;i<= m;i++)
	{
		ask[i].t = i;
		scanf("%d",&ask[i].ca);
		if(ask[i].ca==0)
		{
			scanf("%d%d",&l,&r);
			add(l,i,1),add(r+1,i,-1);
			ask[i].x=++tot;
			lt[tot]=l,rt[tot]=r;
			gs[tot] = top;
		}else if(ask[i].ca==1)
		{
			scanf("%d%d%d",&l,&r,&ask[i].x);
			l = max(l,lt[ask[i].x]),r = min(r,rt[ask[i].x]);
			if(l<=r)
			{
				add(l,i,1),add(r+1,i,-1);
				ask[i].y=++top;
			}
		}else
		{
			scanf("%d%d%d",&ask[i].z,&ask[i].x,&ask[i].y);
			l = ask[i].z;
			add(l,i,1);
		}
	}
	zlt.t=0;
    zlt.ca=1;
    zlt.x=1;
    zlt.y=1;
    ask[0]=zlt;
    for(int i = 1;i<= top;i++)b[i]=++tot;
    val[1] = 1;
	Push_up(1);
	pp[b[1]] = 1;
	for(int i = 2;i<= top;i++)pp[b[i]]=b[i-1];
	for(int i = 1;i<= n;i++)
	{
		for(int t = head[i];t;t=e[t].next)
		{
			if(ask[e[t].to].ca==0)
				{if(e[t].opt==1)Insert0(e[t].to);else Delete0(e[t].to);}
			else if(ask[e[t].to].ca==1)
				{if(e[t].opt==1)Insert1(e[t].to);else Delete1(e[t].to);}
		}
		for(int t = head[i];t;t=e[t].next)
		{
			if(ask[e[t].to].ca==2)
			{
				x = ask[e[t].to].x,y = ask[e[t].to].y;
				if(x==y){ask[e[t].to].ans = 0;continue;}
				make_root(1);
                access(x);
                splay(x,0);
                ans=sum[x];
                x=access(y);
                splay(y,0);
                ans+=sum[y];
                access(x);
                splay(x,0);
                ans-=sum[x]*2;
                ask[e[t].to].ans=ans;
			}
		}
	}
	for(int i = 1;i<= m;i++)
		if(ask[i].ca==2)printf("%d\n",ask[i].ans);
	return 0;
}
