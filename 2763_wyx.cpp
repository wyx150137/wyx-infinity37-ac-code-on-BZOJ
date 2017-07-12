
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <algorithm>
#define N 10010+5
#define M 100000+5
#define inf 0x7fffff
using namespace std;
int head[N],dis[N][12];
bool in[N];
int n,m,p,s,t;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];
inline void add(int x,int y,int z)
{
	static int cnt = 0;
	edge[++cnt]=graph(head[x],y,z);
	head[x]=cnt;
	edge[++cnt]=graph(head[y],x,z);
	head[y]=cnt;
}
deque <int> q;
int spfa()
{
	memset(dis,0x7f,sizeof dis);
	in[s]=1;dis[s][0]=0;
	q.push_front(s);
	while(!q.empty())
	{
		int tt=q.front();
		q.pop_front();
		in[tt]=false;
		for(int i=head[tt];i;i=edge[i].next)
		{
			bool Push=false;
			for(int tmp = 0;tmp <= p;++tmp)
			{	
				if(dis[edge[i].to][tmp]>dis[tt][tmp]+edge[i].val)	
				{
					dis[edge[i].to][tmp]=dis[tt][tmp]+edge[i].val;
					if(!in[edge[i].to])
						Push=true;
				}
				if(dis[edge[i].to][tmp+1]>dis[tt][tmp])
				{
					dis[edge[i].to][tmp+1]=dis[tt][tmp];
					if(!in[edge[i].to])
						Push=true;
				}
			}
			if(Push)
			{
				if(!q.empty())
				{
					int P = q.front();
					if(dis[edge[i].to][0]<dis[P][0])
						q.push_front(edge[i].to);
					else
						q.push_back(edge[i].to);
					in[edge[i].to]=1;
				}
				else
					q.push_front(edge[i].to),in[edge[i].to]=1;	
			}
		}
		
	}
	int re = inf;
	for(int i=0;i<=p;++i)
		re=min(re,dis[t][i]);
	return re;
}
int main()
{
	scanf("%d%d%d%d%d",&n,&m,&p,&s,&t);
	for(int i=1;i<=m;++i)
	{
		int a=read(),b=read(),c=read();
		add(a,b,c);
	}
	cout<<spfa();
}
