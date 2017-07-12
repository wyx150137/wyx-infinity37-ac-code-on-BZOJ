
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
typedef long long ll;
char s[N];
int cnt[N],sa[N],v[N],nv[N],q[N],rnk[N],h[N];
bool is_same(int a,int b,int hl,int len)
{
	return v[a]==v[b]&&((a+hl>len&&b+hl>len)||(a+hl<len&&b+hl<len&&v[a+hl]==v[b+hl]));
}
void build_sa(int len,int lim)
{
	int i,j,k;
	for(i = 0;i<lim;i++)cnt[i]=0;
	for(i = 0;i<len;i++)cnt[v[i]=s[i]]++;
	for(i = 1;i<lim;i++)cnt[i]+=cnt[i-1];
	for(i = len-1;i>=0;i--)sa[--cnt[v[i]]]=i;
	for(int d = 1;;d++)
	{
		int hl = 1<<(d-1),id = 0;
		for(i=len-hl;i<len;i++)q[id++]=i;
		for(i=0;i<len;i++)if(sa[i]>=hl)q[id++]=sa[i]-hl;

		for(i=0;i<lim;i++)cnt[i]=0;
		for(i=0;i<len;i++)cnt[v[q[i]]]++;
		for(i=1;i<lim;i++)cnt[i]+=cnt[i-1];
		for(i=len-1;i>=0;i--)sa[--cnt[v[q[i]]]]=q[i];

		lim=0;
		for(i=0;i<len;lim++)
		{
			for(j=i;j<len-1&&is_same(sa[j],sa[j+1],hl,len);j++);
			for(k=i,i=j+1;k<=j;k++)nv[sa[k]]=lim;
		}
		for(i=0;i<len;i++)v[i]=nv[i];
		if(lim==len)break;
	}
}
void build_rank(int len)
{
	for(int i= 0;i<len;i++)
		rnk[sa[i]]=i;
}
void build_height(int len)
{
	for(int i = 0;i<len;i++)
		if(rnk[i])
		{
			int j = 0;
			if(i)j=max(0,h[rnk[i-1]]-1);
			while(i+j<len&&sa[rnk[i]-1]+j<len&&s[i+j]==s[sa[rnk[i]-1]+j])j++;
			h[rnk[i]]=j;
		}
}
int st[18][N];
int log_2[N];
void build_st(int len)
{
	for(int i = 1;i<len;i++)
		st[0][i]=h[i];
	for(int j = 1;j<= 17;j++)
		for(int i = 1;i+(1<<(j-1))<len;i++)
			st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	for(int i = 2;i<N;i++)
		log_2[i]=log_2[i>>1]+1;
}
int getans(int l,int r,int n)
{
	l=rnk[l],r=rnk[r];
	if(l>r)swap(l,r);
	l++;
	if(l>r)return n-sa[r];
	int lth = log_2[r-l+1];
	return min(st[lth][l],st[lth][r-(1<<lth)+1]); 
}
ll sum[N];
struct Ask
{int l,r,p,q,a,b;ll ans;}ask[N];
int find(ll x,int n)
{
	int l = 0,r = n,ans=-1;
	while(l<=r)
	{
		int mid = (l+r)>>1;
		if(sum[mid]<x)l=mid+1;
		else r = mid-1,ans=mid;
	}
	return ans;
}
int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	scanf("%s",s);
	build_sa(n,256);
	build_rank(n);
	build_height(n);
	build_st(n);
	for(int i = 0;i<n;i++)
		sum[i]=n-sa[i]-h[i];
	for(int i = 1;i< n;i++)
		sum[i]+=sum[i-1];
	ll x,y;
	for(int i = 1;i<= q;i++)
	{
		scanf("%lld%lld",&x,&y);
		int l = find(x,n),p=find(y,n);
		if(l==-1||p==-1){ask[i].ans=-1;continue;}
		ask[i].l=sa[l],ask[i].p=sa[p];
		if(l>=1)ask[i].r=x-sum[l-1]+ask[i].l+h[l]-1;
		else ask[i].r=ask[i].l+x-1;
		if(p>=1)ask[i].q=y-sum[p-1]+ask[i].p+h[p]-1;
		else ask[i].q=ask[i].p+y-1;
		ask[i].a=min(min(ask[i].r-ask[i].l+1,ask[i].q-ask[i].p+1),getans(ask[i].l,ask[i].p,n));
	}
	for(int i = 0;i<n/2;i++)swap(s[i],s[n-i-1]);
	build_sa(n,256);
	build_rank(n);
	build_height(n);
	build_st(n);
	for(int i = 1;i<= q;i++)
	if(ask[i].ans!=-1)
	{
		ask[i].b=min(min(ask[i].r-ask[i].l+1,ask[i].q-ask[i].p+1),getans(n-ask[i].r-1,n-ask[i].q-1,n));
		ask[i].ans=(ll)ask[i].a*ask[i].a+(ll)ask[i].b*ask[i].b;
	}
	for(int i = 1;i<= q;i++)
		printf("%lld\n",ask[i].ans);
	return 0;
}
