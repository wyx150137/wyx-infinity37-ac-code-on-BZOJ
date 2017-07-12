
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue> 
using namespace std;
#define N 500000+5
#define M 1000000+5

const int inf = 2147483647;

int head[N];

struct graph
{
	int next,to;
	int val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,int z)
{
	static int cnt = 0 ;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] = cnt;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int LMAX[N],RMAX[N],MAX[N],dis[N];
int path[N];
bool in[N];
int len;

struct Lux
{
	int x,from;
	int dis;
	Lux () {}
	Lux (int _x,int _from,int _dis = 0)
	:x(_x),from(_from),dis(_dis){}
};

queue <Lux> q;

void Getdis(int x)
{
	q.push(Lux(x,x));
	while(!q.empty())
	{
		Lux tmp = q.front();
		q.pop();
		int tt = tmp.x;
		for(int i=head[tt];i;i=edge[i].next)
			if(edge[i].to!=tmp.from)
			{
				dis[edge[i].to] = dis[tt] + edge[i].val;
				q.push(Lux(edge[i].to,tt));
			}
	}
}

int GetMAX(int x,int fa)
{
	int MAX = 0;
	/*for(int i=head[x];i;i=edge[i].next)
		if(!in[edge[i].to]&&edge[i].to!=fa)
			MAX = max(MAX,GetMAX(edge[i].to,x)+edge[i].val);
	return MAX;*/
	q.push(Lux(x,fa,0));
	while(!q.empty())
	{
		Lux tmp = q.front();
		int dis = tmp.dis;
		q.pop();
		MAX = max(MAX,dis);
		int tt = tmp.x;
		for(int i=head[tt];i;i=edge[i].next)
			if(edge[i].to!=tmp.from && !in[edge[i].to])
				q.push(Lux(edge[i].to,tt,dis+edge[i].val));
	}
	return MAX;
}

int from[N];

bool find(int x,int tmp,int fa)
{
	/*if(x==tmp)
	{
		path[++len] = tmp;
		return 1;
	}
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa && find(edge[i].to,tmp,x))
			{path[++len] = x;return 1;}
	return false;*/
	q.push(Lux(x,x));	
	while(!q.empty())
	{
		Lux tmp1 = q.front();
		q.pop();
		int tt = tmp1.x;
		for(int i=head[tt];i;i=edge[i].next)
			if(edge[i].to!=tmp1.from)
			{
				from[edge[i].to] = tt;
				q.push(Lux(edge[i].to,tt));
			}
	}
	int tt = tmp;
	while(tt!=x)
	{
		path[++len] = tt;
		tt = from[tt];
	}
	path[++len] = x;
	return 1;
}

int que[N];

int main()
{
//	freopen("01.in","r",stdin);
	int n = read() ;
	int s = read();
	for(int i=1;i<n;++i)
	{
		int a = read() , b = read() ;
		int c = read();
		add(a,b,c);
	}
	int A = 1, B = 1;
	Getdis(1);
	for(int i=1;i<=n;++i)
		if(dis[i] >= dis[A])
			A = i;
	dis[A] = 0;
	Getdis(A);
	for(int i=1;i<=n;++i)
		if(dis[i]>=dis[B])
			B = i;
	find(B,A,0);
	for(int i=1;i<=len;++i)
		in[path[i]] = 1;
	for(int i=1;i<=len;++i)
		MAX[i] = GetMAX(path[i],0);
	for(int i=1;i<=len;++i)
		LMAX[i] = dis[path[i]] - dis[path[1]],RMAX[i] = dis[path[len]] - dis[path[i]];
//	cout<<len<<endl;
//	for(int i=1;i<=len;++i)
//		cout<<path[i]<<" ";
//	return 0 ;
	int l = 0, r = 0;
	int ans = inf, tmp;
	for(int i = 1, j = 1; i <= len; i++)
	{
		if(l != r && que[l] < i) que[l++] = 0;
		while(j <= n && dis[path[j]] - dis[path[i]] <= s)
		{
	    	while(l != r && MAX[que[r-1]] <= MAX[j]) que[--r] = 0;
	    	que[r++] = j++;
		}
		tmp = max(MAX[que[l]], max(LMAX[i], RMAX[j-1]));
		ans = min(ans,tmp);
	}
	cout<<ans;
}		
