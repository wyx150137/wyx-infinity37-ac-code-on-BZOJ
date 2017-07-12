
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 3e5+5;
const int Asiz = 1005;
const int Siz = 300;
const int maxA = 1e6+5;
int cnt[maxA],bcnt[Asiz][2];
struct E
{int next,to;}e[M];
int head[N],tot=1,A[N],a[N];
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int dfn[N],DFN[N],low[N],seq[N],Dfn,size[N];
void dfs(int x,int pre)
{
	DFN[x] = low[x] = ++Dfn;
	seq[Dfn] = x;
	for(int i = head[x];i;i=e[i].next)if(pre^1^i)
	{
		if(!DFN[e[i].to])
		{
			dfs(e[i].to,i);
			low[x] = min(low[e[i].to],low[x]);
		}else 
			low[x] = min(low[e[i].to],DFN[x]);
	}
}
void dfs2(int x,int pre)
{
	size[x] = 1;
	dfn[x] = ++Dfn;
	for(int i = head[x];i;i=e[i].next)if(pre^1^i)
	{
		if(!dfn[e[i].to]&&low[e[i].to]>=DFN[x])
		{
			dfs2(e[i].to,i);
			if(low[e[i].to]>DFN[x])
				size[x]+=size[e[i].to];
		}
	}
	for(int i = head[x];i;i=e[i].next)if(pre^1^i)
	{
		if(!dfn[e[i].to]&&low[e[i].to]<DFN[x])
			dfs2(e[i].to,i);
	}
	if(low[x]!=DFN[x])
		size[seq[low[x]]]+=size[x];
}
struct Ask
{
	int l,r,pl;
	int o,p,id;
	bool operator <(const Ask &s)const
	{
		return pl<s.pl||pl==s.pl&&r<s.r;
	}
}ask[N];
int ans[N];
void Delete(int x)
{
	int tx = (a[x]-1)/Asiz+1;
	bcnt[tx][cnt[a[x]]&1]--;
	cnt[a[x]]--;
	if(cnt[a[x]])
		bcnt[tx][cnt[a[x]]&1]++;
}
void Insert(int x)
{
	int tx = (a[x]-1)/Asiz+1;
	if(cnt[a[x]])
		bcnt[tx][cnt[a[x]]&1]--;
	cnt[a[x]]++;
	bcnt[tx][cnt[a[x]]&1]++;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&A[i]);
	int x,y;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,0);
	Dfn = 0;
	dfs2(1,0);
	for(int i = 1;i<= n;i++)a[dfn[i]]=A[i];
	int q;
	scanf("%d",&q);
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d%d",&ask[i].o,&ask[i].l,&ask[i].p);
		ask[i].r = dfn[ask[i].l]+size[ask[i].l]-1;
		ask[i].l = dfn[ask[i].l];
		ask[i].pl = ask[i].l/Siz;
		ask[i].id = i;
	}
	sort(ask+1,ask+q+1);
	int L = 1,R = 0;
	for(int i = 1;i<= q;i++)
	{
		while(L<ask[i].l)Delete(L),L++;
		while(L>ask[i].l)L--,Insert(L);
		while(R<ask[i].r)R++,Insert(R);
		while(R>ask[i].r)Delete(R),R--;
		x=(ask[i].p-1)/Asiz+1;
		for(int j = 1;j< x;j++)
			ans[ask[i].id]+=bcnt[j][ask[i].o];
		for(int j = (x-1)*Asiz+1;j<= ask[i].p;j++)
			if(cnt[j]&&(cnt[j]&1)==ask[i].o)
				ans[ask[i].id]++;
	}
	for(int i = 1;i<= q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
