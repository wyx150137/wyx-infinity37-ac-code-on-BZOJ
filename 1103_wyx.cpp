
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define lowbit(x) ((x)&(-x))
const int N = 250000+5;
const int M = N<<1;
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N];
int fir[N],sec[N];
int T[N],stack[N<<1];
int top,sz;

struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

void updata(int x,int num)
{
	while(x<=M)
	{
		T[x] += num;
		x+=lowbit(x);
	}
}

int ask(int x)
{
	int ans = 0;
	while(x)
	{
		ans += T[x];
		x-=lowbit(x);
	}
	return ans;
}

void DFS(int x,int fa)
{
	fir[x] = ++sz;
	updata(fir[x],1);
	for(int i=head[x] ; i ; i = edge[i].next)
		if(edge[i].to!=fa)
			DFS(edge[i].to,x);	
	sec[x] = ++sz;
	updata(sec[x],-1);
}

int main()
{
	int n = read();
	for(int i=1;i<n;++i)
	{
		int a = read(),b=read();
		add(a,b);
	}
	DFS(1,1);
	sec[1] = ++sz;
	int m = read();
	m += n;
	m --;
	while(m--)
	{
		char str[10];
		scanf("%s",str);
		if(str[0]=='W')
		{
			int x = read();
			printf("%d\n",ask(fir[x])-1);
		}
		else
		{
			int x=read(),y=read();
			updata(fir[y],-1);
			updata(sec[y],1);
		}
	}

}
