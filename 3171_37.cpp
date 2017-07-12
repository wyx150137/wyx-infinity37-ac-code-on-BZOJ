
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 505;
const int M = 1e6+5;
const int INF = 0x3f3f3f3f;
struct E
{int nxt,to,fr,f,c;}e[M];
int head[N],tot=1;
void add(int x,int y,int f,int c)
{
	e[++tot].to=y;e[tot].nxt=head[x];head[x]=tot;
	e[tot].f=f,e[tot].c=c;e[tot].fr=x;
	e[++tot].to=x;e[tot].nxt=head[y];head[y]=tot;
	e[tot].f=0,e[tot].c=-c;e[tot].fr=y;
}
int from[N],dis[N],S,T;
bool v[N];
queue<int>Q;
bool spfa()
{
	for(int i = S;i<= T;i++)
		dis[i] = INF;
	dis[S] = 0,v[S] = true;
	Q.push(S);
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
int ans,mxf;
void mcf()
{
	int x = INF;
	for(int i = from[T];i;i=from[e[i].fr])
		x = min(x,e[i].f);
	mxf+=x;
	for(int i = from[T];i;i=from[e[i].fr])
		e[i].f-=x,e[i^1].f+=x,ans+=e[i].c*x;
}
int id[20][20][2];
int map[20][20];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int main()
{
	int cnt = 0;
	int l,r;
	char s[20];
	scanf("%d%d",&l,&r);
	for(int i = 1;i<= l;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<= r;j++)
		{
			if(s[j]=='U')map[i][j]=0;
			else if(s[j]=='D')map[i][j]=1;
			else if(s[j]=='L')map[i][j]=2;
			else map[i][j]=3;
		}
	}
	for(int i = 1;i<= l;i++)
		for(int j = 1;j<= r;j++)
			for(int k = 0;k<2;k++)
				id[i][j][k]=++cnt;
	S = 0,T =cnt+1;
	for(int i = 1;i<= l;i++)
		for(int j = 1;j<= r;j++)
			for(int d = 0;d<4;d++)
			{
				int nx = i+dx[d],ny = j+dy[d];
				if(nx<1)nx=l;if(ny<1)ny=r;
				if(nx>l)nx=1;if(ny>r)ny=1;
				if(map[i][j]==d)add(id[i][j][0],id[nx][ny][1],1,0);
				else add(id[i][j][0],id[nx][ny][1],1,1);
			}
	for(int i = 1;i<= l;i++)
		for(int j = 1;j<= r;j++)
			add(S,id[i][j][0],1,0),add(id[i][j][1],T,1,0);
	while(spfa())mcf();
	printf("%d\n",ans);
	return 0;
}
