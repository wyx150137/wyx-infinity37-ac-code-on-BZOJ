
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 2000000+5;
using namespace std;

int head[N],a[N],f[N];
int g[N],n,m;
bool in[N];

struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[N];

inline void add(int x,int y)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
}

void DFS(int x)
{
	for(int i=head[x];i;i=edge[i].next)
	{
		DFS(edge[i].to);
		f[x] += f[edge[i].to] ; 
		g[x] ++;
	}
	static int stack[N];
	int top = 0;
	g[x] += a[x];
	for(int i=head[x];i;i=edge[i].next)
		stack[++top] = g[edge[i].to] - 1;
	sort(stack+1,stack+top+1);
	for(int i=1;i<=top;++i)
		if(g[x]+stack[i]<=m)
			f[x] ++ ,g[x] += stack[i];
		else break;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch < '0' || ch > '9')if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
} 

int main()
{
	n = read(),m=read();
	for(int i=1;i<=n;++i) a[i] = read();
	for(int i=1;i<=n;++i)
	{
		int tmp = read();
		for(int j=1;j<=tmp;++j)
		{
			int k = read()+1;
			in[k] = 1;
			add(i,k);
		}
	}
	for(int i=1;i<=n;++i)
		if(!in[i])
			DFS(i),cout<<f[i]<<endl;

}
