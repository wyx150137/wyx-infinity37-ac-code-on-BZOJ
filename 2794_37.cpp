
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const int Q = 1e6+5;
const int M = 1e5+5;
struct A
{int l,r,v,id;}w[N],ask[Q];
bool cmp(A a,A b)
{
	return a.l<b.l;
}
int f[M],ans[Q];
int main()
{
	int n,q;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d%d%d",&w[i].v,&w[i].l,&w[i].r);
	scanf("%d",&q);
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d%d",&ask[i].l,&ask[i].v,&ask[i].r);
		ask[i].r+=ask[i].l;
		ask[i].id = i;
	}
	sort(w+1,w+n+1,cmp);
	sort(ask+1,ask+1+q,cmp);
	f[0] = 1e9;
	int j = 1;
	for(int i = 1;i<= q;i++)
	{
		while(w[j].l<=ask[i].l&&j<=n)
		{
			for(int k = M-5;k>= w[j].v;k--)
				f[k] = max(f[k],min(f[k-w[j].v],w[j].r));
			j++;
		}
		if(f[ask[i].v]>ask[i].r)
			ans[ask[i].id] = 1;
	}
	for(int i = 1;i<= q;i++)
	{
		if(ans[i])printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}
