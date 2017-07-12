
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 300005;
typedef long long ll;
int sa[N],cnt[N],val[N],nv[N],q[N],h[N],rnk[N];
char s[N];
bool is_same(int a,int b,int hl,int len)
{
	return val[a]==val[b]&&((a+hl>len&&b+hl>len)||(a+hl<len&&b+hl<len&&val[a+hl]==val[b+hl]));
}
void build_sa(int lim,int len)
{
	int i,j,k;
	for(i = 0;i<lim;i++)cnt[i]=0;
	for(i = 0;i<len;i++)cnt[val[i]=s[i]-'a']++;
	for(i = 1;i<lim;i++)cnt[i]+=cnt[i-1];
	for(i = len-1;i>= 0;i--)sa[--cnt[val[i]]]=i;
	for(int d = 1;;d++)
	{
		int hl = 1<<(d-1),id = 0;
		for(i = 0;i<len;i++)if(sa[i]+hl>=len)q[id++] = sa[i];
		for(i = 0;i<len;i++)if(sa[i]>=hl)q[id++]=sa[i]-hl;
		
		for(i =0;i<lim;i++)cnt[i]=0;
		for(i = 0;i<len;i++)cnt[val[q[i]]]++;
		for(i = 1;i<lim;i++)cnt[i]+=cnt[i-1];
		for(i = len-1;i>=0;i--)sa[--cnt[val[q[i]]]]=q[i];

		lim = 0;
		for(i = 0;i<len;lim++)
		{
			for(j = i;j<len-1&&is_same(sa[j],sa[j+1],hl,len);j++);
			for(k=i,i=j+1;k<=j;k++)nv[sa[k]]=lim;
		}
		if(lim==len)return ;
		for(i = 0;i<len;i++)val[i] = nv[i];
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
			if(i)j = max(0,h[rnk[i-1]]-1);
			while(i+j<len&&sa[rnk[i]-1]+j<len&&s[i+j]==s[sa[rnk[i]-1]+j])
				j++;
			h[rnk[i]]=j;
		}
}
int fa[N],size[N],n;
ll mx[N],mn[N],a[N];
ll tot,ans;
ll Ans[N][2];
void init()
{
	for(int i = 0;i<n;i++)
		fa[i]=i,mx[i]=mn[i]=a[sa[i]],size[i]=1;
}
int getfa(int x)
{
	if(fa[x]==x)return fa[x];
	else return fa[x]=getfa(fa[x]);
}
void uni(int x,int y)
{
	x = getfa(x),y = getfa(y);
	if(x==y)return ;
	if(x>y)swap(x,y);
	ll tmp = max(mx[x]*mx[y],mn[x]*mn[y]);
	if(tmp>ans||!tot)ans = tmp;
	tot+=(ll)size[x]*size[y];
	fa[y] = x;
	mx[x] = max(mx[x],mx[y]),mn[x] =min(mn[x],mn[y]);
	size[x] = size[x]+size[y];
}
vector<int>Q[N];
int main()
{
	scanf("%d",&n);scanf("%s",s);
	for(int i = 0;i<n;i++)scanf("%lld",&a[i]);
	build_sa(26,n);
	build_rank(n);
	build_height(n);
	init();
	for(int i = 1;i<=n;i++)
		Q[h[i]].push_back(i);
	for(int i = n-1;i>= 0;i--)
	{
		for(int j = 0;j<Q[i].size();j++)
			uni(Q[i][j],Q[i][j]-1);
		Ans[i][0]=tot,Ans[i][1] = ans;
	}
	for(int i = 0;i<n;i++)
		printf("%lld %lld\n",Ans[i][0],Ans[i][1]);
	return 0;
}
