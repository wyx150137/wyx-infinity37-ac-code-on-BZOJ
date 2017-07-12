
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
int cnt;
struct E
{int x,y,id;}edge[N<<2];
void insert(int a,int b,int i)
{
	edge[++cnt].x = a;
	edge[cnt].y = b;
	edge[cnt].id = i; 
}
bool cmp(E a,E b)
{
	if(a.x!=b.x)
		return a.x<b.x;
	return a.y<b.y;
}
struct Edge
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
	e[++tot].to = x;
	e[tot].next = head[y];
	head[y] = tot;
}
int max_dep,end;
void dfs(int x,int fa,int dep)
{
	if(dep>max_dep)
	{
		max_dep = dep;
		end = x;
	}
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
			dfs(e[i].to,x,dep+1);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n-2;i++)
	{
		int a[4];
		scanf("%d%d%d",&a[1],&a[2],&a[3]);
		sort(a+1,a+4);
		insert(a[1],a[2],i);insert(a[1],a[3],i);insert(a[2],a[3],i);
	}
	sort(edge+1,edge+cnt+1,cmp);
	for(int i = 2;i<= cnt;i++)
		if(edge[i].x==edge[i-1].x&&edge[i].y==edge[i-1].y)add(edge[i].id,edge[i-1].id);
	dfs(1,0,1);
	dfs(end,0,1);
	printf("%d\n",max_dep);
	return 0;
}
