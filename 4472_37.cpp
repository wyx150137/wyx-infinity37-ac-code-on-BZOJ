
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
struct data
{
	int val,x;
	data(){}
	data(int val,int x):val(val),x(x){}
	bool operator <(const data &a)const
	{
		return val>a.val;
	}
}stack[N];
int f[N],n;
bool can[N];
struct E
{
	int next,to;
}e[N<<1];
int head[N],tot,top,lim[N],val[N];
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
void dfs(int x,int fa)
{
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
			dfs(e[i].to,x);
	top = 0;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
			stack[++top] = data(f[e[i].to],e[i].to);
	sort(stack+1,stack+top+1);
	int i;
	for(i = 1;i<= top;i++)
	{
		if(stack[i].val<0||i==lim[x])break;
		f[x]+=stack[i].val;
		if(can[stack[i].x])can[x] = true;
		if(stack[i].val==0)can[x] = true;
	}
	if(i<lim[x]&&i<=top&&i!=0&&stack[i].val==stack[i-1].val)
		can[x] = true;
	f[x]+=val[x];
}
int main()
{
	scanf("%d",&n);
	for(int i = 2;i<= n;i++)
		scanf("%d",&val[i]);
	for(int i = 2;i<= n;i++)
		scanf("%d",&lim[i]);
	lim[1] = 10*n;
	int x,y;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,0);
	printf("%d\n",f[1]);
	if(!can[1])printf("solution is unique\n");
	else printf("solution is not unique\n");
	return 0;
}
