
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int K = 1e6+5;
const int N = 2e5+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,val;}e[N<<1];
int head[N],tot,t[K];
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];e[tot].val = f;head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];e[tot].val = f;head[y] = tot;
}
bool used[N];
int sum,root,size[N],f[N],n,k;
void get_root(int x,int fa)
{
	size[x] = 1;f[x] = 0;
	for(int i = head[x];i;i =e[i].next)
	{
		if(e[i].to==fa||used[e[i].to])continue;
		get_root(e[i].to,x);
		size[x]+=size[e[i].to];
		f[x] = max(f[x],size[e[i].to]);
	}
	f[x] = max(f[x],sum-size[x]);
	if(f[x]<f[root])root = x;
}
int dis[N],dep[N];
int ans = INF;
void get_ans(int x,int fa)
{
	if(dis[x]<=k)ans = min(ans,dep[x]+t[k-dis[x]]);
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to==fa||used[e[i].to])continue;
		dep[e[i].to] = dep[x]+1;
		dis[e[i].to] = dis[x]+e[i].val;
		get_ans(e[i].to,x);
	}
}
void init(int x,int fa,int opt)
{
	if(dis[x]<=k)
	{
		if(opt)t[dis[x]] = min(t[dis[x]],dep[x]);
		else t[dis[x]] = INF;
	}
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa&&!used[e[i].to])
			init(e[i].to,x,opt);
}
void work(int x)
{
	used[x] = true,t[0] = 0;
	for(int i = head[x];i;i = e[i].next)
		if(!used[e[i].to])
		{
			dep[e[i].to] = 1,dis[e[i].to] = e[i].val;
			get_ans(e[i].to,0);
			init(e[i].to,0,1);
		}
	for(int i = head[x];i;i = e[i].next)
		if(!used[e[i].to])
			init(e[i].to,0,0);
	for(int i = head[x];i;i = e[i].next)
		if(!used[e[i].to])
		{
			root = 0,sum = size[e[i].to];
			get_root(e[i].to,0);
			work(root);
		}
}
int main()
{
	int x,y,z;
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= k;i++)t[i]=n;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		x++,y++;
		add(x,y,z);
	}
	ans = sum = f[0] = n;
	get_root(1,0);
	work(root);
	if(ans<n)printf("%d\n",ans);
	else printf("-1\n");
	return 0;
}
