
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 100000+5
#define M 400000+5
using namespace std;
int head[N];
int fa[N];
int f[N];
int v[N];
int find(int x)
{
	return f[x]^x?f[x]=find(f[x]):f[x];
}
struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];
struct ask
{
	int pos,kind;
	ask () {}
	ask (int x,int y)
	:pos(x),kind(y){}	
}q[N];
inline void add(int x,int y)
{
	static int cnt = 0;
	edge[++cnt]=graph(head[x],y);
	head[x]=cnt;
	edge[++cnt]=graph(head[y],x);
	head[y]=cnt;
}
void DFS(int x)
{
	if(v[x])
		f[x]=x;
	else
		f[x]=fa[x];
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
			fa[edge[i].to]=x,DFS(edge[i].to);
}
int ans[N];
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read();
		add(x,y);
	}
	for(int i=1;i<=m;++i)
	{
		char ch[5];
		scanf("%s%d",ch,&q[i].pos);
		if(ch[0]=='C'){v[q[i].pos]++;q[i].kind=1;}
	}
	v[1]++;
	DFS(1);
	for (int i=m;i>=1;i--)
	{
    	if (q[i].kind)
    	{
        	v[q[i].pos]--;
        	if (!v[q[i].pos]) 
        		f[q[i].pos]=fa[q[i].pos];
    	}
    	else ans[i]=find(q[i].pos);
    }
	for (int i=1;i<=m;i++) 
		if(!q[i].kind)
			printf("%d\n",ans[i]);
}
