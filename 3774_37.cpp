
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e4+4;
const int M = 1e6+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,f;}e[M];
int head[N],tot=1;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x]=tot;e[tot].f = f;
	e[++tot].to = x;e[tot].next = head[y];head[y]=tot;e[tot].f = 0;
}
queue <int>Q;
int d[N];
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
			if(e[i^1].f&&d[e[i].to]==-1)
			{
				d[e[i].to] = d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[s]!=-1;
}
int get_mxf(int s,int t,int mx)
{
	if(s==t)return mx;
	int last = mx;
	for(int i = head[s];i;i=e[i].next)
		if(d[e[i].to]==d[s]-1&&e[i].f)
		{
			int tof = get_mxf(e[i].to,t,min(e[i].f,last));
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
	{
		ans+=get_mxf(s,t,INF);
	}
	return ans;
}
int n,m;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
inline int id1(int i,int j)
{
	return i*m+j-m;
}
inline int id2(int i,int j)
{
	return i*m+j-m+n*m;
}
int main()
{
	int ans = 0;
	scanf("%d%d",&n,&m);
	int x;
	int S = 0, T = 2*n*m+1;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
		{
			scanf("%d",&x);
			if((i+j)&1)
				add(S,id1(i,j),x);
			else 
				add(id1(i,j),T,x);
		}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
		{
			scanf("%d",&x);
			ans+=2*x;
			if((i+j)&1)
				add(S,id2(i,j),x),add(id1(i,j),T,x);
			else 
				add(id2(i,j),T,x),add(S,id1(i,j),x);
		}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			if((i+j)&1)
			{
				add(id2(i,j),id1(i,j),INF);
				for(int d = 0;d<4;d++)
				{
					int xx = i+dx[d],yy = j+dy[d];
					if(xx<=0||yy<=0||xx>n||yy>m)continue;
					add(id2(i,j),id1(xx,yy),INF);
				}
			}else
			{
				add(id1(i,j),id2(i,j),INF);
				for(int d = 0;d<4;d++)
				{
					int xx = i+dx[d],yy = j+dy[d];
					if(xx<=0||yy<=0||xx>n||yy>m)continue;
					add(id1(xx,yy),id2(i,j),INF);
				}
			}
	ans-=dinic(S,T);
	printf("%d\n",ans);
	return 0;
}
