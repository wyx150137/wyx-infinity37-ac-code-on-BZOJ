
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
const int INF = 0x3f3f3f3f;
using namespace std;
const int N = 205;
struct pos{
	int x,y;
	pos(int a,int b){x = a;y = b;}
	pos(){}
};
int f[N][N],g[N][N],L,R;
char map[N][N];
pos line[N];
int n,m;
int dis(pos t,pos z)
{
	return abs(t.x-z.x)+abs(t.y-z.y);
}
int getans(pos t,int len)
{
	while(L<=R&&dis(t,line[L])>len)L++;
	if(L>R)return -INF;
	return f[line[L].x][line[L].y]+dis(t,line[L]);
}
void Insert(pos t)
{
	while(L<=R&&dis(t,line[R])<=f[t.x][t.y]-f[line[R].x][line[R].y])R--;
	line[++R] = t;
}
void go_up(int lth)
{
	for(int j = 1;j<= m;j++) 
	{
		L = 1,R = 0;
		for(int i = n;i;i--)
		{
			if(map[i][j]=='.')
			{
				pos tmp(i,j);
				g[i][j] = max(f[i][j],getans(tmp,lth));
				Insert(tmp);
			}else
			{L = 1,R = 0;}
		}
	}
	memcpy(f,g,sizeof(f));
}
void go_down(int lth)
{
	for(int j = 1;j<= m;j++)
	{
		L = 1,R = 0;
		for(int i = 1;i<= n;i++)
		{
			if(map[i][j]=='.')
			{
				pos tmp(i,j);
				g[i][j] = max(f[i][j],getans(tmp,lth));
				Insert(tmp);
			}else
			{L = 1,R = 0;}
		}
	}
	memcpy(f,g,sizeof(f));
}
void go_left(int lth)
{
	for(int i = 1;i<= n;i++)
	{
		L = 1,R = 0;
		for(int j = m;j;j--)
		{
			if(map[i][j]=='.')
			{
				pos tmp(i,j);
				g[i][j] = max(f[i][j],getans(tmp,lth));
				Insert(tmp);
			}else
			{L = 1,R = 0;}
		}
	}
	memcpy(f,g,sizeof(f));
}
void go_right(int lth)
{
	for(int i = 1;i<= n;i++)
	{
		L = 1,R = 0;
		for(int j = 1;j<=m;j++)
		{
			if(map[i][j]=='.')
			{
				pos tmp(i,j);
				g[i][j] = max(f[i][j],getans(tmp,lth));
				Insert(tmp);
			}else
			{L = 1,R = 0;}
		}
	}
	memcpy(f,g,sizeof(f));
}
int main()
{
	int sx,sy,t,x,y,z;
	scanf("%d%d%d%d%d",&n,&m,&sx,&sy,&t);
	for(int i = 1;i<= n;i++)
		scanf("%s",map[i]+1);
	memset(f,128,sizeof(f));
	memset(g,128,sizeof(g));
	f[sx][sy] = 0;
	for(int i = 1;i<= t;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if(z==1)go_up(y-x+1);
		else if(z==2)go_down(y-x+1);
		else if(z==3)go_left(y-x+1);
		else go_right(y-x+1);
	}
	int ans = 0;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			ans = max(ans,f[i][j]);
	printf("%d\n",ans);
	return 0;
}
