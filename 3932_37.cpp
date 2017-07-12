
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 200005;
const int M = 4000005;
typedef long long ll;
int ls[M],rs[M],sum[M],ans[M];
int root[N],n,m;
int a[N];
int st[N],ed[N],cnt;
struct P
{int val,id;}T[N];
bool cmpT(P a,P b){return a.val<b.val;}
struct Up
{int pos,val,aa;}ask[N<<1];
int cnt_ask;
bool cmp(Up a,Up b){return a.pos<b.pos;}
int a_T[N];
void init()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d%d",&st[i],&ed[i],&a[i]);
		ask[++cnt_ask] = (Up){st[i],1,i};
		ask[++cnt_ask] = (Up){ed[i]+1,-1,i};
		T[i] = (P){a[i],i};
	}
	sort(T+1,T+n+1,cmpT);
	for(int i = 1;i<= n;i++)
		a_T[T[i].id] = i;
	sort(ask+1,ask+cnt_ask+1,cmp);
}
void update(int &p,int pre,int l,int r,int pos,int val)
{
	p = ++cnt;
	if(l==r)
	{
		sum[p]=sum[pre]+val;
		ans[p]=ans[pre]+val*T[l].val;
		return ;
	}
	int mid = (l+r)>>1;
	ls[p] = ls[pre],rs[p] = rs[pre];
	if(pos<=mid)update(ls[p],ls[pre],l,mid,pos,val);
	else update(rs[p],rs[pre],mid+1,r,pos,val);
	sum[p] = sum[ls[p]]+sum[rs[p]];
	ans[p] = ans[ls[p]]+ans[rs[p]];
}
ll Ans;
void getans(int p,int k)
{
	int l = 1,r = n;
	Ans = 0;
	p = root[p];
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(sum[ls[p]]>=k)
			p = ls[p],r = mid;
		else
			Ans+=ans[ls[p]],k-=sum[ls[p]],p = rs[p],l = mid+1;
	}
	Ans+=ans[p];
	printf("%lld\n",Ans);
}
int main()
{
	init();
	int j=1;
	for(int i = 1;i<= n;i++)
	{
		root[i] = root[i-1];
		while(j<=cnt_ask&&ask[j].pos==i)
		{
			update(root[i],root[i],1,n,a_T[ask[j].aa],ask[j].val);
			j++;
		}
	}
	int x,a,b,c,k;
	Ans=1;
	while(m--)
	{
		scanf("%d%d%d%d",&x,&a,&b,&c);
		k = ((ll)a*Ans+b)%c+1;
		//scanf("%d%d",&x,&k);
		getans(x,k);
	}
	return 0;
}
