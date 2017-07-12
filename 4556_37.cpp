
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 5e6+5;
int ls[M],rs[M],sum[M];
int rot[N],Cnt,n,m;
void update(int &p,int pre,int l,int r,int pos)
{
	p = ++Cnt;
	sum[p] = sum[pre]+1;
	if(l==r)return ;
	ls[p] = ls[pre],rs[p] = rs[pre];
	int mid = (l+r)>>1;
	if(pos<=mid)update(ls[p],ls[pre],l,mid,pos);
	else update(rs[p],rs[pre],mid+1,r,pos);
}
int getans(int L,int R,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return sum[R]-sum[L];
	int mid = (l+r)>>1,ans = 0;
	if(a<=mid)ans+=getans(ls[L],ls[R],l,mid,a,b);
	if(b >mid)ans+=getans(rs[L],rs[R],mid+1,r,a,b);
	return ans;
}
int sa[N],cnt[N],val[N],rnk[N],h[N],q[N],nv[N];
char s[N];
inline bool is_same(int a,int b,int hl,int len)
{return val[a]==val[b]&&((a+hl>len&&b+hl>len)||(a+hl<len&&b+hl<len&&val[a+hl]==val[b+hl]));}
void build_sa(int len,int lim)
{
	int i,j,k;
	for(i = 0;i<lim;i++)cnt[i] = 0;
	for(i = 0;i<len;i++)cnt[val[i]=s[i]]++;
	for(i = 1;i<lim;i++)cnt[i]+=cnt[i-1];
	for(i = len-1;i>=0;i--)sa[--cnt[val[i]]] = i;
	for(int d = 1;;d++)
	{
		int hl = 1<<(d-1),id = 0;
		for(i = 0;i<len;i++)if(sa[i]+hl>=len)q[id++] = sa[i];
		for(i = 0;i<len;i++)if(sa[i]>=hl)q[id++] = sa[i]-hl;

		for(i = 0;i<lim;i++)cnt[i] = 0;
		for(i = 0;i<len;i++)cnt[val[i]]++;
		for(i = 1;i<lim;i++)cnt[i]+=cnt[i-1];
		for(i = len-1;i>=0;i--)sa[--cnt[val[q[i]]]] = q[i];

		lim = 0;
		for(i = 0;i<len;lim++)
		{
			for(j = i;j<len-1&&is_same(sa[j],sa[j+1],hl,len);j++);
			for(k = i,i=j+1;k<=j;k++)nv[sa[k]] = lim;
		}
		if(lim==len)break;
		for(i = 0;i<len;i++)val[i]=nv[i];
	}
}
void build_rank(int len)
{for(int i = 0;i<=len;i++)rnk[sa[i]]=i;}
int mn[N][18];
void build_height(int len)
{
	for(int i = 0;i<len;i++)
		if(rnk[i])
		{
			int j = 0;
			if(i)j = max(h[rnk[i-1]]-1,0);
			while(i+j<len&&sa[rnk[i]-1]+j<len&&s[i+j]==s[sa[rnk[i]-1]+j])j++;
			h[rnk[i]] = j;
		}
}
int lg2[N];
void build_st(int len)
{
	for(int i = 2;i<= len;i++)lg2[i] = lg2[i>>1]+1;
	for(int i = 0;i<=len;i++)mn[i][0] = h[i];
	for(int j = 1;j<= 18;j++)
		for(int i = 0;i+(1<<j)-1<= len;i++)
			mn[i][j] = min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
}
int main()
{
	//freopen("x.in","r",stdin);
	scanf("%d%d",&n,&m);
	scanf("%s",s);
	int a,b,c,d;
	build_sa(n+1,256);
	build_rank(n);build_height(n);
	build_st(n);
	for(int i = 1;i<= n;i++)
		update(rot[i],rot[i-1],1,n,sa[i]+1);
	while(m--)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		int l = 1,r = min(d-c+1,b-a+1),ans=0,mid;
		while(l<=r)
		{
			mid = (l+r)>>1;
			int lp = rnk[c-1],rp = lp;
			for(int k = lg2[n];k>=0;k--)
			{
				if(lp>=(1<<k) && mn[lp-(1<<k)+1][k]>=mid)lp-=(1<<k);
				if(rp<=n-(1<<k) && mn[rp+1][k]>=mid)rp+=(1<<k);
			}
			if(getans(rot[lp-1],rot[rp],1,n,a,b-mid+1)>0)ans = mid,l=mid+1;
			else r = mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
