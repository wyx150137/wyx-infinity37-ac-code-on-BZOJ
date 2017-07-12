
#include <stdio.h>
#include <queue>
#include <bitset>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 105;
struct E
{int next,to,val1,val2;}e[N*N];
int head[N],tot;
int d[N];
void add(int x,int y,int f1,int f2)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val1 = f1;
	e[tot].val2 = f2;
	head[x] = tot;
}
bitset<10005>f[N],g[N];
queue<int>Q;
int main()
{
	int n,m,x,y,u,v;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&x,&y,&u,&v);
		add(x,y,u,v);
		d[y]++;
	}
	for(int i = 1;i<= n;i++)
		if(!d[i])
			Q.push(i);
	f[1] = g[1] = 1;
	while(!Q.empty())
	{
		x = Q.front();
		Q.pop();
		for(int i = head[x];i;i = e[i].next)
		{
			f[e[i].to]|=f[x]<<e[i].val1;
			g[e[i].to]|=g[x]<<e[i].val2;
			if(!--d[e[i].to])
				Q.push(e[i].to);
		}
	}
	for(int i = 1;i<= 10000;i++)
		if(f[n][i]&&g[n][i])
		{
			printf("%d\n",i);
			return 0;
		}
	printf("IMPOSSIBLE\n");
	return 0;
}
