
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3005;
const int M = 9005;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
struct E
{int next,to,f;}e[M];
int head[N],tot=1;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].f = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].f = f;
}
int d[N],n,m;
queue<int>Q;
bool bfs(int s,int t)
{
	memset(d,-1,sizeof(d));
	Q.push(s);
	d[s] = 0;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(d[e[i].to]==-1&&e[i].f)
			{
				d[e[i].to] = d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[t]!=-1;
}
int get_mxf(int s,int t,int mx)
{
	if(s==t)return mx;
	int last = mx;
	for(int i = head[s];i;i=e[i].next)
		if(e[i].f&&d[e[i].to]==d[s]+1)
		{
			int tof = get_mxf(e[i].to,t,min(last,e[i].f));
			if(tof)
			{
				e[i].f-=tof;
				e[i^1].f+=tof;
				if(!(last-=tof))return mx;
			}
		}
	d[s] = -1;
	return mx-last;
}
int dinic(int s,int t)
{
	int ans = 0;
	while(bfs(s,t))
		ans+=get_mxf(s,t,INF);
	return ans;
}
bool vis[N];
int a[N],b[N];
void dfs(int x)
{
	vis[x] = true;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].f&&!vis[e[i].to])
			dfs(e[i].to);
}
void reset()
{
	for(int i = 2;i<=tot;i+=2)
		e[i].f=e[i^1].f=(e[i].f+e[i^1].f)>>1;
}
ull BASE = 1,hash[4][N];
void solve(int l,int r)
{
	if(l==r)return ;
	int s = a[l],t = a[r];
	reset();
	int tmp = dinic(s,t);
	memset(vis,0,sizeof(vis));
	dfs(s);
	BASE *= 131;
	for(int i = 1;i<= n;i++)
		if(~d[i])
			hash[tmp][i]+=BASE;
	int j = l,k = r;
	for(int i = l;i<= r;i++)
		if(vis[a[i]])b[j++]=a[i];
		else b[k--]=a[i];
	for(int i = l;i<= r;i++)a[i]=b[i];
	solve(l,j-1);
	solve(k+1,r);
}
int main()
{
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)a[i]=i;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y,1);
	}
	solve(1,n);
	int Ans = 0;
	for(int i = 1;i<= n;i++)
		for(int j = i+1;j<= n;j++)
			for(int k = 0;k<= 3;k++)if(hash[k][i]!=hash[k][j])
			{
				Ans+=k;
				break;
			}
	printf("%d\n",Ans);
	return 0;
}
