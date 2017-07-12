
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 200;
const int M = 6005;
const int INF = 0x3f3f3f3f;
struct E
{
	int next,to,f;
}e[M];
int head[N],tot=1,a[N],b[N],d[N],n,m;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].f = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].f = f;
}
queue<int>Q;
bool bfs(int s,int t)
{
	memset(d,-1,sizeof(d));
	d[t] = 0;
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
int ans[N][N];
int get_mxf(int s,int t,int mx)
{
	if(s==t)return mx;
	int last = mx;
	for(int i = head[s];i;i=e[i].next)
		if(d[e[i].to]==d[s]-1&&e[i].f)
		{
			int tof = get_mxf(e[i].to,t,min(last,e[i].f));
			if(tof)
			{
				e[i].f-=tof;
				e[i^1].f+=tof;
				if(!(last-=tof))return mx;
			}
		}
	d[s] =-1;
	return mx-last;
}
int dinic(int s,int t)
{
	int ans = 0;
	while(bfs(s,t))
		ans+=get_mxf(s,t,INF);
	return ans;
}
void reset()
{
	for(int i = 2;i<= tot;i+=2)
		e[i].f = e[i^1].f = (e[i].f+e[i^1].f)>>1;
}
bool v[N];
void dfs(int x)
{
	v[x] = true;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].f&&!v[e[i].to])
			dfs(e[i].to);
}
void solve(int l,int r)
{
	if(l==r)return ;
	int s = a[l],t = a[r];
	reset();
	int tmp = dinic(s,t);
	memset(v,0,sizeof(v));
	dfs(s);
	for(int i = 1;i<= n;i++)
		if(v[i])
			for(int j = 1;j<= n;j++)
				if(!v[j])
					ans[i][j] = ans[j][i] = min(ans[i][j],tmp);
	int j = l,k = r;
	for(int i = l;i<= r;i++)
		if(v[a[i]])b[j++]=a[i];
		else b[k--]=a[i];
	for(int i = l;i<= r;i++)
		a[i]=b[i];
	solve(l,j-1);
	solve(k+1,r);
}
void init()
{
	memset(head,0,sizeof(head));
	tot = 1;
	memset(ans,0x3f,sizeof(ans));
}
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		init();
		int u,v,c;
		scanf("%d%d",&n,&m);
		for(int i = 1;i<= n;i++)a[i]=i;
		for(int i = 1;i<= m;i++)
		{
			scanf("%d%d%d",&u,&v,&c);
			add(u,v,c);
		}
		solve(1,n);
		int q;
		scanf("%d",&q);
		for(int i = 1;i<= q;i++)
		{
			scanf("%d",&c);int Ans =0;
			for(int j = 1;j<= n;j++)
				for(int k = j+1;k<= n;k++)
					Ans+=(ans[j][k]<=c);
			printf("%d\n",Ans);
		}
		if(cas)printf("\n");
	}
	return 0;
}
