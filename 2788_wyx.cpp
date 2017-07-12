
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;

const int inf = 1e9+7;
const int N = 600+5;
const int M = 200000+5;

int head[N];

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
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
}

bool in[N],vis[N];
int scc,top,cnt;
int stack[N];
int DFN[N],low[N],belong[N];

void Tarjan(int x)
{	
	vis[x] = in[x] = 1;
	stack[++top] = x;
	low[x] = DFN[x] = ++ cnt;
	for(int i=head[x];i;i=edge[i].next)
		if(!vis[edge[i].to])
		{
			Tarjan(edge[i].to);
			low[x] = min(low[x],low[edge[i].to]);
		}
		else if(in[edge[i].to])
			low[x] = min(low[x],DFN[edge[i].to]);
	if(low[x] == DFN[x])
	{
		int now = 0; scc++;
		while(now ^ x)
		{
			int tt = stack[top--];
			belong[tt] = scc;
			in[tt] = false;
			now = tt;
		}
	}
}

int mp[N][N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	int n = read(),m1 = read(), m2 = read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			mp[i][j] = -inf;

	for(int i=1;i<=n;++i) mp[i][i] = 0;
	for(int i=1;i<=m1;++i)
	{
		int x = read(),y = read();
		add(x,y,1);add(y,x,-1);
		mp[x][y] = max(mp[x][y],1);
		mp[y][x] = max(mp[y][x],-1);

	}
	for(int i=1;i<=m2;++i)
	{
		int x = read(), y = read();
		add(x,y,0);
		mp[x][y] = max(mp[x][y],0);
 	}

 	for(int i=1;i<=n;++i)
 		if(!vis[i])
 			Tarjan(i);
 	int ans = 0;

 	for(int t=1;t<=scc;++t)
 	{
 		int re = 0;
 		for(int k=1;k<=n;++k)
 		{
 			if(belong[k]!=t)  continue;
 			for(int i=1;i<=n;++i)
 			{
 				if( belong[i]!=t || mp[i][k] == -inf) continue;
 				for(int j=1;j<=n;++j)
 				{
 					if(belong[j]!=t || mp[k][j] == -inf) continue;
 					mp[i][j] = max(mp[i][j],mp[i][k]+mp[k][j]);
 				}
 			}
 		}
 		for(int i=1;i<=n;++i)
 		{
 			if(belong[i]!=t) continue;
 			for(int j=1;j<=n;++j)
 			{
 				if(belong[j]!=t) continue;
 				re = max(re,abs(mp[i][j]));
 			}
 		}
 		ans += re + 1;
 	}
 	for(int i=1;i<=n;++i) 
 		if(mp[i][i])
 		{
 			puts("NIE");
 			return 0;
 		}
 	cout << ans << endl;
}
