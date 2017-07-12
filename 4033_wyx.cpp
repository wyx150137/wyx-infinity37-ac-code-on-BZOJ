
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 2000+5
#define M 5000+5

using namespace std;
typedef long long LL;

int head[N];
LL n,lmt;

struct graph
{
	int next,to;
	LL val;
	graph () {}
	graph (int _next,int _to,LL _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,LL z)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] = cnt;
}

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

LL size[N];

LL f[N][N];

void Getsize(int x,int fa)
{
	size[x] = 1;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
			Getsize(edge[i].to,x),size[x] += size[edge[i].to];
}	

void dp(int x,int fa)
{
	f[x][0] = f[x][1] = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
			dp(edge[i].to,x);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
			for(int j=size[x];~j;--j)
				for(int k=0;k<=min(size[edge[i].to],(LL)j);++k)
					f[x][j] = max(f[x][j],f[x][j-k]+f[edge[i].to][k]+((LL)(k)*(lmt-k)+
							(LL)(size[edge[i].to]-k)*(LL)(n-lmt-(size[edge[i].to]-k)))*(LL)edge[i].val
						);
}

int main()
{
	n = read() , lmt = read();
	memset(f,128,sizeof f);
	for(int i=1;i<n;++i)
	{
		int x = read() ,y = read() , z = read();
		add(x,y,z);
	}
	Getsize(1,1);
	dp(1,1);
	cout<<f[1][lmt];	
}
