
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 5e6+5;
int sum[M],ls[M],rs[M],tot,root[N],maxn;
int fa[N];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x]=x;
	else return fa[x]=getfa(fa[x]);
}
void Insert(int &p,int l,int r,int pos)
{
	if(!p)p=++tot;
	if(l==r)
	{
		sum[p]++;
		return ;
	}
	int mid = (l+r)>>1;
	if(pos<=mid)Insert(ls[p],l,mid,pos);
	else Insert(rs[p],mid+1,r,pos);
	sum[p] = sum[ls[p]]+sum[rs[p]];
}
int merge(int x,int y,int l,int r)
{
	if(!x||!y)return x+y;
	if(l==r)
	{
		sum[x] = sum[x]+sum[y];
		return x;
	}
	int mid = (l+r)>>1;
	ls[x] = merge(ls[x],ls[y],l,mid);
	rs[x] = merge(rs[x],rs[y],mid+1,r);
	sum[x] = sum[ls[x]]+sum[rs[x]];
	return x;
}
struct edge
{
	int x,y,w;
	bool operator <(const edge &s)const
	{
		return w<s.w;
	}
}e[5*N];
struct Ask
{
	int p,v,k,no;
	bool operator <(const Ask &s)const
	{
		return v<s.v;
	}
}ask[5*N];
int hill[N],ans[5*N];
int getans(int p,int k)
{
	if(k<=0)return -1;
	int l = 1,r = maxn,ans=-1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(sum[ls[p]]>=k)
			p = ls[p],r=mid;
		else 
		{
			k-=sum[ls[p]];
			p = rs[p],l= mid+1;
		}
	}
	return l;
}
int main()
{
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i = 1;i<=n;i++)
		scanf("%d",&hill[i]),maxn = max(maxn,hill[i]);
	for(int i = 1;i<= m;i++)
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].w);
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d%d",&ask[i].p,&ask[i].v,&ask[i].k);
		ask[i].no = i;
	}
	sort(e+1,e+m+1);sort(ask+1,ask+q+1);
	for(int i = 1;i<= n;i++)
		Insert(root[i],1,maxn,hill[i]);
	int j = 1;
	for(int i = 1;i<= q;i++)
	{
		while(j<=m&&e[j].w<=ask[i].v)
		{
			int fx = getfa(e[j].x),fy = getfa(e[j].y);
			if(fx==fy){j++;continue;}
			fa[fy] = fx;
			root[fx] = merge(root[fx],root[fy],1,maxn);
			j++;
		}
		int tmp = getfa(ask[i].p);
		ans[ask[i].no] = getans(root[tmp],sum[root[tmp]]-ask[i].k+1);
	}
	for(int i = 1;i<= q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
