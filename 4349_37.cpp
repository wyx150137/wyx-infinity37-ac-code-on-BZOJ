
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 55;
const int M = 2505;
const int INF = 0x3f3f3f3f;
const double eps = 1e-7;
struct E
{int u,v;double val;}e[M];
int p[N],num[N],pre[N],vis[N],mark[N];
double c[N],in[N];
double work(int root,int n,int m)
{
	double ans = 0;
	while(true)
	{
		for(int i = 1;i<= n;i++)in[i] = INF;
		for(int i = 1;i<= m;i++)
		{
			int u=e[i].u,v=e[i].v;
			if(u!=v&&e[i].val<in[v])
			{
				in[v] = e[i].val;
				pre[v] = u;
			}
		}
		for(int i = 1;i<= n;i++)
		{
			if(i==root)continue;
			if(fabs(in[i]-INF)<eps)return -1;
		}
		memset(mark,-1,sizeof(mark));
		memset(vis,-1,sizeof(vis));
		in[root] = 0;int cnt = 0;
		for(int i = 1;i<= n;i++)
		{
			ans+=in[i];
			int v=i;
			while(v!=root&&mark[v]==-1&&vis[v]!=i)
			{
				vis[v] = i;
				v = pre[v];
			}
			if(v!=root&&mark[v]==-1)
			{
				++cnt;
				for(int u = pre[v];u!=v;u = pre[u])
					mark[u] = cnt;
				mark[v] = cnt;
			}
		}
		if(cnt==0)break;
		for(int i = 1;i<= n;i++)
			if(mark[i]==-1)mark[i]=++cnt;
		for(int i = 1;i<=m;i++)
		{
			int u = e[i].u,v = e[i].v;
			e[i].u = mark[u],e[i].v = mark[v];
			if(e[i].u!=e[i].v)
				e[i].val-=in[v];
		}
		n=cnt,root = mark[root];
	}
	return ans;
}
int main()
{
	int n,m=0;
	scanf("%d",&n);
	int tmp = n;n = 1;
	double x;int t;
	for(int i = 1;i<= tmp;i++)
	{
		scanf("%lf%d",&x,&t);
		if(t)
		{
			p[i]=++n;
			e[++m] = (E){1,n,x};
			c[n] = x;num[n] = t;
		}
	}
	int a,b,k;
	scanf("%d",&k);
	for(int i = 1;i<= k;i++)
	{
		scanf("%d%d%lf",&a,&b,&x);
		if(p[a]&&p[b])
		{
			e[++m] = (E){p[a],p[b],x};
			c[p[b]] = min(c[p[b]],x);
		}
	}
	double ans = work(1,n,m);
	for(int i = 2;i<= n;i++)
		if(num[i]>1)ans+=c[i]*(num[i]-1);
	printf("%.2f\n",ans);
	return 0;
}
