
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const int M = 20005;
struct E
{int next,to;}e[M];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
queue<int>Q;
int dis[N][N];
void bfs(int s)
{
	memset(dis[s],-1,sizeof(dis[s]));
	Q.push(s);
	dis[s][s] = 0;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i = e[i].next)
			if(dis[s][e[i].to]==-1)
			{
				dis[s][e[i].to] = dis[s][x]+1;
				Q.push(e[i].to);
			}
	}
	return ;
}
struct P
{int no,val;}p[N];
bool cmp(P a,P b)
{
	return a.val>b.val;
}
int f[N];
int main()
{
	int n,en;
	scanf("%d%d",&n,&en);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&p[i].val);
		p[i].no = i;
		int d,x;
		scanf("%d",&d);
		for(int j = 1;j<= d;j++)
		{
			scanf("%d",&x);
			add(i,x);
		}
	}
	for(int i = 1;i<= n;i++)
	{
		bfs(i);
		for(int j = 1;j<= n;j++)
			dis[i][j]*=en;
		dis[0][i] = 0;
	}
	sort(p+1,p+n+1,cmp);
	for(int i = 1;i<= n;i++)
		for(int j = 0;j<i;j++)
			if(dis[p[j].no][p[i].no]>=0)
				f[i] = max(f[i],f[j]-dis[p[j].no][p[i].no]+p[i].val);
	int ans =0;
	for(int i = 1;i<= n;i++)
		ans = max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
