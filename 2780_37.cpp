
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 200005;
int id[N],Dfn,in[N],out[N];
int c[N];
struct E
{int next,to;};
struct Gragh
{
	E e[N];
	int head[N],tot;
	void add(int x,int y){e[++tot].to=y;e[tot].next=head[x];head[x]=tot;}
	void dfs(int x)
	{
		id[++Dfn] = x;
		in[x] = Dfn;
		for(int i = head[x];i;i=e[i].next)
			dfs(e[i].to);
		out[x] = Dfn;
	}
}g1,g2;
int trs[N][26],len[N],fa[N],lastins[N],ans[N];
int cnt,last;
int insert(int x)
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
			for(;p&&trs[p][x]==q;p=fa[p])trs[p][x] = nq;
		}
	}else
	{
		int np = ++cnt,q,nq;
		last = np;len[np] = len[p]+1;
		for(;p&&!trs[p][x];p=fa[p])trs[p][x]=np;
		if(!p)fa[np]=1;
		else
		{
			q = trs[p][x];
			if(len[q]==len[p]+1)fa[np] = q;
			else
			{
				fa[nq=++cnt]=fa[q];
				len[nq]=len[p]+1;
				memcpy(trs[nq],trs[q],sizeof(trs[q]));
				fa[np] = fa[q] = nq;
				for(;p&&trs[p][x]==q;p=fa[p])trs[p][x]=nq;
			}
		}
	}
	return last;
}
void init(){last=cnt=1;}
void build()
{
	for(int i = 1;i<= cnt;i++)
		g1.add(fa[i],i);
	g1.dfs(1);
}
struct Ask
{
	int l,r,no;
	bool operator<(const Ask &S)const
	{
		return r<S.r;
	}
}ask[N];
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
char s[360005];
int main()
{
	int n,q;
	init();
	scanf("%d%d",&n,&q);
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",s+1);
		int l = strlen(s+1);
		last = 1;
		for(int j = 1;j<= l;j++)
		{
			int tmp = insert(s[j]-'a');
			g2.add(tmp,i);
		}
	}
	build();
	for(int i = 1;i<= q;i++)
	{
		scanf("%s",s+1);
		int l = strlen(s+1),p=1;
		bool find = true;
		for(int j=1;j<=l;j++)
			if(!trs[p][s[j]-'a']){find = false;break;}
			else p = trs[p][s[j]-'a'];
		if(find)
			ask[i] = (Ask){in[p],out[p],i};
		else ask[i] = (Ask){-1,-1,i};
	}
	sort(ask+1,ask+q+1);
	int noww;
	int k=1;
	while(k<=q&&ask[k].l==-1)
		k++;
	for(int i=1;i<=cnt;i++)
	{
		for(int j=g2.head[id[i]];j;j=g2.e[j].next)
		{
			noww=g2.e[j].to;
			update(i,1);
			if(lastins[noww])
				update(lastins[noww],-1);
			lastins[noww]=i;
		}
		for(;ask[k].r==i;k++)
			ans[ask[k].no]=getans(ask[k].r)-getans(ask[k].l-1);
	}
	for(int i = 1;i<= q;i++)printf("%d\n",ans[i]);
	return 0;
}
