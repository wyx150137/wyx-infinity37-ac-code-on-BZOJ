
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1e9+7;
const int N = 105;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y){e[++tot].to=y;e[tot].next=head[x];head[x]=tot;}
int c[N][N],f[N][N],g[N][N],size[N],tmp[N],n;
char s[N];
void dfs(int x)
{
	if((x<<1)<=n)add(x,x<<1);
	if((x<<1|1)<=n)add(x,x<<1|1);
	g[x][1] = f[x][1] = size[x] = 1;
	for(int t = head[x];t;t=e[t].next)
	{
		int to = e[t].to;
		dfs(to);
		for(int j = 1;j<= size[to]+size[x];j++)
			tmp[j] = 0;
		for(int i = 1;i<= size[x];i++)
			for(int j = 0;j<= size[to];j++)
				if(s[to]=='>')
					(tmp[i+j]+=(ll)f[x][i]*g[to][j]%mod*c[i+j-1][i-1]%mod
							  *c[size[x]-i+size[to]-j][size[x]-i]%mod)%=mod;
				else
					(tmp[i+j]+=(ll)f[x][i]*(g[to][size[to]]-g[to][j]+mod)%mod
							  *c[i+j-1][i-1]%mod
							  *c[size[x]-i+size[to]-j][size[x]-i]%mod)%=mod;
		for (int i=1; i<=size[x]+size[to]; i++)
            f[x][i] = tmp[i]%mod, g[x][i] = (g[x][i-1]+f[x][i])%mod;
        size[x] += size[to];
	}
}
int main()
{
	scanf("%d",&n);
	scanf("%s",s+2);
	c[0][0] = 1;
	for(int i = 1;i< N;i++)
	{
		c[i][0] = 1;
		for(int j = 1;j<N;j++)
			c[i][j] = (c[i-1][j-1]+c[i-1][j])%mod;
	}
	dfs(1);
	printf("%d\n",g[1][size[1]]);
	return 0;
}
