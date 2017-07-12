
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3005;
int s[N];
int sa[N],q[N],v[N],nv[N],cnt[N],rnk[N],h[N];
bool is_same(int a,int b,int hl,int len)
{
	return v[a]==v[b]&&((a+hl>len&&b+hl>len)||(a+hl<len&&b+hl<len&&v[a+hl]==v[b+hl]));
}
void build_sa(int len,int lim)
{
	int i,j,k;
	for(i=0;i<lim;i++)cnt[i]=0;
	for(i=0;i<len;i++)cnt[v[i]=s[i]]++;
	for(i=1;i<lim;i++)cnt[i]+=cnt[i-1];
	for(i=len-1;i>=0;i--)sa[--cnt[v[i]]]=i;
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
	for(int i = 0;i<len;i++)
		rnk[sa[i]]=i;
}
void build_height(int len)
{
	for(int i = 0;i<len;i++)
		if(rnk[i])
		{
			int j  =0;
			if(i)j=max(0,h[rnk[i-1]]-1);
			while(i+j<len&&sa[rnk[i]-1]+j<len&&s[i+j]==s[sa[rnk[i]-1]+j])j++;
			h[rnk[i]]=j;
		}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0;i<n;i++)
		scanf("%1d",&s[i]);
	build_sa(n,2);
	build_rank(n);
	build_height(n);
	int l,r;
	for(int i = 0;i< n;i++)
		for(int j = h[i]+1;sa[i]+j-1<n;j++)
		{
			for(l=i;l>=0&&h[l]>=j;l--);
			for(r=i+1;r<n&&h[r]>=j;r++);
			if(r-l>1)printf("%d\n",r-l);
		}
	return 0;
}
