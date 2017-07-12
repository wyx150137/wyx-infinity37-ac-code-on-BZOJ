
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1005;
const int M = 500005;
const ll INF = 1e18;
const int inf = 0x3f3f3f3f;
struct E
{int next,to;ll f;};
ll dis[N];
int d[N];
bool v[N];
queue<int>Q;
struct G
{
	int head[N],tot;
	E e[M];
	void addE(int x,int y,int z)
	{e[++tot].to=y;e[tot].next = head[x];head[x]=tot;e[tot].f=z;}
	void addF(int x,int y,ll f)
	{
		e[++tot].to=y;e[tot].next=head[x];e[tot].f=f;head[x]=tot;
		e[++tot].to=x;e[tot].next=head[y];e[tot].f=0;head[y]=tot;
	}
	void spfa(int s,int n)
	{
		for(int i = 1;i<= n;i++)dis[i]=INF;
		dis[s]=0;v[s]=true;
		Q.push(s);
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			v[x] = false;
			for(int i = head[x];i;i=e[i].next)
				if(dis[x]+e[i].f<dis[e[i].to])
				{
					dis[e[i].to]=dis[x]+e[i].f;
					if(!v[e[i].to])
					{
						Q.push(e[i].to);
						v[e[i].to]=true;
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
					d[e[i].to] = d[x]+1;
					Q.push(e[i].to);
				}
		}
		return d[s]!=-1;
	}
	ll get_maxflow(int s,int t,ll mf)
	{
		if(s==t)return mf;
		ll last = mf;
		for(int i = head[s];i;i=e[i].next)
			if(d[e[i].to]==d[s]-1&&e[i].f)
			{
				ll tof = get_maxflow(e[i].to,t,min(e[i].f,last));
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
	ll dinic(int s,int t)
	{
		ll ans=0,nowflow;
		while(bfs(s,t))
			while((nowflow=get_maxflow(s,t,INF)))
				ans+=nowflow;
		return ans;
	}
}F,G;
int c[N],x[M],y[M],z[M];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x[i],&y[i],&z[i]);
		G.addE(x[i],y[i],z[i]);
		G.addE(y[i],x[i],z[i]);
	}
	for(int i = 1;i<= n;i++)
		scanf("%d",&c[i]);
	G.spfa(1,n);
	F.tot = 1;
	for(int i = 1;i<= m;i++)
	{
		if(dis[x[i]]+z[i]==dis[y[i]])
			F.addF(x[i]+n,y[i],INF);
		if(dis[y[i]]+z[i]==dis[x[i]])
			F.addF(y[i]+n,x[i],INF);
	}
	for(int i = 1;i<= n;i++)
		F.addF(i,i+n,c[i]);
	ll ans = F.dinic(n+1,n);
	printf("%lld\n",ans);
	return 0;
}
