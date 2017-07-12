
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5005;
const int M = 50000050;
inline int p0(int i){return i*2;}
inline int p1(int i){return i*2+1;}
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x<<1)+(x<<3) + ch - '0'; ch = getchar(); }
	return x * f;
}
struct E
{int next,to;}e[M];
int head[N<<1],tot,n;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
bool v[N<<1],ins[N<<1],r[N][N];
int stack[N<<1],top,dep[N<<1],low[N<<1],bel[N<<1],dfn,scc;
void tarjan(int x)
{
	v[x] = true;
	low[x] = dep[x] = ++dfn;
	stack[++top] =x ;
	ins[x] = true;
	for(int i = head[x];i;i=e[i].next)
	{
		if(!v[e[i].to])
			{tarjan(e[i].to);low[x] = min(low[x],low[e[i].to]);}
		else if(ins[e[i].to])
			{low[x] = min(low[x],dep[e[i].to]);}
	}
	if(low[x]==dep[x])
	{
		scc++;
		int tmp;
		do
		{
			tmp = stack[top--];
			ins[tmp] = false;
			bel[tmp] = scc;
		}while(tmp!=x);
	}
}
void Read()
{
	scanf("%d",&n);
	int k,x;
	for(int i = 1;i<= n;i++)
	{
		k = read();
		for(int j = 1;j<= k;j++)
			{x = read();r[i][x] = r[x][i] = true;}
	}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<i;j++)
		{
			if(r[i][j])add(p1(i),p0(j)),add(p1(j),p0(i));
			else add(p0(i),p1(j)),add(p0(j),p1(i));
		}
}
int ans[N],cnt[N],dir[N],Ans;
void work()
{
	for(int i = 2;i<= 2*n+1;i++)
		if(!v[i])
			tarjan(i);
	for(int i = 1;i<= n;i++)if(bel[p1(i)]==bel[p0(i)])return ;
	int cnt1 = 0,cnt0 = 0;
	for(int i = 1;i<= n;i++)
	{
		ans[i] = (bel[p0(i)]>bel[p1(i)]);
		if(ans[i])cnt1++;else cnt0++;
	}
	Ans = (cnt1&&cnt0);
	int t0 = 0,t1 = 0;
	for(int i = 1;i<= n;i++)
	{
		if(ans[i])
		{
			for(int j = 1;j<= n;j++)
				if(i!=j&&!ans[j]&&!r[i][j])
					cnt[i]++,dir[i] = j;
		}
		else
		{
			for(int j = 1;j<= n;j++)
				if(i!=j&&ans[j]&&r[i][j])
					cnt[i]++,dir[i] = j;
		}
	}
	for(int i = 1;i<= n;i++)
	{
		if(ans[i])
		{
			if(!cnt[i]&&cnt1>1)Ans++;
			if(!cnt[i])t1++;
			if(cnt[i]==1&&((cnt[dir[i]]==1&&dir[dir[i]]==i&&i<dir[i])||!cnt[dir[i]]))
				Ans++;
		}
		else
		{
			if(!cnt[i]&&cnt0>1)Ans++;
			if(!cnt[i])t0++;
			if(cnt[i]==1&&((cnt[dir[i]]==1&&dir[dir[i]]==i&&i<dir[i])||!cnt[dir[i]]))
				Ans++;
		}
	}
	Ans+=t0*t1;
}
int main()
{
	Read();
	work();
	printf("%d\n",Ans);
	return 0;
}
