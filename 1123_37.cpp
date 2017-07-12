
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
const int M = 1000005;
typedef long long LL;
struct E
{int next,to;}e[M];
int head[N],tot=1;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int dfn[N],low[N],top,cnt,size[N],n,m;
bool v[N];
LL ans[N];
void tarjan(int x,int l)
{
	v[x] = true;
	dfn[x] = low[x] = ++cnt;
	int tmp = 0;
	size[x] = 1;
	for(int i = head[x];i;i = e[i].next)
	{
		if(i==(l^1))continue;
		if(!v[e[i].to])
		{
			tarjan(e[i].to,i);
			low[x] = min(low[x],low[e[i].to]);
			size[x]+=size[e[i].to];
			if(low[e[i].to]>=dfn[x])
			{
				ans[x]+=(LL)tmp*size[e[i].to];
				tmp+=size[e[i].to];
			}
		}else low[x] = min(low[x],dfn[e[i].to]);
	}
	ans[x]+=(LL)tmp*(n-tmp-1);
}
int main()
{
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	tarjan(1,0);
	for(int i = 1;i<= n;i++)
		printf("%lld\n",(ans[i]+n-1)<<1);
	return 0;
}
