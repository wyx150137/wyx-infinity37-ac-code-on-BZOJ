
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 1e7;
int rot[N][2],cnt,n,m;
int ls[M],rs[M],sum[M],a[N];
void update(int &p,int l,int r,int pos,int val)
{
	if(!p)p = ++cnt;
	sum[p]+=val;
	if(l==r)return ;
	int mid = (l+r)>>1;
	if(pos<=mid)update(ls[p],l,mid,pos,val);
	else update(rs[p],mid+1,r,pos,val);
	//sum[p] = sum[ls[p]]+sum[rs[p]];
}
int getans(int p,int l,int r,int a,int b)
{
	if(!p)return 0;
	if(a>b)return 0;
	if(l>=a&&r<=b)return sum[p];
	int mid = (l+r)>>1,ans = 0;
	if(a<=mid)ans+=getans(ls[p],l,mid,a,b);
	if(b >mid)ans+=getans(rs[p],mid+1,r,a,b);
	return ans;
}
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int pos[N],T,log_2[N<<1];
int min_dpt[N<<1][18],dpt[N];
void dfs(int x,int from)
{
	min_dpt[pos[x]=++T][0] = dpt[x];
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=from)
		{
			dpt[e[i].to] = dpt[x]+1;
			dfs(e[i].to,x);
			min_dpt[++T][0] = dpt[x];
		}
}
void build_lca()
{
	for(int i = 2;i<=T;i++)
		log_2[i] = log_2[i>>1]+1;
	for(int j = 1;j<= log_2[T];j++)
		for(int i = 1;i+(1<<j)-1<=T;i++)
			min_dpt[i][j] = min(min_dpt[i][j-1],min_dpt[i+(1<<(j-1))][j-1]);
}
int get_lcadpt(int x,int y)
{
	x = pos[x],y = pos[y];
	if(x>y)swap(x,y);
	int l = log_2[y-x+1];
	return min(min_dpt[x][l],min_dpt[y-(1<<l)+1][l]);
}
int getdis(int x,int y)
{
	return dpt[x]+dpt[y]-2*get_lcadpt(x,y);
}
bool used[N];
int size[N],f[N],Sum,father[N];
void get_size(int x,int pre)
{
	size[x] = 1;
	for(int i = head[x];i;i=e[i].next)
		if(!used[e[i].to]&&e[i].to!=pre)
		{
			get_size(e[i].to,x);
			size[x]+=size[e[i].to];
		}
}
int root;
void get_root(int x,int pre)
{
	size[x] = 1,f[x] = 0;
	for(int i = head[x];i;i=e[i].next)
		if(!used[e[i].to]&&e[i].to!=pre)
		{
			get_root(e[i].to,x);
			size[x]+=size[e[i].to];
			f[x] = max(f[x],size[e[i].to]);
		}
	f[x] = max(f[x],Sum-size[x]);
	if(f[x]<f[root])root = x;
}
int stack[N],top;
void DFS(int x,int pre)
{
	stack[++top] = x;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=pre&&!used[e[i].to])
			DFS(e[i].to,x);
}
void Build(int x,int pre)
{
	get_size(x,0);
	Sum = size[x];f[0] = Sum,root = 0;
	get_root(x,0);
	x = root;
	father[x] = pre;
	used[x] = true;
	top = 0;
	DFS(x,0);
	for(int i = 1;i<= top;i++)
	{
		int y = stack[i];
		update(rot[x][0],0,n,getdis(y,x),a[y]);
		update(rot[x][1],0,n,getdis(y,father[x]),a[y]);
	}
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=pre&&!used[e[i].to])
			Build(e[i].to,x);
}
void Update(int x,int del)
{
	for(int i = x;i;i=father[i])
	{
		update(rot[i][0],0,n,getdis(x,i),del);
		if(father[i])update(rot[i][1],0,n,getdis(x,father[i]),del);
	}
	a[x]+=del;
}
int Getans(int x,int k)
{
	int ans = 0;
	for(int i = x;i;i=father[i])
	{
		int Dis = getdis(i,x);
		if(Dis<=k)
			ans = ans+getans(rot[i][0],0,n,0,k-Dis);
		if(father[i])
		{
			int Dis2 = getdis(father[i],x);
			if(Dis2<=k)ans = ans-getans(rot[i][1],0,n,0,k-Dis2);
		}
	}
	return ans;
}
int main()
{
	//freopen("x.in","r",stdin);
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	int opt;
	dpt[1] = 1;
	dfs(1,0);
	build_lca();
	Build(1,0);
	int lastans = 0;
	while(m--)
	{
		scanf("%d%d%d",&opt,&x,&y);
		x = x^lastans,y = y^lastans;
		if(opt==0)
			printf("%d\n",lastans = Getans(x,y));
		else Update(x,y-a[x]);
	}
	return 0;
}
