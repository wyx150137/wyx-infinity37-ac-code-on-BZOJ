
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 6e4+5;
char s[N];
int cnt[N],q[N],v[N],nv[N],sa[N],rnk[N],h[N];
bool is_same(int a,int b,int hl,int len)
{
	return v[a]==v[b]&&((a+hl>len&&b+hl>len)||(a+hl<len&&b+hl<len&&v[a+hl]==v[b+hl]));
}
void build_sa(int lim,int len)
{
	int i,j,k;
	for(i = 0;i<lim;i++)cnt[i]=0;
	for(i = 0;i<len;i++)cnt[v[i]=s[i]]++;
	for(i = 1;i<lim;i++)cnt[i]+=cnt[i-1];
	for(i = len-1;i>=0;i--)sa[--cnt[v[i]]]=i;
	for(int d = 1;;d++)
	{
		int hl=1<<(d-1),id = 0;
		for(i=len-hl;i<len;i++)q[id++]=i;
		for(i = 0;i<len;i++)if(sa[i]>=hl)q[id++]=sa[i]-hl;

		for(i=0;i<lim;i++)cnt[i]=0;
		for(i=0;i<len;i++)cnt[v[q[i]]]++;
		for(i=1;i<lim;i++)cnt[i]+=cnt[i-1];
		for(i=len-1;i>=0;i--)sa[--cnt[v[q[i]]]]=q[i];

		lim = 0;
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
int main()
{
	int n;
	char ch;
	scanf("%d",&n);
	for(int i = 0;i<n;i++)
	{
		ch = getchar();while(ch<'A'||ch>'Z')ch = getchar();
		s[i]=ch;
	}
	int len = n;
	s[len]='$';
	for(int i = n-1;i>=0;i--)
		s[++len]=s[i];
	len++;
	build_sa(256,len);
	build_rank(len);
	int l = 0,r = n+1;
	for(int i = 0;i<n;i++)
	{
		if(r>=len||rnk[l]<rnk[r])
			{printf("%c",s[l]);l++;}
		else {printf("%c",s[r]);r++;}
		if(i%80==79)printf("\n");
	}
	return 0;
}
