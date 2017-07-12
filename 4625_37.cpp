
#include <stdio.h>
#include <map>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 1e5+5;
const int BASE = 30000;
typedef long long ll;
map<pair<int,int>,int>val,vis;
int ex[N],x[N],y[N],c[N];
int dx[]={0,0,1,-1,1,-1};
int dy[]={1,-1,0,0,1,-1};
struct E
{
	int next,to,f;
}e[N*100];
int head[N],tot=1;
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
	Q.push(t);
	d[t] = 0;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(d[e[i].to]==-1&&e[i^1].f)
			{
				d[e[i].to] = d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[s]!=-1;
}
int get_mxf(int s,int t,int mf)
{
	if(s==t)return mf;
	int last = mf;
	for(int i = head[s];i;i=e[i].next)
	if(d[e[i].to]==d[s]-1&&e[i].f)
	{
		int tof = get_mxf(e[i].to,t,min(e[i].f,last));
		if(tof)
		{
			e[i].f-=tof;
			e[i^1].f+=tof;
			if(!(last-=tof))return mf;
		}
	}
	return mf-last;
}
int dinic(int s,int t)
{
	int ans = 0;
	while(bfs(s,t))
		ans+=get_mxf(s,t,INF);
	return ans;
}
int l[N],r[N];
int main()
{
	int n,z,C,cnt = 0,ans=0;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d%d%d",&x[i],&y[i],&z,&C);
		x[i]-=z,y[i]-=z;
		c[i] = (x[i]+y[i])%3==0?C*11:C*10;
		ans+=c[i];
		if(!vis[make_pair(x[i],y[i])])
			vis[make_pair(x[i],y[i])]=i,val[make_pair(x[i],y[i])]=c[i];
		else
			val[make_pair(x[i],y[i])]+=c[i],ex[i]=true;
	}
	int idx = 0;
	for(int i = 1;i<= n;i++)
		l[i]=++idx,r[i]=++idx;
	int S = ++idx,T = ++idx;
	for(int i = 1;i<= n;i++)
		if(!ex[i]&&(x[i]+y[i]+BASE)%3==0)
			add(l[i],r[i],val[make_pair(x[i],y[i])]);
	for(int i = 1;i<= n;i++)
		if(!ex[i]&&(x[i]+y[i]+BASE)%3==1)
			add(S,r[i],val[make_pair(x[i],y[i])]);
	for(int i = 1;i<= n;i++)
		if(!ex[i]&&(x[i]+y[i]+BASE)%3==2)
			add(l[i],T,val[make_pair(x[i],y[i])]);
	for(int i = 1;i<= n;i++)
		if(!ex[i])
		{
			for(int j = 0;j<6;j++)
			{
				int xx = x[i]+dx[j],yy = y[i]+dy[j];
				int tmp = vis[make_pair(xx,yy)];
				if(!tmp)continue;
				if ((xx+yy+BASE) % 3 == 0 && (x[i]+y[i]+BASE)%3 == 1) add(r[i],l[tmp],INF);
            	if ((xx+yy+BASE) % 3 == 2 && (x[i]+y[i]+BASE)%3 == 0) add(r[i],l[tmp],INF);

			}
		}
	ans-=dinic(S,T);
	printf("%d.%d\n",ans/10,ans%10);
	return 0;
}
