
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
struct E
{int next,to,val;};
int pos[N],n,q;
namespace Tree
{
	E e[N<<1];
	int head[N],tot,dis[N],dep[N],fa[N],lg2[N<<1];
	int a[N<<1][20],cnt;
	void add(int x,int y,int f)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x]=tot;e[tot].val = f;
		e[++tot].to = x;e[tot].next = head[y];head[y]=tot;e[tot].val = f;
	}
	void dfs(int x)
	{
		static int T=0;
		dep[x] = dep[fa[x]]+1;
		a[pos[x] = ++T][0] = dis[x];
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=fa[x])
			{
				fa[e[i].to] = x;
				dis[e[i].to] = dis[x]+e[i].val;
				dfs(e[i].to);
				a[++T][0] = dis[x];
			}
	}
	void init()
	{
		for(int i = 2;i<(N<<1);i++)
			lg2[i] = lg2[i>>1]+1;
		for(int j = 1;j<= 19;j++)
			for(int i = 1;i+(1<<(j-1))<=(n<<1);i++)
				a[i][j] = min(a[i][j-1],a[i+(1<<(j-1))][j-1]);
	}
	int getlca(int x,int y)
	{
		int l = pos[x],r = pos[y];
		if(l>r)swap(l,r);
		int lth = lg2[r-l+1];
		return min(a[l][lth],a[r-(1<<lth)+1][lth]);
	}
	int getdis(int x,int y)
	{
		return dis[x]+dis[y]-2*getlca(x,y);
	}
};
namespace New_Tree
{
	E e[N<<1];
	int head[N],tot,fa[N];
	ll dis_sum1[N],dis_sum2[N],sum1[N],sum2[N],ROOT;
	void add(int x,int y,int z)
	{
		e[++tot].to = y;
		e[tot].val = z;
		e[tot].next = head[x];
		head[x] =tot;
	}
	int root,sum,f[N],size[N];
	bool used[N];
	void get_root(int x,int pre)
	{
		size[x] = 1;
		f[x] =0;
		for(int i = Tree::head[x];i;i=Tree::e[i].next)
			if(Tree::e[i].to!=pre&&!used[Tree::e[i].to])
			{
				get_root(Tree::e[i].to,x);
				size[x]+=size[Tree::e[i].to];
				f[x] = max(f[x],size[Tree::e[i].to]);
			}
		f[x] = max(f[x],sum-size[x]);
		if(f[x]<f[root])root = x;
	}
	void work(int x)
	{
		used[x] = true;
		for(int i = Tree::head[x];i;i=Tree::e[i].next)
		{
			int to = Tree::e[i].to;
			if(used[to])continue;
			sum = size[to],root = 0;
			get_root(to,0);
			fa[root] = x;
			add(x,root,to);
			work(root);
		}
	}
	void update(int x,int y)
	{
		sum1[x]+=y;
		for(int i = x;fa[i];i=fa[i])
		{
			int dis = Tree::getdis(x,fa[i]);
			dis_sum1[fa[i]]+=(ll)dis*y;
			dis_sum2[i]+=(ll)dis*y;
			sum1[fa[i]]+=y;
			sum2[i]+=y;
		}
		return ;
	}
	ll calc(int x)
	{
		ll ans = dis_sum1[x];
		for(int i = x;fa[i];i=fa[i])
		{
			int dis = Tree::getdis(x,fa[i]);
			ans+=dis_sum1[fa[i]]-dis_sum2[i];
			ans+=(sum1[fa[i]]-sum2[i])*dis;
		}
		return ans;
	}
	ll getans(int x)
	{
		ll cst = calc(x);
		for(int i = head[x];i;i=e[i].next)
		{
			ll tmp = calc(e[i].val);
			if(tmp<cst)
				return getans(e[i].to);
		}
		return cst;
	}
};
int main()
{
	int x,y,c;
	scanf("%d%d",&n,&q);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&c);
		Tree::add(x,y,c);
	}
	Tree::dfs(1);
	Tree::init();
	New_Tree::f[0] = New_Tree::sum = n;
	New_Tree::root = 0;
	New_Tree::get_root(1,0);
	New_Tree::ROOT = New_Tree::root;
	New_Tree::work(New_Tree::root);
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d",&x,&y);
		New_Tree::update(x,y);
		ll ans = New_Tree::getans(New_Tree::ROOT);
		printf("%lld\n",ans);
	}
	return 0;
}
