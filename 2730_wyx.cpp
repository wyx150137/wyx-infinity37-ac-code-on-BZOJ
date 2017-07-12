
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 2000+5;
const int M = N;
typedef long long LL;
using namespace std;
int head[N]; 
struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

int cct = 0;

inline void add(int x,int y)
{
	edge[++cct] = graph(head[x],y); head[x] = cct;
	edge[++cct] = graph(head[y],x); head[y] = cct;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int low[N],DFN[N],cnt;
int belong[N],stack[N],top;

void DFS(int x)
{
	DFN[x] = low[x] = ++cnt;
	for(int i=head[x];i;i=edge[i].next)
		if(DFN[edge[i].to]) low[x] = min(low[x],DFN[edge[i].to]);
		else {
			DFS(edge[i].to);
			low[x] = min(low[x],low[edge[i].to]);
			if(low[edge[i].to] >= DFN[x]) belong[x] ++;
		}
}

int ans1;
LL ans2 ;

void DFS2(int x)
{
	DFN[x] = low[x] = ++cnt;
	stack[++top] = x;
	for(int i=head[x];i;i=edge[i].next)
	{	
		if(DFN[edge[i].to])
			low[x] = min(low[x],DFN[edge[i].to]);
		else
		{
			DFS2(edge[i].to);
			low[x] = min(low[x],low[edge[i].to]);
			if(low[edge[i].to] >= DFN[x])
			{
				int tmp = 0,size = 0, cc = 0;
				while(tmp != edge[i].to)
				{
					tmp = stack[top--];
					if(belong[tmp] >= 2) cc ++; size ++;
				}
				if(belong[x] >= 2) cc ++; size++;
				if(!cc) ans1 += 2, ans2 = ans2 * size*(size-1) / 2;
				else if(cc == 1) ans1 ++,ans2 = ans2 * (size - 1);	
			}
		}
	}
}

void init()
{
	cnt = top = cct = ans1 = 0 ; ans2 = 1;
	memset(low,0,sizeof low);
	memset(DFN,0,sizeof DFN);
	memset(head,0,sizeof head);
	memset(belong,0,sizeof belong);
}

int main()
{
	int m, x, y,n = 0, testcases = 0 ;
	while(~scanf("%d",&m))
	{
		if(!m) return 0;
		init(); n = 0;
		for(int i=1;i<=m;++i)
		{
			x = read(), y = read();
			add(x,y); n = max(n,max(x,y));
		}
		for(int i=1;i<=n;++i) 
			if(!DFN[i]) 
				DFS(i);
			else 
				belong[i] ++;
		memset(DFN,0,sizeof DFN);
		for(int i=1;i<=n;++i)
			if(!DFN[i]) 
				DFS2(i);
		cout << "Case " << ++ testcases << ": " << ans1 << " " << ans2 << endl;
	}
}
