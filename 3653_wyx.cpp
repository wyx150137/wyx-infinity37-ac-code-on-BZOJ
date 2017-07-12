
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const int N = 300000+5;
const int M = N << 2;
const int Maxm = N << 5;
using namespace std;

int root[N];
int head[N];
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

LL tr[Maxm];
int sz,ls[Maxm],rs[Maxm],n,Q;

void change(int &k,int l,int r,int pos,int x)
{
	if(!k) k = ++sz;tr[k] += x;
	if(l==r)return; int mid = (l+r) >> 1;
	if(pos <= mid) change(ls[k],l,mid,pos,x);
	else change(rs[k],mid+1,r,pos,x);
}

int depth[N],fa[N];
int size[N];

struct Lux
{
	int x, k;
};

vector <Lux> V[N];

LL ans[N];

int merge(int x,int y)
{
	if(!x || !y) return x + y;
	tr[x] += tr[y];
	ls[x] = merge(ls[x],ls[y]);
	rs[x] = merge(rs[x],rs[y]);
	return x;
}

LL ask(int k,int l,int r,int pos)
{
	if(l==r)return tr[k];
	int mid = (l+r) >> 1;
	if(pos <= mid)return ask(ls[k],l,mid,pos);
	else return tr[ls[k]] + ask(rs[k],mid+1,r,pos);;
}

void DFS(int x)
{
	depth[x] = depth[fa[x]] + 1;size[x] =1 ;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			fa[edge[i].to] = x;
			DFS(edge[i].to);
			size[x] += size[edge[i].to];
			root[x] = merge(root[x],root[edge[i].to]);
		}
	for(int i=0;i<V[x].size();++i)
	{
		int tt = V[x][i].k;
		ans[V[x][i].x] = ask(root[x],1,n,depth[x]+tt);
		ans[V[x][i].x] += ((LL)size[x]-1)*min(depth[x]-1,tt);
	}
	change(root[x],1,n,depth[x],size[x]-1);
}

inline char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
  
inline int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
  

int main()
{
	n = read(), Q = read();
	for(int i=1;i<n;++i) add(read(),read());
	for(int i=1;i<=Q;++i)
	{
		int t = read(), K = read();
		V[t].push_back((Lux){i,K});
	}
	DFS(1);
	for(int i=1;i<=Q;++i)
		printf("%lld\n",ans[i]);
}
