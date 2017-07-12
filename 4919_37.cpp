
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <set>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
typedef long long ll;
int v[N],p[N],idx[N];
multiset<int>heap[N];
multiset<int>::iterator it;
struct E
{int next,to;}e[N];
int head[N],tot;
void add(int x,int y){e[++tot].to=y;e[tot].next=head[x];head[x]=tot;}
int merge(int x,int y)
{
	if(heap[x].size()<heap[y].size())swap(x,y);
	for(it = heap[y].begin();it!=heap[y].end();it++)
		heap[x].insert(*it);
	heap[y].clear();
	return x;
}	
void debug(int x)
{
	printf("Case #%d\n",x);
	for(it = heap[x].begin();it!=heap[x].end();it++)
		printf("%d ",*it);
	printf("\n");
}
int cnt;
void dfs(int x)
{
	bool lef = true;
	for(int i = head[x];i;i=e[i].next)
		dfs(e[i].to),lef = false;
	if(lef)idx[x] = ++cnt;
	else idx[x] = idx[e[head[x]].to];
	for(int i = e[head[x]].next;i;i=e[i].next)
		idx[x] = merge(idx[x],idx[e[i].to]);
	it = heap[idx[x]].lower_bound(v[x]);
	if(it==heap[idx[x]].end())heap[idx[x]].insert(v[x]);
	else heap[idx[x]].erase(it),heap[idx[x]].insert(v[x]);
	//debug(idx[x]);
}
int main()
{
	int n,rot;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&v[i],&p[i]);
		add(p[i],i);if(p[i]==0)rot=i;
	}
	dfs(rot);
	printf("%d\n",heap[idx[rot]].size());
	return 0;
}
