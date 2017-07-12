
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 100000+5;
const int M = 200000+5;
using namespace std;

const int inf = 10000000;

int head[N];

struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

int pos = 0;

inline void add(int x,int y,int z)
{
	static int cnt = 1;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] = cnt;
}

int s2[N],s1[N];
int MAX;

int DFS(int x,int fa)
{
	int mx_1 = 0;
	int mx_2 = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
		{
			int tt = edge[i].val+DFS(edge[i].to,x);
			if(tt > mx_1)
				mx_2 = mx_1,mx_1 = tt,s2[x] = s1[x] ,s1[x] = i;
			else if(tt > mx_2)
				mx_2 = tt,s2[x] = i;
		}	
	if(mx_1 + mx_2 > MAX)
		MAX = mx_1 + mx_2,pos = x;
	return mx_1;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1) + (x<<3) + ch - '0' ; ch = getchar();}
	return x*f;
} 

int main()
{
	int n = read() ,k = read();
	for(int i=1;i<n;++i)
	{
		int x = read(), y =read();
		add(x,y,1);
	}

	DFS(1,0);

	if(k==1)
	{
		cout << ((n-1) <<1 ) - MAX + 1 << endl;
		return 0;
	}
	else
	{
		int tMAX = MAX;
		MAX = -inf;
		for(int i=s1[pos];i;i=s1[edge[i].to])edge[i].val = edge[i^1].val = -1;
		for(int i=s2[pos];i;i=s1[edge[i].to])edge[i].val = edge[i^1].val = -1;
		DFS(1,0);
		cout << ((n-1) <<1 ) - MAX - tMAX + 2;
	}
}
