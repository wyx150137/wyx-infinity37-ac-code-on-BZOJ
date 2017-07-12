
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 505;
const int M = 1e6+5;
struct E
{int next,to;}e[M];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
bool used[N],pass[N];
int fa[N];
bool dfs(int x)
{
	for(int i=head[x];i;i = e[i].next)
		if(!used[e[i].to])
		{
			used[e[i].to] = true;
			if(!fa[e[i].to]||dfs(fa[e[i].to]))
			{
				fa[e[i].to] = x;
				return true;
			}
		}
	return false;
}
int main()
{
	int n,m,r,t,k,x,y;
	scanf("%d%d%d%d%d",&n,&m,&r,&t,&k);
	for(int i = 1;i<= k;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	int ans1 = 0,ans2 = 0;
	for(int j = r;j<=t;j = j+r)
	{
		for(int i = 1;i<= n;i++)
			if(!pass[i])
			{
				memset(used,0,sizeof(used));
				if(dfs(i))ans1++,ans2+=j;
				else pass[i] = true;
			}
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
}
