
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 8e4+5;
const int M = 32*17*N;
struct E
{int next,to;}e[N<<2];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int fa[N][18];
int sz[M],ls[M],rs[M],root[N];
int q[N],a[N],T[N],F[N],dep[N],size[N];
int cnt;
void update(int &p,int pre,int l,int r,int x)
{
	p = ++cnt;
	ls[p] = ls[pre],rs[p] = rs[pre];
	sz[p] = sz[pre]+1;
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(x<=mid)
		update(ls[p],ls[pre],l,mid,x);
	else update(rs[p],rs[pre],mid+1,r,x);
}
int getans(int l,int r,int k,int x,int y,int u,int v)
{
	if(l==r)return T[l];
	int mid = (l+r)>>1;
	if(sz[ls[x]]+sz[ls[y]]-sz[ls[u]]-sz[ls[v]]>=k)
		return getans(l,mid,k,ls[x],ls[y],ls[u],ls[v]);
	else return getans(mid+1,r,k-(sz[ls[x]]+sz[ls[y]]-sz[ls[u]]-sz[ls[v]]),rs[x],rs[y],rs[u],rs[v]);
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i = 17;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x = fa[x][i];
	if(x==y)return x;
	for(int i = 17;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
void init(int x)
{
	for(int j = 1;j<= 17;j++)
		fa[x][j] = fa[fa[x][j-1]][j-1];
}
int top;
void DFS(int x)
{
    int l = 1, r = 0;
    q[++r] = x;
    while(l<=r)
    {
        int tt = q[l++]; 
        init(tt);
        update(root[tt],root[fa[tt][0]],1,top,a[tt]);
        for(int i=head[tt];i;i=e[i].next)
            if(e[i].to!=fa[tt][0])
            {
                fa[e[i].to][0] = tt;
                dep[e[i].to] = dep[tt]  + 1;
                q[++r] = e[i].to;
            }
    }
}
int find(int x)
{
	if(F[x]==x||!F[x])return F[x] = x;
	else return F[x] = find(F[x]);
}
int main()
{
	int p;
	scanf("%d",&p);
	int n,m,t;
	scanf("%d%d%d",&n,&m,&t);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		T[i] = a[i];
	}
	sort(T+1,T+n+1);
	for(int i = 1;i<= n;i++)
		if(T[i]!=T[i-1])
			T[++top] = T[i];
	for(int i = 1;i<= n;i++)
		a[i] = lower_bound(T+1,T+top+1,a[i])-T;
	for(int i = 1;i<= n;i++)size[i] = 1;
	int x,y,z;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
		int fx = find(x),fy = find(y);
		if(fx==fy)continue;
		if(size[fx]<size[fy])swap(fx,fy);
		size[fx]+=size[fy];
		F[fy] = fx;
	}
	for(int i = 1;i<= n;i++)
		if(!root[i])
		{
			dep[i] = 1;
			DFS(i);
		}
	char opt[3];
	int ans=0;
	for(int i = 1;i<= t;i++)
	{
		scanf("%s%d%d",opt,&x,&y);
		x = x^ans,y = y^ans;
		if(opt[0]=='L')
		{
			add(x,y);
			int fx = find(x),fy = find(y);
			if(size[fx]<size[fy])
				swap(fx,fy),swap(x,y);
			F[fy] = fx;size[fx]+=size[fy];
			fa[y][0] = x;dep[y] = dep[x]+1;
			DFS(y);
		}else
		{
			scanf("%d",&z);z = z^ans;
			int u = getlca(x,y);int v = fa[u][0];
			printf("%d\n",ans = getans(1,top,z,root[x],root[y],root[u],root[v]));
		}
	}
	return 0;
}
