
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 20005;
const int maxN = 1000001;
int cnt[maxN],q[N],sa[N],h[N],rnk[N],v[N],nv[N];
int s[N],n,k;
bool is_same(int a,int b,int ln,int len)
{
	return (v[a]==v[b])&&((a+ln>len&&b+ln>len)||(a+ln<len&&b+ln<len&&v[a+ln]==v[b+ln]));
}
void build_sa(int len,int lim)
{
	int i,j,k;
	for(i = 0;i<lim;i++)cnt[i]=0;
	for(i = 0;i<len;i++)cnt[v[i]=s[i]]++;
	for(i = 1;i<lim;i++)cnt[i]+=cnt[i-1];
	for(i = len-1;i>=0;i--)sa[--cnt[v[i]]] = i;
	for(int d = 1;;d++)
	{
		int ln = 1<<(d-1),id = 0;
		for(i = len-ln;i<len;i++)q[id++]=i;
		for(i = 0;i<len;i++)if(sa[i]>=ln)q[id++]=sa[i]-ln;

		for(i = 0;i<lim;i++)cnt[i]=0;
		for(i = 0;i<len;i++)cnt[v[q[i]]]++;
		for(i = 1;i<lim;i++)cnt[i]+=cnt[i-1];
		for(i=len-1;i>=0;i--)sa[--cnt[v[q[i]]]]=q[i];

		lim = 0;
		for(i=0;i<len;lim++)
		{
			for(j=i;j<len-1&&is_same(sa[j],sa[j+1],ln,len);j++);
			for(k=i,i=j+1;k<=j;k++)nv[sa[k]]=lim;
		}
		for(i=0;i<len;i++)v[i]=nv[i];
		if(lim==len)break;
	}
}
void build_rank(int len)
{
	for(int i = 0;i<len;i++)
		rnk[sa[i]]=i;
}
void build_height(int len)
{
	for(int i = 0;i<len;i++)
		if(rnk[i])
		{
			int j = 0;
			if(i)j = max(h[rnk[i-1]]-1,0);
			while(i+j<len&&sa[rnk[i]-1]+j<len&&s[i+j]==s[sa[rnk[i]-1]+j])j++;
			h[rnk[i]]=j;
		}
}
bool check(int mid,int len)
{
	int tmp = 0;
	for(int i = 1;i<len;i++)
	{
		if(h[i]>=mid)tmp++;
		else tmp = 0;
		if(tmp>=k-1)return true;
	}
	return false;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i = 0;i< n;i++)scanf("%d",&s[i]);
	build_sa(n,maxN);
	build_rank(n);
	build_height(n);
	int l = 0,r = n,ans=0;
	while(l<=r)
	{
		int mid = (l+r)>>1;
		if(check(mid,n))l=mid+1,ans=mid;
		else r = mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
