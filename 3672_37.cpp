
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
typedef long long ll;
struct E
{int next,to;ll val;}e[N<<1];
int head[N],tot,fa[N];
ll dis[N];
void add(int x,int y,ll f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].val = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].val = f;
}
void dfs(int x)
{
	for(int i = head[x];i;i=e[i].next)if(e[i].to!=fa[x])
	{
		fa[e[i].to] = x;
		dis[e[i].to] = dis[x]+e[i].val;
		dfs(e[i].to);
	}
}
ll p[N],q[N],l[N];
int f[N],size[N],sum,root;
bool used[N];
void get_root(int x,int pre)
{
	f[x] = 0,size[x] = 1;
	for(int i = head[x];i;i=e[i].next)if(e[i].to!=pre&&!used[e[i].to])
	{
		get_root(e[i].to,x);
		size[x]+=size[e[i].to];
		f[x] = max(f[x],size[e[i].to]);
	}
	f[x] = max(f[x],sum-size[x]);
	if(f[x]<f[root])root = x;
}
int seq[N];
inline bool cmp(int x,int y){return dis[x]-l[x]>dis[y]-l[y];}
void Dfs(int x,int pre)
{
	seq[++tot] = x;
	for(int i = head[x];i;i=e[i].next)if(e[i].to!=pre&&!used[e[i].to])
		Dfs(e[i].to,x);
}
ll dp[N];
inline double slope(int x,int y)
{
	return (double)(dp[x]-dp[y])/(double)(dis[x]-dis[y]);
}
int stack[N],top;
double k[N];
void Insert(int x)
{
	while(top>1&&slope(x,stack[top])>slope(stack[top],stack[top-1]))
		top--;
	stack[++top] = x;
	k[top] = -slope(x,stack[top-1]);
}
void solve(int x)
{
	if(sum<=1)return ;
	root = 0;
	get_root(x,0);
	int now = root;
	for(int i = head[fa[now]];i;i=e[i].next)
		if(e[i].to==now&&!used[e[i].to])
		{
			used[now] = true;
			sum = size[x]-size[now];
			solve(x);
			break;
		}
	for(int i = fa[now];i!=fa[x];i=fa[i])
		if(dis[now]-dis[i]<=l[now])
			dp[now]=min(dp[now],dp[i]+(dis[now]-dis[i])*p[now]+q[now]);
	tot = 0;
	for(int i = head[now];i;i=e[i].next)
		if(e[i].to!=fa[now]&&!used[e[i].to])
			Dfs(e[i].to,now);
	sort(seq+1,seq+tot+1,cmp);
	top = 0;
	for(int i = 1,j = now;i<= tot;i++)
	{
		for(;j!=fa[x]&&dis[j]>=dis[seq[i]]-l[seq[i]];j=fa[j])
			Insert(j);
		if(top==1)
		{	
			if(dis[seq[i]]-dis[stack[top]]<=l[seq[i]])
				dp[seq[i]] = min(dp[seq[i]],dp[stack[top]]+
								(dis[seq[i]]-dis[stack[top]])*p[seq[i]]+q[seq[i]]);
		}else
		{
			int ot=min(top,upper_bound(k+2,k+top+1,-p[seq[i]])-k-1);
			if(dis[seq[i]]-dis[stack[ot]]<=l[seq[i]])
			dp[seq[i]] = min(dp[seq[i]],dp[stack[ot]]+
							(dis[seq[i]]-dis[stack[ot]])*p[seq[i]]+q[seq[i]]);
		}
	}
	for(int i = head[now];i;i=e[i].next)
		if(e[i].to!=fa[now]&&!used[e[i].to])
		{
			used[e[i].to] = true;
			sum = size[e[i].to];
			solve(e[i].to);
		}
}
int main()
{
	int n,t,a;ll b;
	scanf("%d%d",&n,&t);
	for(int i = 2;i<= n;i++)
	{
		scanf("%d%lld",&a,&b);
		add(i,a,b);
		scanf("%lld%lld%lld",&p[i],&q[i],&l[i]);
	}
	dfs(1);
	for(int i = 2;i<= n;i++)dp[i]=1ll<<60;
	sum = f[root=0] = n;
	used[1] = true;
	solve(1);
	for(int i = 2;i<= n;i++)printf("%lld\n",dp[i]);
	return 0; 
}
