
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>
#define N 1000+50
#define M 20000+50
using namespace std;
int head[N],dis[N];
const int inf = 0x7fffff;
int pre[N],from[N];
struct graph
{
	int next,to,val;
	int deval;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];
int cnt = 0;
inline void add(int x,int y,int z)
{
	edge[++cnt] = graph(head[x],y,z);
	head[x]=cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y]=cnt;
}
int S,T;
bool in[N];
queue<int>Q;
void spfa()
{
	memset(dis,0x3f,sizeof dis);
	memset(in,false,sizeof in);
	memset(pre,0,sizeof pre);
	memset(from,0,sizeof from);
	Q.push(S),dis[S]=0;in[S]=1;
	while(!Q.empty())
	{
		int tt=Q.front();Q.pop();in[tt]=false;
		for(int i=head[tt];i;i=edge[i].next)
			if(dis[edge[i].to]>dis[tt]+edge[i].deval)
			{
				dis[edge[i].to]=dis[tt]+edge[i].deval;
				pre[edge[i].to] = tt;from[edge[i].to] = i;
				if(!in[edge[i].to])
				{
					Q.push(edge[i].to);
					in[edge[i].to]=1;
				}
			}
	}
}
int n,m,k;
bool check(int mid)
{
	for(int i=1;i<=cnt;++i)
	{
		if(edge[i].val<=mid)edge[i].deval = 0;
		else edge[i].deval = 1;
	}
	spfa();
	if(dis[T]>k)
		return false;
	return true;
}
inline int read()
{
	int x=0,f=1;char ch = getchar ();
	while (ch < '0' || ch > '9') {if (ch == '-')f=-1;ch = getchar();}
	while (ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch -'0';ch = getchar();}
	return x*f;
}
int main()
{	
	n=read(),m=read(),k=read();
	S = 1,T = n;
	int l = 0 , r = 0;
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read(),z=read();
		add(x,y,z); l = min(l,z),r = max(r,z);
	}
	int ans = inf;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(check(mid))
		{
			int now = n;	
			int tmp = 0;
			while(now ^ 1)
			{
				if(edge[from[now]].deval == 0)
					tmp = max(tmp,edge[from[now]].val);
				now = pre[now];
			}
			ans = min(ans,tmp);
			r = mid;
		}
		else
			l = mid + 1;
	}
	printf("%d\n",ans == inf ? -1 : ans);
}
