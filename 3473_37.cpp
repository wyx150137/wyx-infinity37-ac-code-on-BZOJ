
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2e5+5;
char s[N];
struct E{int next,to;};
int id[N],in[N],out[N],Dfn,num[N],n,k,to[N];
ll ans[N];
int last,cnt;
int trs[N][26],fa[N],len[N];
vector<int>ed[N];
bool v[N];
struct Gragh
{
	E e[N];
	int head[N],tot;
	void add(int x,int y)
	{
		e[++tot].to = y;
		e[tot].next = head[x];
		head[x] = tot;
	}
	void dfs(int x)
	{
		id[++Dfn] = x;
		in[x] = Dfn;
		for(int i = head[x];i;i=e[i].next)
			dfs(e[i].to);
		out[x] = Dfn;
	}
	void getans(int x,ll Ans)
	{
		if(num[x]>=k)Ans+=len[x]-len[fa[x]];
		for(int i = 0;i<ed[x].size();i++)
			ans[ed[x][i]]+=Ans;
		for(int i = head[x];i;i=e[i].next)
			getans(e[i].to,Ans);
	}
}g1,g2;
void init(){last=cnt=1;}
int insert(int x,int y)
{
	int p = last;
	if(trs[p][x])
	{
		int q = trs[p][x];
		if(len[q]==len[p]+1)last = q;
		else
		{
			int nq = ++cnt;
			last = nq;
			fa[nq] = fa[q];len[nq]=len[p]+1;
			memcpy(trs[nq],trs[q],sizeof(trs[q]));
			fa[q] = nq;
			for(;p&&trs[p][x]==q;p=fa[p])trs[p][x]=nq;
		}
	}else
	{
		int np = ++cnt,q,nq;
		last = np;len[np] = len[p]+1;
		for(;p&&!trs[p][x];p=fa[p])trs[p][x]=np;
		if(!p)fa[np] = 1;
		else
		{
			q = trs[p][x];
			if(len[q]==len[p]+1)fa[np] = q;
			else
			{
				fa[nq=++cnt]=fa[q];
				len[nq] = len[p]+1;
				memcpy(trs[nq],trs[q],sizeof(trs[q]));
				fa[np] = fa[q] = nq;
				for(;p&&trs[p][x]==q;p=fa[p])trs[p][x] = nq;
			}
		}
	}
	ed[last].push_back(y);
	return last;
}
void build()
{
	for(int i = 1;i<= cnt;i++)
		g1.add(fa[i],i);
	g1.dfs(1);
}
int c[N];
void update(int x,int y)
{
	for(int i = x;i<=cnt;i+=i&(-i))
		c[i]+=y;
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=c[i];
	return ans;
}
int lst[N];
struct Ask
{
	int l,r,no;
	bool operator<(const Ask &s)const
	{
		return r<s.r;
	}
}ask[N];
int pos[N];
int main()
{
	scanf("%d%d",&n,&k);
	init();
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",s+1);
		int l = strlen(s+1);
		last = 1;
		for(int j = 1;j<= l;j++)
		{
			int tmp=insert(s[j]-'a',i);
			g2.add(tmp,i);
		}
	}
	build();
	for(int i = 1;i<=cnt;i++)
		ask[i] = (Ask){in[i],out[i],i};
	sort(ask+1,ask+cnt+1);
	int tt = 1;
	for(int i = 1;i<= cnt;i++)
	{
		for(int j = g2.head[id[i]];j;j=g2.e[j].next)
		{
			int p = g2.e[j].to;
			if(lst[p])update(lst[p],-1);
			update(i,1);
			lst[p] = i;
		}
		for(;ask[tt].r==i;tt++)
			num[ask[tt].no]=getans(ask[tt].r)-getans(ask[tt].l-1);
	}
	g1.getans(1,0);
	for(int i = 1;i<= n;i++)
		printf("%lld ",ans[i]);
	printf("\n");
	return 0;
}
