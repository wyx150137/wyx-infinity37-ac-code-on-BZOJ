
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const int M = 5e4+5;
const int INF = 0x3f3f3f3f;
struct E
{int nxt,to,fr,f,c;}e[M];
int head[N],tot=1,from[N];
void add(int x,int y,int f,int c)
{
	e[++tot].to=y;e[tot].nxt=head[x];head[x]=tot;
	e[tot].f=f,e[tot].c=c,e[tot].fr=x;
	e[++tot].to=x;e[tot].nxt=head[y];head[y]=tot;
	e[tot].f=0,e[tot].c=-c,e[tot].fr=y;
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
		for(int i = head[x];i;i=e[i].nxt)
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
int ans =0,mxf;
void mcf()
{
	int x = INF;
	for(int i = from[T];i;i=from[e[i].fr])
		x = min(x,e[i].f);
	mxf+=x;
	for(int i = from[T];i;i=from[e[i].fr])
		e[i].f-=x,e[i^1].f+=x,ans+=e[i].c*x;
}
int a[M],b[M],C[M],W[M];
int main()
{
	//freopen("x.in","r",stdin);
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i= 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&a[i],&b[i],&C[i],&W[i]);
		add(a[i],b[i],C[i],0);
	}
	S = 1,T = n;
	while(spfa())mcf();
	printf("%d",mxf);
	add(0,1,k,0);
	S = 0;
	memset(from,0,sizeof(from));
	ans = mxf = 0;
	for(int i = 1;i<= m;i++)
		add(a[i],b[i],INF,W[i]);
	while(spfa())mcf();
	printf(" %d\n",ans);
	return 0;
}
