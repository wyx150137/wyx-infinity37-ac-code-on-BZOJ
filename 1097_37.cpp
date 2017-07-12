
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int M = 200005;
const int N = 20005;
const int S = 1<<20;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,val;}e[M<<1];
struct H
{int pos,val;}heap[N<<2];
int head[N],tot,cnt,n,m,k;
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val = f;
	head[x] = tot;
	e[++tot].to = x;
	e[tot].next = head[y];
	e[tot].val = f;
	head[y] = tot;
}
int f[25][N],v[N];
bool cmp(H a,H b){return a.val>b.val;}
void dijk(int st)
{
	memset(f[st],0x3f,sizeof(f[st]));
	memset(v,0,sizeof(v));
	f[st][st] = 0;
	heap[1].val = 0,heap[1].pos = st;
	cnt++;
	while(cnt)
	{
		int x = heap[1].pos;
		pop_heap(heap+1,heap+cnt+1,cmp);
		cnt--;
		if(v[x])continue;
		v[x] = true;
		for(int i = head[x];i;i = e[i].next)
		{
			int to = e[i].to;
			if(f[st][x]+e[i].val<f[st][to])
			{
				f[st][to] = f[st][x]+e[i].val;
				cnt++;
				heap[cnt].pos = to;heap[cnt].val = f[st][to];
				push_heap(heap+1,heap+cnt+1,cmp);
			}
		}
	}
	return ;
}
int pre[25],ban[25],num[S],dp[25][S];
void init()
{
	for(int i = 0;i<S;i++)
	{
		int tmp = i;
		while(tmp)
		{
			tmp-=tmp&(-tmp);
			num[i]++;
		}
	}
	memset(dp,-1,sizeof(dp));
	for(int i = 1;i<= k+1;i++)
		dijk(i);
	return ;
}
int dfs(int x,int y)
{
    if(dp[x][y]>=0)return dp[x][y];
    if(y==(1<<k)-1)return f[x][n];
    dp[x][y]=INF;
    for(int i= 2;i<= k+1;i++)
    	if((y&pre[i])==pre[i])
    		dp[x][y]=min(dp[x][y],f[x][i]+dfs(i,y|(1<<(i-2))));
    return dp[x][y];  
}
int main()
{
	int x,y,c,ord;
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x,&y,&c);
		add(x,y,c);
	}
	init();
	scanf("%d",&ord);
	for(int i = 1;i<= ord;i++)
	{
		scanf("%d%d",&x,&y);
		ban[x]|=(1<<(y-2));
		pre[y]|=(1<<(x-2));
	}
	printf("%d\n",dfs(1,0));
	return 0;
}
