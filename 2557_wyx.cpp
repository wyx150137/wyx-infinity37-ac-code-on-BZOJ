
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>

const int N = 500+10;
const int M = N * N ; 

using namespace std;

int head[N];

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

bool pass[N],used[N];
int col[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
	return x*f;
}

bool DFS(int x)
{
	for(int i=head[x];i;i=edge[i].next)
		if(!used[edge[i].to])
		{
			used[edge[i].to] = 1;
			if(!col[edge[i].to] || DFS(col[edge[i].to]))
				return col[edge[i].to] = x, true;
		}
	return false;
}

int main()
{

	int n = read(), m = read(),r = read(), tt = read(),T = read();
	for(int i=1;i<=T;++i)
	{
		int x = read(), y = read();
		add(x,y);
	}
	int ans1 = 0 , ans2 = 0;
	for(int j=1;j<=tt/r;++j)
		for(int i=1;i<=n;++i)
			if(!pass[i])
			{
				memset(used,0,sizeof used);
				if(DFS(i))
					ans1 ++,ans2 += j;
				else pass[i] = 1;
			}
	cout << ans1 << " " << (long long)ans2 *r << endl;
}
