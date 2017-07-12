
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 4e5+5;
char s1[N>>1],s2[N>>1],s[N];
int sa[N],rnk[N],val[N],nv[N],q[N],cnt[N],h[N],a[N];
inline bool is_same(int a,int b,int hl,int len)
{
	return val[a]==val[b]&&((a+hl>len&&b+hl>len)||(a+hl<len&&b+hl<len&&val[a+hl]==val[b+hl]));
}
void build_sa(int len,int lim)
{
	int i,j,k;
	for(i = 0;i<lim;i++)cnt[i] = 0;
	for(i = 0;i<len;i++)cnt[val[i]=s[i]]++;
	for(i = 1;i<lim;i++)cnt[i]+=cnt[i-1];
	for(i = len-1;i>= 0;i--)sa[--cnt[val[i]]] = i;
	for(int d = 1;;d++)
	{
		int hl = 1<<(d-1),id = 0;
		for(i = 0;i<len;i++)if(sa[i]+hl>=len)q[id++] = sa[i];
		for(i = 0;i<len;i++)if(sa[i]>=hl)q[id++] = sa[i]-hl;

		for(i = 0;i<lim;i++)cnt[i] = 0;
		for(i = 0;i<len;i++)cnt[val[q[i]]]++;
		for(i = 1;i<lim;i++)cnt[i]+=cnt[i-1];
		for(i = len-1;i>= 0;i--)sa[--cnt[val[q[i]]]] = q[i];

		lim = 0;
		for(i = 0;i<len;lim++)
		{
			for(j = i;j<len-1&&is_same(sa[j],sa[j+1],hl,len);j++);
			for(k = i,i=j+1;k<= j;k++)nv[sa[k]] = lim;
		}
		if(lim==len)return ;
		for(i = 0;i<len;i++)val[i] = nv[i];
	}
}
void build_height(int len)
{
	for(int i = 0;i< len;i++)rnk[sa[i]]=i;
	for(int i = 0;i< len;i++)
		if(rnk[i])
		{
			int j = 0;
			if(i)j = max(h[rnk[i-1]]-1,0);
			while(i+j<len&&sa[rnk[i]-1]+j<len&&s[i+j]==s[sa[rnk[i]-1]+j])j++;
			h[rnk[i]] = j;
		}
}
inline bool cmp(int a,int b){return h[a]>h[b];}
int fa[N];
ll st[N],en[N];
long long ans;
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x]=x;
	else return fa[x] = getfa(fa[x]);
}
void calc(int x)
{
	if(!x)return ;
	int r1 = getfa(x),r2 = getfa(x-1);
	ans+=(ll)(st[r1]*en[r2]+st[r2]*en[r1])*h[x];
	st[r1]+=st[r2],en[r1]+=en[r2],fa[r2] = r1;
}

int main()
{
	scanf("%s",s1);
	int l1 = strlen(s1);
	scanf("%s",s2);
	int l2 = strlen(s2);
	for(int i = 0;i<l1;i++)
		s[i] = s1[i];
	s[l1] = 'z'+1;
	for(int i = 0;i<l2;i++)s[i+l1+1]=s2[i];
	int len = l1+l2+1;
	build_sa(len,256);
	build_height(len);
	for(int i = 0;i<len;i++)a[i]=fa[i]=i,st[i]=(sa[i]<l1),en[i] = 1-st[i];
	sort(a,a+len,cmp);
	for(int i = 0;i<len;i++)calc(a[i]);
	printf("%lld\n",ans);
	return 0;
}
