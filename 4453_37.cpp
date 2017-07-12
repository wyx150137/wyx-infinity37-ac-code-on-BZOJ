
#include <stdio.h>
#include <set>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
char s[N];
int len;
namespace SA
{
	int sa[N],val[N],nv[N],h[N],rnk[N],cnt[N],q[N];
	bool is_same(int a,int b,int hl,int len)
	{
		return val[a]==val[b]&&((a+hl>len&&b+hl>len)||(a+hl<len&&b+hl<len&&val[a+hl]==val[b+hl]));
	}
	void build_sa(int lim,int len)
	{
		int i,j,k;
		for(i = 0;i<lim;i++)cnt[i] = 0;
		for(i = 0;i<len;i++)cnt[val[i]=s[i]]++;
		for(i = 1;i<lim;i++)cnt[i]+=cnt[i-1];
		for(i = len-1;i>= 0;i--)sa[--cnt[val[i]]] = i;
		for(int d = 1;;d++)
		{
			int hl = 1<<(d-1);
			int id = 0;
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
				for(k = i,i = j+1;k<=j;k++)nv[sa[k]] = lim;
			}
			for(i = 0;i<len;i++)val[i] = nv[i];
			if(lim==len)break;
		}
	}
	void build_rank(int len)
	{
		for(int i = 0;i<len;i++)
			rnk[sa[i]] = i;
	}
	void build_height(int len)
	{
		for(int i = 0;i<len;i++)
			if(rnk[i])
			{
				int j = 0;
				if(i)j = max(h[rnk[i-1]]-1,0);
				while(i+j<len&&sa[rnk[i]-1]+j<len&&s[i+j]==s[sa[rnk[i]-1]+j])
					j++;
				h[rnk[i]] = j;
			}
	}
	int st[N][20];
	int lg2[N];
	void build_st(int len)
	{
		for(int i = 2;i<N;i++)
			lg2[i] = lg2[i>>1]+1;
		for(int i = 0;i<len;i++)
			st[i][0] = h[i];
		for(int j = 1;j<= 18;j++)
			for(int i = 0;i+(1<<(j-1))<=len;i++)
				st[i][j] = min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	}
	int lcp(int i,int j)
	{
		i = rnk[i],j = rnk[j];
		if(i>j)swap(i,j);
		i++;
		int lth = lg2[j-i+1];
		return min(st[i][lth],st[j-(1<<lth)+1][lth]);
	}
}
struct E{int next,to,id;};
struct List
{
	E e[N];
	int h[N],tot;
	void insert(int x,int y)
	{
		e[++tot].to = y;
		e[tot].next = h[x];
		h[x] = tot;
	}
}g,list;
struct Q
{int next,to,id;}q[N];
int head[N],tot;
void addq(int x,int y,int id)
{
	q[++tot].to = y;
	q[tot].next = head[x];
	q[tot].id = id;
	head[x] = tot;
}
int vis[N];
set<int>S;
void dfs(int x)
{
	vis[x] = 1;
	S.erase(x);
	for(int i = g.h[x];i;i=g.e[i].next)
	{
		int to = g.e[i].to;
		if(vis[to])continue;
		dfs(to);
	}
}
int stack[N],top,ans[N];
void solve()
{
	for(int r = 0;r< len;r++)
	{
		S.insert(r);
		while(top)
		{
			int lth = SA::lcp(r,stack[top]);
			if(s[r+lth]<s[stack[top]+lth])break;
			list.insert(r+lth,stack[top]);
			g.insert(r,stack[top]);
			top--;
		}
		stack[++top] = r;
		for(int i = list.h[r];i;i=list.e[i].next)
		{
			int to = list.e[i].to;
			if(!vis[to])dfs(to);
		}
		for(int i = head[r];i;i=q[i].next)
			ans[q[i].id] = *S.lower_bound(q[i].to);
	}
}
int main()
{
	scanf("%s",s);
	len = strlen(s);
	SA::build_sa(255,len);
	SA::build_rank(len);
	SA::build_height(len);
	SA::build_st(len);
	int q,l,r;
	scanf("%d",&q);
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d",&l,&r);
		l--,r--;
		addq(r,l,i);
	}
	solve();
	for(int i = 1;i<= q;i++)printf("%d\n",ans[i]+1);
	return 0;
}
