
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int col[N],typ[N];
int dfs(int x,int fa)
{
	if(typ[x]<=0)return col[x];
	int sum = 0;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
			sum+=dfs(e[i].to,x);
	if(sum<0)return -1;
	else if(sum>0)return 1;
	return 0;
}
int ans[N],top;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&typ[i]);
		if(typ[i]==-2)col[i] = 1;
		else if(typ[i]==-1)col[i] = -1;
		else if(typ[i]>0)
		{
			int m = typ[i],x;
			while(m--)
				scanf("%d",&x),add(i,x);
		}
	}
	if(dfs(1,0)<0)printf("NIE\n");
	else
	{
		for(int i = 1;i<= n;i++)
			if(typ[i]==0)
			{
				col[i] = 1;
				if(dfs(1,0))ans[++top] = i;
				col[i] = 0;
			}
		printf("TAK %d\n",top);
		for(int i = 1;i<= top;i++)
		{
			printf("%d",ans[i]);
			if(i!=top)printf(" ");
		}
	}
	return 0;
}
