
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2e5+5;
struct E
{int next,to;}e[N<<1];
int head[N],tot,n,m,key;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int top[N],size[N],son[N],fa[N],dep[N],q[N],rk[N],a[N];
void dfs(int x)
{
	dep[x] = dep[fa[x]]+1;
	size[x] = 1;
	for(int i = head[x];i;i=e[i].next)
	{
		dfs(e[i].to);
		size[x]+=size[e[i].to];
		if(size[e[i].to]>size[son[x]])son[x] = e[i].to;
	}
}
int seq[N],Dfn,in[N],out[N];
void dfs2(int x,int tp)
{
	top[x] = tp;
	in[x] = ++Dfn;seq[Dfn] = x;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
	out[x] = ++Dfn;seq[Dfn] = x;
}
int getlca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x = fa[top[x]];
	}
	if(dep[x]<dep[y])return x;
	else return y;
}
struct data
{
	int x,y,k;
	data(int _x=0,int _y=0,int _k=0):x(_x),y(_y),k(_k){}
}b[N];
int cnt;
ll c[N],ans[N],res;
bool vis[N];
void Add(int x,ll y)
{
	for(int i = x;i<=n;i+=i&(-i))
		c[i]+=y;
}
ll Getans(int x)
{
	ll ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=c[i];
	return ans;
}
void Insert(int x,int y)
{
	int lca = getlca(x,y);
	if(in[x]>in[y])swap(x,y);
	cnt++;
	b[cnt] = data(lca==x?in[x]:out[x],in[y],cnt+1);
}
int per;
void update(int y)
{
	int x = rk[y];
	vis[y]^=1;
	if(vis[y])
	{
		per++;
		Add(x,(ll)a[y]*n+1);
		ll z = Getans(x)-1;
		res+=(ll)a[y]*(per-z%n-1)+z/n;
	}else
	{
		ll z = Getans(x)-1;
		res-=(ll)a[y]*(per-z%n-1)+z/n;
		per--;
		Add(x,-((ll)a[y]*n+1));
	}
}
int bl;
bool cmp1(int x,int y)
{
	return a[x]<a[y];
}
bool cmp2(const data &a,const data &b)
{
	if(a.x/bl==b.x/bl)return a.y<b.y;
	return a.x/bl<b.x/bl;
}
int main()
{
	int root =0;
	scanf("%d%d%d",&n,&m,&key);
	bl = sqrt(2*n);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]),q[i]=i;
	sort(q+1,q+n+1,cmp1);
	for(int i=1;i<= n;i++)rk[q[i]]=i;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&fa[i]);
		if(fa[i])add(fa[i],i);
		else root = i;
	}
	dfs(root);dfs2(root,root);
	int x=1,y;char opt[3];
	for(int i = 1;i<= m;i++)
	{
		scanf("%s%d",opt,&y);
		if(opt[0]=='C')x=y;
		else
		{
			Insert(x,y%n+1);
			Insert(x,(y+key)%n+1);
		}
	}
	sort(b+1,b+cnt+1,cmp2);
	int l = 1,r = 0;res = 0;
	for(int i = 1;i<= cnt;i++)
	{
		while(l<b[i].x)update(seq[l]),l++;
		while(b[i].x<l)l--,update(seq[l]);
		while(r<b[i].y)r++,update(seq[r]);
		while(b[i].y<r)update(seq[r]),r--;
		x=seq[l]; y=seq[r]; int z=getlca(x,y);
		if (x!=z) update(z); 
		ans[b[i].k]=res; 
		if (x!=z) update(z);
	}
	ll tmp = 0;
	for(int i = 1;i<= cnt>>1;i++)
	{
		tmp = ans[i<<1|(tmp&1)];
		printf("%lld\n",tmp);
	}
	return 0;
}
