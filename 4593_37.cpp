
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;
struct node {int to;int next;};node bian[200005];
int first[100005],size,f[100005],h[100005],g[1000010];
int father[100005],d[100005],c[100005],n,a,b,maxc;
void inser(int x,int y) {
	size ++;
	bian[size].to = y;
	bian[size].next = first[x];
	first[x] = size;
}
void dfs(int x,int Anc) {
	father[x] = Anc;
	int _d1 = d[x],_d2 = d[x] - c[father[x]],ret = 0;
	for(int u = first[x];u;u = bian[u].next)
	{
		if(bian[u].to == Anc) continue;
		dfs(bian[u].to,x);
		if(f[bian[u].to] == h[bian[u].to])
		{
			_d1 -= c[bian[u].to];
			_d2 -= c[bian[u].to];
			ret += f[bian[u].to];
		}
		else ret += h[bian[u].to];
	}
	f[x] = ret + max(_d1,0);
	h[x] = ret + max(_d2,0);
}
void bfs(int x,int Anc) {
	father[x] = Anc;
	int _d1 = d[x],_d2 = d[x] - c[father[x]],ret = 0;
	for(int u = first[x];u;u = bian[u].next)
	{
		if(bian[u].to == Anc) continue;
		bfs(bian[u].to,x);
		if(f[bian[u].to] - h[bian[u].to] < c[bian[u].to])
		{
			_d1 -= c[bian[u].to];
			_d2 -= c[bian[u].to];
			ret += f[bian[u].to];
		}
		else ret += h[bian[u].to];
	}
	if(_d1 < 0) 
	{
		int _n = 0;g[0] = 0;
		for(int u = first[x];u;u = bian[u].next)
		{
			if(bian[u].to == Anc) continue;
			if(f[bian[u].to] - h[bian[u].to] >= c[bian[u].to]) continue;
			for(int i = _n + 1;i <= _n + c[bian[u].to];i ++)
				g[i] = 0;
			_n = _n + c[bian[u].to];
			int C = c[bian[u].to],D = f[bian[u].to] - h[bian[u].to];
			for(int i = 0;i + C <= _n;i ++)
				g[i + C] = ((g[i + C] > g[i] + D) ? g[i + C] : g[i] + D);
		}
		f[x] = ret;
		for(int i = 1;i <= _n;i ++)
			f[x] = min(f[x],max(0,_d1 + i) + ret - g[i]);
		//f[x] = ret - g[_n];
	}
	else f[x] = ret + max(_d1,0);
	if(_d2 < 0) 
	{
		int _n = 0;g[0] = 0;
		for(int u = first[x];u;u = bian[u].next)
		{
			if(bian[u].to == Anc) continue;
			if(f[bian[u].to] - h[bian[u].to] >= c[bian[u].to]) continue;
			for(int i = _n + 1;i <= _n + c[bian[u].to];i ++)
				g[i] = 0;
			_n = _n + c[bian[u].to];
			int C = c[bian[u].to],D = f[bian[u].to] - h[bian[u].to];
			for(int i = 0;i + C <= _n;i ++)
				g[i + C] = ((g[i + C] > g[i] + D) ? g[i + C] : g[i] + D);
		}
		h[x] = ret;
		for(int i = 1;i <= _n;i ++)
			h[x] = min(h[x],max(0,_d1 + i) + ret - g[i]);	
	}
	else h[x] = ret + max(_d2,0);
}
int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++)
		scanf("%d",&d[i]);
	for(int i = 1;i <= n;i ++)
		scanf("%d",&c[i]),maxc = max(maxc,c[i]);
	for(int i = 2;i <= n;i ++)
	{
		scanf("%d%d",&a,&b);
		inser(a,b);
		inser(b,a);
	}
	if(maxc <= 1) dfs(1,0); else bfs(1,0);
	printf("%d",f[1]);
}
