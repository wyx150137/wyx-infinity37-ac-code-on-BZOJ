
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5005;
const int K = 1e6+5;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
struct A
{int s,t,k,no,ans;}ask[K];
bool cmp1(A a,A b){return a.s<b.s;}
bool cmp2(A a,A b){return a.no<b.no;}
queue<int>Q;
int f[N],g[N];
bool v[N];
void spfa(int s)
{
	memset(f,0x3f,sizeof(f));
	memset(g,0x3f,sizeof(g));
	Q.push(s);
	f[s] = 0;
	v[s] = true;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		v[x] = false;
		for(int i = head[x];i;i = e[i].next)
		{
			if(f[x]+1<g[e[i].to]||g[x]+1<f[e[i].to])
			{
				f[e[i].to] = min(f[e[i].to],g[x]+1);
				g[e[i].to] = min(g[e[i].to],f[x]+1);
				if(!v[e[i].to])
				{
					Q.push(e[i].to);
					v[e[i].to] = true;
				}
			}
			else if(e[i].to==s)
			{
				if(f[s]==0)f[s] = g[x]+1,g[s] = f[x]+1;
				else f[s] = min(g[x]+1,f[s]),g[s] = min(f[x]+1,g[s]);
			}
		}
	}
	if(f[s]==0)f[s] = 0x3f3f3f3f;
}
int main()
{
	int n,m,k,x,y;
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	for(int i = 1;i<= k;i++)
	{
		scanf("%d%d%d",&ask[i].s,&ask[i].t,&ask[i].k);
		ask[i].no = i;
	}
	sort(ask+1,ask+k+1,cmp1);
	int j = 0;
	for(int i = 1;i<= k;i++)
	{
		if(ask[i].s!=j)
		{
			spfa(ask[i].s);
			j = ask[i].s;
		}
		if(ask[i].k%2==1)
			{if(g[ask[i].t]<=ask[i].k)ask[i].ans = 1;}
		else {if(f[ask[i].t]<=ask[i].k)ask[i].ans = 1;}
	}
	sort(ask+1,ask+k+1,cmp2);
	for(int i = 1;i<= k;i++)
	{
		if(ask[i].ans)printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}
