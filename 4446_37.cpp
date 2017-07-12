
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2e5+5;
ll f[N][20],g[N][20],A[N],B[N],dep[N],dis[N];
int ls[N],rs[N],fa[N];
void dp(int x)
{
	if(!ls[x]&&!rs[x])
	{
		for(int y = 2;y<=dep[x];y++)
		{
			int lca = x>>(dep[x]-y+1),z = x>>(dep[x]-y)^1;
			f[x][y]=(dis[x]+dis[z]-2*dis[lca])*A[z];
		}
	}else if(ls[x]&&!rs[x])
	{
		dp(ls[x]);
		for(int y = 2;y<= dep[x];y++)
			f[x][y]=A[ls[x]]*B[ls[x]]+f[ls[x]][y];
	}else
	{
		dp(ls[x]),dp(rs[x]);
		for(int y = 2;y<= dep[x];y++)
			f[x][y]=min(A[ls[x]]*B[ls[x]]+f[ls[x]][dep[x]+1]+f[rs[x]][y],
						A[rs[x]]*B[rs[x]]+f[rs[x]][dep[x]+1]+f[ls[x]][y]);
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<=n;i++)
		scanf("%lld",&A[i]);
	dep[1]=1;
	for(int i = 2;i<= n;i++)
	{
		scanf("%lld",&B[i]);
		fa[i]=i>>1;
		dep[i]=dep[fa[i]]+1;
		dis[i]=dis[fa[i]]+B[i];
		if(ls[fa[i]])rs[fa[i]]=i;
		else ls[fa[i]]=i;
	}
	dp(1);
	for(int x = n;x>=1;x--)
		for(int y = 0;y<=dep[x];y++)
		{
			if(!rs[x])
			{
				if(!ls[x])
				{
					if(!y)g[x][y]=0;
					else
					{
						int z=x>>(dep[x]-y);
						g[x][y]=(dis[x]-dis[z])*A[z];
					}
				}else
					g[x][y]=A[ls[x]]*B[ls[x]]+g[ls[x]][y];
			}else
			{
				g[x][y]=min(A[ls[x]]*B[ls[x]]+f[ls[x]][dep[x]+1]+g[rs[x]][y],
							A[rs[x]]*B[rs[x]]+f[rs[x]][dep[x]+1]+g[ls[x]][y]);
			}
		}
	ll ans = g[1][0];
	for(int i = 2;i<= n;i++)
	{
		int x = i;ll sum = g[x][dep[x]-1];
		while(x!=1)
		{
			if((x^1)>n)
				sum+=A[x>>2]*B[x>>1];
			else 
				sum+=A[x^1]*B[x^1]+g[x^1][dep[x>>1]-1];
			x=x>>1;
		}
		ans = min(ans,sum);
	}
	printf("%lld\n",ans);
	return 0;
}
