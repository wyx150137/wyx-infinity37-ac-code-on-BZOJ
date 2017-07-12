
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 405;
const int M = 4e4+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,f;}e[M];
int head[N],tot=1;
void add(int x,int y,int f)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;e[tot].f=f;
	e[++tot].to=x;e[tot].next=head[y];head[y]=tot;e[tot].f=0;
}
int d[N];
queue<int>Q;
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
				d[e[i].to]=d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[s]!=-1;
}
int get_mf(int s,int t,int mf)
{
	if(s==t)return mf;
	int last = mf;
	for(int i = head[s];i;i=e[i].next)
		if(e[i].f&&d[e[i].to]==d[s]-1)
		{
			int tof = get_mf(e[i].to,t,min(last,e[i].f));
			if(tof)
			{
				e[i].f-=tof;
				e[i^1].f+=tof;
				if(!(last-=tof))return mf;
			}
		}
	d[s]=-1;
	return mf-last;
}
int dinic(int s,int t)
{
	int ans = 0,nf;
	while(bfs(s,t))
		while((nf=get_mf(s,t,INF)))
			ans+=nf;
	return ans;
}
int cntb[N],cntg[N];
char map[N][N];
void debug()
{
	for(int i = 0;i<= 7;i++)
	{
		printf("%d:",i);
		for(int j = head[i];j;j=e[j].next)
			printf("%d(%d) ",e[j].to,e[j].f);
		printf("\n");
	}
}
void build(int n,int mid,int k)
{
    tot=1;memset(head,0,sizeof(head));
    for(int i=1;i<=n;i++)add(0,i*2-1,mid);
    for(int i=1;i<=n;i++)add(i*2-1,i*2,k);
    for(int i=1;i<=n;i++)add(n*2+i*2,n*2+i*2-1,k);
    for(int i=1;i<=n;i++)add(n*2+i*2-1,4*n+1,mid);
    for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
		{
			if(map[i][j]=='N')
				add(i*2,n*2+j*2,1);
			else
				add(i*2-1,2*n+j*2-1,1);
		}
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)
		scanf("%s",map[i]+1);
	int st = 0,end = 4*n+1;
	int l = 0,r = n,ans=0;
	while(l<=r)
	{
		int mid = (l+r)>>1;
		build(n,mid,k);
		if(dinic(st,end)>=n*mid)l=mid+1,ans=mid;
		else r = mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
