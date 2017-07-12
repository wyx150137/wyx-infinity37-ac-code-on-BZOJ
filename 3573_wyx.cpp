
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 500005;
const int M = N << 1;
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x * f;
}

int head[N],in[N],a[N];

const double eps = 1e-9;

inline bool equal(double x,double y)
{
	return fabs(x-y) < eps * max(x,y);
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
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

double s[N];

void DFS(int x,int fa)
{
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
		{
			s[edge[i].to] = s[x] + log(in[x]);
			DFS(edge[i].to,x);
		}
}

double V[N];
int tt;

int main()
{
	int n = read();
	for(int i=1;i<=n;++i)
		a[i] = read();
	for(int i=1;i<n;++i)
	{
		int x = read(), y = read();
		add(x,y);
		in[x] ++ , in[y] ++;
	}
//	puts("/**********");
	for(int i=2;i<=n;++i)
		in[i] --;
	s[1] = 0;DFS(1,0);
	for(int i=1;i<=n;++i)
		V[++tt] = s[i] + log(a[i]);
	int cnt = 1;
	int ans = 0;
	sort(V+1,V+tt+1);
	V[tt+1] = 122211323;
	for(int i=1;i<=n;++i)
	{
		if(equal(V[i],V[i+1]))
			cnt ++;
		else ans = max(ans,cnt),cnt = 1;
	}
	cout << n - ans << endl;
}
