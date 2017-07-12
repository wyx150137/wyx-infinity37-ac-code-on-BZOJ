
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int INF = 0x3f3f3f3f;
struct data
{
	int mn,dep,lazy;
	void add(int x)
	{
		mn+=x,dep+=x,lazy+=x;
	}
}a[N];
int ef[N],et[N],n,m;
void Push_up(int p)
{
	int l = p<<1,r = p<<1|1;
	a[p].mn = ef[p]?a[p].dep:INF;
	if(l<=n)a[p].mn = min(a[p].mn,a[l].mn);
	if(r<=n)a[p].mn = min(a[p].mn,a[r].mn);
}
void Push_down(int p)
{
	if(!a[p].lazy)return ;
	int l = p<<1,r = p<<1|1;
	if(l<=n)a[l].add(a[p].lazy);
	if(r<=n)a[r].add(a[p].lazy);
	a[p].lazy = 0;
}
void relax(int p)
{
	if(!p)return ;
	relax(p>>1);
	Push_down(p);
}
void dfs(int x,bool f)
{
	Push_down(x);
	if(ef[x]&&a[x].dep==a[x].mn)
		ef[x]--;
	else
	{
		int to = (x<<1)^(a[x].mn!=a[x<<1].mn);
		dfs(to,1);
	}
	Push_up(x);
	if(f&&!++et[x])a[x].add(2);
}
int ans = 0;
void get_max_flow(int x)
{
	relax(x);
	int mc = INF,mw,c1 = 0;
	for(int i = x;i;i>>=1)
	{
		int c2 = c1+a[i].mn-a[i].dep;
		if(c2<mc)
		{
			mc = c2;
			mw = i;
		}
		c1+=et[i]>0?-1:1;
	}
	for(int i = x;i!=mw;i>>=1)
	{
		Push_up(i);
		if(!et[i]--)a[i].add(-2);
	}
	dfs(mw,0);
	for(;mw;mw>>=1)Push_up(mw);
	ans+=mc;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&ef[i]);
	for(int i = 1;i<= n;i++)a[i].dep = a[i>>1].dep+1;
	int x;
	for(int i = n;i;i--)Push_up(i);
	for(int i = 1;i<= m;i++)
	{
		if(i!=1)printf(" ");
		scanf("%d",&x);
		get_max_flow(x);
		printf("%d",ans);
	}
	return 0;
}
