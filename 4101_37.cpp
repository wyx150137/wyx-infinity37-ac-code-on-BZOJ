
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
struct G
{int s,p;}g[N];
bool cmp(G a,G b)
{
	return a.p<b.p;
}
int n,b;
int find(int x)
{
	int l = 1,r = n+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(g[mid].p<x)l = mid+1;
		else r = mid;
	}
	return l;
}
int main()
{
	scanf("%d%d",&n,&b);
	for(int i = 1;i<= n;i++)
		scanf("%d%d",&g[i].s,&g[i].p);
	sort(g+1,g+n+1,cmp);
	int l = find(b)-1;
	int r = l+1;
	int ans = 0x3f3f3f3f;
	for(int i = l;i>=1;i--)
	{
		while(r<=n&&g[r].p-g[i].p<=g[i].s)
		{
			ans = min(ans,g[r].p-g[i].p-g[r].s);
			r++;
		}
	}
	r = l+1;
	for(int i = r;i<=n;i++)
	{
		while(l&&g[i].p-g[l].p<=g[i].s)
		{
			ans = min(ans,g[i].p-g[l].p-g[l].s);
			l--;
		}
	}
	if(ans!=0x3f3f3f3f)printf("%d\n",max(ans,0));
	else printf("-1\n");
	return 0;
}
