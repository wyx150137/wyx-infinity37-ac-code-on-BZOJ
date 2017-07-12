
#include <stdio.h>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 3e5+5;
const int M = 8e5+5;
struct E{int next,to,val;};
struct Edge{int x,y,f;}a[M];
ll dis[N];
bool vis[N];
queue<int>Q;
E e[M];
int head[N],tot,deg[N],n,m,id[N],cnt;
void add(int x,int y,int f=0)
{e[++tot].to=y;e[tot].next=head[x];e[tot].val=f;head[x]=tot;deg[y]++;}
void spfa(int s)
{
	memset(dis,0x3f,sizeof(dis));
	dis[s] = 0;vis[s] = true;
	Q.push(s);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		vis[x] = false;
		for(int i = head[x];i;i=e[i].next)
			if(dis[e[i].to]>dis[x]+e[i].val)
			{
				dis[e[i].to] = dis[x]+e[i].val;
				if(!vis[e[i].to])
				{
					vis[e[i].to]=true;
					Q.push(e[i].to);
				}
			}
	}
}
int dep[N],fa[N][18],size[N],sum[M];
void rebuild()
{
	memset(head,0,sizeof(head));
	memset(deg,0,sizeof(deg));
	tot = 0;cnt = n;
	for(int i = 1;i<= n;i++)size[i]=dis[i]<dis[0];
	for(int i = 1;i<= m;i++)
	{
		if(dis[a[i].x]+a[i].f==dis[a[i].y])
			id[++cnt]=i,add(a[i].x,cnt),add(cnt,a[i].y);
		if(dis[a[i].y]+a[i].f==dis[a[i].x])
			id[++cnt]=i,add(a[i].y,cnt),add(cnt,a[i].x);
	}
	for(int i = 1;i<= cnt;i++)
		if(!deg[i])
			add(cnt+1,i);
	cnt++;
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i = 17;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i = 17;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
vector<int>E[N];
void dfs(int x)
{
	for(int i = 0;i<E[x].size();i++)
	{
		dfs(E[x][i]);
		size[x]+=size[E[x][i]];
	}
	sum[id[x]]=size[x];
}
ll ans[N];
int main()
{
	int s;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].f);
		add(a[i].x,a[i].y,a[i].f),add(a[i].y,a[i].x,a[i].f);
	}
	scanf("%d",&s);
	spfa(s);
	rebuild();
	Q.push(cnt);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		if(fa[x][0])E[fa[x][0]].push_back(x);
		dep[x] = dep[fa[x][0]]+1;
		for(int i = 1;i<18;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
		for(int i = head[x];i;i=e[i].next)
		{
			if(!fa[e[i].to][0])fa[e[i].to][0]=x;
			else fa[e[i].to][0]=getlca(fa[e[i].to][0],x);
			if(!--deg[e[i].to])Q.push(e[i].to);
		}	
	}
	dfs(cnt);
	for(int i = 1;i<= m;i++)
		ans[a[i].x]+=sum[i],ans[a[i].y]+=sum[i];
	for(int i = 1;i<= n;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
