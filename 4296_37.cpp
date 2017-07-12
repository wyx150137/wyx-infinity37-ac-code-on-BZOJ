
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 200005;
int fa[N],size[N];
struct E
{
	int next,to;
}e[N<<1];
int head[N],tot,d[N];
int n,m,D;
bool v[N];
void add(int x,int y)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;d[x]++;
	e[++tot].to=x;e[tot].next=head[y];head[y]=tot;d[y]++;
}
queue<int>Q;
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x]=x;
	else return fa[x]=getfa(fa[x]);
}
void uni(int x,int y)
{
	x = getfa(x),y = getfa(y);
	if(x==y)return ;
	fa[x] = y;
	size[y]=size[x]+size[y];
	size[x] = 0;
}
int main()
{
	int x,y;
	scanf("%d%d%d",&n,&m,&D);
	for(int i = 1;i<= n;i++)size[fa[i]=i]=1;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	for(int i = 1;i<= n;i++)
		if(d[i]<D)
			Q.push(i),v[i]=true;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(!v[e[i].to])
			{
				d[e[i].to]--;
				if(d[e[i].to]<D)Q.push(e[i].to),v[e[i].to]=true;
			}
	}
	for(int i = 1;i<= n;i++)
		if(!v[i])
			for(int j = head[i];j;j=e[j].next)
				if(!v[e[j].to])
					uni(i,e[j].to);
	int maxi = 0;
	for(int i = 1;i<= n;i++)
		if(!v[i]&&getfa(i)==i)
			if(size[i]>size[maxi])
				maxi = i;
	if(maxi==0)printf("NIE\n");
	else
	{
		printf("%d\n",size[maxi]);
		for(int i = 1;i<= n;i++)
			if(!v[i]&&getfa(i)==maxi)
				printf("%d ",i);
	}
	return 0;
}
