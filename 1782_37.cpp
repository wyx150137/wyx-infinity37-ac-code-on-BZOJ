
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
struct E
{int next,to;}e[N<<1];
int head[N],tot,c[N],w[N],son[N],size[N],cnt,p[N],top[N],end[N];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
void update(int x,int y)
{
	for(int i = x;i<N;i+=i&(-i))
		c[i]+=y;
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=c[i];
	return ans;
}
void dfs1(int x,int fa)
{
	size[x]++;
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to!=fa)
		{
			dfs1(e[i].to,x);
			size[x]+=size[e[i].to];
			if(size[e[i].to]>size[son[x]])son[x] = e[i].to;
		}
	}
}
void dfs2(int x,int fa,int tp)
{
	top[x] = tp;
	w[x] = ++cnt;
	if(son[x])dfs2(son[x],x,tp);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa&&e[i].to!=son[x])
			dfs2(e[i].to,x,e[i].to);
	end[x] = cnt;
}
int main()
{
	int n,x,y;
	scanf("%d",&n);
	for(int i = 2;i<= n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	for(int i= 1;i<= n;i++)
	{
		scanf("%d",&p[i]);
		printf("%d\n",getans(w[p[i]]));
		update(w[p[i]],1);
		update(end[p[i]]+1,-1);
	}
	return 0;
}
