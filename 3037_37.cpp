
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
const int INF = 0x3f3f3f3f;
struct E
{
	int next,to;
}e[N<<1];
int head[N],tot,a[N],edge;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
bool v[N];
int p;
void dfs(int x)
{
	v[x] = true;
	if(v[a[x]]){p = x;return ;}
	dfs(a[x]);
}
int g[N],f[N];
void dp(int x,int fa)
{
	f[x] = 1,g[x] = INF,v[x] = true;
	if(x==edge)g[x]= 0;
	for(int i = head[x];i;i= e[i].next)
	{
		if(e[i].to!=fa&&e[i].to!=p)
		{
			dp(e[i].to,x);
			g[x] += min(g[e[i].to],f[e[i].to]);
			g[x] = min(g[x],f[x]+f[e[i].to]-1);
			f[x] += min(g[e[i].to],f[e[i].to]); 
		}
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		add(a[i],i);
	}
	int ans = 0;
	for(int i = 1;i<= n;i++)
	{
		if(v[i])continue;
		dfs(i);
		edge = a[p];
		dp(p,0);int tmp = f[p];
		edge = 0;
		dp(p,0);
		ans+=min(tmp,g[p]);
	}
	printf("%d\n",n-ans);
	return 0;
}
