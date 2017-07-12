
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
int fa[N<<1];
int idx[N<<1],cnt;
int getfa(int x)
{
	if(fa[x]==x)return x;
	else return fa[x]=getfa(fa[x]);
}
void uni(int x,int y)
{
	x = getfa(x),y = getfa(y);
	if(x==y)return ;
	fa[x] = y;
}
void init()
{
	for(int i = 1;i<= cnt;i++)fa[i]=i;
}
struct seg
{
	int x,y,o;
}a[N];
int find(int x)
{
	int l = 1,r = cnt+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(idx[mid]<=x)l=mid+1;
		else r = mid;
	}
	return l-1;
}
int main()
{
	int cas;
	int n;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%d",&n);
		cnt = 0;
		for(int i = 1;i<= n;i++)
		{
			scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].o);
			idx[++cnt]=a[i].x,idx[++cnt]=a[i].y;
		}
		sort(idx+1,idx+cnt+1);
		int tmp = cnt;cnt = 0;
		for(int i = 1;i<= tmp;i++)
			if(i==1||idx[i]!=idx[i-1])
				idx[++cnt] = idx[i];
		init();
		for(int i = 1;i<= n;i++)
			if(a[i].o)uni(find(a[i].x),find(a[i].y));
		bool flag = true;
		for(int i = 1;i<= n&&flag;i++)
			if(a[i].o==0)
			{
				if(getfa(find(a[i].x))==getfa(find(a[i].y)))
					flag = false;
			}
		if(flag)puts("YES");
		else puts("NO");
	}
	return 0;
}
