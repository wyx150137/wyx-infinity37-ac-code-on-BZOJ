
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define inf 1000000000
#define N 100000+5
#define M 200000+5
using namespace std;
int head[N],lead[N],v[N],n,m;
long long sum[N],size[N],root;
struct heap
{
	heap *ls,*rs;
	int key;
	int h;
	heap (int x);
}*null = new heap(0) ,*tr[M];
heap :: heap(int x)
{
	ls = rs = null;
	if(!null) h=-1;
	else h=0; key=x;
}
heap *Merge(heap *x,heap *y)
{
	if(x==null)return y;
	if(y==null)return x;
	if(x->key < y->key)swap(x,y);
	x->rs = Merge(x->rs , y);
	if(x->rs->h < x->ls->h)swap(x->ls,x->rs);
	x->h = x->rs->h + 1;
	return x;
}
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
	edge[++cnt]=graph(head[x],y);
	head[x]=cnt;
}
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
long long ans = 0;
void DFS(int x)
{
	for(int i=head[x];i;i=edge[i].next)
	{
		DFS(edge[i].to);
		tr[x]=Merge(tr[x],tr[edge[i].to]);
		sum[x]+=sum[edge[i].to];
		size[x]+=size[edge[i].to];
		while(sum[x]>m)
		{
			sum[x]-=tr[x]->key;
			--size[x];
			tr[x]=Merge(tr[x]->ls,tr[x]->rs);
		}
	}
	ans = max(ans,(long long)size[x]*lead[x]);
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i)
	{
		int tmp=read();
		if(tmp)
			add(tmp,i);
		else
			root = i;
		sum[i]=read(),lead[i]=read();
		tr[i]=new heap(sum[i]);
		size[i]=1;
	}
	DFS(root);
	cout<<ans<<endl;
}
