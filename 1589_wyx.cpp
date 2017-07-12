
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>
#define N 200000+5
#define M 100000+5
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
	static int cnt  = 0;
	edge[++cnt]=graph(head[x],y);
	head[x]=cnt;
}
bool vis[N],cirlce[N];
int belong[N],ans[N],step[N];
queue<int>Q;
int in[N];
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-')f= -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
void DFS(int x,int fa,int dep)
{
	if(vis[x] && belong[x]==fa)
	{
		ans[x]=dep-step[x];
		return;
	}
	belong[x]=fa;
	cirlce[x]=1;
	step[x]=dep;
	vis[x]=1;
	for(int i=head[x];i;i=edge[i].next)
	{
		DFS(edge[i].to,fa,dep+1);
		ans[x]=ans[edge[i].to];
	}
}
void reDFS(int x)
{
	if(ans[x])return;
	for(int i=head[x];i;i=edge[i].next)
	{
		reDFS(edge[i].to);
		ans[x]=ans[edge[i].to]+1;
	}
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		int x=read();
		add(i,x);
		in[x]++;
	}
	for(int i=1;i<=n;++i)
		if(!in[i])
			Q.push(i),vis[i]=1;
	while(!Q.empty())
	{
		int tt=Q.front();
		Q.pop();
		for(int i=head[tt];i;i=edge[i].next)
			if(!(--in[edge[i].to]))
				Q.push(edge[i].to),vis[edge[i].to]=1;
	}
	for(int i=1;i<=n;++i)
		if(!vis[i])
			DFS(i,i,1);
	for(int i=1;i<=n;++i)
		if(!cirlce[i])
			reDFS(i);
	for(int i=1;i<=n ;++i)
		printf("%d\n",ans[i] );
}
