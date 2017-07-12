
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2005;
const int M = 1e5+5;
const int INF = 0x3f3f3f3f;
struct F
{int next,to,f,c,from;}e[M];
int head[N],tot=1;
void add(int x,int y,int f,int c)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;
	e[tot].f=f;e[tot].c=c;e[tot].from=x;
	e[++tot].to=x;e[tot].next=head[y];head[y]=tot;
	e[tot].f=0;e[tot].c=-c;e[tot].from=y;
}
queue<int>Q;
int dis[N],from[N];bool v[N];
 bool spfa(int s,int t)
{
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	v[s]=true;
	Q.push(s);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		v[x]=false;
		for(int i = head[x];i;i=e[i].next)
			if(dis[x]+e[i].c<dis[e[i].to]&&e[i].f)
			{
				dis[e[i].to]=dis[x]+e[i].c;
				from[e[i].to]=i;
				if(!v[e[i].to])
				{
					Q.push(e[i].to);
					v[e[i].to]=true;
				}
			}
	}
	return dis[t]!=INF;
}
int ans,st,end;
void mcf()
{
	int x = INF;
	for(int i = from[end];i;i=from[e[i].from])
		x = min(x,e[i].f);
	for(int i = from[end];i;i=from[e[i].from])
		e[i].f-=x,e[i^1].f+=x,ans+=e[i].c*x;
}
int a[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	st = 0,end = 2*n+1;
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)
	{
		add(st,i,1,0);
		add(i+n,end,1,0);
		add(0,i+n,1,a[i]);
	}
	int x,y,z;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if(x>y)swap(x,y);
		add(x,y+n,1,z);
	}
	while(spfa(st,end))mcf();
	printf("%d\n",ans);
	return 0;
}
