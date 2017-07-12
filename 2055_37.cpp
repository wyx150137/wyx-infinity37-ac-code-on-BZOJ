
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 305;
const int M = 1e5+5;
const int INF = 0x3f3f3f3f;
struct E
{
	int next,to,f,c,from;
}e[M];
int head[N],tot = 1;
int in[N],out[N],ans;
void add(int x,int y,int lr,int ur,int c)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[tot].f = ur-lr,e[tot].c = c,e[tot].from = x;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
	e[tot].f = 0;e[tot].c = -c;e[tot].from = y;
	out[x]+=lr,in[y]+=lr;
	ans+=lr*c;
}
bool vis[N];
int dis[N],from[N];
queue<int>Q;
bool spfa(int s,int t)
{
	for(int i = 1;i<= t;i++)dis[i] = INF,vis[i] = false;
	Q.push(s);
	dis[s] = 0;
	vis[s] = true;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		vis[x] = false;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].f&&dis[e[i].to]>dis[x]+e[i].c)
			{
				dis[e[i].to] = dis[x]+e[i].c;
				from[e[i].to] = i;
				if(!vis[e[i].to])
				{
					Q.push(e[i].to);
					vis[e[i].to] = true;
				}
			}
	}
	return dis[t]!=INF;
}
void get_mcf(int s,int t)
{
	int x = INF;
	for(int i = from[t];i;i=from[e[i].from])
		x = min(x,e[i].f);
	for(int i = from[t];i;i=from[e[i].from])
		e[i].f-=x,e[i^1].f+=x,ans+=x*e[i].c;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int SS = n+n+2,TT = n+n+3,S = n+n+4,T = n+n+5;
	add(SS,n+n+1,0,m,0);
	for(int i = 1;i<= n;i++)
		add(n+n+1,i,0,INF,0),add(i+n,TT,0,INF,0);
	int x;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		add(i,i+n,x,x,0);
	}
	for(int i = 1;i< n;i++)
		for(int j = 1;j<=n-i;j++)
		{
			scanf("%d",&x);
			if(x==-1)continue;
			add(n+i,i+j,0,INF,x);
		}
	add(TT,SS,0,INF,0);
	for(int i = 1;i<= TT;i++)
		if(in[i]<out[i])
			add(i,T,0,out[i]-in[i],0);
		else if(out[i]<in[i])
			add(S,i,0,in[i]-out[i],0);
	while(spfa(S,T))get_mcf(S,T);
	printf("%d\n",ans);
	return 0;
}
