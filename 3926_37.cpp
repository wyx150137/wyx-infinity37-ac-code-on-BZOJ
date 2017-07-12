
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 4e6+5;
struct E
{int next,to;};
E e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int ch[M][10],fa[M],len[M],last,cnt;
int insert(int p,int x)
{
	int np = ++cnt,q,nq;
	last = np,len[np] = len[p]+1;
	for(;p&&!ch[p][x];p = fa[p])ch[p][x] = np;
	if(!p)fa[np] = 1;
	else
	{
		q = ch[p][x];
		if(len[q]==len[p]+1)fa[np] = q;
		else
		{
			fa[nq=++cnt] = fa[q];
			len[nq] = len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[q]));
			fa[np] = fa[q] = nq;
			for(;p&&ch[p][x]==q;p=fa[p])ch[p][x]=nq;
		}
	}
	return last;
}
long long ans;
void solve()
{
	for(int i=1;i<= cnt;i++)
		ans+=len[i]-len[fa[i]];
}
int id[N],val[N],ind[N];
void dfs(int x,int f,int p)
{
	int t = insert(p,val[x]);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=f)
			dfs(e[i].to,x,t);
}
int main()
{
	int n,c,x,y;
	scanf("%d%d",&n,&c);
	for(int i = 1;i<= n;i++)scanf("%d",&val[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
		ind[x]++,ind[y]++;
	}
	id[0] = 1;
	cnt = 1;
	for(int i = 1;i<= n;i++)
		if(ind[i]==1)
			dfs(i,0,1);
	solve();
	printf("%lld\n",ans);
	return 0;
}
