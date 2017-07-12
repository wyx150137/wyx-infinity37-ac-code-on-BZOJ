
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
int fa[N],h[N],v[N],dep[N],cnt;
int getfa(int x)
{
	if(fa[x] == x) return  x;
	else return getfa(fa[x]);
}
void pre(int x)
{
	if(fa[x]==x)return ;
	pre(fa[x]);
	dep[x] = dep[fa[x]]+1;
}
int Ask(int x,int y)
{
	pre(x),pre(y);
	if(dep[x]<dep[y])swap(x,y);
	int re = 0;
	while(dep[x]>dep[y]&&x!=y)
	{
		re = max(re,v[x]);
		x = fa[x];
	}
	while(x!=y)
	{
		re = max(re,max(v[x],v[y]));
		x = fa[x],y = fa[y];
	}
	return re;
}
int main()
{
	int n,m,lastans = 0;
	int opt,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)fa[i]=i;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&opt,&x,&y);
		x^=lastans,y^=lastans;
		int fx = getfa(x),fy = getfa(y);
		if(opt==0)
		{
			cnt++;
			if(fx!=fy)
			{
				if(h[fx]<=h[fy])
				{
					fa[fx] = fy;v[fx] = cnt;
					h[fy]+=(h[fx]==h[fy]);
				}else
				{
					fa[fy] = fx;v[fy] = cnt;
				}
			}
		}else
		{
			if(fx!=fy)printf("%d\n",lastans = 0);
			else printf("%d\n",lastans=Ask(x,y));
		}
	}
}
