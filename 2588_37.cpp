
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 200005;
const int M = 8000005;
typedef long long ll;
struct E
{int next,to;}e[N<<1];
inline int read() 
{
	int f = 1; ll x = 0; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) f = ch == '-' ? -1 : 1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	return f * x;
}
int head[N],tot,n,m;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int fa[N][20],dep[N],line[N],tail;
int cnt,root[N],ls[M],rs[M];
int sum[M],val[N],pos[N],top,ans;
int getpos(int x)
{
	int l = 1,r = top+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(pos[mid]<x)l = mid+1;
		else r = mid;
	}
	return l;
}
void init()
{
	for(int j = 1;j<= 18;j++)
		for(int i = 1;i<=n;i++)
			fa[i][j] = fa[fa[i][j-1]][j-1];
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i = 18;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x = fa[x][i];
	if(x==y)return x;
	for(int i = 18;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
void update(int &p,int l,int r,int pos,int val,int pre)
{
	p = ++cnt;
	sum[p] = sum[pre]+1;
	if(l==r)return ;
	int mid = (l+r)>>1;
	ls[p] = ls[pre],rs[p] = rs[pre];
	if(pos<=mid)
		update(ls[p],l,mid,pos,val,ls[pre]);
	else
		update(rs[p],mid+1,r,pos,val,rs[pre]);
	//sum[p] = sum[ls[p]]+sum[rs[p]];
}
int a[N],b[N];
void build(int &p,int l,int r)
{
	p = ++cnt;
	if(l==r)return ;
	int mid = (l+r)>>1;
	build(ls[p],l,mid);
	build(rs[p],mid+1,r);
}
void dfs(int x)
{
	update(root[x],1,n,a[x],1,root[fa[x][0]]);
	dep[x] = dep[fa[x][0]]+1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x][0])
		{
			fa[e[i].to][0] = x;
			dfs(e[i].to);
		}
}
void solve(int x,int y,int k)
{
	int u = getlca(x,y);
	int v = fa[u][0];
	int l = 1,r = n,ret;
	x = root[x],y = root[y],u = root[u],v = root[v];
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(sum[ls[x]]+sum[ls[y]]-sum[ls[u]]-sum[ls[v]]>=k)
		{
			x = ls[x],y = ls[y];
			u = ls[u],v = ls[v];
			r = mid;
		}else
		{
			k-=sum[ls[x]]+sum[ls[y]]-sum[ls[u]]-sum[ls[v]];
			x = rs[x],y = rs[y];
			u = rs[u],v = rs[v];
			l = mid+1;
		}
	}
	ans = b[l];
	printf("%d",ans);
}
int main()
{
	n = read();m = read();
	for(int i = 1;i<= n;i++){a[i] = read();b[i] = a[i];}
	sort(b+1,b+n+1);
	for(int i = 1;i<= n;i++)
		a[i] = lower_bound(b+1,b+n+1,a[i])-b;
	int x,y,z;
	for(int i = 1;i<n;i++)
	{
		x = read();y = read();
		add(x,y),add(y,x);
	}
	build(root[0],1,n);
	dfs(1);
	init();
	for(int i = 1;i<= m;i++)
	{
		x = read();y = read();z = read();
		x = x^ans;
		//if(x==y){ans = val[x];printf("%d",ans);}
		solve(x,y,z);
		if(i!=m)printf("\n");
	}
	return 0;
}
