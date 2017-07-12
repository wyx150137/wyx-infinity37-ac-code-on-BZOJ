
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
const int MOD = 100007;
const int TOP = 100000;
struct Tree_s
{
	int c[TOP+5];
	void update(int x,int y)
	{
		for(int i = x;i<TOP;i+=i&(-i))
			(c[i] +=y)%=MOD;
	}
	int getans(int x)
	{
		int ans = 0;
		for(int i = x;i>0;i-=i&(-i))
			(ans+=c[i])%=MOD;
		return ans;
	}

}g[2][15],f[2][15];
int G[N][15],F[N][15];
struct P
{int x,y;}pos[N];
bool cmp(P a,P b)
{
	return a.x<b.x;
}
int main()
{	
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)
		scanf("%d%d",&pos[i].x,&pos[i].y);
	sort(pos+1,pos+n+1,cmp);
	for(int i = 1;i<= n;i++)
	{
		F[i][0] = 1;
		G[i][0] = 1;
		f[0][0].update(pos[i].y,F[i][0]),f[1][0].update(TOP-pos[i].y,F[i][0]);
		g[0][0].update(pos[i].y,G[i][0]),g[1][0].update(TOP-pos[i].y,G[i][0]);
		for(int j = 1;j<= k;j++)
		{
			F[i][j] = (F[i][j]+g[0][j-1].getans(pos[i].y-1)+f[0][j].getans(pos[i].y-1))%MOD;
			G[i][j] = (G[i][j]+g[1][j].getans(TOP-pos[i].y-1)+f[1][j-1].getans(TOP-pos[i].y-1))%MOD;
			f[0][j].update(pos[i].y,F[i][j]),f[1][j].update(TOP-pos[i].y,F[i][j]);
			g[0][j].update(pos[i].y,G[i][j]),g[1][j].update(TOP-pos[i].y,G[i][j]);
		}
	}
	int ans = 0;
	for(int i = 1;i<= n;i++)
		ans = (ans+F[i][k]+G[i][k])%MOD;
	printf("%d\n",ans);
	return 0;
}
