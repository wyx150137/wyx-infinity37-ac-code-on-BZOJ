
#include <stdio.h>
#include <set>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 1e4+5;
struct Point 
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
	void read(){scanf("%d%d",&x,&y);}
	int operator *(const Point &s)const
	{
		return x*s.y-y*s.x;
	}
}p[N];
struct E
{
	int x,y;
	double alp;
	E(int _x=0,int _y=0):x(_x),y(_y)
	{
		alp = atan2(p[_y].x-p[_x].x,p[_y].y-p[_x].y);
	}
}e[N];
struct Edge
{
	int x,y,v;
	Edge(int _x=0,int _y=0,int _v=0):x(_x),y(_y),v(_v){}
}ed[N];
int bel[N],cnt,tp=1;
int w[N];
struct Pic_to_Gra
{
	struct cmp
	{
		bool operator()(const int &a,const int &b)
			{return e[a].alp<e[b].alp;}
	};
	set<int,cmp>g[N];
	set<int>::iterator it;
	bool del[N];
	int q[N];
	void Insert(int x,int y){g[x].insert(y);}
	void work()
	{
		int t,j;
		for(int i = 2;i<=tp;i++)
			if(!del[i])
			{
				t = 1;
				q[t] = j = i;
				while(true)
				{
					it = g[e[j].y].find(j^1);
					it++;
					if(it==g[e[j].y].end())it = g[e[j].y].begin();
					if(*it==i)break;
					q[++t] = j = *it;
				}
				int s= 0;
				for(j=1;j<=t;j++)s+=p[e[q[j]].x]*p[e[q[j]].y];
				++cnt;
				for(j=1;j<=t;j++)del[q[j]]=true,bel[q[j]]=cnt;
			}
	}
}p2g;
struct Minimum_Tree_Gragh
{
	int pre[N],id[N],in[N],vis[N];
	int work(int root,int n,int m)
	{
		int tn,tm,ans = 0;
		while(true)
		{
			for(int i = 1;i<= n;i++)in[i]=INF,pre[i]=0;
			for(int i = 1;i<= m;i++)
				if(ed[i].v<in[ed[i].y])
				{
					in[ed[i].y] = ed[i].v;
					pre[ed[i].y] = ed[i].x;
				}
			tn = tm = in[root] = 0;
			for(int i = 1;i<= n;i++)id[i]=vis[i] = 0;
			for(int v,i = 1;i<= n;i++)
			{
				ans+=in[v=i];
				while(vis[v]!=i&&!id[v]&&v!=root)vis[v]=i,v=pre[v];
				if(v!=root&&!id[v])
				{
					id[v] = ++tn;
					for(int u = pre[v];u!=v;u=pre[u])id[u]=tn;
				}
			}
			if(!tn)break;
			for(int i = 1;i<= n;i++)if(!id[i])id[i]=++tn;
			for(int i = 1;i<= m;i++)
				if(id[ed[i].x]!=id[ed[i].y])
					ed[++tm] = Edge(id[ed[i].x],id[ed[i].y],ed[i].v-in[ed[i].y]);
			n = tn,m = tm,root = id[root];
		}
		return ans;
	}
	void solve()
	{
		int n = cnt+1,root = cnt+1,m=0,sum = 0;
		for(int i = 2;i<= tp;i++)
			if(bel[i]&&bel[i^1]&&w[i])
			{
				ed[++m] = Edge(bel[i],bel[i^1],w[i]);
				sum+=w[i];
			}
		for(int i = 1;i<= cnt;i++)ed[++m] = Edge(root,i,sum);
		printf("%d\n",work(root,n,m)-sum);
	}
}mtg;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)p[i].read();
	for(int i = 1;i<= m;i++)
	{
		int u,v;
		scanf("%d%d%d%d",&u,&v,&w[i*2],&w[i*2+1]);
		e[++tp] = E(u,v),p2g.Insert(u,tp);
		e[++tp] = E(v,u),p2g.Insert(v,tp);
	}
	p2g.work();
	mtg.solve();
	return 0;
}
