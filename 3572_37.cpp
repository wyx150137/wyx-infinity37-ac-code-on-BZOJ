
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e5+100;
const int INF = 0x3f3f3f3f;
struct E
{int next,to;};
int size[N],fa[N][20],dep[N],dfn[N],Dfn;
struct Gragh
{
	E e[N<<1];
	int head[N],tot;
	void add(int x,int y)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x]=tot;
		e[++tot].to = x;e[tot].next = head[y];head[y]=tot;
	}
	void dfs(int x,int f)
	{
		fa[x][0] = f;
		dep[x] = dep[f]+1;
		size[x] = 1;
		dfn[x] = ++Dfn;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=f)
			{
				dfs(e[i].to,x);
				size[x]+=size[e[i].to];
			}
	}
	void init(int n)
	{
		for(int j = 1;j<= 19;j++)
			for(int i = 1;i<= n;i++)
				fa[i][j] = fa[fa[i][j-1]][j-1];
	}
	int getlca(int x,int y)
	{
		if(dep[x]<dep[y])swap(x,y);
		for(int i = 19;i>=0;i--)
			if(dep[fa[x][i]]>=dep[y])
				x = fa[x][i];
		if(x==y)return x;
		for(int i = 19;i>=0;i--)
			if(fa[x][i]!=fa[y][i])
				x = fa[x][i],y = fa[y][i];
		return fa[x][0];
	}
	int jump(int x,int h)
	{
		for(int i = 19;i>=0;i--)
			if(dep[fa[x][i]]>=h)
				x=fa[x][i];
		return x;
	}
}tree;
int h[N],stk[N],top;
bool cmp(int a,int b)
{
	return dfn[a]<dfn[b];
}
int father[N],rec[N],val[N],dis[N],ans[N],tr[N],len[N],near[N];
int main()
{
	int n;
	scanf("%d",&n);
	int x,y;
	for(int i= 1;i< n;i++)
	{
		scanf("%d%d",&x,&y);
		tree.add(x,y);
	}
	tree.dfs(1,0);
	tree.init(n);
	int q,m;
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d",&m);
		int cnt = 0;
		for(int i = 1;i<= m;i++)
		{
			scanf("%d",&h[i]);
			tr[++cnt] = h[i];
			rec[i] = near[h[i]]=h[i];
			dis[h[i]]=ans[h[i]]=0;
		}
		top = 0;
		sort(h+1,h+m+1,cmp);
		for(int i=1;i<=m;i++)
		{
			if(!top)father[stk[++top]=h[i]]=0;
			else
			{
				int lca = tree.getlca(stk[top],h[i]);
				while(dep[lca]<dep[stk[top]])
				{
					if(dep[lca]>=dep[stk[top-1]])
						father[stk[top]]=lca;
					top--;
				}
				if(stk[top]!=lca)
				{
					father[lca]=stk[top];
					stk[++top]=tr[++cnt]=lca;
					near[lca]=0,dis[lca]=INF;
				}
				father[stk[++top]=h[i]]=lca;
			}
		}
		sort(tr+1,tr+cnt+1,cmp);
		for(int i = 1;i<= cnt;i++)
		{
			val[tr[i]]=size[tr[i]];
			len[tr[i]]=dep[tr[i]]-dep[father[tr[i]]];
		}
		for(int i = cnt;i>=2;i--)
		{
			if(dis[father[tr[i]]]>dis[tr[i]]+len[tr[i]])
			{
				dis[father[tr[i]]]=dis[tr[i]]+len[tr[i]];
				near[father[tr[i]]]=near[tr[i]];
			}else if(dis[father[tr[i]]]==dis[tr[i]]+len[tr[i]])
				near[father[tr[i]]]=min(near[father[tr[i]]],near[tr[i]]);
		}
		for(int i = 2;i<= cnt;i++)
		{
			if(dis[tr[i]]>dis[father[tr[i]]]+len[tr[i]])
			{
				dis[tr[i]] = dis[father[tr[i]]]+len[tr[i]];
				near[tr[i]] = near[father[tr[i]]];
			}else if(dis[tr[i]]==dis[father[tr[i]]]+len[tr[i]])
				near[tr[i]]=min(near[father[tr[i]]],near[tr[i]]);
		}
		for(int i = 1;i<= cnt;i++)
		{
			if(i==1)ans[near[tr[i]]]=n-size[tr[i]];
			else
			{
				int x = tree.jump(tr[i],dep[father[tr[i]]]+1);
				int s = size[x]-size[tr[i]];
				val[father[tr[i]]]-=size[x];
				if(near[father[tr[i]]]==near[tr[i]])
					ans[near[tr[i]]]+=s;
				else
				{
					int num = dis[father[tr[i]]]+dis[tr[i]]+len[tr[i]]+1;
					int mid = dep[tr[i]]+dis[tr[i]]-(num+1)/2+1;
					if((num&1)&&near[tr[i]]>near[father[tr[i]]])mid++;
					x=size[x]-size[tree.jump(tr[i],mid)];
					ans[near[father[tr[i]]]]+=x;
					ans[near[tr[i]]]+=s-x;
				}
			}
		}
		for(int i = 1;i<= cnt;i++)
			ans[near[tr[i]]]+=val[tr[i]];
		for(int i = 1;i<= m;i++)
			printf("%d ",ans[rec[i]]);
		printf("\n");
	}
	return 0;
}
