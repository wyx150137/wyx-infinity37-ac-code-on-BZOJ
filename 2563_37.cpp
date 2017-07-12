
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e4+5;
const int M = 1e5+5;
struct E
{int next,to,val;}e[M<<1];
int head[N],tot,w[N];
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].val = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].val = f;
}
struct data
{
	int id,val;
	bool operator <(const data &s)const
	{
		return val>s.val;
	}
}p[N];
int main()
{
	long long ans = 0;
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&w[i]),ans-=w[i];
	int a,b,c;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c),ans-=c;
	}
	for(int i = 1;i<= n;i++)
	{
		p[i].id = i;
		p[i].val = 2*w[i];
		for(int j = head[i];j;j=e[j].next)
			p[i].val+=e[j].val;
	}
	sort(p+1,p+n+1);
	for(int i = 1;i<= n;i+=2)
		ans+=p[i].val;
	printf("%lld\n",ans);
	return 0;
}
