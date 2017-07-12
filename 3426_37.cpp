
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 500005;
const int M = 1000005;
struct E
{int next,to;}e[M<<1];
int head[N],tot;
bool u1[N],u2[N];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
void cover2(int x)
{
	u1[x] = true;
	for(int i = head[x];i;i = e[i].next)
		u1[e[i].to] = true;
	return ;
}
void cover1(int x)
{
	u1[x] = u2[x] = true;
	for(int i = head[x];i;i =e[i].next)
	{
		if(u2[e[i].to])continue;
		u2[e[i].to] = true;
		cover2(e[i].to);
	}
	return ;
}
int ans[N],cnt;
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	int x,y;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	for(int i = 1;i<= n;i++)
		if(!u1[i])
		{
			ans[++cnt] = i;
			cover1(i);
		}
	printf("%d\n",cnt);
	for(int i = 1;i<cnt;i++)
		printf("%d ",ans[i]);
	printf("%d",ans[cnt]);
	return 0;
}
