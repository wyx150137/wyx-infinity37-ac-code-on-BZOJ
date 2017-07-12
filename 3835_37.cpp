
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1000005;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int sum[N],max_dep;
void dfs(int x,int dep)
{
	max_dep = max(max_dep,dep);
	sum[dep]++;
	for(int i = head[x];i;i = e[i].next)
		dfs(e[i].to,dep+1);
}
struct Ask
{int k,no,ans;}qur[N];
bool cmp(Ask a,Ask b){return a.k<b.k;}
bool ret(Ask a,Ask b){return a.no<b.no;}
int line[N],L,R;
double calc(int i,int j)
{
	return (double)(sum[i]-sum[j])/(double)(i-j);
}
int main()
{
	int n,q,x;
	scanf("%d%d",&n,&q);
	for(int i = 1;i<= q;i++)
	{
		scanf("%d",&qur[i].k);
		qur[i].no = i;
	}
	sort(qur+1,qur+1+q,cmp);
	for(int i = 2;i<=n;i++)
	{
		scanf("%d",&x);
		add(x,i);
	}
	dfs(1,1);
	for(int i = max_dep;i>=1;i--)
		sum[i]+=sum[i+1];
	R = -1;
	for(int i = 1;i<= max_dep;i++)
	{
		while(L<R&&calc(i,line[R-1])>=calc(line[R],line[R-1]))R--;
		line[++R] = i;
	}
	for(int t = 1;t<= q;t++)
	{
		int i = qur[t].k;
		while(L<R&&i*line[L]+sum[line[L]]<i*line[L+1]+sum[line[L+1]])L++;
		qur[t].ans = line[L];
	}
	sort(qur+1,qur+q+1,ret);
	for(int i = 1;i< q;i++)
		printf("%d ",max(max_dep,(sum[qur[i].ans]+qur[i].k-1)/qur[i].k+qur[i].ans-1));
	printf("%d\n",max(max_dep,(sum[qur[q].ans]+qur[q].k-1)/qur[q].k+qur[q].ans-1));
	return 0;
}
