
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int S = 1<<8;
const int N = 1e4+5;
const int INF = 0x3f3f3f3f;
int dis[S][N];
bool vis[N];
queue<int>Q;
struct E
{int next,to,val;}e[N<<1];
int head[N],tot,ans[S];
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].val = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].val = f;
}

void spfa(int dis[])
{
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		vis[x] = false;
		for(int i = head[x];i;i=e[i].next)
			if(dis[e[i].to]>dis[x]+e[i].val)
			{
				dis[e[i].to] = dis[x]+e[i].val;
				if(!vis[e[i].to])
				{
					Q.push(e[i].to);
					vis[e[i].to] = true;
				}
			}
	}
}
int n,m,d;
bool check_sta(int s)
{
	bool flag = true;
	for(int i = 1;i<= d;i++)
		flag&= ((s>>(i-1))&1)==((s>>(2*d-i))&1);
	return flag;
}
int main()
{
	int x,y,z;
	scanf("%d%d%d",&n,&m,&d);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	memset(dis,0x3f,sizeof(dis));
	for(int i = 1;i<= d;i++)dis[1<<(i-1)][i] = 0;
	for(int i = 1;i<= d;i++)dis[1<<(2*d-i)][n-i+1] = 0;
	int end = 1<<(2*d);
	for(int s = 0;s<end;s++)
	{
		for(int i = 1;i<= n;i++)
		{
			for(int t = s;t;t=(t-1)&s)
				dis[s][i] = min(dis[s][i],dis[t][i]+dis[s^t][i]);
			if(dis[s][i]!=INF)Q.push(i),vis[i]=true;
		}
		spfa(dis[s]);
	}
	memset(ans,0x3f,sizeof(ans));
	for(int s = 0;s<end;s++)
		if(check_sta(s))
			for(int i = 1;i<= n;i++)
				ans[s] = min(ans[s],dis[s][i]);
	for(int s = 0;s<end;s++)
		for(int t = s;t;t = (t-1)&s)
			ans[s] = min(ans[s],ans[s^t]+ans[t]);
	if(ans[end-1]!=INF)printf("%d\n",ans[end-1]);
	else puts("-1");
	return 0;
}
