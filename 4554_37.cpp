
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 6005;
const int INF = 0x3f3f3f3f;
struct E
{
	int next,to,f;
}e[N*10];
int head[N],tot=1;
int d[N];
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].f = f;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;e[tot].f = 0;
}
queue<int>Q;
bool bfs(int s,int t)
{
	for(int i = s;i<=t;i++)d[i]=-1;
	d[s] = 0;
	Q.push(s);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(d[e[i].to]==-1&&e[i].f)
			{
				d[e[i].to] = d[x]+1;
				Q.push(e[i].to);
			}
	}
	return d[t]!=-1;
}
int get_mxf(int s,int t,int mx)
{
	if(s==t)return mx;
	int last = mx;
	for(int i = head[s];i;i=e[i].next)
		if(d[e[i].to]==d[s]+1&&e[i].f)
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
int n,m;
char s[55][55];
inline int id(int x,int y)
{
	return (x-1)*m+y;
}
int bl1[N],bl2[N];
int main()
{
	int cnt1=1,cnt2=1;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		scanf("%s",s[i]+1);
	for(int i = 1;i<= n;i++)
	{
		for(int j = 1;j<= m;j++)
			if(s[i][j]=='#')cnt1++;
			else bl1[id(i,j)] = cnt1;
		cnt1++;
	}
	for(int j = 1;j<= m;j++)
	{
		for(int i = 1;i<= n;i++)
			if(s[i][j]=='#')cnt2++;
			else bl2[id(i,j)]=cnt2;
		cnt2++;
	}
	int S =0,T = cnt1+cnt2+1;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			if(s[i][j]=='*')add(bl1[id(i,j)],bl2[id(i,j)]+cnt1,1);
	for(int i = 1;i<= cnt1;i++)add(S,i,1);
	for(int i = 1;i<= cnt2;i++)add(i+cnt1,T,1);
	printf("%d\n",dinic(S,T));
	return 0;
}
