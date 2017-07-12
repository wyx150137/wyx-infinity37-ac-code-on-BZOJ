
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 3e6+5;
const int INF = 0x3f3f3f3f;
int p[45],P,m,n,from[N];
int t[45][105];
struct E
{int next,to,c,f,from;}e[M];
int head[N],tot=1,st,end;
void add(int x,int y,int f,int c)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;e[tot].f=f;e[tot].c=c;
	e[++tot].to=x;e[tot].next=head[y];head[y]=tot;e[tot].f=0;e[tot].c=-c;
	e[tot-1].from=x;e[tot].from=y;
}
int dis[N];bool v[N];
queue<int>Q;
bool spfa()
{
	memset(dis,0x3f,sizeof(dis));
	Q.push(st);
	dis[st]=0,v[st]=true;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		v[x]=false;
		for(int i = head[x];i;i=e[i].next)
			if(dis[e[i].to]>dis[x]+e[i].c&&e[i].f)
			{
				dis[e[i].to]=dis[x]+e[i].c;
				from[e[i].to] = i;
				if(!v[e[i].to])
				{
					Q.push(e[i].to);
					v[e[i].to] = true;
				}
			}
	}
	return dis[end]!=INF;
}
int ans;
void mcf()
{
	int x = INF,a,b,y;
	for(int i = from[end];i;i=from[e[i].from])
	{
		x = min(x,e[i].f);
		if(e[i].from==0)
		{
			y = e[i].to;
			a = (y-1)/P+1;b = y%P+1;
		}
	}
	for(int i = from[end];i;i=from[e[i].from])
	{
		e[i].f-=x;e[i^1].f+=x;ans+=e[i].c*x;
	}
	for(int i = 1;i<= m;i++)
		add((a-1)*P+b,n*P+i,1,b*t[i][a]);
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&p[i]);
		P+=p[i];
	}
	for(int i = 1;i<= m;i++)
		for(int j = 1;j<= n;j++)
			scanf("%d",&t[i][j]);
	st = 0,end = n*P+m+1;
	for(int i = 1;i<= n*P;i++)
		add(st,i,1,0);
	for(int i = 1;i<= m;i++)
		add(n*P+i,end,p[i],0);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			add((i-1)*P+1,n*P+j,1,t[j][i]);
	while(spfa())mcf();
	printf("%d\n",ans);
	return 0;
}
