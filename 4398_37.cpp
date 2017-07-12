
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int M = 1e5+5;
const int N = 4e4+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,val;};
struct p
{
	int v,no;
}heap[N<<2];
bool cmp(p a,p b)
{
	return a.v>b.v;
}
int dist[N],pre[N],cnt;
bool v[N];
struct G
{
	E e[M<<1];
	int head[N],tot;
	void add(int x,int y,int f)
	{
		e[++tot].to = y;
		e[tot].next = head[x];
		e[tot].val  = f;
		head[x] = tot;
	}
	void spfa()
	{
		dist[1]=0;
		heap[1].v = 0;heap[1].no = 1;
		cnt++;
		push_heap(heap+1,heap+cnt+1,cmp);
		while(cnt)
		{
			int now=heap[1].no;
			pop_heap(heap+1,heap+1+cnt,cmp);
			cnt--;
			if(v[now])continue;
			v[now]=1;
			for(int i=head[now];i;i=e[i].next)
				if(dist[now]+e[i].val<dist[e[i].to]&&!v[e[i].to])
				{
					dist[e[i].to]=dist[now]+e[i].val;
					if(now==1)pre[e[i].to]=e[i].to;
					else pre[e[i].to]=pre[now];
					heap[++cnt].v = dist[e[i].to];
					heap[cnt].no = e[i].to;
					push_heap(heap+1,heap+cnt+1,cmp);
				}
		}
	}
}g1,g2;
int main()
{
	int n,m,x,y,u,w;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&x,&y,&u,&w);
		g1.add(x,y,u);
		g1.add(y,x,w);
	}
	memset(dist,0x3f,sizeof(dist));
	g1.spfa();
	int end = n+1;
	for(int i = g1.head[1];i;i = g1.e[i].next)
	{
		if(pre[g1.e[i].to]!=g1.e[i].to)
			g2.add(1,g1.e[i].to,g1.e[i].val);
		//else g2.add(1,g1.e[i].to,dist[g1.e[i].to]);
	}
	for(int i = 2;i<= n;i++)
	{
		for(int j = g1.head[i];j;j = g1.e[j].next)
		{
			if(g1.e[j].to==1)
			{
				if(pre[i]!=i)
					g2.add(1,end,dist[i]+g1.e[j].val);
				else g2.add(i,end,g1.e[j].val);
			}else
			{
				if(pre[g1.e[j].to]!=pre[i])
					g2.add(1,g1.e[j].to,dist[i]+g1.e[j].val);
				else g2.add(i,g1.e[j].to,g1.e[j].val);
			}
		}
	}
	memset(dist,0x3f,sizeof(dist));
	memset(v,0,sizeof(v));
	g2.spfa();
	if(dist[end]==INF)printf("-1\n");
	else printf("%d\n",dist[end]);
	return 0;
}
