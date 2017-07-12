
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2005;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,f,c;}e[N*N];
int head[N<<1],tot = 1;
void add(int x,int y,int f,int c)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[tot].f = f,e[tot].c = c;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
	e[tot].f = 0;e[tot].c = -c;
}
int dis[N<<1],n;bool vis[N<<1];
queue<int>Q;
bool spfa(int s,int t)
{
	for(int i = s;i<= t;i++)dis[i] = -1;
	dis[s] = 0;
	vis[s] = true;
	Q.push(s);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		vis[x] = false;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].f&&dis[e[i].to]<dis[x]+e[i].c)
			{
				dis[e[i].to] = dis[x]+e[i].c;
				if(!vis[e[i].to])
				{
					Q.push(e[i].to);
					vis[e[i].to] = true;
				}
			}
	}
	return dis[t]!=-1;
}
bool visit[N<<1];
int getflow(int p,int s,int t,int mf)
{
	if(p==t)return mf;
	visit[p] = true;
	int last = mf;
	for(int i = head[p];i;i=e[i].next)
		if(e[i].f&&dis[p]+e[i].c==dis[e[i].to]&&(!visit[e[i].to]||e[i].to==t))
		{
			int tof = getflow(e[i].to,s,t,min(last,e[i].f));
			e[i].f-=tof;
			e[i^1].f+=tof;
			last-=tof;
			if(!last)
				return mf;
		}
	return mf-last;
}
int Maxcost(int s,int t)
{
	int res = 0;
	while(spfa(s,t))
	{
		memset(visit,0,sizeof(visit));
		res+=getflow(s,s,t,INF)*dis[t];
	}
	return res;
}
struct Point
{
	int x,y;
	Point(){}
	Point(int _x,int _y):x(_x),y(_y){}
	void read()
	{
		scanf("%d%d",&x,&y);
	}
	bool operator <(const Point &s)const
	{
		return x<s.x||(x==s.x&&y<s.y);
	}
}p[N];
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		p[i].read();
	sort(p+1,p+n+1);
	add(0,1,2,0);
	int S = 1,T = 2*n+2;
	for(int i = 1;i<= n;i++)
		add(S,i<<1,1,0),
		add(i<<1|1,T,1,0),
		add(i<<1,i<<1|1,1,1),
		add(i<<1,i<<1|1,1,0);
	for(int i = 1;i<= n;i++)
	{
		int Min = INF;
		for(int j = i+1;j<= n;j++)
		{
			if(p[j].y<Min&&p[j].y>=p[i].y)
				add(i<<1|1,j<<1,2,0);
			if(p[j].y>=p[i].y)
				Min = min(Min,p[j].y);
		}
	}
	printf("%d\n",Maxcost(0,T));
	return 0;
}
