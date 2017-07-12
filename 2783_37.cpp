
#include <stdio.h>
#include <set>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
struct E
{int next,to;}e[N<<1];
int head[N],tot,a[N],sum[N];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int line[N],h,t,cnt,n,s;
multiset<int>Q;
void dfs(int x)
{
	for(int i = head[x];i;i = e[i].next)
	{
		sum[e[i].to] = sum[x]+a[e[i].to];
		if(Q.find(sum[e[i].to]-s)!=Q.end())cnt++;
		Q.insert(sum[e[i].to]);
		dfs(e[i].to);
		Q.erase(Q.find(sum[e[i].to]));
	}
}
int main()
{
	int x,y;
	scanf("%d%d",&n,&s);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	Q.insert(0);
	sum[1] = a[1];
	Q.insert(sum[1]);
	dfs(1);
	printf("%d\n",cnt);
	return 0;
}
