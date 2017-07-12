
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 7e4+5;
const int M = 7e5+5;
const int INF = 0x3f3f3f3f;
struct E
{
	int next,to,f;
}e[M];
int head[N],tot=1;
void add(int x,int y,int f1,int f2)
{
	e[++tot].to=y;e[tot].next=head[x];head[x]=tot;e[tot].f=f1;
	e[++tot].to=x;e[tot].next=head[y];head[y]=tot;e[tot].f=f2;
}
queue<int>Q;
int pos[45][45][45];
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
			if(d[e[i].to]==-1&&e[i^1].f)
			{
				d[e[i].to] = d[x]+1;
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
		if(d[e[i].to]==d[s]-1&&e[i].f)
		{
			int tof = get_mf(e[i].to,t,min(last,e[i].f));
			if(tof)
			{
				e[i].f-=tof;
				e[i^1].f+=tof;
				if(!(last-=tof))return mf;
			}
		}
	d[s] = -1;
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
int main()
{
	int n,id = 0;
	scanf("%d",&n);
	int st = 0,end = n*n*n+1;
	for(int i=1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			for(int k = 1;k<= n;k++)
				pos[i][j][k]=++id;
	for(int i= 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			for(int k = 1;k<= n;k++)
			{
				if(i!=n)add(pos[i][j][k],pos[i+1][j][k],1,1);
				if(j!=n)add(pos[i][j][k],pos[i][j+1][k],1,1);
				if(k!=n)add(pos[i][j][k],pos[i][j][k+1],1,1);
			}
	char ch;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			for(int k = 1;k<= n;k++)
			{
				ch = getchar();while(ch!='P'&&ch!='N'&&ch!='?')ch = getchar();
				if(ch=='P')
				{
					if((i+j+k)&1)add(st,pos[i][j][k],INF,0);
					else add(pos[i][j][k],end,INF,0);
				}else if(ch=='N')
				{
					if((i+j+k)&1)add(pos[i][j][k],end,INF,0);
					else add(st,pos[i][j][k],INF,0);
				}
			}
	int ans = dinic(st,end);
	printf("%d",3*n*n*(n-1)-ans);
	return 0;
}
