
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 500005;
struct P
{
	int f,size;
}p[N];
bool cmp(P a,P b)
{
	return a.f-a.size>b.f-b.size;
}
int size[N],f[N],c[N];
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
P stack[N];
int top;
void dfs(int x,int fa)
{
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
			dfs(e[i].to,x);
	top = 0;
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
		{
			p[e[i].to].size+=2;
			p[e[i].to].f = max(p[e[i].to].f+1,p[e[i].to].size);
			stack[++top] = p[e[i].to];
		}
	sort(stack+1,stack+top+1,cmp);
	p[x].f = c[x];
	for(int i = 1;i<=top;i++)
	{
		p[x].f = max(p[x].f,stack[i].f+p[x].size);
		p[x].size+=stack[i].size;
	}
}
int main()
{
	int n,x,y;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&c[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1,0);
	printf("%d\n",max(p[1].f,p[1].size+c[1]));
	return 0;
}
