
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 200005;
int fa[N];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x] = x;
	return fa[x] = getfa(fa[x]);
}
void uni(int x,int y)
{
	int fx = getfa(x),fy = getfa(y);
	if(fx!=fy)
		fa[fx] = fy;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int x,y;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		uni(x,y);
	}
	bool flag = true;
	for(int i = 1;i<= n;i++)
		if(fa[i]==0)
			flag = false;
	if(flag)printf("TAK\n");
	else printf("NIE\n");
	return 0;
}
