
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
const int M = 4e6+5;
struct E
{int next,to;}e[N<<1];
int head[N],tot,n,m;
struct Ask
{int x,y;}ask[N];
bool cmp(Ask a,Ask b)
{
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}
ll gcd(ll x,ll y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x]=tot;
	e[++tot].to = x;e[tot].next = head[y];head[y]=tot;
}
int fa[N][18],root[N];
int ls[M],rs[M],sum[M];
int in[N],end[N],ind,dep[N],cnt;
int getans(int x,int y,int u,int v,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)
		return sum[x]+sum[y]-sum[u]-sum[v];
	int mid = (l+r)>>1;
	int ans = 0;
	if(a<=mid)ans+=getans(ls[x],ls[y],ls[u],ls[v],l,mid,a,b);
	if(b>mid) ans+=getans(rs[x],rs[y],rs[u],rs[v],mid+1,r,a,b);
	return ans;
}
void update(int &p,int pre,int l,int r,int pos,int val)
{
	p = ++cnt;
	if(l==r)
	{
		sum[p] = sum[pre]+val;
		return ;
	}
	int mid = (l+r)>>1;
	ls[p] = ls[pre],rs[p] = rs[pre];
	if(pos<=mid)
		update(ls[p],ls[pre],l,mid,pos,val);
	else update(rs[p],rs[pre],mid+1,r,pos,val);
	sum[p] = sum[ls[p]]+sum[rs[p]];
}
void dfs(int x)
{
	in[x] = ++ind;
	dep[x] = dep[fa[x][0]]+1;
	for(int j = 1;j<= 17;j++)
		fa[x][j] = fa[fa[x][j-1]][j-1];
	for(int i = head[x];i;i=e[i].next)
	{
		if(e[i].to==fa[x][0])continue;
		fa[e[i].to][0] = x;
		dfs(e[i].to);
	}
	end[x] = ++ind;
}
vector<int>a[N];
void dfs2(int x)
{
	root[x] = root[fa[x][0]];
	for(int i = 0;i<a[x].size();i++)
	{
		update(root[x],root[x],1,ind,in[a[x][i]],1);
		update(root[x],root[x],1,ind,end[a[x][i]],-1);
	}
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x][0])
			dfs2(e[i].to);
}
ll ans = 0;
int getlca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i = 17;i>= 0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x = fa[x][i];
	if(x==y)return x;
	for(int i = 17;i>= 0;i--)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
void solve()
{
	for(int i = 1;i<= m;i++)
	{
		int x=ask[i].x,y = ask[i].y;int u = getlca(x,y),v = fa[u][0];
		ans+=getans(root[x],root[y],root[u],root[v],1,ind,in[u],in[x]);
		ans+=getans(root[x],root[y],root[u],root[v],1,ind,in[u],in[y]);
		ans-=getans(root[x],root[y],root[u],root[v],1,ind,in[u],in[u]);
		ans--;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	int x,y;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		a[x].push_back(y);
		ask[i].x = x,ask[i].y = y;
	}
	sort(ask+1,ask+m+1,cmp);
	dfs(1);
	dfs2(1);
	solve();
	ll b = (ll)m*(m-1)/2;
	int j;
	for(int i = 1;i<= m;i=j)
		for(j=i;ask[i].x==ask[j].x&&ask[i].y==ask[j].y;j++)
			ans-=(ll)(j-i)*(j-i-1)/2;
	ll t = gcd(ans,b);
	ans = ans/t,b = b/t;
	printf("%lld/%lld\n",ans,b);
	return 0;
}
