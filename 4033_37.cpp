
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2005;
typedef long long LL;
struct E
{int next,to,val;}e[N<<1];
int head[N],tot,n,K;
LL f[N][N];
int size[N];
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val  = f;
	head[x] = tot;
}
void dp(int x,int fa,int val)
{
	size[x]++;
	f[x][0] = f[x][1] = 0;
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to==fa)continue;
		dp(e[i].to,x,e[i].val);
		size[x]+=size[e[i].to];
		for(int j = min(size[x],K);j>= 0;j--)
			for(int k = 0;k<= j&&k<=size[e[i].to];k++)
				if(j-k>=0&&f[x][j-k]!=-1)f[x][j] = max(f[x][j],f[x][j-k]+f[e[i].to][k]);
	}
	for(int bn = 0;bn<= K&&bn<=size[x];bn++)
	{
		if(f[x][bn]==-1)f[x][bn] = 0;
		f[x][bn] = f[x][bn]+(LL)val*(LL)bn*(K-bn)+(LL)val*(LL)(size[x]-bn)*(n-K-size[x]+bn);
	}
}
int main()
{
	int x,y,c;
	scanf("%d%d",&n,&K);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&c);
		add(x,y,c),add(y,x,c);
	}
	memset(f,-1,sizeof(f));
	dp(1,0,0);
	printf("%lld\n",f[1][K]);
	return 0;
}
