
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int inf = 0x7fffffff;
const int N = 5e5+5;
const int M = N << 2;
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N];
int head1[N];
int in[N],out[N];

struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M],edge1[M];

inline void add(int x,int y)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt; in[y] ++;
}

inline void add2(int x,int y)
{
	static int cnt = 0;
	edge1[++cnt] = graph(head1[x],y);
	head1[x] = cnt;out[y] ++;
}

int tr[M];
int MAX[M];

void change(int k,int l,int r,int pos,int tt)
{
	if(l==r)
	{
		tr[k] += tt;
		if(tr[k] > 0) MAX[k] = l;
		else MAX[k] = -1,tr[k] = 0;
		return;
	}
	int mid = (l+r) >> 1;
	if(pos <= mid) change(k<<1,l,mid,pos,tt);
	else change(k<<1|1,mid+1,r,pos,tt);
	MAX[k] = max(MAX[k<<1],MAX[k<<1|1]);
}

int q[N],p[N];
int f[N],g[N];
int n;

void solve()
{
	int l = 1;
	int r = 0;
	for(int i=1;i<=n;++i)
		if(!in[i])
			q[++r] = i;
	while(l<=r)
	{
		int tt = q[l++];
		for(int i=head[tt];i;i=edge[i].next)
		{
			f[edge[i].to] = max(f[edge[i].to],f[tt] + 1);
			if(!--in[edge[i].to])
				q[++r] = edge[i].to;
			
		}
	}
	l = 1;
	r = 0;
	for(int i=1;i<=n;++i)
		if(!out[i])
			p[++r] = i;
	while(l<=r)
	{
		int tt = p[l++];
		for(int i=head1[tt];i;i=edge1[i].next)
		{
			g[edge1[i].to] = max(g[edge1[i].to],g[tt] + 1);
			if(!--out[edge1[i].to])
				p[++r] = edge1[i].to;
		}	
	}
}

int main()
{
	n = read();
	int m = read();
	for(int i=1;i<=m;++i)
	{
		int x = read(), y = read();
		add(x,y);add2(y,x);
	}
	solve();
	for(int i=1;i<=n;++i)
		change(1,0,n,g[i],1);
	int ansx = 0;
	int ans = inf;

	for(int i=1;i<=n;++i)
	{
		int tt = q[i];
		for(int i=head1[tt];i;i=edge1[i].next)
		{
			change(1,0,n,g[tt]+f[edge1[i].to]+1,-1);
		}
		change(1,0,n,g[tt],-1);
		
		if(MAX[1] < ans ) ans = MAX[1],ansx = tt;

		for(int i=head[tt];i;i=edge[i].next)
			change(1,0,n,f[tt]+g[edge[i].to]+1,1);
		change(1,0,n,f[tt],1);
	}
	
	cout << ansx << " " << ans << endl;
}
