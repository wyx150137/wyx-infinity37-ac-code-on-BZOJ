
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define fir first
#define sec second
const int N = 55;
const int L = 65540;
struct E
{int next,to;}e[N*N];
int head[N],tot=1;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
vector<int>member[N];
int bel[N],cnt,dfn[N],low[N],Dfn,stack[N],top;
bool vis[N];
void tarjan(int x)
{
	dfn[x] = low[x] = ++Dfn;
	stack[++top] = x;
	for(int i = head[x];i;i=e[i].next)
	{
		if(vis[e[i].to])continue;
		if(dfn[e[i].to])
			low[x] = min(low[x],dfn[e[i].to]);
		else
		{
			tarjan(e[i].to);
			low[x] = min(low[x],low[e[i].to]);
		}
	}
	if(dfn[x]==low[x])
	{
		++cnt;
		int tmp;
		do
		{
			tmp = stack[top--];
			bel[tmp] = cnt;
			member[cnt].push_back(tmp);
			vis[tmp] = true;
		}while(tmp!=x);
	}
}
struct AM
{
	int n,m;
	int trs[N][2],out[N];
	void Read()
	{
		int x;
		scanf("%d%d",&n,&m);
		for(int i = 1;i<= m;i++)
		{
			scanf("%d",&x);
			out[x] = true;
		}
		for(int i = 0;i< n;i++)
			scanf("%d%d",&trs[i][0],&trs[i][1]);
	}
}a[N];
bool bfs(const AM &x,const AM &y)
{
	static pii q[L];
	static bool v[N][N];
	memset(v,0,sizeof(v));
	int hd=1,tl=0;
	q[++tl] = make_pair(0,0);
	v[0][0] = true;
	while(hd<=tl)
	{
		pii sta = q[hd++];
		if(x.out[sta.fir] && !y.out[sta.sec])
			return false;
		for(int i = 0;i<2;i++)
		{
			int xx = x.trs[sta.fir][i];
			int yy = y.trs[sta.sec][i];
			if(v[xx][yy])continue;
			v[xx][yy] = true;
			q[++tl] = make_pair(xx,yy);
		}
	}
	return true;
}
int f[N],ans,n;
void topo()
{
	static int q[N],deg[N];
	for(int i = 1;i<= n;i++)
		for(int j = head[i];j;j=e[j].next)
			if(bel[i]!=bel[e[j].to])
				deg[bel[e[j].to]]++;
	int hd = 1,tl = 0;
	for(int i = 1;i<= cnt;i++)
		if(!deg[i])
			q[++tl] = i;
	while(hd<=tl)
	{
		int tmp = q[hd++];
		f[tmp]+=member[tmp].size();
		for(int id = 0;id<member[tmp].size();id++)
		{
			int x = member[tmp][id];
			for(int i = head[x];i;i=e[i].next)
			{
				if(bel[e[i].to]==tmp)continue;
				f[bel[e[i].to]] = max(f[bel[e[i].to]],f[tmp]);
				if(!--deg[bel[e[i].to]])q[++tl] = bel[e[i].to];
			}
		}
		ans = max(ans,f[tmp]);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		a[i].Read();
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			if(i!=j&&bfs(a[i],a[j]))
				add(i,j);
	for(int i = 1;i<= n;i++)
		if(!vis[i])
			tarjan(i);
	topo();
	printf("%d\n",ans);
	return 0;
}
