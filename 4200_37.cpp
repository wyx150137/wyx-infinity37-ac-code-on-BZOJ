
#include <stdio.h>
#include <queue>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+10;
const int S = 5e4+3,T = 5e4+4,SS = 5e4+1,TT = 5e4+2;
const int M = 5e5+5;
const int INF = 0x3f3f3f3f;
struct P
{
	int x,y,id;
}p[N];
inline bool cmp1(const P &a,const P &b)
{return a.x+a.y==b.x+b.y?a.y<b.y:a.x+a.y<b.x+b.y;}
inline bool cmp2(const P &a,const P &b)
{return a.x-a.y==b.x-b.y?a.y<b.y:a.x-a.y<b.x-b.y;}
inline bool cmp3(const P &a,const P &b)
{return a.x==b.x?a.y<b.y:a.x<b.x;}
inline bool cmp4(const P &a,const P &b)
{return a.y==b.y?a.x<b.x:a.y<b.y;}
int s[N],t1[N],t2[N],t3[N],f[N],ff[N],l[N],r[N],lf[N],rf[N],a[N],an;
vector<int>v,t[N];
namespace Max_Flow
{
	queue<int>Q;
	struct E
	{int next,to,f;}e[M];
	int head[N],_head[N],tot,d[N];
	void add(int x,int y,int f)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].f=f;
		e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].f=0;
	}
	bool bfs(int s,int t)
	{
		memset(d,-1,sizeof(d));
		d[s] = 0;Q.push(s);
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			for(int i = head[x];i;i=e[i].next)
				if(e[i].f&&d[e[i].to]==-1)
				{
					d[e[i].to] = d[x]+1;
					Q.push(e[i].to);
				}
		}
		memcpy(_head,head,sizeof(head));
		return d[t]!=-1;
	}
	int get_mxf(int s,int t,int mx)
	{
		if(s==t)return mx;
		int last = mx;
		for(int &i = _head[s];i;i=e[i].next)
			if(e[i].f&&d[e[i].to]==d[s]+1)
			{
				int tof = get_mxf(e[i].to,t,min(last,e[i].f));
				if(tof)
				{
					e[i].f-=tof;e[i^1].f+=tof;
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
}
void update(int x,int y)
{
	if(ff[y]+1>f[x])f[x]=ff[y]+1,t[x].clear();
	if(ff[y]+1==f[x])t[x].push_back(y);
}
void getans(int x)
{
	a[++an] = x;
	int i,j,u=1;
	if(f[x]==ff[x])
	{
		u = 0;
		if(p[x].id)getans(t[x][0]);
	}
	for(i=l[x];u&&i<x;i++)if(f[i]+x-l[x]==ff[x])
	{
		u=0;
        for(j=x;--j>i;)a[++an]=j;
        for(j=l[x];j<=i;++j)a[++an]=j;
        if(p[i].id)getans(t[i][0]);
	}
	for(i=r[i];u&&i>x;--i)if(f[i]+r[x]-x==ff[x])
	{
        u=0;
        for(j=x;++j<i;)a[++an]=j;
        for(j=r[x];j>=i;--j)a[++an]=j;
        if(p[i].id)getans(t[i][0]);
	}
}
int d[N],u[N],c[N];
void Insert(int x,int y)
{
	Max_Flow::add(x,y,INF);
	c[x]++,c[y]--;
}
void dfs(int x)
{
    if(d[x])return;
    int i,j;d[x]=1;
    if(f[x]==ff[x]&&!u[x])
    	for(u[x]=1,i=0;i<t[x].size();++i)
    		Insert(t[x][i],x),dfs(t[x][i]);
    for(i=l[x];i<x;++i)
    	if(f[i]+x-l[x]==ff[x]&&!u[i])
    		for(u[i]=1,j=0;j<t[i].size();++j)
    			Insert(t[i][j],i),dfs(t[i][j]);
    for(i=r[x];i>x;--i)
    	if(f[i]+r[x]-x==ff[x]&&!u[i])
    		for(u[i]=1,j=0;j<t[i].size();++j)
    			Insert(t[i][j],i),dfs(t[i][j]);
}
int main()
{
	int n,ans = 0;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&p[i].x,&p[i].y);
		p[i].id = i;
	}
	sort(p,p+n+1,cmp1);
	for(int i = 0;i<n;i++)if(p[i].x+p[i].y==p[i+1].x+p[i+1].y)t1[p[i].id]=p[i+1].id;
	sort(p,p+n+1,cmp2);
	for(int i = 0;i<n;i++)if(p[i].x-p[i].y==p[i+1].x-p[i+1].y)t2[p[i].id]=p[i+1].id;
	sort(p,p+n+1,cmp3);
	for(int i = 0;i<n;i++)if(p[i].x==p[i+1].x)t3[p[i].id] = p[i+1].id;
	sort(p,p+n+1,cmp4);for(int i = 0;i<= n;i++)s[p[i].id] = i;
	memset(f,0xef,sizeof(f));
	f[s[0]] = 0;
	for(int i = 0;i<= n;i=r[i]+1)
	{
		for(l[i]=r[i]=i;r[i]<n&&p[r[i]].y==p[r[i]+1].y;++r[i]);
		for(int j = l[i];++j<=r[i];)
			l[j]=l[i],r[j]=r[i];
		lf[l[i]] = -INF;
		for(int j = l[i];++j<=r[i];)lf[j] = max(lf[j-1],f[j-1]);
		rf[r[i]] = -INF;
		for(int j = r[i];--j>=l[i];)rf[j] = max(rf[j+1],f[j+1]);
		for(int j = l[i];j<=r[i];j++)
		{
			ff[j] = max(f[j],max(lf[j]+j-l[i],rf[j]+r[i]-j));
			if(t1[p[j].id])update(s[t1[p[j].id]],j);
			if(t2[p[j].id])update(s[t2[p[j].id]],j);
			if(t3[p[j].id])update(s[t3[p[j].id]],j);
			if(ff[j]>ans)ans=ff[j],v.clear();
			if(ff[j]==ans)v.push_back(j);
		}
	}
	Max_Flow::tot = 1;
	printf("%d\n",ans);
	getans(v[0]);
	for(int i = an;--i;)
		printf("%d ",p[a[i]].id);
	printf("\n");
	for(int i = 0;i<v.size();i++)dfs(v[i]);
	for(int i = 0;i<= n;i++)
	{
		if(c[i]<0)Max_Flow::add(S,i,-c[i]);
		if(c[i]>0)Max_Flow::add(i,T,c[i]);
		Max_Flow::add(SS,i,INF),Max_Flow::add(i,TT,INF);
	}
	Max_Flow::dinic(S,T);
	Max_Flow::add(TT,SS,INF);
	printf("%d\n",Max_Flow::dinic(S,T));
	return 0;
}
