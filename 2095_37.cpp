
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const int M = 2005;
const int EM = 1e6+5;
const int INF = 0x3f3f3f3f;
struct Edge
{
	int x,y,a,b;
	Edge(int x=0,int y=0,int a=0,int b=0):x(x),y(y),a(a),b(b){}
}ed[M];
struct E
{int next,to,f;}e[EM];
int head[N],tot=1,n,m;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].f = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].f = 0;
}
queue<int>Q;
int d[N];
bool bfs(int s,int t)
{
	memset(d,-1,sizeof(d));
	d[t] = 0;
	Q.push(t);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(e[i^1].f&&d[e[i].to]==-1)
			{
				d[e[i].to] = d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[s]!=-1;
}
int get_mxf(int s,int t,int mx)
{
	if(s==t)return mx;
	int last = mx;
	for(int i = head[s];i;i=e[i].next)
		if(d[e[i].to]==d[s]-1&&e[i].f)
		{
			int tof = get_mxf(e[i].to,t,min(last,e[i].f));
			if(tof)
			{
				e[i].f-=tof;
				e[i^1].f+=tof;
				if(!(last-=tof))return mx;
			}
		}
	d[s] = -1;
	return mx-last;
}
int dinic(int s,int t)
{
	int ans = 0;
	while(bfs(s,t))
		ans+=get_mxf(s,t,INF);
	return ans;
}
int fa[N],cnt;
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x] = x;
	else return fa[x] = getfa(fa[x]);
}
void uni(int x,int y)
{
	x = getfa(x),y = getfa(y);
	if(x==y)return ;
	fa[x] = y;
	cnt--;
}
int dgr[N],S,T;
bool judge(int ans)
{
	memset(fa,0,sizeof(fa));cnt=n;
	memset(head,0,sizeof(head));tot = 1;
	memset(dgr,0,sizeof(dgr));
	for(int i = 1;i<= m;i++)
	{
		if(ed[i].b<=ans)
		{
			uni(ed[i].x,ed[i].y);
			dgr[ed[i].x]++;
			dgr[ed[i].y]--;
			add(ed[i].x,ed[i].y,1);
		}
		else if(ed[i].a<=ans)
		{
			uni(ed[i].x,ed[i].y);
			dgr[ed[i].x]--;
			dgr[ed[i].y]++;
		}
	}
	if(cnt>=2)return false;
	for(int i = 1;i<= n;i++)
	{
		if(dgr[i]&1)return false;
		if(dgr[i]>0)
			add(S,i,dgr[i]>>1);
		else add(i,T,(-dgr[i])>>1);
	}
	dinic(S,T);
	for(int i =head[S];i;i=e[i].next)
		if(e[i].f)
			return false;
	return true;
}
int main()
{
	scanf("%d%d",&n,&m);
	S = 0,T = n+1;
	int x,y,a,b,max_num = 0;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&x,&y,&a,&b);
		if(a>b)swap(a,b),swap(x,y);
		ed[i]=Edge(x,y,a,b);
		max_num = max(max_num,b);
	}
	int l = 1,r = max_num+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(judge(mid))r = mid;
		else l = mid+1;
	}
	if(l!=max_num+1)printf("%d\n",l);
	else printf("NIE\n");
	return 0;
}
