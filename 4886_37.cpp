
#include <stdio.h>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 250005;
int cnt,mx;
int a[N],b[N],g[N<<1],idx[N<<1],fa[N<<1],mxv[N<<1];
bool d[N<<1];
map<int,int>h;
int getfa(int x)
{
	if(fa[x]==x)return x;
	else return fa[x]=getfa(fa[x]);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		idx[++cnt]=a[i],idx[++cnt]=b[i];
	}
	sort(idx+1,idx+cnt+1);
	for(int i = 1;i<= cnt;i++)
		if(i==1||idx[i]!=idx[i-1])
			g[h[idx[i]]=++mx] = idx[i];
	long long ans = 0;
	for(int i = 1;i<= mx;i++)
	{
		fa[i] = i;mxv[i] = g[i];
		ans-=g[i];
	}
	for(int i = 1;i<= n;i++)
	{
		ans+=a[i]+b[i];
		int fx = getfa(h[a[i]]),fy = getfa(h[b[i]]);
		if(fx!=fy)
		{
			d[fx]|=d[fy];
			mxv[fx] = max(mxv[fx],mxv[fy]);
			fa[fy] = fx;
		}else
			d[fx] = true;
	}
	for(int i = 1;i<= mx;i++)
		if(getfa(i)==i&& !d[i])ans+=mxv[i];
	printf("%lld\n",ans);
	return 0;
}
