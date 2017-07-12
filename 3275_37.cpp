
#include <stdio.h>
#include <queue>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3005;
const int M = 2e6+5;
const int INF = 0x3f3f3f3f;
struct F
{int next,to,flow;}e[M];
int head[N],tot=1;
void add(int x,int y,int f)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;e[tot].flow=f;
	e[++tot].to=x;e[tot].next=head[y];head[y]=tot;e[tot].flow=0;
}
int d[N];
queue<int>Q;
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
			if(d[e[i].to]==-1&&e[i^1].flow)
			{
				d[e[i].to] = d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[s]!=-1;
}
int get_maxflow(int s,int t,int mf)
{
	if(s==t)return mf;
	int last = mf;
	for(int i = head[s];i;i=e[i].next)
		if(d[e[i].to]==d[s]-1&&e[i].flow)
		{
			int tof = get_maxflow(e[i].to,t,min(e[i].flow,last));
			if(tof)
			{
				e[i].flow-=tof;
				e[i^1].flow+=tof;
				if(!(last-=tof))return mf;
			}
		}
	d[s] = -1;
	return mf-last;
}
int dinic(int s,int t)
{
	int ans=0,nowflow;
	while(bfs(s,t))
		while((nowflow=get_maxflow(s,t,INF))!=0)
			ans+=nowflow;
	return ans;
}
int a[N];
int gcd(int x,int y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
bool check(int x,int y)
{
	if(gcd(x,y)!=1)return false;
	int tmp = x*x+y*y;
	if(((int)sqrt(tmp))*((int)sqrt(tmp))==tmp)return true;
	return false;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	int st = 0,end = n+1;
	int sum = 0;
	for(int i = 1;i<= n;i++)
	{
		if(a[i]&1)add(st,i,a[i]);
		else add(i,end,a[i]);
		sum+=a[i];
	}
	for(int i = 1;i<= n;i++)
		if(a[i]&1)
			for(int j = 1;j<= n;j++)
				if(!(a[j]&1))
					if(check(a[i],a[j]))
						add(i,j,INF);
	int ans = dinic(st,end);
	printf("%d\n",sum-ans);
	return 0;
}
