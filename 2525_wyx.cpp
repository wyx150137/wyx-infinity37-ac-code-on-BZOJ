
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define mp make_pair
const int N = 600000+5;
const int M = N << 1;
typedef pair<int,int> P;

const int inf = 0x3f3f3f3f;

int head[N];

struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val=0)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,int z=0)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] = cnt;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
	return x*f;
}

int mid;
int tt;
int d[N];

P DFS(int x,int fa)
{
	P re = mp(-inf,inf);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa)
		{
			P tmp = DFS(edge[i].to,x);
			re.first = max(re.first,tmp.first+1);
			re.second = min(re.second,tmp.second+1);
		}
	if(d[x] && re.second > mid) re.first = max(0,re.first);
	if(re.first + re.second <= mid) re.first = -inf;
	if(re.first == mid)  tt ++,re.first = -inf,re.second = 0;
	return re;
}


int main()
{
	int n = read(), m = read();
	for(int i=1;i<=n;++i) d[i] = read();
	for(int i=1;i<n;++i)
	{
		int x = read(),y = read();
		add(x,y);
	}
	int l = 0 ;
	int r = n;
	int ans=0;
	while(l<=r)
	{
		mid = (l+r)>>1;
		tt = 0;
		P tmp = DFS(1,1);
		if(tmp.first + tmp.second > mid) tt ++;
		if(tt <= m)  ans = mid,r = mid - 1;
		else l = mid + 1;
	}
	cout << ans << endl;
}
