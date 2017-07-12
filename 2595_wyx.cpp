
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 12;
const int Maxn = 1030;
using namespace std;
const int inf = 0x3f3f3f3f;

int n,m;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct Lux
{
	int s,t,d;
	Lux () {}
	Lux (int _s,int _t,int _d=0)
	:s(_s),t(_t),d(_d){}
}pre[N][N][Maxn];

const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,1,-1};

queue <Lux> q;
int F[N][N][Maxn];
int a[N][N];
bool in[N][N];

void spfa(int sta)
{
	while(!q.empty())
	{
		Lux tt = q.front(); 
		q.pop();in[tt.s][tt.t] = false;
		for(int i=0;i<4;++i)
		{
			int nowx = tt.s + dx[i],nowy = tt.t + dy[i];
			if(F[nowx][nowy][sta] > F[tt.s][tt.t][sta] + a[nowx][nowy])
			{
				F[nowx][nowy][sta] = F[tt.s][tt.t][sta] + a[nowx][nowy];
				pre[nowx][nowy][sta] = Lux(tt.s,tt.t,sta);
				if(!in[nowx][nowy])
				{
					in[nowx][nowy] = 1;
					q.push(Lux(nowx,nowy));
				}
			}
		}
	}
}

bool vis[N][N];

void find(int x,int y,int sta)
{
	if(x >= inf || pre[x][y][sta].d == 0) return;
	vis[x][y] = 1;
	Lux t = pre[x][y][sta];
	find(t.s,t.t,t.d);
	if(t.s == x && t.t == y) find(x,y,sta-t.d);
}

int main()
{
	n = read(), m = read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) a[i][j] = read();
	int cnt = 0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) if(!a[i][j]) cnt ++;

	int Max = (1<<cnt) - 1;

	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) 
			for(int k=0;k<=Max;++k)
				F[i][j][k] = pre[i][j][k].s = inf;

	cnt = 0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(!a[i][j])
			{
				F[i][j][1<<cnt] = 0;
				cnt ++;
			}

	for(int sta=1;sta<=Max;++sta)
	{
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
			{
				for(int s=sta&(sta-1);s;s=sta&(s-1))
				{
					int tmp = F[i][j][s] + F[i][j][sta-s] - a[i][j];
					if(tmp < F[i][j][sta])
					{
						F[i][j][sta] = tmp;
						pre[i][j][sta] = Lux(i,j,s);
					}
				}
				if(F[i][j][sta] < inf)
					q.push(Lux(i,j)),in[i][j] = 1;
			}
		spfa(sta);
	}

	int x,y;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(!a[i][j])
				{x = i, y = j;break;}
	find(x,y,Max);

	cout << F[x][y][Max] << endl;

	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			if(!a[i][j])printf("x");
			else if(vis[i][j]) printf("o");
			else printf("_");
		}
		puts("");
	}
}
