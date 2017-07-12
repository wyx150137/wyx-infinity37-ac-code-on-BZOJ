
#include <cctype>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000010;
const int M = N << 1;
typedef long long LL;
using namespace std;

LL ans;
int head[N];
int in[N],k;

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
	in[x] ++ , in[y] ++;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

int a[N];

char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}

LL read()
{
    static char ch;
    static LL D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}


int m,n;

int ask(LL x)
{
	int l = 1; 
	int r = m;
	int re ;
	if(x > a[m]) return m;
	if(x < a[1]) return 0;
	while( l <= r )
	{
		int mid = (l+r) >> 1;
		if(a[mid] < x) re = mid , l = mid + 1;
		else r = mid - 1;
	}
	return re;
}

void DFS(int x,int fa,int t)
{
	if(!in[x])
		ans += ask((LL)(k+1)*t) - ask((LL)k * t);
	if((LL)t*in[x] > a[m]) return ;t = t * in[x];
	for(int  i = head[x] ; i ; i =edge[i].next)
		if( i > 2 && edge[i].to != fa)
			DFS(edge[i].to,x,t);
}

int main()
{
	n = read(), m = read(),k = read();
	register int i;
	for( i = 1; i <= m ; ++ i) a[i] = read();
	sort(a+1,a+m+1);
	for( i = 1; i < n ; ++i) {
		int x = read(), y = read();
		add(x,y);
	}
	for( i = 1; i <= n; ++ i) -- in[i];
	DFS(edge[1].to,0,1);
	DFS(edge[2].to,0,1);
	cout << ans * k;
}
