
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#define fir first
#define sec second
using namespace std;
typedef long long ll;
typedef pair<ll,int> pil;
const int N = 1e6+5;
const ll INF = 1e18;
priority_queue<pil, vector<pil> , greater<pil> >Q;
struct E
{int next,to,val;}e[N];
int head[N],tot,cnt;
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];
	head[x] = tot;e[tot].val = f;
}
int n,m,fa[N],a[N],deg[N],ans[N];
ll dis[N],f[N];
void dfs(int x,int pre)
{
	f[x] = x<=n?0:INF;
	for(int i = head[x];i;i=e[i].next)
	{
		fa[e[i].to] = x;
		dis[e[i].to] = dis[x]+e[i].val;
		dfs(e[i].to,i);
		if(f[e[i].to]<f[x])f[x] = f[e[i].to];
		deg[x]++;
	}
	f[x]+=e[pre].val;
}
char name[N>>1][15];
bool cmp(int a,int b)
{return dis[a]<dis[b];}
void Push(int x)
{
	if(x==n+1)return ;
	if(--deg[x])return ;
	cnt++;
	Q.push(pil(f[x],x));
}
int main()
{
	int x,d;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",name[i]+1);
		scanf("%d%d",&x,&d);
		add(x+n+1,i,d);
	}
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&d);
		add(x+n+1,i+n+1,d);
	}
	dfs(n+1,0);
	f[n+1] = INF;
	for(int i = 1;i<= n;i++)a[i]=i;
	sort(a+1,a+n+1,cmp);
	cnt = n;
	for(int i = 1;i<= n;i++)Q.push(pil(f[i],i));
	for(int i = 1;i<= n;ans[a[i++]]=cnt)
		while(!Q.empty())
		{
			pil t = Q.top();
			if(t.fir>dis[a[i]])break;
			Q.pop();
			cnt--;
			Push(fa[t.sec]);
		}
	for(int i = 1;i<= n;i++)
		printf("%s %d\n",name[i]+1,ans[i]+1);
	return 0;
}
