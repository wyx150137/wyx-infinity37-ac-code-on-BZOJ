
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 605;
const int M = 2e5+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,val;}e[M];
int head[N],tot;
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val = f;
	head[x] = tot;
}
bool ins[N],v[N];
int dep[N],low[N],stack[N],dfn,top,bel[N],scc;
int map[N][N];
void tarjan(int x)
{
	v[x] = ins[x] = true;
	stack[++top] = x;
	dep[x] = low[x] = ++dfn;
	for(int i = head[x];i;i = e[i].next)
	{
		if(!v[e[i].to])
			{tarjan(e[i].to);low[x] = min(low[e[i].to],low[x]);}
		else if(ins[e[i].to])
			{low[x] = min(low[x],dep[e[i].to]);}
	}
	if(dep[x]==low[x])
	{
		scc++;
		int tmp;
		do
		{
			tmp = stack[top--];
			ins[tmp] =false;
			bel[tmp] = scc;
		}while(tmp!=x);
	}
}
int main()
{
	int n,m1,m2;
	scanf("%d%d%d",&n,&m1,&m2);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			map[i][j] = -INF;
	for(int i = 1;i<= n;i++)map[i][i] = 0;
	int x,y;
	for(int i = 1;i<= m1;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y,1),add(y,x,-1);
		map[x][y] = max(map[x][y],1);
		map[y][x] = max(map[y][x],-1);
	}
	for(int i = 1;i<= m2;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y,0);
		map[x][y] = max(map[x][y],0);
	}
	for(int i = 1;i<= n;i++)
		if(!v[i])
			tarjan(i);
	int t_ans = 0;
	for(int t = 1;t<= scc;t++)
	{
		for(int k = 1;k<= n;k++)
		{
			if(bel[k]!=t)continue;
			for(int i = 1;i<= n;i++)
			{
				if(bel[i]!=t||map[i][k]==-INF)continue;
				for(int j = 1;j<= n;j++)
				{
					if(bel[j]!=t||map[k][j]==-INF)continue;
					map[i][j] = max(map[i][j],map[i][k]+map[k][j]);
				}
			}
		}
		int ans = 0;
		for(int i = 1;i<= n;i++)
			if(bel[i]==t)
				for(int j = 1;j<= n;j++)
					if(bel[j]==t)
						ans = max(ans,abs(map[i][j]));
		t_ans += ans+1;
	}
	for(int i = 1;i<= n;i++)
		if(map[i][i])
		{
			printf("NIE\n");
			return 0;
		}
	printf("%d\n",t_ans);
	return 0;
}
