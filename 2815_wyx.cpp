
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>
const int N = 240000+5;
const int M = 240000+5;
using namespace std;

int stack[N];
int top;

struct graph
{
	int head[N],n,size[N];
	int in[N],fa[N][20],depth[N];
	queue <int> q;

	struct line
	{
		int next,to;
		line () {}
		line (int _next,int _to)
		:next(_next),to(_to){}
	}edge[M];

	inline void add(int x,int y)
	{
		static int cnt = 0;
		edge[++cnt] = line(head[x],y);
		head[x] = cnt;
	}

	void Topological_sorting()
	{
		for(int i=1;i<=n;++i)
			if(!in[i])
				q.push(i);
		while(!q.empty())
		{
			int tt = q.front();
			q.pop();
			stack[++top] = tt;
			for(int i=head[tt];i;i=edge[i].next)
				if(!--in[edge[i].to])
					q.push(edge[i].to);
		}
	}

	int lca(int x,int y)
	{
		if(x==-1)return y;
		if(depth[x] < depth[y])swap(x,y);
		int tt = depth[x] - depth[y];
		for(int i=0;i<20;++i)
			if((1<<i)&tt)
				x = fa[x][i];
		if(x==y)return x;
		for(int i=19;~i;--i)
			if(fa[x][i]!=fa[y][i])
				x = fa[x][i],y = fa[y][i];
		return fa[x][0];
	}

	void Pre(int x)
	{
		for(int i=1;i<20;++i)
			fa[x][i] = fa[fa[x][i-1]][i-1];
	}

	void DFS(int x)
	{
		size[x] = 1;
		for(int i=head[x];i;i=edge[i].next)
			if(edge[i].to!=fa[x][0])
				DFS(edge[i].to),size[x] += size[edge[i].to];
	}

}G1,G2;

void build()
{
	for(int tmp = top;tmp>0;--tmp)
	{
		int x = stack[tmp];
		int fa = -1;	
		for(int i=G1.head[x];i;i=G1.edge[i].next)
			fa = G2.lca(fa,G1.edge[i].to);
		if(fa == -1) fa = 0;
		G2.add(fa,x);
		G2.depth[x] = G2.depth[fa] + 1;
		G2.fa[x][0] = fa;
		G2.Pre(x); 
	}
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	int n = read();
	G1.n = G2.n = n;
	for(int i=1;i<=n;++i)
	{
		int tmp = read();
		while(tmp)
		{
			G1.add(i,tmp);
			G1.in[tmp]++;
			tmp = read();
		}
	}
	G1.Topological_sorting();
//	for(int i=1;i<=top;++i) 
//		cout << stack[i] << endl;
	build();
	G2.DFS(0);
	for(int i=1;i<=n;++i)
		printf("%d\n",G2.size[i]-1);
}
