
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 10000+5
#define M 50000+5
struct data
{int next,to;}e[M],d[M];
int head[N],n,m,cnt,top,dfn[N],low[N],q[N],belong[N],hav[N],h[N],ans,scc;
bool vis[N],inq[N];
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
void DFS(int a)
{
	int now;
	vis[a]=inq[a]=true;
	low[a]=dfn[a]=++cnt;
	q[++top]=a;
	int c=head[a];
	while(c)
	{
		if(!vis[e[c].to])
		{
			DFS(e[c].to);
			low[a]=min(low[a],low[e[c].to]);
		}
		else if(inq[e[c].to])
			low[a]=min(low[a],dfn[e[c].to]);
		c=e[c].next;
	}
	if(low[a]==dfn[a])
	{
		scc++;
		while(now^a)
		{
			now=q[top--];
			inq[now]=false;
			belong[now]=scc;
			++hav[scc];
		}
	}
}
void rebuild()
{
	cnt=0;
	for(int i=1;i<=n;++i)
	{
		int c=head[i];
		while(c)
		{
			if(belong[i]^belong[e[c].to])
			{
				d[++cnt].to=belong[e[c].to];
				d[cnt].next=h[belong[i]];
				h[belong[i]]=cnt;
			}
			c=e[c].next;
		}
	}
}
void tarjan()
{
	for(int i=1;i<=n;i++)if(!vis[i])DFS(i);
    rebuild();
}
void work()
{
	for(int i=1;i<=scc;++i)
		if(!h[i])
		{
			if(ans)
				{ans=0;return ;}
			else
				ans=hav[i];
		}	
}
int main()
{	
	cin>>n>>m;
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read();
		e[i].to=y,e[i].next=head[x];
		head[x]=i;
	}
	tarjan();
	work();
	cout<<ans;
}	
