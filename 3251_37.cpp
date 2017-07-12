
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N=100005;
long long a[N];
struct E
{int next,to;}e[N<<1];
int head[N],tot,n,q,fa[N];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int dep[N];
void dfs(int x,int f)
{
	fa[x] = f;
	dep[x] = dep[f]+1;
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=f)
			dfs(e[i].to,x);
}
long long stack[100];
int top;
bool getans(int x,int y)
{
	top = 0;
	if(dep[y]>dep[x])swap(x,y);
	while(dep[x]>dep[y])
	{
		stack[++top] = a[x];
		if(top>=55)return true;
		x = fa[x];
	}
	while(x!=y)
	{
		stack[++top] = a[x];
		stack[++top] = a[y];
		if(top>=55)return true;
		x = fa[x],y = fa[y];
	}
	stack[++top] = a[x];
	sort(stack+1,stack+top+1);
	for(int i = 1;i<= top-2;i++)
		if(stack[i]+stack[i+1]>stack[i+2])
			return true;
	return false;
}
int main()
{
	//freopen("tree.in","r",stdin);
	//freopen("tree.out","w",stdout);
	int x,y;
	scanf("%d%d",&n,&q);
	for(int i = 1;i<= n;i++)
		scanf("%I64d",&a[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1,0);
	int ju;
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d%d",&ju,&x,&y);
		if(ju==0)
		{
			if(getans(x,y))printf("Y\n");
			else printf("N\n");
		}else
			a[x] = y;
	}
	return 0;
}
