
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e5+5;
const int M = 1e7+5;
typedef long long ll;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
int dfn[N],Dfn,dep[N],size[N],end[N],R,root[N];
struct P
{
	int dep,size,dfn;
	P(){}
	P(int dep,int size,int dfn):dep(dep),size(size),dfn(dfn){}
	bool operator <(const P &s)const
	{
		return dfn<s.dfn;
	}
}p[N];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	R = max(R,dep[x]);
	size[x]=1;
	dfn[x]=++Dfn;
	for(int i =head[x];i;i=e[i].next)
		if(e[i].to!=fa)
		{
			dfs(e[i].to,x);
			size[x]+=size[e[i].to];
		}
	end[x] = Dfn;
}
int ls[M],rs[M];
ll sum[M];
void update(int &p,int pre,int l,int r,int pos,int v)
{
	p = ++tot;
	sum[p] = sum[pre];
	ls[p] = ls[pre],rs[p] = rs[pre];
	if(l==r)
	{
		sum[p]+=v;
		return ;
	}
	int mid = (l+r)>>1;
	if(pos<=mid)update(ls[p],ls[pre],l,mid,pos,v);
	else update(rs[p],rs[pre],mid+1,r,pos,v);
	sum[p] = sum[ls[p]]+sum[rs[p]];
}
ll getans(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)
		return sum[p];
	int mid = (l+r)>>1;
	ll ans = 0;
	if(a<=mid)ans+=getans(ls[p],l,mid,a,b);
	if(b >mid)ans+=getans(rs[p],mid+1,r,a,b);
	return ans;
}
int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	int x,y;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	for(int i = 1;i<= n;i++)
		p[i] = P(dep[i],size[i],dfn[i]);
	sort(p+1,p+n+1);
	for(int i = 1;i<= n;i++)
		update(root[i],root[i-1],1,R,p[i].dep,p[i].size-1);
	int p,k;
	while(q--)
	{
		scanf("%d%d",&p,&k);
		ll ans = getans(root[end[p]],1,R,dep[p]+1,min(dep[p]+k,R));
		ans = ans-getans(root[dfn[p]-1],1,R,dep[p]+1,min(dep[p]+k,R));
		ans+=(ll)(size[p]-1)*min(k,dep[p]-1);
		printf("%lld\n",ans);
	}
	return 0;
}
