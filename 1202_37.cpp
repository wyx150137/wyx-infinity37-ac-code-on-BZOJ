
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int fa[105];
int pos[105];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x] = x;
	else
	{
		int tmp = getfa(fa[x]);
		pos[x] = pos[fa[x]]+pos[x];
		return fa[x] = tmp;
	}
}
void work()
{
	memset(fa,0,sizeof(fa));
	memset(pos,0,sizeof(pos));
	int n,m,x,y,c;
	scanf("%d%d",&n,&m);
	int flag = true;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x,&y,&c);
		int fx = getfa(x),fy = getfa(y+1);
		if(fx==fy)
		{
			if(pos[y+1]-pos[x]!=c)flag = false;
		}
		else
		{
			fa[fy] = x;
			pos[fy] = c-pos[y+1];
		}
	}
	if(flag)printf("true\n");
	else printf("false\n");
	return ;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
		work();
	return 0;
}
