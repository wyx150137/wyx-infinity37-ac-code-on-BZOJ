
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 505;
const int M = 3e5+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,f;};
int d[N],dis[N];
bool v[N];
queue<int>Q;
struct G
{
	E e[M];
	int head[N],tot;
	void init()
	{
		memset(head,0,sizeof(head));
		tot=1;
	}
	void addE(int x,int y,int f)
	{
		e[++tot].to = y;
		e[tot].next = head[x];
		e[tot].f = f;
		head[x] = tot;
	}
	void addF(int x,int y,int f)
	{
		e[++tot].to=y;e[tot].next=head[x];e[tot].f=f;head[x]=tot;
		e[++tot].to=x;e[tot].next=head[y];e[tot].f=0;head[y]=tot;
	}
	void spfa(int s)
	{
		memset(dis,0x3f,sizeof(dis));
		dis[s]=0;v[s] = true;
		Q.push(s);
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			v[x] = false;
			for(int i = head[x];i;i=e[i].next)
				if(e[i].f+dis[x]<dis[e[i].to])
				{
					dis[e[i].to]=dis[x]+e[i].f;
					if(!v[e[i].to])
					{
						Q.push(e[i].to);
						v[e[i].to] = true;
					}
				}
		}
	}
	bool bfs(int s,int t)
	{
		memset(d,-1,sizeof(d));
		d[t]=0;
		Q.push(t);
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			for(int i = head[x];i;i=e[i].next)
				if(d[e[i].to]==-1&&e[i^1].f)
				{
					d[e[i].to]=d[x]+1;
					Q.push(e[i].to);
				}
		}
		return d[s]!=-1;
	}
	int get_maxflow(int s,int t,int mf)
	{
		if(s==t)return mf;
		int last = mf;
		for(int i = head[s];i;i=e[i].next)
			if(d[e[i].to]==d[s]-1&&e[i].f)
			{
				int tof = get_maxflow(e[i].to,t,min(e[i].f,last));
				if(tof)
				{
					e[i].f-=tof;
					e[i^1].f+=tof;
					if(!(last-=tof))return mf;
				}
			}
		d[s]=-1;
		return mf-last;
	}
	int dinic(int s,int t)
	{
		int ans=0,nowflow;
		while(bfs(s,t))
			while((nowflow=get_maxflow(s,t,INF)))
				ans+=nowflow;
		return ans;
	}
}G,F;
int x[M],y[M],c[M],t[M];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&x[i],&y[i],&t[i],&c[i]);
		G.addE(x[i],y[i],t[i]),G.addE(y[i],x[i],t[i]);
	}
	G.spfa(1);
	printf("%d\n",dis[n]);
	F.init();
	for(int i = 1;i<= m;i++)
	{
		if(dis[x[i]]+t[i]==dis[y[i]])
			F.addF(x[i],y[i],c[i]);
		if(dis[y[i]]+t[i]==dis[x[i]])
			F.addF(y[i],x[i],c[i]);
	}
	int ans = F.dinic(1,n);
	printf("%d\n",ans);
	return 0;
}
