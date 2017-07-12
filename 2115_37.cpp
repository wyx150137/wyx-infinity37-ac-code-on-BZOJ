
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int M = 2e5+5;
const int N = 5e4+5;
typedef long long ll;
struct E
{
	int to,next;
	ll val;
}e[N<<1];
int head[N],tot;
void add(int x,int y,ll f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].val = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].val = f;
}
ll sum[N];
void dfs(int x,int f)
{
	for(int i = head[x];i;i=e[i].next)if(e[i].to!=f)
	{
		sum[e[i].to] = sum[x]^e[i].val;
		dfs(e[i].to,x);
	}
}
int st[M],end[M];
ll a[M],p[70],dis[M];
bool on_tree[M];
int father[N];
int getfa(int x)
{
	if(father[x]==x)return x;
	else return father[x] = getfa(father[x]);
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)father[i] = i;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%lld",&st[i],&end[i],&dis[i]);
		int fx = getfa(st[i]),fy = getfa(end[i]);
		if(fx==fy)continue;
		add(st[i],end[i],dis[i]);
		on_tree[i] = true;
		father[fx] = fy;
	}
	dfs(1,0);
	ll ans = sum[n];
	int tot = 0;
	for(int i = 1;i<= m;i++)
		if(!on_tree[i])
			a[++tot] = sum[st[i]]^sum[end[i]]^dis[i];
	for(int i = 1;i<= tot;i++)
		for(int j = 63;j>= 0;j--)
			if((a[i]>>j)&1)
			{
				if(!p[j]){p[j] = a[i];break;}
				else a[i]^=p[j];
			}
	for(int i = 63;i>= 0;i--)if((ans^p[i])>ans)ans = ans^p[i];
	printf("%lld\n",ans);
	return 0;
}
