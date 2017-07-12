
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int S = 1e6+5;
struct E
{int next,to;char ch[15];}e[N<<1];
int head[N],tot;
char str[N][15];
void add(int x,int y,char *CH)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	memcpy(e[tot].ch+1,CH+1,sizeof(char)*strlen(CH+1));
	head[x] = tot;
}
int son[N],size[N],top[N],dep[N],id[N],w[N],fa[N],cnt,n;
void dfs(int x)
{
	dep[x] = dep[fa[x]]+1;
	size[x] = 1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x])
		{
			fa[e[i].to] = x;
			memcpy(str[e[i].to]+1,e[i].ch+1,sizeof(char)*strlen(e[i].ch+1));
			dfs(e[i].to);
			size[x]+=size[e[i].to];
			if(size[e[i].to]>size[son[x]])son[x] = e[i].to;
		}
}
void Dfs(int x,int tp)
{
	top[x] = tp;
	w[x] = ++cnt;
	id[cnt] = x;
	if(son[x])Dfs(son[x],tp);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=son[x]&&e[i].to!=fa[x])
			Dfs(e[i].to,e[i].to);
}
struct Trie
{
	int cnt;
	int son[S][27],sum[S],root[N];
	int insert(int x,char *ch)
	{
		int tmp = ++cnt,y = cnt,len = strlen(ch+1);
		for(int i = 1;i<= len;i++)
		{
			int p = ch[i]-'a'+1;
			for(int j = 0;j<= 26;j++)
				son[y][j] = son[x][j];
			sum[y] = sum[x]+1;
			son[y][p] = ++cnt;
			x = son[x][p],y = son[y][p];
		}
		sum[y] = sum[x]+1;
		return tmp;
	}
	int getans(int l,int r,char *ch)
	{
		int x = root[l-1],y = root[r],len = strlen(ch+1);
		for(int i = 1;i<= len;i++)
		{
			int p = ch[i]-'a'+1;
			x = son[x][p],y = son[y][p];
		}
		return sum[y]-sum[x];
	}
	void build()
	{
		cnt = 1;
		for(int i = 2;i<= n;i++)
			root[i] = insert(root[i-1],str[id[i]]);
	}
}trie;
void ask(int x,int y,char *ch)
{
	int ans = 0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=trie.getans(w[top[x]],w[x],ch);
		x = fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	ans+=trie.getans(w[y]+1,w[x],ch);
	printf("%d\n",ans);
}
int main()
{
	int m,x,y;
	char s[15];
	scanf("%d",&n);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%s",&x,&y,s+1);
		add(x,y,s),add(y,x,s);
	}
	dfs(1);
	Dfs(1,1);
	trie.build();
	scanf("%d",&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%s",&x,&y,s+1);
		ask(x,y,s);
	}
	return 0;
}
/*
4
1 2 ab
2 4 ac
1 3
bc
3
1 4 a
3 4 b
3 2 ab
*/
