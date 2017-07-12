
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
struct E{int next,to;}e[N<<1];
int head[N],tot,n,m,logx[N],root;
long long f[N<<2];
long long minn[N<<2];
long long INF;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int deep[N],top[N],fa[N],son[N],w[N],size[N],end[N],cnt;
int anc[18][N];
bool v[N];
void init()
{
	for(int j = 1;j<= 17;j++)
		for(int i = 1;i<=n;i++)
			anc[j][i] = anc[j-1][anc[j-1][i]];
}
void dfs1(int x,int dep)
{
	deep[x] = dep;
	v[x] = true;
	size[x]++;
	for(int i = head[x];i;i = e[i].next)
	{
		int tmp = e[i].to;
		if(!v[tmp])
		{
			dfs1(tmp,dep+1);
			size[x]+=size[tmp];
			fa[tmp] = x;
			if(size[tmp]>size[son[x]])son[x] = tmp;
		}
	}
}
void dfs2(int x,int tp)
{
	top[x] = tp;
	w[x] = ++cnt;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
	end[x] = cnt;
}
void push_down(int p)
{
	f[p<<1] = f[p];
	f[(p<<1)+1] = f[p];
	minn[p<<1] = f[p];
	minn[(p<<1)+1] = f[p];
	f[p] = 0;
}
void update(int p,int l,int r,int a,int b,long long c)
{
	if(l>=a&&r<=b)
		{f[p] = c;minn[p] = c;return ;}
	if(f[p])push_down(p);
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,c);
	if(b>mid)update((p<<1)+1,mid+1,r,a,b,c);
	minn[p] = min(minn[p<<1],minn[(p<<1)+1]);
	return ;
}
long long getans(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)
		return minn[p];
	if(f[p])push_down(p);
	int mid = (l+r)>>1;
	long long ans = INF;
	if(a<=mid)
		ans = min(ans,getans(p<<1,l,mid,a,b));
	if(b>mid)
		ans = min(ans,getans((p<<1)+1,mid+1,r,a,b));
	return ans;
}
void get_update(int x,int y,long long c)
{
	while(top[x]!=top[y])
	{
		if(deep[top[x]]<deep[top[y]])
			swap(x,y);
		update(1,1,n,w[top[x]],w[x],c);
		x = fa[top[x]];
	}
	if(deep[x]<deep[y])swap(x,y);
	update(1,1,n,w[y],w[x],c);
}
long long Ask(int x)
{
	if(w[root]<w[x]||w[root]>end[x])
		return getans(1,1,n,w[x],end[x]);
	else if(root==x)
		return minn[1];
	else
	{
		int tmp = root;
		for(int j = 17;j>=0;j--)
			if(deep[fa[anc[j][tmp]]]>=deep[x])
				tmp = anc[j][tmp];
		long long ans = INF;
		ans = min(ans,getans(1,1,n,1,w[tmp]-1));
		ans = min(ans,getans(1,1,n,end[tmp]+1,n));
		return ans;
	}
}
int main()
{
	memset(minn,0x3f,sizeof(minn));
	INF = minn[0];
	int x,y;long long z;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs1(1,1);
	dfs2(1,1);
	long long tmp;
	for(int i = 1;i<= n;i++)
	{
		scanf("%lld",&tmp);
		update(1,1,n,w[i],w[i],tmp);
		anc[0][i]= fa[i];
	}
	init();
	scanf("%d",&root);
	int opt;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&opt);
		if(opt==1){scanf("%d",&x);root = x;}
		else if(opt==2){scanf("%d%d%lld",&x,&y,&z);get_update(x,y,z);}
		else {scanf("%d",&x);printf("%lld\n",Ask(x));}
	}
	return 0;
}
