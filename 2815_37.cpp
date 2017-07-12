
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 65534+5;
struct E
{int next,to;}e1[N<<4],e2[N<<1],ef[N<<4];
int he[N],ht[N],hf[N],tote,tott,fa[N][17],ind[N],dep[N];
void adde(int x,int y)
{
	ind[y]++;
	e1[++tote].to = y;
	e1[tote].next = he[x];
	he[x] = tote;
	ef[tote].to = x;
	ef[tote].next = hf[y];
	hf[y] = tote;
}
void addt(int x,int y)
{
	e2[++tott].to = y;
	e2[tott].next = ht[x];
	ht[x] = tott;
	e2[++tott].to = x;
	e2[tott].next = ht[y];
	ht[y] = tott;
}
queue <int>Q;
int line[N],cnt,n;
void addleaf(int x,int y)
{
	dep[x] = dep[y]+1;fa[x][0] = y;
	for(int i = 1;i<17;i++)
		fa[x][i] = fa[fa[x][i-1]][i-1];
}
int getlca(int x,int y)
{
	if(x<0)return y;
	if(dep[x]<dep[y])swap(x,y);
	for(int j = 16;j>=0;j--)
		if(dep[fa[x][j]]>=dep[y])
			x = fa[x][j];
	if(x==y)return x;
	int re;
	for(int j = 16;j>=0;j--)
	{
		if(fa[x][j]!=fa[y][j])
		{
			x = fa[x][j];
			y = fa[y][j];
		}else re = fa[x][j];
	}
	return re;
}
void topo()
{
	for(int i = 1;i<= n;i++)
		if(!ind[i])
			Q.push(i),addt(0,i),dep[i] = 1;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = he[x];i;i = e1[i].next)
		{
			--ind[e1[i].to];
			if(!ind[e1[i].to])
			{
				Q.push(e1[i].to);
				line[++cnt] = e1[i].to;
			}
		}
	}
}
void build(int x)
{
	int tmp = -1;
	for(int i = hf[x];i;i = ef[i].next)
		tmp = getlca(tmp,ef[i].to);
	addt(tmp,x);
	addleaf(x,tmp);
}
int size[N];
void dfs(int x,int fa)
{
	size[x]++;
	for(int i = ht[x];i;i = e2[i].next)
		if(e2[i].to!=fa)
		{
			dfs(e2[i].to,x);
			size[x]+=size[e2[i].to];
		}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		int x;
		while(scanf("%d",&x))
		{
			if(x==0)break;
			adde(x,i);
		}
	}
	topo();
	for(int i = 1;i<= cnt;i++)
		build(line[i]);
	dfs(0,-1);
	for(int i = 1;i<= n;i++)
		printf("%d\n",size[i]-1);
	return 0;
}
