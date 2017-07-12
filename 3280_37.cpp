
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2005;
const int M = 1e7+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,fr,f,c;}e[M];
int head[N],tot = 1,from[N];
void add(int x,int y,int f,int c)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;e[tot].f=f,e[tot].c=c;
	e[++tot].to=x;e[tot].next=head[y];head[y]=tot;e[tot].f=0,e[tot].c=-c;
	e[tot-1].fr=x,e[tot].fr=y;
}
bool v[N];
int dis[N],S,T;
queue<int>Q;
bool spfa()
{
	for(int i = S;i<= T;i++)
		dis[i] = INF;
	Q.push(S);
	v[S] = true;dis[S] = 0;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		v[x] = false;
		for(int i = head[x];i;i=e[i].next)
			if(dis[x]+e[i].c<dis[e[i].to]&&e[i].f)
			{
				dis[e[i].to] = dis[x]+e[i].c;
				from[e[i].to] = i;
				if(!v[e[i].to])
				{
					Q.push(e[i].to);
					v[e[i].to] = true;
				}
			}
	}
	return dis[T]!=INF;
}
int ans =0,maxf;
void mcf()
{
	int x = INF;
	for(int i = from[T];i;i=from[e[i].fr])
		x = min(x,e[i].f);
	maxf+=x;
	for(int i = from[T];i;i=from[e[i].fr])
		e[i].f-=x,e[i^1].f+=x,ans+=e[i].c*x;
}
void init()
{
	memset(head,0,sizeof(head));
	memset(from,0,sizeof(from));
	tot = 1;
	ans=0,maxf=0;
}
int a[N],l[N],p[N],d[N],q[N];
void work()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	int sum = 0;
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]),sum+=a[i];
	for(int i = 1;i<= m;i++)
		scanf("%d%d",&l[i],&p[i]);
	for(int i = 1;i<= k;i++)
		scanf("%d%d",&d[i],&q[i]);
	S = 0,T = 2*n+m+1;
	for(int i = 1;i<= m;i++)
		add(S,i,l[i],0);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			add(j,m+n+i,INF,p[j]);
	for(int i = 1;i<= n;i++)
	{
		add(m+n+i,T,a[i],0);
		if(i<n)add(m+n+i,m+n+i+1,INF,0);
	}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= k;j++)
		{
			int to = i+d[j]+1;
			if(to<=n)add(m+i,m+n+to,INF,q[j]);
		}
	for(int i = 1;i<= n;i++)
		add(S,m+i,a[i],0);
	while(spfa())mcf();
	if(maxf==sum)printf("%d\n",ans);
	else printf("impossible\n");
}
int main()
{
	int cas;
	scanf("%d",&cas);
	for(int i = 1;i<= cas;i++)
	{
		printf("Case %d: ",i);
		init();
		work();
	}
	return 0;
}
