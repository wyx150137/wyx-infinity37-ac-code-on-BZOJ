
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n,tot_root,b;
long long m;
struct Heap{
	Heap *ls,*rs;
	int key;
	Heap(int f)
	{
		ls = rs = NULL;
		key = f;
	}
};
Heap* Merge(Heap *x,Heap *y)
{
	if(!x)return y;
	if(!y)return x;
	if(y->key>x->key)
		swap(x,y);
	if(rand()%2==1)
		x->ls = Merge(x->ls,y);
	else 
		x->rs = Merge(x->rs,y);
	return x;
}
struct e
{int next,to;}edge[100005];
int head[100005],tot;
long long c[100005],l[100005],tc[100005],tp[100005];
Heap *h[100005];
void add(int x,int y)
{
	edge[++tot].to = y;
	edge[tot].next = head[x];
	head[x] = tot;
}
long long ans = 0;
void dfs(int x)
{
	Heap *root = new Heap(c[x]);
	tc[x]+=c[x];tp[x]++;
	for(int i = head[x];i;i = edge[i].next)
	{
		dfs(edge[i].to);
		root = Merge(root,h[edge[i].to]);
		tc[x]+=tc[edge[i].to];
		tp[x]+=tp[edge[i].to];
	}
	while(tc[x]>m)
	{
		tc[x]-=root->key;
		root = Merge(root->ls,root->rs);
		tp[x]--;
	}
	ans = max(ans,(long long)tp[x]*l[x]);
	h[x] = root;
}
int main()
{
	scanf("%d%lld",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%lld%lld",&b,&c[i],&l[i]);
		if(b==0)tot_root = i;
		else add(b,i);
	}
	dfs(tot_root);
	printf("%lld",ans);
	return 0;
}
