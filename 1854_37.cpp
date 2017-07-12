
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 10005;
int fa[N];
int vis[N];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x] = x;
	else return fa[x] = getfa(fa[x]);
}
int main()
{
	int n,x,y;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&x,&y);
		int fx = getfa(x),fy = getfa(y);
		if(fx==fy)
			vis[fx] = true;
		else
		{
			if(fx>fy){vis[fy] = true;fa[fy] = fx;}
			else {vis[fx] = true;fa[fx] = fy;}
		}
	}
	for(int i = 1;i<= N+1;i++)
		if(!vis[i])
			{printf("%d\n",i-1);break;}
	return 0;
}
