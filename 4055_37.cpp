
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e3+5;
const int M = 8e3+5;
typedef long double ld;
struct E
{int next,to,b;ld c;};
struct H
{int v,no;}heap[M];
bool cmp(H a,H b)
{
    return a.v>b.v;
}
bool on_tree[M];
int dis[N],ind[N],rei[N],a[N],n,m,cnt;bool v[N];
ld arc[N][N];
ld R[N],tr[N];
queue<int>Q;
struct Gragh
{
	E e[M];
	int head[N],tot;
	void init()
	{
		memset(head,0,sizeof(head));
		tot = 1;
	}
	void add(int x,int y,int b,ld c)
	{
		e[++tot].to = y;
		e[tot].next = head[x];
		head[x] = tot;
		e[tot].b = b,e[tot].c = c;
	}
	void spfa(int s)
	{
		cnt = 0;
		memset(dis,0x3f,sizeof(dis));
		memset(v,false,sizeof(v));
		dis[s]=0;
		heap[1].v = 0;heap[1].no = s;
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
				if(dis[now]+e[i].b<dis[e[i].to]&&!v[e[i].to])
				{
					dis[e[i].to]=dis[now]+e[i].b;
					heap[++cnt].v = dis[e[i].to];
					heap[cnt].no = e[i].to;
					push_heap(heap+1,heap+cnt+1,cmp);
				}
		}
		for(int i = 1;i<= n;i++)
			for(int j = head[i];j;j=e[j].next)
				if(dis[i]+e[j].b==dis[e[j].to])
					on_tree[j] = true,ind[e[j].to]++,rei[i]++;
	}
	void topo(int s)
	{
		arc[s][s] = 1;
		for(int i = 1;i<= n;i++)
			if(!ind[i])
				Q.push(i);
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			for(int i = head[x];i;i=e[i].next)
				if(on_tree[i])
				{
					arc[s][e[i].to]+=e[i].c*arc[s][x];
					if(!--ind[e[i].to])
						Q.push(e[i].to);
				}
		}
	}
	void retopo(int s)
	{
		for(int i = 1;i<= n;i++)
		{
			if(!rei[i])
				Q.push(i);
			tr[i] = 0;
		}
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			for(int i = head[x];i;i=e[i].next)
			if(on_tree[i^1])
			{
				tr[e[i].to]+=e[i].c*tr[x];
				tr[e[i].to]+=e[i].c*a[x]/arc[s][x];
				if(!--rei[e[i].to])
					Q.push(e[i].to);
			}
		}
	}
	void getR(int s)
	{
		for(int i=1;i<= n;i++)
			if(i!=s)
				R[i]+=arc[s][i]*a[s]*tr[i];
	}
}g;
int main()
{
	//freopen("misc.in","r",stdin);
	//freopen("misc.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	int u,v,d;ld c;
	g.init();
	for(int i = 1;i<=m;i++)
	{
		scanf("%d%d%d%Lf",&u,&v,&d,&c);
		g.add(u,v,d,c);
		g.add(v,u,d,c);
	}
	for(int i= 1;i<= n;i++)
	{
		memset(ind,0,sizeof(ind));
		memset(rei,0,sizeof(rei));
		memset(on_tree,0,sizeof(on_tree));
		g.spfa(i);
		g.topo(i);
		g.retopo(i);
		g.getR(i);
	}
	for(int i = 1;i<= n;i++)
		printf("%.8Lf\n",R[i]);
	return 0;
}
