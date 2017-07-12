
#include <stdio.h>
#include <queue>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5010;
const int M = 1e6+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,f;}e[M];
int head[N],tot=1,n,m,T;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].f = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].f = 0;
}
queue<int>Q;
int d[N];
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
		if(d[e[i].to]==d[s]+1&&e[i].f)
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
vector<int>to[N],val[N];
int main()
{
	scanf("%d%d%d",&n,&m,&T);
	int x,y,z;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		to[x].push_back(y);
		val[x].push_back(z);
	}
	int st=0,ed=N-1,ans =0;
	add(st,1,T);
	for(int day = 1;;day++)
	{
		for(int i = 1;i<= n;i++)
			for(int j = 0;j<to[i].size();j++)
				add(n*(day-1)+i,n*day+to[i][j],val[i][j]);
		for(int i = 1;i<= n;i++)
			add(n*(day-1)+i,n*day+i,INF);
		add(n*day+n,ed,INF);
		if((ans+=dinic(st,ed))==T)
		{
			printf("%d\n",day);
			return 0;
		}
	}
	return 0;
}
