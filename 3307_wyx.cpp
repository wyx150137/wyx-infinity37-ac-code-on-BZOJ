
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#define N 100100
#define M 200100
using namespace std;

int head[N],size[N],top[N];
int w[N],sz,fa[N],depth[N];
int ans[N],n,m;
vector<int> op[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct seg{
    seg *ls,*rs;
    int pos,val;
    void* operator new (size_t)
    {
        static seg *mempool,*C;
        if(C==mempool)
            mempool=(C=new seg[1<<15])+(1<<15);
        C->ls=C->rs=NULL;
        C->pos=0;C->val=0;
        return C++;
    }
    void updata()
    {
        val=0;
        if(ls&&ls->val>val)
            val=ls->val,pos=ls->pos;
        if(rs&&rs->val>val)
            val=rs->val,pos=rs->pos;
    }
    friend void change(seg *&p,int x,int y,int pos,int val)
    {
        int mid=(x+y)>>1;
        if(!p) p=new seg;
        if(x==y)
        {
            p->pos=mid;
            p->val+=val;
            if(!p->val)
                p=NULL;
            return ;
        }
        if(pos<=mid)
            change(p->ls,x,mid,pos,val);
        else
            change(p->rs,mid+1,y,pos,val);
        p->updata();
        if(!p->val)
            p=NULL;
    }
    friend void merge(seg *&p1,seg *p2,int x,int y)
    {
        int mid=(x+y)>>1;
        if(!p2) return ;
        if(!p1)
        {
            p1=p2;
            return ;
        }
        if(x==y)
        {
            p1->val+=p2->val;
            return ;
        }
        merge(p1->ls,p2->ls,x,mid);
        merge(p1->rs,p2->rs,mid+1,y);
        p1->updata();
    }
}*tr[M];

struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

void DFS1(int x)
{
	size[x] = 1;
	for(int i=head[x]; i ;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			depth[edge[i].to] = depth[x]+1;
			fa[edge[i].to] = x;
			DFS1(edge[i].to);
			size[x] += size[edge[i].to];
		}
}

void DFS2(int x,int chain)
{
	top[x] = chain;
	int k = 0;

	for(int i=head[x] ; i ; i=edge[i].next)
		if(edge[i].to!=fa[x] && size[k] < size[edge[i].to])
			k = edge[i].to;

	if(!k)return;
	DFS2(k,chain);
	for(int i=head[x]; i ; i=edge[i].next)
		if(edge[i].to!=fa[x] && edge[i].to !=k)
			DFS2(edge[i].to,edge[i].to);
}

int Lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]] < depth[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return depth[x] < depth[y] ? x : y;
}

void DFS3(int x)
{
	for(int i=head[x]; i ; i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			DFS3(edge[i].to);
			merge(tr[x],tr[edge[i].to],1,1000000000);
		}
	vector <int> ::iterator it;
	for(it = op[x].begin();it!=op[x].end();it++)
		if( *it > 0)
			change(tr[x],1,1000000000,*it,1);
		else
			change(tr[x],1,1000000000,-*it,-1);
	if(tr[x])
		ans[x] = tr[x] -> pos;
}

int main()
{
	cin>>n>>m;

	for(int i=1;i<n;++i)
	{
		int x=read(),y=read();
		add(x,y);
	}

	DFS1(1);
	DFS2(1,1);

	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read();
		int z=read();
		int L = Lca(x,y);
		//cout<<L<<endl;
		op[x].push_back(z);
		op[y].push_back(z);
		op[L].push_back(-z);
		op[fa[L]].push_back(-z);
	}
	DFS3(1);

	for(int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
}
