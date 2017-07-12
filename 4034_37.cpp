
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
struct E
{int next,to;}e[N<<1];
int head[N],tot,n;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int w[N],top[N],deep[N],son[N],size[N],fa[N],end[N],cnt;
bool v[N];
void dfs1(int x,int dep)
{
	deep[x] = dep;
	size[x]++;
	v[x] = true;
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
long long sum[N<<3],f[N<<3];
void push_down(int p,int l,int r)
{
	f[p<<1]+=f[p];
	f[(p<<1)+1]+=f[p];
	int mid = (l+r)>>1;
	sum[p<<1]+=f[p]*(mid-l+1);
	sum[(p<<1)+1]+=f[p]*(r-mid);
	f[p] = 0;
}
void update(int p,int l,int r,int a,int b,long long c)
{
	if(f[p])push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		f[p]+=c;
		sum[p]+=c*(r-l+1);
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,c);
	if(b>mid)update((p<<1)+1,mid+1,r,a,b,c);
	sum[p] = sum[p<<1]+sum[(p<<1)+1];
}
long long getans(int p,int l,int r,int a,int b)
{
	if(f[p])push_down(p,l,r);
	if(l>=a&&r<=b)return sum[p];
	int mid = (l+r)>>1;
	long long ans = 0;
	if(a<=mid)ans+=getans(p<<1,l,mid,a,b);
	if(b>mid)ans+=getans((p<<1)+1,mid+1,r,a,b);
	return ans;
}
long long qurey(int x,int y)
{
	long long ans = 0;
	while(top[x]!=top[y])
	{
		if(deep[top[x]]<deep[top[y]])
			swap(x,y);
		ans+=getans(1,1,n,w[top[x]],w[x]);
		x = fa[top[x]];
	}
	if(deep[x]<deep[y])
		swap(x,y);
	ans+=getans(1,1,n,w[y],w[x]);
	return ans;
}
int num[N];
int main()
{
	int x,y,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		scanf("%d",&num[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs1(1,1);
	dfs2(1,1);
	for(int i = 1;i<= n;i++)
		update(1,1,n,w[i],w[i],num[i]);
	int opt;
	long long z;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&opt,&x);
		if(opt==1)
		{
			scanf("%lld",&z);
			update(1,1,n,w[x],w[x],z);
		}else if(opt==2)
		{
			scanf("%lld",&z);
			update(1,1,n,w[x],end[x],z);
		}else
			printf("%lld\n",qurey(1,x));
	}
	return 0;
}
