
#include <stdio.h>
#include <bitset>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 250005;
const int INF = 0x3f3f3f3f;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
bitset<N>F;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
	e[++tot].to = x;
	e[tot].next = head[y];
	head[y] = tot;
}
int size[N],tb[N];
int root,dirr,n;
LL ans;
void dfs(int x,int fa)
{
	size[x]++;
	for(int i = head[x];i;i = e[i].next)
	{
		if(fa!=e[i].to)
		{
			dfs(e[i].to,x);
			size[x]+=size[e[i].to];
			tb[x] = max(tb[x],size[e[i].to]);
		}
	}
	tb[x] = max(tb[x],n-size[x]);
	if(tb[x]<tb[root])
	{
		root = x;
		dirr = fa;
	}
}
int ts[N];
void getpre(int x,int fa,int dep)
{
	ans+=dep;
	ts[x]++;
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to!=fa)
		{
			getpre(e[i].to,x,dep+1);
			ts[x]+=ts[e[i].to];
		}
	}
}
void solve1(int x)
{
	F[0] = 1;
	for(int i = head[x];i;i = e[i].next)
		F |= F<<ts[e[i].to];
	LL tmp = 0;
	for(int i = 1;i<= n;i++)
		if(F[i])
			tmp = max(tmp,(LL)i*(n-i-1));
	ans+=tmp;
}
int heap[N],cnt;
void solve2(int x)
{
	for(int i = head[x];i;i =e[i].next)
	{
		heap[++cnt] = ts[e[i].to];
		push_heap(heap+1,heap+cnt+1);
	}
	while(cnt>=2)
	{
		int t1 = heap[1];
		pop_heap(heap+1,heap+cnt+1);cnt--;
		int t2 = heap[1];
		pop_heap(heap+1,heap+cnt+1);cnt--;
		heap[++cnt] = abs(t1-t2);
		push_heap(heap+1,heap+cnt+1);
	}
	ans+=(LL)((n-1+heap[1])/2)*((n-1-heap[1])/2);
}
int d[N];
int main()
{
	int x,y;
	scanf("%d",&n);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
		d[x]++;d[y]++;
	}
	tb[0] = INF;
	dfs(1,0);
	getpre(root,0,0);
	if(d[root]<=800)
		solve1(root);
	else solve2(root);
	printf("%d %lld\n",n-1,ans);
	return 0;
}
