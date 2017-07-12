
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
struct E
{int next,to;}e[N<<1];
int head[N],tot,c[N],g[N],mrk[N],Ans[N];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
	c[y]--;
}
int ans = 0;
void dfs(int x,int fa)
{
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
		{
			dfs(e[i].to,x);
			int tmp = min(c[x],c[e[i].to]);
			c[x]-=tmp,c[e[i].to]-=tmp,ans+=tmp<<1;
			if(c[e[i].to])g[x]=e[i].to;
		}
}
void solve(int x,int fa)
{
	Ans[x]=ans;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
		{
			if(c[x]){c[x]--,ans++,mrk[x]=0;}
			else if(g[e[i].to]){c[g[e[i].to]]--,ans++,mrk[x]=1;}
			else {c[e[i].to]++,ans--,mrk[x]=2;}
			solve(e[i].to,x);
			if(mrk[x]==0){c[x]++,ans--;}
			else if(mrk[x]==1){c[g[e[i].to]]++,ans--;}
			else {c[e[i].to]--,ans++;}
		}
}
int main()
{
	int n,x,y;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&c[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		x++,y++;
		add(x,y),add(y,x);
	}
	ans = (n-1)<<1;
	dfs(1,0);solve(1,0);
	for(int i = 1;i<= n;i++)
		printf("%d\n",Ans[i]);
	return 0;
}
