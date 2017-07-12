
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
#define M 200000+5
using namespace std;


int n,r,h,s;
int a[N],q[N],fa[N];
int head[N];

struct graph
{
	int next, to;
	graph() {}
	graph(int _next, int _to)
	: next(_next), to(_to) {}
} edge[M];

inline void add(int x, int y)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x], y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y], x);
	head[y] = cnt;
}

int sum;
int ans ;

void DFS(int x)
{
	q[++r] = a[x];
	sum += a[x];
	while(sum>s)
		sum-=q[++h];
	if(sum==s)++ans;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			fa[edge[i].to] = x;
			DFS(edge[i].to);
		}
	sum-=q[r--];
	while(h && sum + q[h]<=s)
		sum += q[h--];
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
	cin >> n >> s;
	for(int i=1;i<=n;++i)
		a[i] = read();
	for(int i=1;i<n;++i)
	{
		int x = read() , y = read();
		add(x,y);
	}
	DFS(1);
	cout<<ans<<endl;
}
