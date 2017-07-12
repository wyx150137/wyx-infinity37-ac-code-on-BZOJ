
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e6+5;
const int mod = 1e9;
int fa[N],g[N];
struct P
{int x,y,z;}p[N];
int getfa(int x)
{
	if(fa[x]==x)return x;
	int tmp = getfa(fa[x]);
	g[x]^=g[fa[x]];
	return fa[x] = tmp;
}
int n,m,q;
int calc()
{
	for(int i = 1;i<= n+m;i++)fa[i]=i,g[i]=0;
	fa[m+1] = 1;
	for(int i = 1;i<= q;i++)
	{
		int u= getfa(p[i].x),v = getfa(p[i].y+m);
		int tmp = g[p[i].x]^g[p[i].y+m]^p[i].z;
		if(u!=v){fa[u]=v,g[u]=tmp;}
		else if(tmp)return 0;
	}
	int ans = -1;
	for(int i=1;i<=m+n;i++)
		if(getfa(i)==i)
		{
			if(ans==-1)ans=1;
			else
			{
				ans = ans<<1;
				if(ans>=mod)
					ans-=mod;
			}
		}
	return ans;
}
int main()
{
	scanf("%d%d%d",&m,&n,&q);
	bool f[2] = {true,true};
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z);
		if(p[i].x==1&&p[i].y==1)
			{f[p[i].z] = false,i--,q--;continue;}
		if(!(p[i].x&1||p[i].y&1))p[i].z^=1;
	}
	int ans = 0;
	if(f[1])ans= calc();
	if(f[0])
	{
		for(int i = 1;i<= q;i++)
			if(p[i].x>1&&p[i].y>1)
				p[i].z^=1;
		ans+=calc();
	}
	if(ans>=mod)ans-=mod;
	printf("%d\n",ans);
	return 0;
}
