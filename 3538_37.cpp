
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 10005;
const int M = 50005;
bool v[N];
struct E
{int next,to,val;};
queue<int>Q;
struct G
{
	E e[M<<1];
	int head[N],tot,minn;
	void add(int x,int y,int f)
	{
		e[++tot].to = y;
		e[tot].next = head[x];
		e[tot].val = f;
		head[x] = tot;
	}
	int dis[N];
	void spfa(int s,int t)
	{
		memset(dis,0x3f,sizeof(dis));
		dis[s] = 0;
		v[s] = true;
		Q.push(s);
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			v[x] = false;
			for(int i = head[x];i;i = e[i].next)
			{
				if(dis[x]+e[i].val<dis[e[i].to])
				{
					dis[e[i].to] = dis[x]+e[i].val;
					if(!v[e[i].to])
					{
						Q.push(e[i].to);
						v[e[i].to] = true;
					}
				}
			}
		}
		minn = dis[t];
	}
}g1,g2,g;
int main()
{
	int n,m,x,y,u,w;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&x,&y,&u,&w);
		g1.add(y,x,u);
		g2.add(y,x,w);
	}
	g1.spfa(n,1);
	g2.spfa(n,1);
	for(int i = 1;i<= n;i++)
		for(int j = g1.head[i];j;j = g1.e[j].next)
		{
			int t = g1.e[j].to;
			int cnt = 0;
			if(g1.dis[i]+g1.e[j].val!=g1.dis[t])cnt++;
			if(g2.dis[i]+g2.e[j].val!=g2.dis[t])cnt++;
			g.add(t,i,cnt);
		}
	g.spfa(1,n);
	printf("%d\n",g.minn);
	return 0;
}
