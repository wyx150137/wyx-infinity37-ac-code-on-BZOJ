
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2005;
const int M = 4e6+5;
struct E
{int x,y,val;}e[M];
bool cmp(const E &a,const E &b)
{
	return a.val<b.val;
}
int fa[N];
int getfa(int x)
{
	if(fa[x]==x)return x;
	else return fa[x] = getfa(fa[x]);
}
void uni(int x,int y)
{
	x = getfa(x),y = getfa(y);
	if(x==y)return ;
	fa[x] = y;
}
int main()
{
	int n;
	scanf("%d",&n);
	int x,tot = 0;
	for(int i = 1;i<= n;i++)
		for(int j = i;j<= n;j++)
		{
			scanf("%d",&x);
			e[++tot].x = i-1,e[tot].y = j,e[tot].val = x;
		}
	for(int i = 0;i<=n;i++)fa[i] = i;
	sort(e+1,e+tot+1,cmp);
	long long ans = 0;
	for(int i = 1;i<= tot;i++)
	{
		int tx = e[i].x,ty = e[i].y;
		tx = getfa(tx),ty = getfa(ty);
		if(tx==ty)continue;
		ans+=e[i].val;
		uni(tx,ty);
	}
	printf("%lld\n",ans);
	return 0;
}
