
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 250010;
typedef long long ll;
struct E
{int next,to,val;};
int dep[N],fa[N][22],dfn[N],Dfn;
vector<int>to[N];
vector<int>val[N];
ll f[N],mn[N];
int stack[N],top,num[N];
struct Gragh
{
	E e[N<<1];
	int head[N],tot;
	void add(int x,int y,int f)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x]=tot;e[tot].val=f;
		e[++tot].to = x;e[tot].next = head[y];head[y]=tot;e[tot].val=f;
	}
	void dfs(int x,int f,int dp)
	{
		fa[x][0] = f;
		dep[x] = dp;
		dfn[x] = ++Dfn;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=f)
			{
				mn[e[i].to] = min(mn[x],(ll)e[i].val);
				dfs(e[i].to,x,dp+1);
			}
	}
	void init(int n)
	{
		for(int j = 1;j<= 21;j++)
			for(int i = 1;i<= n;i++)
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
}tree;
bool cmp(int a,int b)
{
	return dfn[a]<dfn[b];
}
void add(int x,int y)
{
	if(x==y)return ;
	to[x].push_back(y);
	to[y].push_back(x);
}
void dfs(int x,int ff)
{
	ll tmp = 0;
	int sz = to[x].size();
	f[x] = mn[x];
	for(int i = 0;i<sz;i++)
	{
		int t = to[x][i];
		if(t!=ff)
		{
			dfs(t,x);
			tmp+=f[t];
		}
	}
	if(tmp&&tmp<=f[x])f[x]=tmp;
	to[x].clear();
}
int main()
{
	int n,m,k;
	scanf("%d",&n);
	int x,y,c;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&c);
		tree.add(x,y,c);
	}
	mn[1]=1ll<<60;
	tree.dfs(1,0,1);
	tree.init(n);
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d",&k);
		for(int i = 1;i<= k;i++)
			scanf("%d",&num[i]);
		sort(num+1,num+k+1,cmp);
		int tmp = k;
		num[k=1] = num[1];
		for(int i = 2;i<= tmp;i++)
			if(tree.getlca(num[k],num[i])!=num[k])
				num[++k]=num[i];
		top = 0;
		stack[++top]=1;
		for(int i = 1;i<= k;i++)
		{
			int v = num[i];
			int lca = tree.getlca(stack[top],v);
			while(true)
			{
				if(dep[lca]>=dep[stack[top-1]])
					{add(lca,stack[top--]);break;}
				add(stack[top-1],stack[top]);
				top--;
			}
			if(stack[top]!=lca)stack[++top]=lca;
			if(stack[top]!=v)stack[++top] = v;
		}
		for(int i = 1;i<=top-1;i++)
			add(stack[i],stack[i+1]);
		dfs(1,0);
		printf("%lld\n",f[1]);
	}
	return 0;
}
