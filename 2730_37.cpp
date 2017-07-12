
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 505;
const int M = 1005;
struct E
{int next,to;}e[M];
int head[N],tot = 1;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
	e[++tot].to = x;
	e[tot].next = head[y];
	head[y] = tot;
}
int stack[N],low[N],dfn[N],dcc,cnt,top,m,n;
bool ins[N],v[N];
int bel[N];
int ans1;
long long ans2;
void init()
{
	memset(v,0,sizeof(v));
	memset(head,0,sizeof(head));
	tot = 1,cnt = 0,dcc = 0,top = 0,n = 0;
	ans1 = 0;ans2 = 1;
	memset(bel,0,sizeof(bel));
}
void tarjan(int x,int l)
{
	dfn[x] = low[x] = ++cnt;
	//stack[++top] = x;
	v[x] = true;
	for(int i = head[x];i;i = e[i].next)
	{
		if(i==(l^1))continue;
		if(v[e[i].to])low[x] = min(low[x],dfn[e[i].to]);
		else
		{
			tarjan(e[i].to,i);
			low[x] = min(low[x],low[e[i].to]);
			if(low[e[i].to]>=dfn[x])
				bel[x]++;
		}
	}
}
void tarjan1(int x,int l)
{
	dfn[x] = low[x] = ++cnt;
	stack[++top] = x;
	ins[x] = v[x] = true;
	int temp,size;
	for(int i = head[x];i;i = e[i].next)
	{
		if(i==(l^1))continue;
		if(v[e[i].to])low[x] = min(low[x],dfn[e[i].to]);
		else
		{
			tarjan1(e[i].to,i);
			low[x] = min(low[x],low[e[i].to]);
			if(low[e[i].to]>=dfn[x])
			{
				temp = size = 0;
				int tmp;
				do
				{
					tmp = stack[top--];
					ins[tmp] = false;
					if(bel[tmp]>=2)
						temp++;
					size++;
				}while(tmp!=e[i].to);
				tmp = x;
				if(bel[tmp]>=2)
					temp++;
				size++;
				if(!temp)
					ans1+=2,ans2*=size*(size-1)/2;
				else if(temp==1) 
					ans1++,ans2*=size-1;
			}
		}
	}
}
int main()
{
	int x,y,T = 0;
	while(scanf("%d",&m)&&m!=0)
	{
		T++;
		init();
		for(int i = 1;i<= m;i++)
		{
			scanf("%d%d",&x,&y);
			add(x,y);
			n = max(n,max(x,y));
		}
		for(int i = 1;i<= n;i++)
			if(!v[i])
				tarjan(i,-1);
			else bel[i]++;
		memset(v,0,sizeof(v));
		cnt = 0;
		for(int i = 1;i<= n;i++)
			if(!v[i])
				tarjan1(i,-1);
		printf("Case %d: %d %lld\n",T,ans1,ans2);
	}
	return 0;
}
