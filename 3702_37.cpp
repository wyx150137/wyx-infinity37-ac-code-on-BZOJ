
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
LL cnt1,cnt2;
const int N = 200005;
int root[N<<1],L[N<<1],R[N<<1],ls[4000005],rs[4000005],sum[4000005],cv[N<<1],tot,seg,n;
void scantree(int x)
{
	scanf("%d",&cv[x]);
	if(!cv[x])
	{
		L[x]=++tot;
		scantree(L[x]);
		R[x]=++tot;
		scantree(R[x]);
	}
}
void build(int &p,int l,int r,int c)
{
	if(!p)p = ++seg;
	if(l==r)
	{
		sum[p] = 1;
		return ;
	}
	int mid = (l+r)>>1;
	if(c<=mid)build(ls[p],l,mid,c);
	else build(rs[p],mid+1,r,c);
	sum[p] = sum[rs[p]]+sum[ls[p]];
}
int merge(int x,int y)
{
	if(!x)return y;
	if(!y)return x;
	cnt1+=(LL)sum[ls[x]]*sum[rs[y]];
	cnt2+=(LL)sum[rs[x]]*sum[ls[y]];
	ls[x] = merge(ls[x],ls[y]);
	rs[x] = merge(rs[x],rs[y]);
	sum[x] = sum[ls[x]]+sum[rs[x]];
	return x;
}
LL ans;
void solve(int x)
{
	if(!x)return ;
	solve(L[x]);solve(R[x]);
	if(!cv[x])
	{
		cnt1 = cnt2 = 0;
		root[x] = merge(root[L[x]],root[R[x]]);
		ans+=min(cnt1,cnt2);
	}
}
int main()
{
	scanf("%d",&n);
	tot++;
	scantree(1);
	for(int i = 1;i<= tot;i++)
		if(cv[i])build(root[i],1,n,cv[i]);
	solve(1);
	printf("%lld\n",ans);
	return 0;
}
