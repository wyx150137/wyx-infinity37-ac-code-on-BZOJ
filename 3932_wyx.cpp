
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 100000+5;
const int M = N << 1;
const int Maxm = 8000005;
typedef long long LL;
using namespace std;

int head[N];

struct graph
{
	int next,to;bool val;
	graph () {}
	graph (int _next,int _to,bool _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,bool z)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z); head[x] = cnt;
}

LL tr[Maxm];
int cnt[Maxm],ls[Maxm],rs[Maxm],root[N],sz;

void change(int L,int R,int x,int &y,int pos,int val)
{
	y = ++sz; rs[y] = rs[x],ls[y] = ls[x];
	cnt[y] = cnt[x] + val; tr[y] = tr[x] + (LL)val*pos;
	if(L == R) return;
	int mid = (L+R) >> 1;
	if(pos <= mid) change(L,mid,ls[x],ls[y],pos,val);
	else change(mid+1,R,rs[x],rs[y],pos,val);
}

LL find(int y,int rank,int L,int R)
{
	if(!cnt[y] || !rank) return 0;
	if(L == R) 
		return tr[y]/cnt[y]*rank;
	int mid = (L+R) >> 1, tt = cnt[ls[y]] ;
	if(rank <= tt) return find(ls[y],rank,L,mid);
	else return tr[ls[y]] + find(rs[y],rank-tt,mid+1,R);
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{

	int m = read(), n = read();

	for(int i=1;i<=m;++i)
	{
		int x = read(), y = read()+1, z = read();
		add(x,z,1);
		add(y,z,0);
	}

	for(int i=1;i<=n;++i)
	{
		root[i] = root[i-1];
		for(int j=head[i];j;j=edge[j].next)
			change(1,10000000+5,root[i],root[i],edge[j].to,(edge[j].val == 0 ? -1 : 1));
	}

	LL lastans = 1;
	int times,A,B,C;
	for(int i=1;i<=n;++i)
	{
		times = read(), A = read(), B = read(), C = read();
		A = ((long long)A * lastans + B)%C + 1;
		printf("%lld\n",lastans = find(root[times],A,1,10000000+5));
	}
}
