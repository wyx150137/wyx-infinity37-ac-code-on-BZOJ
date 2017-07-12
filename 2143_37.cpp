
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define fir first
#define sec second
#define mp make_pair
#define N 160
#define inf 1000000000

const int dx[4]={-1,1,0,0};
const int dy[4]={0,0,-1,1};
int m,n,len;
int stix1,stix2,stix3,stiy1,stiy2,stiy3,t1,t2,t3;
int a[N][N],b[N][N],dis[N][N][N<<1];
bool vis[N][N][N<<1];
struct node{ int x,y,z,d; };
priority_queue<node> q;
bool operator <(const node &u,const node &v){ return u.d>v.d; }
void solve(int sx,int sy)
{
	while (!q.empty()) q.pop();
	for (int i=1; i<=m; i++)
		for (int j=1; j<=n; j++)
			for (int k=0; k<=len; k++)
			{
				vis[i][j][k]=0; 
				dis[i][j][k]=inf;
			}
	dis[sx][sy][0]=0;
	node u,v; u.x=sx; u.y=sy; u.z=u.d=0; 
	q.push(u);
	while (!q.empty() && !(vis[stix1][stiy1][0] && vis[stix2][stiy2][0] && vis[stix3][stiy3][0]))
	{
		u=q.top(); q.pop();
		if (vis[u.x][u.y][u.z]) continue; vis[u.x][u.y][u.z]=1;
		if (u.z)
		{
			for (int k=0; k<4; k++)
			{
				int i=u.x+dx[k];int j=u.y+dy[k];
				if (i>0 && i<=m && j>0 && j<=n && u.d<dis[i][j][u.z-1])
				{
					dis[i][j][u.z-1]=v.d=u.d;
					v.x=i; v.y=j; v.z=u.z-1; q.push(v);
				}
			}
			v=u; v.z--;
			if (v.d<dis[v.x][v.y][v.z]){ dis[v.x][v.y][v.z]=v.d; q.push(v); }
		} else 
		{
			v=u; v.z=a[v.x][v.y]; v.d+=b[v.x][v.y];
			if (v.d<dis[v.x][v.y][v.z])
			{
				dis[v.x][v.y][v.z]=v.d; q.push(v);
			}
		}
	}
}
int main()
{
	scanf("%d%d",&m,&n);
	for (int i=1; i<=m; i++)
		for (int j=1; j<=n; j++)
		{
			scanf("%d",&a[i][j]); 
			a[i][j]=min(a[i][j],max(i-1,m-i)+max(j-1,n-j)+1);
			len=max(len,a[i][j]);
		}
	for (int i=1; i<=m; i++)
		for (int j=1; j<=n; j++) 
			scanf("%d",&b[i][j]);
	scanf("%d%d%d%d%d%d",&stix1,&stiy1,&stix2,&stiy2,&stix3,&stiy3);
	solve(stix1,stiy1); 
	t2+=dis[stix2][stiy2][0]; t3+=dis[stix3][stiy3][0];
	solve(stix2,stiy2); 
	t1+=dis[stix1][stiy1][0]; t3+=dis[stix3][stiy3][0];
	solve(stix3,stiy3); 
	t1+=dis[stix1][stiy1][0]; t2+=dis[stix2][stiy2][0];
	int ans=min(min(t1,t2),t3);
	if (ans<inf)
	{
		puts((ans==t1)?"X":(ans==t2)?"Y":"Z");
		printf("%d\n",ans);
	} else puts("NO");
	return 0;
}

