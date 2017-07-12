
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>
#define N 100000+5
#define M 2000000+5
using namespace std;

long long dis[N],sec[N];
int head[N],pre[N];
bool in[N];
int n,m,k;

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
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] = cnt;
}

queue <int> Q;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

void spfa()
{
	memset(dis,0x7f,sizeof dis);
	memset(sec,0x7f,sizeof sec);
	memset(in,false,sizeof false);
	for(int i=1;i<=k;++i)
	{
		int x = read()+1;
		dis[x] = sec[x] = 0;
		in[x] = 1;Q.push(x);
	}
	while(!Q.empty())
	{
		int tt = Q.front();Q.pop();in[tt] = false;
		for(int i=head[tt];i;i=edge[i].next)
		{
			int x = edge[i].to;
			if(dis[x]>=sec[tt]+edge[i].val)
			{
				if(pre[x]!=tt)
					sec[x] = dis[x];
				dis[x] = sec[tt] + edge[i].val;
				pre[x] = tt;
				if(!in[x])
				{
					in[x] = 1;
					Q.push(x);
				}
			}
			else if(sec[x]>sec[tt]+edge[i].val)
			{
				sec[x] = sec[tt] + edge[i].val;
				if(!in[x])
				{
					in[x] = 1;
					Q.push(x);
				}
			}
		}
	}
}

int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=m;++i)
	{
		int x=read()+1,y=read()+1,z=read();
		add(x,y,z);
	}
	spfa();
	cout<<sec[1];
}
