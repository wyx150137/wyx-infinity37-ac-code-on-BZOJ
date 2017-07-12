
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 2e5+5;
struct E
{int next,to;}e[M<<1];
int head1[N],head2[N],tot;
void add1(int x,int y){e[++tot].to=y;e[tot].next=head1[x];head1[x]=tot;}
void add2(int x,int y){e[++tot].to=y;e[tot].next=head2[x];head2[x]=tot;}
int fa[N],size[N],outd[N];
bool bo[N];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x]=x;
	else return fa[x]=getfa(fa[x]);
}
void merge(int x,int y)
{
	x = getfa(x),y = getfa(y);
	if(x==y)return ;
	if(size[x]<size[y])swap(x,y);
	fa[y] = x;size[x]+=size[y];
}
queue<int>Q;
int main()
{
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add1(x,y),add2(y,x),outd[x]++;
	}
	for(int i = 1;i<= n;i++)fa[i]=i,size[i]=1;
	for(int i = 1;i<= n;i++)
	{
		for(int id = head1[i];id;id=e[id].next)bo[e[id].to]=true;
		for(int id = head2[i];id;id=e[id].next)
			if(bo[e[id].to])merge(i,e[id].to);
		for(int id = head1[i];id;id=e[id].next)bo[e[id].to]=false;
	}
	for(int i = 1;i<= n;i++)
	{
		int y = 0;
		for(int id = head1[i];id;id=e[id].next)
			if(y)merge(y,e[id].to);
			else y = e[id].to;
	}
	memset(bo,true,sizeof(bo));
	for(int i = 1;i<= n;i++)
		if(size[getfa(i)]>1)Q.push(i),bo[i]=false;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head1[x];i;i=e[i].next)
		{
			merge(x,e[i].to);
			if(bo[e[i].to]){bo[e[i].to]=false;Q.push(e[i].to);}
		}
	}
	long long ans = 0;
	for(int i = 1;i<= n;i++)
		if(getfa(i)==i)
		{
			if(size[i]>1)ans+=(long long)size[i]*(size[i]-1);
			else ans+=outd[i];
		}
	printf("%lld\n",ans);
	return 0;
}
