
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const int M = 2e4+5;
struct E
{int next,to;}e[M];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
bool ins[N];
int dfn[N],low[N],stack[N],top,cnt,bel[N],dcc;
void tarjan(int x)
{
	low[x] = dfn[x] = ++cnt;
	stack[++top] = x;
	ins[x] = true;
	for(int i = head[x];i;i=e[i].next)
	{
		if(!dfn[e[i].to])
		{
			tarjan(e[i].to);
			low[x] = min(low[x],low[e[i].to]);
		}else if(ins[e[i].to])
			low[x] = min(low[x],dfn[e[i].to]);
	}
	if(dfn[x]==low[x])
	{
		dcc++;
		int tmp;
		do
		{
			tmp = stack[top--];
			ins[tmp] = false;
			bel[tmp] = dcc;
		}while(tmp!=x);
	}
}
int getnum(char s[10])
{
	int now = 1;
	int ans = 0;
	while(s[now])
	{
		ans=ans*10+s[now]-'0';
		now++;
	}
	return ans*2;
}
void work()
{
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(bel,0,sizeof(bel));
	tot = cnt = dcc = top = 0;
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	char s1[10],s2[10];
	for(int i=1;i<=m;i++)
	{
		scanf("%s%s",s1,s2);
		x = getnum(s1),y = getnum(s2);
		if(s1[0]=='m')x++;
		if(s2[0]=='m')y++;
		add(x^1,y);
		add(y^1,x);
	}
	for(int i = 2;i<= 2*n+1;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i = 1;i<= n;i++)
	{
		if(bel[i<<1]==0||bel[i<<1|1]==0)continue;
		if(bel[i<<1]==bel[i<<1|1])
			{printf("BAD\n");return ;}
	}
	printf("GOOD\n");
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)work();
	return 0;
}
