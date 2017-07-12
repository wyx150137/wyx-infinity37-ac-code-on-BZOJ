
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100010
#define M N << 1
using namespace std;

int head[N];

struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y)
{
	static int cnt = 0 ;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n,s;
int ans;
int f[N],a[N];

void DFS(int x,int fa,int lmt)
{
	f[x] = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
			DFS(edge[i].to,x,lmt);
	int cnt = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
			a[++cnt] = f[edge[i].to] + 1;
	sort(a+1,a+cnt+1);
	while(cnt && a[cnt] + a[cnt-1] > lmt)
		cnt -- , ans ++ ;
	f[x] = a[cnt];
}

bool check(int mid)
{
	ans = 0;
	DFS(1,0,mid);
	return ans <= s;
}

int main()
{
	cin >> n >> s;
	for(int i=1;i<n;++i)
	{
		int x = read() , y = read();
		add(x,y);
	}
	int l = 1;
	int r = n;
	int ans = n;
	while(l<=r)
	{
		int mid = (l+r)>>1;
		if(check(mid))
			ans = mid , r = mid - 1 ;
		else l = mid + 1;
	}
	printf("%d\n",ans);
}
