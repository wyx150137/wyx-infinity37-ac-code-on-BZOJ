
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e6+5;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int fa[N],a[N],st[N],top;
LL f[N],g[N];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x] = x;
	return fa[x] = getfa(fa[x]);
}
void dfs(int x,int fa,int ban)
{
	for(int i = head[x];i;i = e[i].next)
		if(fa!=e[i].to)
			dfs(e[i].to,x,ban);
	f[x]= a[x],g[x] = 0;
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to==fa)continue;
		if(e[i].to==ban)
			f[x]+=g[e[i].to],g[x]+=g[e[i].to];
		else 
		{
			f[x]+=g[e[i].to];
			g[x]+=max(g[e[i].to],f[e[i].to]);
		}
	}
}
int main()
{
	int n,x;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&a[i],&x);
		int fx = getfa(x),fy = getfa(i);
		if(fx==fy){st[++top] = x,st[++top] = i;continue;}
		fa[fx]= fy;
		add(x,i),add(i,x);
	}
	LL t_ans = 0;
	LL ans = 0;
	for(int i = 1;i<= top;i=i+2)
	{
		ans = 0;
		dfs(st[i],0,st[i+1]);
		ans = max(ans,max(f[st[i]],g[st[i]]));
		dfs(st[i+1],0,st[i]);
		ans = max(ans,max(f[st[i+1]],g[st[i+1]]));
		t_ans+=ans;
	}
	printf("%lld\n",t_ans);
	return 0;
}
