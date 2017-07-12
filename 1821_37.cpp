
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct E	
{
	int x,y;
	double val;
	bool operator < (const E &s) const
	{
		return val < s.val;
	}
}edge[2000005];
int tot,fa[1005];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])
		return fa[x] = x;
	else return fa[x] = getfa(fa[x]);
}
void uni(int x,int y)
{
	int fx = getfa(x),fy = getfa(y);
	if(fx!=fy)
		fa[fx] = fy;
}
int x[1005],y[1005];
int main()
{
	//freopen("group.in","r",stdin);
	//freopen("group.out","w",stdout);
	int n,k;
	scanf("%d%d",&n,&k);
	int cnt = 0;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
	}
	for(int i = 1;i<= n;i++)
	{
		for(int j = i+1;j<= n;j++)
		{
			edge[++tot].x = i;
			edge[tot].y = j;
			edge[tot].val = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
			edge[++tot].x = j;
			edge[tot].y = i;
			edge[tot].val = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
		}
	}
	double ans = 0;
	std::sort(edge+1,edge+tot+1);
	for(int i = 1;i<= tot;i++)
	{
		int fx = getfa(edge[i].x);
		int fy = getfa(edge[i].y);
		if(fx==fy)continue;
		if(cnt>=n-k)
		{
			ans = edge[i].val;
			break;
		}
		cnt++;
		uni(fx,fy);
	}
	printf("%.2lf",ans);
	return 0;
}
