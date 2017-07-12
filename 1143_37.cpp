
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 205;
const int M = 1e4+5;
const int INF = 0x3f3f3f3f;
int a[105][105],lk[105],n,m,u,v;
bool map[105][105],vis[105];
bool find(int x)
{
	for(int i = 1;i<= n;i++)
		if(a[x][i]&&!vis[i])
		{
			vis[i] = true;
			if(find(lk[i])||!lk[i])
			{
				lk[i] = x;
				return true;
			}
		}
	return false;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&u,&v);
		map[u][v] = true;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				map[i][j]|=(map[i][k]&map[k][j]);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			if(i!=j&&map[i][j])
				a[i][j] = true;
	int ans = n;
	for(int i = 1;i<= n;i++)
	{
		memset(vis,0,sizeof(vis));
		ans-=find(i);
	}
	printf("%d\n",ans);
	return 0;
}
