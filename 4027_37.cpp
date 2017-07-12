
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2000005;
int top,c[N],k[N],val[N],n,m,ans;
int stack[N];
bool cmp(int a,int b)
{
	return val[a]<val[b];
}
struct E
{int next,to;}e[N];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
void dfs(int x)
{
	for(int i = head[x];i;i = e[i].next)
		dfs(e[i].to);
	top = 0;
	for(int i= head[x];i;i = e[i].next)
		stack[++top] = e[i].to;
	sort(stack+1,stack+top+1,cmp);
	for(int i = 1;i<= top;i++)
	{
		if(val[x]+val[stack[i]]-1<=m)
		{
			ans++;
			val[x]+=val[stack[i]]-1;
		}else break;
	}
}
int main()
{
	int x;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		scanf("%d",&c[i]);
	for(int i = 1;i<=n;i++)
	{
		scanf("%d",&k[i]);
		val[i] = k[i]+c[i];
		for(int j = 1;j<= k[i];j++)
		{
			scanf("%d",&x);
			add(i,x+1);
		}
	}
	dfs(1);
	printf("%d\n",ans);
	return 0;
}
