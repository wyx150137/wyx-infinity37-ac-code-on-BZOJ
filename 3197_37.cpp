
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int sed = 237;
const int mul = 213;
const int N = 705;
const int INF = 0x3f3f3f3f;
int f[N][N],f1[N],f2[N],root,cg[2],n;
ull hash[N];
bool cmp(int x,int y)
{
	return hash[x]<hash[y];
}
namespace Tree
{
	struct E
	{int next,to;}e[N<<1];
	int head[N],tot,size[N],fa[N];
	void add(int x,int y)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
		e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
	}
	void Get_G(int x,int father)
	{
		size[x] = 1;int F=0;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=father)
			{
				Get_G(e[i].to,x);
				size[x]+=size[e[i].to];
				F = max(F,size[e[i].to]);
			}
		F = max(F,n-size[x]);
		if(!(F<<1>n))
		{
			if(cg[0])cg[1] = x;
			else cg[0] = x;
		}
	}
	int dep[N];
	void Get_Hash(int x)
	{
		dep[x] = dep[fa[x]]+1;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=fa[x])
			{
				fa[e[i].to] = x;
				Get_Hash(e[i].to);
			}
		static int stack[N],top;
		top = 0;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=fa[x])
				stack[++top] = e[i].to;
		sort(stack+1,stack+top+1,cmp);
		hash[x] = sed;
		for(int i = 1;i<= top;i++)
		{
			hash[x] = hash[x]*mul+hash[stack[i]];
			hash[x] = hash[x]^hash[stack[i]];
			hash[x] = hash[x]+hash[stack[i]];
		}
	}
}
namespace Flow
{
	struct E
	{int next,to,f,c,from;}e[N*N<<1];
	int head[N<<1],tot,ans,from[N<<1];
	void add(int x,int y,int f,int c)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].from = x;
		e[tot].f = f;e[tot].c = c;
		e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].from = y;
		e[tot].f = 0;e[tot].c = -c;
	}
	void init()
	{
		memset(head,0,sizeof(head));
		tot = 1;ans = 0;
	}
	int dis[N<<1];bool vis[N<<1];
	queue<int>Q;
	bool spfa(int S,int T)
	{
		for(int i = S;i<= T;i++)dis[i] = INF;
		dis[S] = 0;vis[S] = true;
		Q.push(S);
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			vis[x] = false;
			for(int i = head[x];i;i=e[i].next)
				if(e[i].f&&dis[e[i].to]>dis[x]+e[i].c)
				{
					dis[e[i].to] = dis[x]+e[i].c;
					from[e[i].to] = i;
					if(!vis[e[i].to])
					{
						Q.push(e[i].to);
						vis[e[i].to] = true;
					}
				}
		}
		return dis[T]!=INF;
	}
	void mcf(int S,int T)
	{
		int x = INF;
		for(int i = from[T];i;i=from[e[i].from])
			x = min(x,e[i].f);
		for(int i = from[T];i;i=from[e[i].from])
			ans+=x*e[i].c,e[i].f-=x,e[i^1].f+=x;
	}
	int getmcf(int S,int T)
	{
		while(spfa(S,T))mcf(S,T);
		return ans;
	}
}
int solve(int x,int y)
{
	static int stack1[N],stack2[N];
	int top1 = 0,top2 = 0;
	for(int i = Tree::head[x];i;i=Tree::e[i].next)
		if(Tree::e[i].to!=Tree::fa[x])
			stack1[++top1]=Tree::e[i].to;
	for(int i = Tree::head[y];i;i=Tree::e[i].next)
		if(Tree::e[i].to!=Tree::fa[y])
			stack2[++top2]=Tree::e[i].to;
	sort(stack1+1,stack1+1+top1,cmp);
	sort(stack2+1,stack2+1+top2,cmp);
	Flow::init();
	int j;
	for(int i = 1;i<= top1;i=j)
	{
		for(j=i+1;j<=top1&&hash[stack1[i]]==hash[stack1[j]];j++);
		for(int k=i;k<j;k++)
			for(int l=i;l<j;l++)
				Flow::add(k,top1+l,1,f[stack1[k]][stack2[l]]);
	}
	int S = 0,T = 2*n+1;
	for(int i = 1;i<= top1;i++)
	{
		Flow::add(S,i,1,0);
		Flow::add(i+top1,T,1,0);
	}
	return Flow::getmcf(S,T)+(f1[x]^f2[y]);
}
pair<pair<int,ull>,int> sorter[N]; 
int main()
{
	int x,y;
	scanf("%d",&n);
	Tree::tot = 1;
	for(int i = 1;i< n;i++)
	{
		scanf("%d%d",&x,&y);
		Tree::add(x,y);
	}
	for(int i = 1;i<= n;i++)scanf("%d",&f1[i]);
	for(int i = 1;i<= n;i++)scanf("%d",&f2[i]);
	Tree::Get_G(1,0);
	if(cg[1])
	{
		root = ++n;
		for(int i = Tree::head[cg[1]];i;i=Tree::e[i].next)
			if(Tree::e[i].to==cg[0])
			{
				Tree::e[i].to = Tree::e[i^1].to = n;
				break;
			}
		Tree::add(root,cg[0]);
		Tree::add(root,cg[1]);
	}else root = cg[0];
	Tree::Get_Hash(root);
	for(int i = 1;i<= n;i++)
		sorter[i] = make_pair(make_pair(-Tree::dep[i],hash[i]),i);
	sort(sorter+1,sorter+n+1);
	int j;
	for(int i = 1;i<= n;i=j)
	{
		for(j=i+1;j<=n&&sorter[i].first==sorter[j].first;j++);  
        for(int x=i;x<j;x++)  
            for(int y=i;y<j;y++)  
                f[sorter[x].second][sorter[y].second]=solve(sorter[x].second,sorter[y].second);  
	}
	printf("%d\n",f[root][root]);
	return 0;
}
