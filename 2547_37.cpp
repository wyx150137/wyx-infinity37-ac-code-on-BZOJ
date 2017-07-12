
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define vx v.x
#define ux u.x
#define vy v.y
#define uy u.y
const int N = 115;
const int INF = 0x3f3f3f3f;
int h[N][N],dis[N][N],n,m,par[N],tot,mp[N][N],cnt,pt;
struct P
{
	int x,y;
	P(int x=0,int y=0):x(x),y(y){}
}a[N],b[N];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
bool vis[N][N],bo[N];
queue<P>Q;
void spfa(int sx,int sy,int p)
{
	memset(dis,0x3f,sizeof(dis));
	dis[sx][sy]=0;
	vis[sx][sy]=true;
	Q.push(P(sx,sy));
	P u,v;
	int t;
	while(!Q.empty())
	{
		u = Q.front();
		Q.pop();
		vis[ux][uy]=false;
		for(int i = 0;i<4;i++)
		{
			vx = ux+dx[i],vy=uy+dy[i];
			if(vx<=0||vy<=0||vx>n||vy>m)continue;
			if(p^(dis[ux][uy]&1))
				{if(h[vx][vy]<=h[ux][uy])t=0;else t=1;}
			else
				{if(h[vx][vy]>=h[ux][uy])t=0;else t=1;}
			if(dis[ux][uy]+t<dis[vx][vy])
			{
				dis[vx][vy]=dis[ux][uy]+t;
				if(!vis[vx][vy])
				{
					Q.push(P(vx,vy));
					vis[vx][vy]=true;
				}
			}
		}
	}
}
bool get_partner(int x,int lim)
{
	for(int i = 1;i<= tot;i++)
		if(bo[i]&&mp[x][i]<=lim)
		{
			bo[i]=false;
			if(!par[i]||get_partner(par[i],lim))
			{
				par[i]=x;
				return true;
			}
		}
	return false;
}
bool check(int x)
{
	int tmp = 0;
	memset(par,0,sizeof(par));
	for(int i= 1;i<= cnt<<1;i++)
	{
		memset(bo,1,sizeof(bo));
		if(get_partner(i,x))tmp++;
	}
	return tmp+x>=(cnt<<1);
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&cnt,&pt);
	int x,y,t;
	for(int i = 1;i<=(cnt<<1|1);i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	for(int i = 1;i<=pt;i++)
	{
		scanf("%d%d%d",&x,&y,&t);
		while(t--)
			b[++tot].x=x,b[tot].y=y;
	}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			scanf("%d",&h[i][j]);
	for(int i = 1;i<= cnt<<1;i++)
	{
		if(i<=cnt)spfa(a[i].x,a[i].y,0);
		else spfa(a[i].x,a[i].y,1);
		for(int j = 1;j<= tot;j++)mp[i][j]=dis[b[j].x][b[j].y];
	}
	int l = 0,r = cnt*2;
	while(l<r)
	{
		int mid =(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}
