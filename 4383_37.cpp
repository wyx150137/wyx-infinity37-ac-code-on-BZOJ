
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int Ed = 2e6+5;
const int N = 6e5+5;
const int INF = 1e9;
struct E
{int next,to,val;}e[Ed];
int ls[N],rs[N],L[N],R[N];
int sit[N];
int head[N],tot,cnt,ind[N],c[N],d[N],ans[N];
bool done[N];
void add(int x,int y,int f)
{
	ind[y]++;
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val = f;
	head[x] = tot;
}
int build(int l,int r)
{
	cnt++;
	L[cnt] = l,R[cnt] = r;
	int p = cnt;
	if(l==r)
	{
		sit[l] = cnt;
		return p;
	}
	int mid = (l+r)>>1;
	ls[p] = build(l,mid);
	add(p,ls[p],0);
	rs[p] = build(mid+1,r);
	add(p,rs[p],0);
	return p;
}
void update(int p,int a,int b,int c)
{
	if(L[p]>=a&&R[p]<=b)
	{
		add(c,p,0);return ;
	}
	int mid = (L[p]+R[p])>>1;
	if(a<=mid)update(ls[p],a,b,c);
	if(b>mid)update(rs[p],a,b,c);
	return ;
}
void dfs(int x)
{
	done[x] = true;
	for(int i = head[x];i;i = e[i].next)
	{
		ans[e[i].to] = min(ans[e[i].to],ans[x]-e[i].val);
		ind[e[i].to]--;
		if(!ind[e[i].to])dfs(e[i].to);
	}
}
int main()
{
	int n,s,m;
	scanf("%d%d%d",&n,&s,&m);
	build(1,n);
	for(int i = 1;i<= cnt;i++)ans[i] = INF;
	int tmp = cnt;
	for(int i = 1;i<= s;i++)
	{
		scanf("%d%d",&c[i],&d[i]);
		ans[sit[c[i]]] = d[i];
	}
	int left,right,k;
	int y;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&left,&right,&k);
		y = left;
		cnt++;
		for(int i = 1;i<= k;i++)
		{
			int x;
			scanf("%d",&x);
			add(sit[x],cnt,1);
			if(x>y)update(1,y,x-1,cnt);
			y = x+1;
		}
		if(right>=y)update(1,y,right,cnt);
	}
	for(int i = tmp+1;i<= cnt;i++)ans[i] = INF;
	dfs(1);
	for(int i = 1;i<= n;i++)
		if(!done[sit[i]]||ans[sit[i]]<1)
			{printf("NIE\n");return 0;}
	for(int i = 1;i<= s;i++)
		if(ans[sit[c[i]]]!=d[i])
			{printf("NIE\n");return 0;}
	printf("TAK\n");
	for(int i = 1;i< n;i++)
		printf("%d ",ans[sit[i]]);
	printf("%d\n",ans[sit[n]]);
	return 0;
}
