
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 300000+5;
const int M = N << 1;
using namespace std;

int head[N];
int fa[N];
int f[N];

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

int mid;

void DFS(int x)
{
	int tot = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			fa[edge[i].to] = x;
			DFS(edge[i].to);
			tot += f[edge[i].to]+1;
		}
	f[x] = max(tot-mid,0);
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
	if(n==1) {puts("0");return 0;}

	for(int i=1;i<n;++i)
	{
		int x = read(), y = read();
		add(x,y);
	}

	int l = 1;
	int r = n;

	while(l<r)
	{
		memset(f,0,sizeof f);
		mid = (l+r) >> 1;
		DFS(1);
		if(!f[1]) r = mid;
		else l = mid + 1; 
	}

	cout << l << endl;
}
