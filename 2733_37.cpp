
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int Q = 300005;
const int N = 100005;
int root[N],ls[N*20],rs[N*20],sum[N*20],num[N],seg;
void update(int &p,int l,int r,int x)
{
	if(!p)p = ++seg;
	if(l==r)
	{
		sum[p] = 1;
		return ;
	}
	int mid = (l+r)>>1;
	if(x<=mid)update(ls[p],l,mid,x);
	else update(rs[p],mid+1,r,x);
	sum[p] = sum[ls[p]]+sum[rs[p]];
}
int getans(int p,int l,int r,int x,int s)
{
	if(!p)return -1;
	if(l==r)
		return l;
	int mid = (l+r)>>1;
	if(sum[ls[p]]+s<x)
		return getans(rs[p],mid+1,r,x,sum[ls[p]]+s);
	else return getans(ls[p],l,mid,x,s);
}
int merge(int x,int y)
{
	if(!x)return y;
	if(!y)return x;
	ls[x] = merge(ls[x],ls[y]);
	rs[x] = merge(rs[x],rs[y]);
	sum[x] = sum[ls[x]]+sum[rs[x]];
	return x;
}
int fa[N],rnk[N];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x] = x;
	else
	{ 
		int tmp = getfa(fa[x]);
		//root[x] = merge(root[tmp],root[x]);
		return fa[x] = tmp;
	}
}
void uni(int x,int y)
{
	int fx = getfa(x),fy = getfa(y);
	if(fx==fy)return ;
	if(rnk[fx]>rnk[fy])
	{
		fa[fy] = fx;
		root[fx] = merge(root[fx],root[fy]);
	}
	else
	{
		fa[fx] = fy,rnk[fy]+=rnk[fx]==rnk[fy];
		root[fy] = merge(root[fy],root[fx]);
	}
}
int imc[N],bri[N];
int main()
{
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&imc[i]);
		bri[imc[i]] = i;
		update(root[i],1,n,imc[i]);
	}
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		uni(x,y);
	}
	int q;
	scanf("%d",&q);
	char ju[3];
	for(int i = 1;i<= q;i++)
	{
		scanf("%s",ju);
		scanf("%d%d",&x,&y);
		if(ju[0]=='B')uni(x,y);
		else
		{
			int fx = getfa(x);
			int tmp = getans(root[fx],1,n,y,0);
			if(tmp==-1)printf("-1\n");
			else printf("%d\n",bri[tmp]);
		}
	}
	return 0;
}
