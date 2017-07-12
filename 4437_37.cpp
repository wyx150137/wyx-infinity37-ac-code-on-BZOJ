
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int M=2000000;
const int P=(1<<24)-1;
char map[105][105];
struct E
{int x,y,next;}e[M+5];
int head[P+1],tot,n,m;
void add(int x,int y)
{
	int p = ++tot;
	e[p].x = x;
	e[p].y = y;
	e[p].next = head[((x<<9)^y)&P];
	head[((x<<9)^y)&P] = p;
}
bool ask(int x,int y)
{
	for(int i = head[((x<<9)^y)&P];i;i=e[i].next)
		if(x==e[i].x&&y==e[i].y)
			return true;
	return false;
}
int _dx[]={0,0,1,-1};
int _dy[]={1,-1,0,0};
int l,r,Qx[M],Qy[M];
const int lim = 10000;
int cnt;
void bfs()
{
	l=r=-1;Qx[++r]=0,Qy[r]=0;
	add(0,0);
	int x,y,sx,sy;
	while(l<r&&cnt<lim)
	{
		x = Qx[++l],y = Qy[l];
		for(int d = 0;d<4;d++)
		{
			sx = x+_dx[d],sy = y+_dy[d];
			if(!ask(sx,sy)&&map[(sx%n+n)%n][(sy%m+m)%m]=='.')
			{
				Qx[++r] = sx,Qy[r] = sy;
				add(sx,sy);
				if(sx%n==0&&sy%m==0)cnt++;
				if(r==M-1)return ;
			}
		}
	}
}
inline ll Abs(ll x){return x>0?x:-x;}
int flag;
ll dx,dy;
void getans(int x,int y)
{
	if(cnt<lim&&r<M-1){printf("%s\n",ask(x,y)?"yes":"no");return ;}
	if(flag){printf("%s\n",ask((x%n+n)%n,(y%m+m)%m)?"yes":"no");return ;}
	int L = -1e9,R = 1e9;
	while(L+5<R)
	{
		int m1 = (L+L+R)/3,m2 = (L+R+R)/3;
		ll f1 = Abs(dx*m1+x)+Abs(dy*m1+y);
		ll f2 = Abs(dx*m2+x)+Abs(dy*m2+y);
		if(f1<f2)R = m2;
		else L = m1;
	}
	int k = L;
	for(int i = L;i<= R;i++)
		if(Abs(dx*k+x)+Abs(dy*k+y)>=Abs(dx*i+x)+Abs(dy*i+y))
		{
			if (ask(x+dx*i,y+dy*i)) return void(printf("yes\n"));
			k=i;
		}
	printf("no\n");
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 0;i< n;i++)
		scanf("%s",map[i]);
	bfs();
	if(cnt>=lim||r==M-1)
	{
		if(ask(n,0)&&ask(0,m))
			flag = 1;
		else
		{
			dx = 1ll<<40,dy = 1ll<<40;
			for (int i=1;i<=r;i++)
				if (Qx[i]%n==0 && Qy[i]%m==0)
					if (Qx[i]+Qy[i]<dx+dy)
						dx=Qx[i],dy=Qy[i];
		}
	}
	int Q,x,y;
	scanf("%d",&Q);
	while(Q--)
	{
		scanf("%d%d",&x,&y);
		getans(x,y);
	}
	return 0;
}
