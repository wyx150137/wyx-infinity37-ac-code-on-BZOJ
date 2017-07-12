
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e6+1000;
const int INF = 0x3f3f3f3f;
struct E
{int next,to;};
int dep[N],fa[N][22],dfn[N],Dfn;
struct Gragh
{
	E e[N<<1];
	int head[N],tot;
	void add(int x,int y)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
		e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
	}
	void dfs(int x,int ff)
	{
		dep[x] = dep[ff]+1;
		fa[x][0]=ff;
		dfn[x] =++Dfn;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=ff)
				dfs(e[i].to,x);
	}
	void init(int n)
	{
		for(int j = 1;j<= 21;j++)
			for(int i = 1;i<= n;i++)
				fa[i][j] = fa[fa[i][j-1]][j-1];
	}
	int lca(int x,int y)
	{
		if(dep[x]<dep[y])swap(x,y);
		for(int i = 21;i>=0;i--)
			if(dep[fa[x][i]]>=dep[y])
				x = fa[x][i];
		if(x==y)return x;
		for(int i = 21;i>=0;i--)
			if(fa[x][i]!=fa[y][i])
				x = fa[x][i],y = fa[y][i];
		return fa[x][0];
	}
}tree;
vector<int>to[N];
vector<int>val[N];
void add(int x,int y,int f)
{
	if(x==y)return ;
	to[x].push_back(y);
	to[y].push_back(x);
	val[x].push_back(f);
	val[y].push_back(f);
}
int size[N];
bool v[N];
ll ans1,ans2,ans3;
void Tree_DP(int x,int from)
{
	static long long f[N],g[N],max_dis[N],min_dis[N];
	//f[x]表示以x为根的子树中有多少关键点
	//g[x]表示以x为根的子树中所有关键点到x的距离之和
	//max_dis[x]/min_dis[x]表示节点x为根的子树中的关键点到x的距离的最大/最小值
	int i;
	f[x]=v[x];g[x]=0;
	max_dis[x]=(v[x]?0:-INF);
	min_dis[x]=(v[x]?0:INF);
	int sz = to[x].size();
	for(i=0;i<sz;i++)
	{
		int t = to[x][i];
		if(t==from)
			continue;
		Tree_DP(t,x);
		int dis=val[x][i];
		ans1+=(g[x]+f[x]*dis)*f[t]+g[t]*f[x];
		ans2=min(ans2,min_dis[x]+min_dis[t]+dis);
		ans3=max(ans3,max_dis[x]+max_dis[t]+dis);
		f[x]+=f[t];
		g[x]+=g[t]+f[t]*dis;
		max_dis[x]=max(max_dis[x],max_dis[t]+dis);
		min_dis[x]=min(min_dis[x],min_dis[t]+dis);
	}
	v[x] = false,to[x].clear(),val[x].clear();
}
/*void dfs(int x,int ff,int dis)
{
	size[x] = v[x];
	if(v[x]&&dis)ans2 = min(ans2,dis),dis = 0;
	int sz = to[x].size();
	for(int i = 0;i<sz;i++)
	{
		int t = to[x][i];
		if(t!=ff)
		{
			dfs(t,x,dis+val[x][i]);
			size[x]+=size[t];
			ans1+=(ll)(tn-size[t])*size[t]*val[x][i];
		}
	}
	v[x] = false;
	to[x].clear(),val[x].clear();
}
int end,maxdis;
void get_rope(int x,int dis,int ff)
{
	if(dis&&dis>maxdis&&v[x])
	{
		maxdis = dis;
		end = x;
	}
	int sz = to[x].size();
	for(int i = 0;i<sz;i++)
	{
		int t = to[x][i];
		if(t!=ff)
			get_rope(t,dis+val[x][i],x);
	}
}*/
bool cmp(int a,int b)
{
	return dfn[a]<dfn[b];
}
int h[N],stk[N],top;
int main()
{
	int n,q,x,y;
	scanf("%d",&n);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		tree.add(x,y);
	}
	tree.dfs(1,0);
	tree.init(n);
	scanf("%d",&q);
	while(q--)
	{
		int k;
		scanf("%d",&k);
		for(int i = 1;i<= k;i++)
			scanf("%d",&h[i]),v[h[i]]=true;
		sort(h+1,h+k+1,cmp);
		top = 0;
		stk[++top]=h[1];
		for(int i = 2;i<= k;i++)
		{
			int u = h[i];
			int lca = tree.lca(u,stk[top]);
			while(true)
			{
				if(dep[lca]>=dep[stk[top-1]])
				{
					int len = dep[stk[top]]-dep[lca];
					add(lca,stk[top--],len);
					break;
				}
				add(stk[top-1],stk[top],dep[stk[top]]-dep[stk[top-1]]);
				top--;
			}
			if(stk[top]!=lca)stk[++top]=lca;
			if(stk[top]!=u)stk[++top]=u;
		}
		for(int i = 1;i<top;i++)
			add(stk[i],stk[i+1],dep[stk[i+1]]-dep[stk[i]]);
		ans1 = 0,ans2 = INF,ans3 = -INF;
		Tree_DP(h[1],-1);
		printf("%lld %lld %lld\n",ans1,ans2,ans3);
	}
	return 0;
}
