
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 20000+5;
const int M = N << 2;
typedef long long LL;
using namespace std;

int head[N];
bool vis[N];

struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,int z)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z); head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z); head[y] = cnt;
}

int root,sum;
int F[N],size[N],dis[N];

void DFS1(int x,int fa)
{
	size[x] = 1, F[x] = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa && !vis[edge[i].to])
		{
			DFS1(edge[i].to,x);
			size[x] += size[edge[i].to];
			F[x] = max(F[x],size[edge[i].to]);
		}
	F[x] = max(F[x],sum-size[x]);
	root = F[x] < F[root] ? x : root;
}

int stack[N],top;

void DFS2(int x,int fa)
{
	stack[++top] = dis[x];
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to])
		{
			dis[edge[i].to] = (dis[x] + edge[i].val)%3;
			DFS2(edge[i].to,x);
		}
}

LL get_ans(int x,int d)
{
	LL tmp[3] = {};
	top = 0,dis[x] = d;DFS2(x,x);
	LL ans = 0;
	for(int i=1;i<=top;++i) tmp[stack[i] %3] ++;
	ans += tmp[0] * (tmp[0]-1)+ tmp[1] * tmp[2] * 2;
	return ans;
}

LL ans = 0;

void solve(int x)
{
	int tmp = get_ans(x,0);
	//cout << x << " " << tmp << endl;
	ans += tmp; vis[x] = 1;
	for(int i=head[x];i;i=edge[i].next)
		if(!vis[edge[i].to])
		{
			ans -= get_ans(edge[i].to,dis[edge[i].to]);
			sum = size[edge[i].to],root = 0;
			DFS1(edge[i].to,edge[i].to);
			solve(root);
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
	LL n = read();
	for(int i=1;i<n;++i)
	{
		int x = read(), y = read(), z = read();
		add(x,y,z);
	}
	sum = n, F[root = 0] = 0x7fffffff;
	DFS1(1,1);
	solve(root);
	ans += n;
	printf("%lld/%lld\n",ans/__gcd(n*n,ans),n*n/__gcd(n*n,ans));
}
