
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e6+5;
const int M = N << 1;
using namespace std;

int head[N];
int a[N];

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
}

int depth[N],fa[N];
int MAX;
int T[N];

void DFS(int x)
{
	for(int i=head[x];i;i=edge[i].next)
	{
		depth[edge[i].to] = depth[x] + 1;
		DFS(edge[i].to);
	}
	T[depth[x]] ++ ; MAX = max(MAX,depth[x]); 
}

int ans[N];
int s[N],t;

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	int n =read(), m = read();
	for(int i=1;i<=m;++i) a[i] = read();
	for(int i=2;i<=n;++i) fa[i] = read(),add(fa[i],i);
	depth[1] = 1;DFS(1);	
	for(int i=MAX-1;i;--i) T[i] += T[i+1];
	s[1] = 1,s[2] = 2;
	int r = 2,l = 1;

	for(int i=3;i<=MAX;++i)
	{
		while(r > 1 && (s[r]-s[r-1])*(T[i]-T[s[r-1]]) - (T[s[r]] - T[s[r-1]])*(i-s[r-1]) >= 0) r--;
		s[++r] = i;
	}

	for(int i=1;i<=n;++i)
	{
		while(l < r && i*s[l] + T[s[l]] < i*s[l+1] + T[s[l+1]]) ++ l;
		ans[i] = s[l];
	}

	for(int i=1;i<=m;++i)
	{
		int x = a[i];
		if(x >= n) printf("%d",MAX);
		else printf("%d",max(ans[x]-1+(T[ans[x]]+x-1)/x,MAX));
		if(i!=m) putchar(' ');
	}
}
