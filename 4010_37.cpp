
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
struct E
{int next,to;}e[N];
int head[N],tot,deg[N],n,m;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
	deg[y]++;
}
int ans[N],top,heap[N],cnt;
void topo()
{
	for(int i = n;i>=1;i--)
		if(!deg[i])
			heap[++cnt] = i;
	while(cnt)
	{
		int x = heap[1];
		ans[++top] = x;
		pop_heap(heap+1,heap+cnt+1);
		cnt--;
		for(int i = head[x];i;i=e[i].next)
			if(!(--deg[e[i].to]))
				heap[++cnt] = e[i].to,push_heap(heap+1,heap+cnt+1);
	}
}
void init()
{
	memset(head,0,sizeof(head));
	tot = 0;
	memset(deg,0,sizeof(deg));
	cnt = top = 0;
}
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		init();
		scanf("%d%d",&n,&m);
		int x,y;
		for(int i = 1;i<= m;i++)
		{
			scanf("%d%d",&x,&y);
			add(y,x);
		}
		topo();
		if(top!=n)printf("Impossible!\n");
		else
		{
			for(int i = n;i>= 1;i--)
				printf("%d ",ans[i]);
			printf("\n");
		}
	}
	return 0;
}
