
#include <stdio.h>
#include <queue>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const double eps = 1e-8;
struct Edge{int next,to;}e[N<<1];
int head[N],tot,cnt[N],v[N],dis[N];
int step[N][N];
double f[N][N];
queue <int>Q;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
void spfa(int sta)
{
	memset(v,0,sizeof(v));
	memset(dis,0x3f,sizeof(dis));
	Q.push(sta);
	v[sta] = true;
	dis[sta] = 0;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		v[x] = false;
		for(int i = head[x];i;i = e[i].next)
		{
			if(dis[x]+1<dis[e[i].to]||(dis[x]+1==dis[e[i].to]&&x<step[sta][e[i].to]))
			{
				step[sta][e[i].to] = x;
				dis[e[i].to] = dis[x]+1;
				if(!v[e[i].to])
				{
					Q.push(e[i].to);
					v[e[i].to] = true;
				}
			}
		}
	}
	return ;
}
double dfs(int x,int y)
{
	if(x==y)return f[x][y] = 0;
	if(f[x][y]>eps)return f[x][y];
	if(step[y][x]==y||step[y][step[y][x]]==y)return f[x][y] = 1.0;
	int tmp = step[y][step[y][x]];
	double ans = dfs(tmp,y);
	for(int i=head[y];i;i = e[i].next)
		ans+=dfs(tmp,e[i].to);
	ans = ans/(double)(cnt[y]+1)+1;
	f[x][y] = ans;
	return ans;
}
int main()
{
	int n,E,c,m;
	scanf("%d%d%d%d",&n,&E,&c,&m);
	int x,y;
	for(int i = 1;i<= E;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
		cnt[x]++;cnt[y]++;
	}
	for(int i = 1;i<= n;i++)
		spfa(i);
	//printf("warning\n");
	memset(f,0xc2,sizeof(f));
	printf("%.3f",dfs(c,m));
	return 0;
}
