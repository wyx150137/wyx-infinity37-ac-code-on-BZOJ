
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int INF=2e9;
const int MAXN=3005;
int i;
struct na
{
	int x,z;
	na(int _x,int _z):x(_x),z(_z){}
};
int n,m,x,y,z,a[21],k,p1,p2,en,t;
bool map[11][101];
int f[2][MAXN+1],ans=-INF,re[101][11];
int v[2][MAXN+1];
queue <na> q;
inline int gx(int x,int q1,int q2)
{
	k=0;
	for (register int i=m+1;i;i--) 
		k=k*3+(i==x?q1:(i==x+1?q2:a[i]));
	return k;
}
inline void up(int x,int z,int lj,int la)
{
	if (la) lj+=re[x/m+1][x%m+1];
	x++;
	k=x%2;
	if (v[k][z]!=x) v[k][z]=x,f[k][z]=-INF,q.push(na(x,z));
	if (f[k][z]<lj) f[k][z]=lj;
}
int main()
{
	int i,j,p;
	scanf("%d%d",&n,&m);
	memset(f,INF,sizeof(f));
	for (j=1;j<=n;j++)
	for (i=1;i<=m;i++)
	scanf("%d",&re[j][i]),map[i][j]=1;
	en=n*m-1;
	f[0][0]=0;
	v[0][0]=1;
	q.push(na(0,0));
	while(!q.empty())
	{
		p=0;
		na no=q.front();q.pop();
		int an=f[no.x%2][no.z];
		if(no.x%m==0) no.z*=3;
		x=no.x%m+1;y=no.x/m+1;
		for (i=1;i<=m+1;i++) a[i]=0;
		for (i=1,j=no.z;j;i++,j/=3)
		{
			a[i]=j%3;
			if (a[i]) p++;
		}
		if (a[x]==1&&a[x+1]==2)
		{
			if (ans<an+re[y][x]&&p==2) ans=an+re[y][x];
		}
		else if (a[x]==2&&a[x+1]==1) up(no.x,gx(x,0,0),an,1);
		else if (a[x]==0&&a[x+1]==0)
		{
			if (no.x!=en)
			{
				if (map[x][y+1]&&map[x+1][y]) up(no.x,gx(x,1,2),an,1);
				up(no.x,gx(x,0,0),an,0);
			}
		}
		else if (a[x]==0)
		{
			if (map[x+1][y]) up(no.x,gx(x,0,a[x+1]),an,1);
			if (map[x][y+1]) up(no.x,gx(x,a[x+1],0),an,1);
		}
		else if (a[x+1]==0)
		{
			if (map[x+1][y]) up(no.x,gx(x,0,a[x]),an,1);
			if (map[x][y+1]) up(no.x,gx(x,a[x],0),an,1);
		}
		else if (a[x]==a[x+1])
		{
			p1=p2=0;
			if (a[x]==1)
			for (j=0,i=x+2;i<=m+1;i++)
			{
				if (a[i]==1) j--;
				if (a[i]==2) j++;
				if (j>0&&!p1) p1=i,j--;
				if (j>0&&p1){p2=i;break;}
			}
			else
			for (j=0,i=x-1;i;i--)
			{
				if (a[i]==1) j++;
				if (a[i]==2) j--;
				if (j>0&&!p2) p2=i,j--;
				if (j>0&&p2){p1=i;break;}
			}
			a[p1]=1;a[p2]=2;up(no.x,gx(x,0,0),an,1);
		}
		//printf("%d\n",ans);
	}
	printf("%d\n",ans);
}
