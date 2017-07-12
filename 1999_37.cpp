
#include <stdio.h>
#include <queue>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int M = 5e5+5;
struct E
{int next,to,val;}e[M<<1];
int head[M],tot;
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].val  = f;
	e[tot].next = head[x];
	head[x] = tot;
}
queue <int>Q;
int pre[M];
int path[M],cnt,v[M];
LL dis[M],dep[M],Mdep[M],lth[M];
int line[M],L,R;
int end,n,s;
void bfs(int s)
{
	Q.push(s);
	while(!Q.empty())
	{
		int x= Q.front();
		Q.pop();
		for(int i = head[x];i;i = e[i].next)
			if(!dis[e[i].to]&&e[i].to!=s)
			{
				dis[e[i].to] = dis[x]+e[i].val;
				if(dis[e[i].to]>dis[end])end = e[i].to;
				Q.push(e[i].to);
			}
	}
	int st = end;
	memset(dis,0,sizeof(dis));
	Q.push(st);
	while(!Q.empty())
	{
		int x= Q.front();
		Q.pop();
		for(int i = head[x];i;i = e[i].next)
			if(!dis[e[i].to]&&e[i].to!=st)
			{
				dis[e[i].to] = dis[x]+e[i].val;
				pre[e[i].to] = x;
				if(dis[e[i].to]>dis[end])end = e[i].to;
				Q.push(e[i].to);
			}
	}
	int x = end;
	while(x!=st)
	{
		path[++cnt] = x;
		lth[cnt] = dis[end]-dis[x];
		v[x] = true;
		x = pre[x];
	}
	path[++cnt] = x;
	v[x] = true;
	lth[cnt] = dis[end]-dis[x];
	return ;
}
void get_Maxdep(int st,int no)
{
	dep[st] = 0;
	Q.push(st);
	while(!Q.empty())
	{
		int x= Q.front();
		Q.pop();
		Mdep[no] = max(Mdep[no],dep[x]);
		for(int i = head[x];i;i = e[i].next)
			if(!v[e[i].to]&&!dep[e[i].to])
				dep[e[i].to] = dep[x]+e[i].val,Q.push(e[i].to);
	}
}
int main()
{
	int x,y,c;
	scanf("%d%d",&n,&s);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&c);
		add(x,y,c);
		add(y,x,c);
	}
	bfs(1);
	for(int i = 1;i<= cnt;i++)
		get_Maxdep(path[i],i);
	int j = 1;
	LL ans = 1e18+1;
	L = 0,R = -1;
	for(int i = 1;i<= cnt;i++)
	{
		while(L<=R&&lth[i]-lth[line[L]]>s)L++;
		while(i>=j&&lth[i]-lth[j]>s)j++;
		while(L<=R&&Mdep[i]>=Mdep[line[R]])R--;
		line[++R] = i;
		ans = min(ans,max(Mdep[line[L]],max(lth[j],lth[cnt]-lth[i])));
	}
	printf("%lld\n",ans);
	return 0;
}
