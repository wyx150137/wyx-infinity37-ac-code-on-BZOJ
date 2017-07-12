
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 11;
const int S = 1<<10;
const int INF = 0x3f3f3f3f;
#define f(i,j,s1,s2) f[i][j][s1]+f[i][j][s2]
int f[N][N][S],a[N][N],n,m,K;;
struct Pair{int x,y;};
struct Tele{int x,y,s;};
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
Tele pre[N][N][S];
queue <Pair>Q;
bool v[N][N];
void spfa(int sta)
{
	while(!Q.empty())
	{
		Pair t = Q.front();
		Q.pop();
		v[t.x][t.y] = false;
		for(int i = 0;i<4;i++)
		{
			int xx = t.x+dx[i],yy = t.y+dy[i];
			if(xx<0||yy<0||xx>n||yy>m)continue;
			if(f[xx][yy][sta]>f[t.x][t.y][sta]+a[xx][yy])
			{
				f[xx][yy][sta] = f[t.x][t.y][sta]+a[xx][yy];
				pre[xx][yy][sta] = (Tele){t.x,t.y,sta};
				if(!v[xx][yy])
				{
					Q.push((Pair){xx,yy});
					v[xx][yy] = true;
				}	
			}
		}
	}
}
bool used[N][N];
void dfs(int x,int y,int sta)
{
	if(x>=INF||pre[x][y][sta].s==0)return ;
	used[x][y] = true;
	Tele t = pre[x][y][sta];
	dfs(t.x,t.y,t.s);
	if(t.x==x&&t.y==y)dfs(x,y,sta-t.s);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
		{
			scanf("%d",&a[i][j]);
			if(!a[i][j])K++;
		}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			for(int s = 0;s<1<<K;s++)
				f[i][j][s] = pre[i][j][s].x = INF;
	K = 0;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			if(!a[i][j])
				{f[i][j][1<<K] = 0;K++;}
	for(int sta = 0;sta<1<<K;sta++)
	{
		for(int i = 1;i<= n;i++)
			for(int j = 1;j<= m;j++)
			{
				for(int s = sta&(sta-1);s;s = sta&(s-1))
					if(f(i,j,s,sta-s)-a[i][j]<f[i][j][sta])
					{
						f[i][j][sta] = f(i,j,s,sta-s)-a[i][j];
						pre[i][j][sta] = (Tele){i,j,s};
					}
				if(f[i][j][sta]<INF)
					{Q.push((Pair){i,j});v[i][j] = true;}
			}
		spfa(sta);
	}
	int x,y;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			if(!a[i][j])
				{x = i,y = j;break;}
	dfs(x,y,(1<<K)-1);
	printf("%d\n",f[x][y][(1<<K)-1]);
	for(int i = 1;i<= n;i++)
	{
		for(int j = 1;j<= m;j++)
		{
			if(!a[i][j])printf("x");
			else if(used[i][j])printf("o");
			else printf("_");
		}
		printf("\n");
	}
	return 0;
}
