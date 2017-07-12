
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const int M = 2e4+5;
struct E
{int next,to;}e[M];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int col[N],vis[N],Dfn;
void dfs(int x)
{
	Dfn++;
	for(int i = head[x];i;i=e[i].next)
		vis[col[e[i].to]] = Dfn;
	for(int i = 1;;i++)
		if(vis[i]<Dfn)
		{
			col[x] = i;
			break;
		}
	for(int i = head[x];i;i=e[i].next)
		if(!col[e[i].to])dfs(e[i].to);
}
void init()
{
	memset(vis,0,sizeof(vis));
	memset(col,0,sizeof(col));
	memset(head,0,sizeof(head)),tot = 0,Dfn = 0;
}
int main()
{
	int cas,n,m,k,x,y;
	scanf("%d",&cas);
	while(cas--)
	{
		init();
		scanf("%d%d%d",&n,&m,&k);
		for(int i = 1;i<= m;i++)
		{
			scanf("%d%d",&x,&y);
			add(x,y);
		}
		for(int i = 1;i<= n;i++)
			if(!col[i])dfs(i);
		bool cola = true;
		for(int i = 1;i<= n;i++)
			if(col[i]>k)
			{
				cola = false;
				if(col[i]==k+1)x = i;
			}
		if(cola)
		{
			printf("color");
			for(int i = 1;i<= n;i++)
				printf(" %d",col[i]);
			printf("\n");
			continue;
		}
		printf("path");
		for(int i =1;i<= k+1;i++)
		{
			printf(" %d",x);
			for(int j = head[x];j;j=e[j].next)
				if(col[e[j].to]==col[x]-1)
				{x = e[j].to;break;}
		}
		printf("\n");
	}
	return 0;
}
