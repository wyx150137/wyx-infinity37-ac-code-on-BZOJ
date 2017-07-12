
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 405;
const int M = 805;
const int INF = 0x3f3f3f3f;
struct Edge
{int u,v,w;}edge[N*N];
struct E
{int next,to;}e[M*M];
int head[N],tot,n;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x]=tot;
}
bool cmp(const Edge &a,const Edge &b)
{
	if(a.w==b.w)
	{
		if(a.u==b.u)return a.v>b.v;
		else return a.u>b.u;
	}	
	else return a.w>b.w;
}
int fa[N],d[N];
int getfa(int x)
{
	if(fa[x]==x)return fa[x];
	int res = getfa(fa[x]);
	d[x]^=d[fa[x]];
	return fa[x] = res;
}
int a[N][N];
bool ins[N];
int low[N],dfn[N],stack[N],top,dcc,bel[N],cnt;
void tarjan(int x)
{
	stack[++top] =x;
	dfn[x]=low[x]=++cnt;
	ins[x] = true;
	for(int i = head[x];i;i=e[i].next)
	{
		if(!dfn[e[i].to])
		{
			tarjan(e[i].to);
			low[x] = min(low[x],low[e[i].to]);
		}else if(ins[e[i].to])
			low[x] = min(low[x],dfn[e[i].to]);
	}
	if(low[x]==dfn[x])
	{
		dcc++;
		int tmp;
		do
		{
			tmp = stack[top--];
			ins[tmp] = false;
			bel[tmp] = dcc;
		}while(tmp!=x);
	}
}
bool check(int s1,int s2)
{
	for(int i = 1;i<= 2*n;i++)head[i]=low[i]=dfn[i]=bel[i]=ins[i]=0;
	top = dcc = tot = cnt = 0;
	for(int i = 1;i<= n;i++)
		for(int j = i+1;j<= n;j++)
		{
			if(a[i][j]>s1)
			{
				add(i*2-1,j*2);
				add(j*2-1,i*2);
			}if(a[i][j]>s2)
			{
				add(i*2,j*2-1);
				add(j*2,i*2-1);
			}
		}
	for(int i = 1;i<= 2*n;i++)if(!dfn[i])tarjan(i);
	for(int i = 1;i<= n;i++)if(bel[i*2]==bel[i*2-1])return false;
	return true;
}
int getans(int c)
{
	int l = 0,r = c;
	while(l<=r)
	{
		int mid = (l+r)>>1;
		if(check(c,mid))r = mid-1;
		else l = mid+1;
	}
	return l;
}
int main()
{
	int id = 0;
	scanf("%d",&n);
	if(n<=2){printf("0\n");return 0;}
	for(int i = 1;i<= n;i++)
		for(int j = i+1;j<= n;j++)
		{
			id++;
			scanf("%d",&a[i][j]);a[j][i]=a[i][j];
			edge[id]=(Edge){i,j,a[i][j]};
		}
	for(int i = 1;i<= n;i++)fa[i]=i,d[i]=0;
	sort(edge+1,edge+id+1,cmp);
	int ans = INF;
	for(int i = 1;i<= id;i++)
	{
		int u = edge[i].u,v = edge[i].v,w = edge[i].w;
		int x = getfa(u),y = getfa(v);
		if(x!=y)
		{
			ans = min(ans,w+getans(w));
			d[x] = d[u]^d[v]^1;
			fa[x] = y;
		}else if(d[u]==d[v])
		{
			ans=min(ans,w+getans(w));
			break;
		}
	}
	printf("%d\n",ans);
	return 0;
}
