
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
struct E
{int next,to,val;}e[N<<1];
int head[N],tot = 1;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val = 1;
	head[x] = tot;
}
int max_dep,end;
int pre[N],prp[N];
void dfs(int x,int fa,int pe,int dep)
{
	pre[x] = pe;
	prp[x] = fa;
	if(dep>max_dep)
	{
		max_dep = dep;
		end = x;
	}
	for(int i = head[x];i;i =e[i].next)
		if(e[i].to!=fa)
			dfs(e[i].to,x,i,dep+e[i].val);
}
int md[N],stack[N],top;
bool cmp(int a,int b){return a>b;}
void dp(int x,int fa)
{
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
		{
			dp(e[i].to,x);
			md[x] = max(md[x],md[e[i].to]+e[i].val);
		}
	top = 0;
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa&&md[e[i].to]+e[i].val>=0)
			stack[++top] = md[e[i].to]+e[i].val;
	sort(stack+1,stack+top+1,cmp);
	if(top>=2)max_dep = max(max_dep,stack[1]+stack[2]);
	else if(top>=1)max_dep = max(max_dep,stack[1]);
}
int main()
{
	int n,k,x,y;
	scanf("%d%d",&n,&k);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1,0,0,0);
	int tmp = end;
	max_dep = 0;
	dfs(end,0,0,0);
	int len1 = max_dep;
	if(k==1)printf("%d\n",2*(n-1)-max_dep+1);
	else
	{
		max_dep = 0;
		while(tmp!=end)
		{
			e[pre[end]].val = -1;
			e[pre[end]^1].val = -1;
			end = prp[end];
		}
		dp(1,0);
		printf("%d\n",2*(n-1)-len1+1-max_dep+1);
	}
	return 0;
}
