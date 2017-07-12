
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1e9+7;
const int N = 405;
struct E
{int next,to;}e[N];
int head[N],tot,deg[N];
void add(int x,int y)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;
	deg[y]++;
}
int fa[N],f[N][N],g[N],size[N],c[N][N];
bool vis[N];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x]=x;
	else return fa[x]=getfa(fa[x]);
}
bool dfs(int x,int pre)
{
	vis[x] = true;
	bool flag = false;
	for(int i = head[x];i;i=e[i].next)if(e[i].to!=pre)
	{
		if(vis[e[i].to])return false;
		if(!dfs(e[i].to,x))return false;
		if(flag)
		{
			memset(g,0,sizeof(g));
			for(int j = 1;j<= size[x];j++)
				for(int k = 1;k<= size[e[i].to];k++)
					if(f[x][j]&&f[e[i].to][k])
					for(int I = max(j,k);I<=j+k;I++)
						(g[I]+=(ll)f[x][j]*f[e[i].to][k]%mod*c[j][j+k-I]%mod*c[I][j]%mod)%=mod;
			size[x]+=size[e[i].to];
			for(int I = 1;I<= size[x];I++)
				f[x][I] = g[I];
		}else
		{
			size[x]= size[e[i].to];
			flag = true;
			for(int I = 1;I<= size[x];I++)
				f[x][I] = f[e[i].to][I];
		}	
	}
	if(x)
	{
		size[x]++;
		if(flag)for(int i = size[x];i;i--)f[x][i] = f[x][i-1];
		else f[x][1] = 1;
	}
	return true;
}
void uni(int x,int y)
{
	x = getfa(x),y =getfa(y);
	if(x==y)return ;
	fa[x] = y;
}
int X[N],Y[N];
int main()
{
	int n,m,x,y;
	char opt[3];
	scanf("%d%d",&n,&m);
	c[0][0]=1;
	for(int i = 1;i<= 400;i++)
	{
		c[i][0] = 1;
		for(int j = 1;j<= 400;j++)
			c[i][j] = (c[i-1][j-1]+c[i-1][j])%mod;
	}
	int cnt = 0;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%s%d",&x,opt,&y);
		if(opt[0]=='=')
			uni(x,y);
		else
			X[++cnt] =x,Y[cnt] = y;
	}
	for(int i = 1;i<= cnt;i++)
	{
		x = getfa(X[i]),y = getfa(Y[i]);
		if(x==y){printf("0\n");return 0;}
		add(x,y);
	}
	for(int i=1;i<=n;i++)if(!deg[getfa(i)])add(0,getfa(i));
	if(!dfs(0,-1))return printf("0\n"),0;
	for(int i = 1;i<= n;i++)
		if(fa[i]==i&&!vis[i])return printf("0\n"),0;
	int ans = 0;
	for(int i = 1;i<= size[0];i++)ans=(ans+f[0][i])%mod;
	printf("%d\n",ans);
	return 0;
}
