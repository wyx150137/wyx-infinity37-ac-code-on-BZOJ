
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int M = 2e6+5;
const int N = 1e6+5;
int fa[N],rnk[N];
int a[M],b[M];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return x;
	else return fa[x] = getfa(fa[x]);
}
void uni(int x,int y)
{
	x = getfa(x),y = getfa(y);
	if(x==y)return ;
	if(rnk[x]>rnk[y])
		fa[y] = x;
	else
	{
		fa[x] = y;
		rnk[y]+=rnk[x]==rnk[y];
	}
}
int main()
{
	int n,m,k,x,y,cnt = 0;
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		if(x<=k||y<=k)
		{
			a[++cnt] = x;
			b[cnt] = y;
		}else uni(x,y);
	}
	int ans = 0;
	for(int i = 1;i<= cnt;i++)
	{
		int fx = getfa(a[i]),fy = getfa(b[i]);
		if(fx==fy)ans++;
		else uni(a[i],b[i]);
	}
	printf("%d\n",ans);
	return 0;
}
