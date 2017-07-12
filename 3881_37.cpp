
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define s(i) (s[i]-'a')
const int N = 2e6+5;
char s[N];
int ch[N][26],fail[N],q[N],cnt,h,t;
int s_p[N];
int c[N],Dfn,fa[N][22],dfn[N],dep[N],end[N];
struct E
{
	int next,to;
}e[N<<1];
int head[N],tot;
void add(int x,int y){e[++tot].to=y;e[tot].next=head[x];head[x]=tot;}
void update(int x,int y)
{
	for(int i = x;i<N;i+=i&(-i))
		c[i]+=y;
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=c[i];
	return ans;
}
void dfs(int x)
{
	dfn[x] = ++Dfn;
	dep[x] = dep[fa[x][0]]+1;
	for(int i = head[x];i;i=e[i].next)
	{
		fa[e[i].to][0] = x;
		dfs(e[i].to);
	}
	end[x] = Dfn;
}
void Init()
{
	for(int j = 1;j<= 21;j++)
		for(int i = 1;i<= cnt;i++)
			fa[i][j] = fa[fa[i][j-1]][j-1];
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i = 21;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x = fa[x][i];
	if(x==y)return x;
	for(int i = 21;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
void init()
{
	cnt = 1;
	for(int i = 0;i<26;i++)
		ch[0][i] = 1;
}
void insert(int id)
{
	int now = 1,i = 0;
	while(s[i])
	{
		if(!ch[now][s(i)])ch[now][s(i)]=++cnt;
		now = ch[now][s(i)];
		i++;
	}
	s_p[id] = now;
}
void build()
{
	h = 0,t = -1;
	q[++t] = 1,fail[0] = 1;
	while(h<=t)
	{
		int x = q[h++];
		for(int i = 0;i<26;i++)
		{
			int j = ch[x][i];
			if(!j)
			{
				ch[x][i]=ch[fail[x]][i];
				continue;
			}
			int k = fail[x];
			while(!ch[k][i])k = fail[k];
			fail[j] = ch[k][i];
			q[++t]=j;
			add(fail[j],j);
		}
	}
}
int st[N],top;
int match()
{
	int now = 1,i = 0,top = 0;
	while(s[i])
	{
		now = ch[now][s(i)];
		st[++top] = now;
		i++;
	}
	return top;
}
bool cmp(int a,int b)
{
	return dfn[a]<dfn[b];
}
int main()
{
	int n;
	scanf("%d",&n);
	init();
	for(int i= 1;i<= n;i++)
	{
		scanf("%s",s);
		insert(i);
	}
	build();
	dfs(1);
	Init();
	int q;
	scanf("%d",&q);
	int opt,x;
	while(q--)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%s",s);
			int lth = match();
			sort(st+1,st+lth+1,cmp);
			top = 0;
			for(int i = 1;i<= lth;i++)
				if(st[top]!=st[i])
					st[++top] = st[i];
			lth = top;
			for(int i = 1;i<= lth;i++)
			{
				update(dfn[st[i]],1);
				if(i>1)update(dfn[getlca(st[i-1],st[i])],-1);
			}
		}else
		{
			scanf("%d",&x);
			x=s_p[x];
			printf("%d\n",getans(end[x])-getans(dfn[x]-1));
		}
	}
	return 0;
}
