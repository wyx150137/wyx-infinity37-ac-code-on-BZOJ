
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define reverse(k) rev[k]^=1, swap(ch[k][0],ch[k][1])
const int M = 100000+5;
const int N = M << 1;
using namespace std;

int ch[N][2],tr[N],val[N],pos[N],n,m,fa[N];
bool rev[N],root[N];

void updata(int k)
{
	tr[k] = val[k],pos[k] = k;
	if(tr[ch[k][0]] > tr[k]) tr[k] = tr[ch[k][0]], pos[k] = pos[ch[k][0]];
	if(tr[ch[k][1]] > tr[k]) tr[k] = tr[ch[k][1]], pos[k] = pos[ch[k][1]];
}

void push(int k)
{
	if(rev[k])
	{
		rev[k] ^=1;
		if(ch[k][0]) reverse(ch[k][0]);
		if(ch[k][1]) reverse(ch[k][1]);
	}
}

void down(int x)
{
	if(!root[x]) down(fa[x]);
	push(x);
}

void rotate(int x)
{
	int y = fa[x] , k = ch[y][1] == x;
	ch[y][k] = ch[x][!k] , fa[ch[y][k]] = y;
	ch[x][!k] = y, fa[x] = fa[y], fa[y] = x;
	if(root[y]) swap(root[x],root[y]);
	else ch[fa[x]][ch[fa[x]][1] == y] = x;
	updata(y);
}

void Splay(int x)
{
	down(x);
	while(!root[x])
	{
		int y = fa[x], z = fa[y];
		if(root[y]) rotate(x);
		else if((ch[z][1] == y) == (ch[y][1] == x)) rotate(y),rotate(x);
		else rotate(x),rotate(x);
	}
	updata(x);
}

void access(int x)
{
	int y = 0;
	while(x)
	{
		Splay(x); root[ch[x][1]] = 1 ,root[y] = 0; ch[x][1] = y;
		updata(x);  y = x; x = fa[x];
	}
}

void move(int x)
{
	access(x);
	Splay(x);
	reverse(x);
}

inline void link(int x,int y)
{
	move(x);
	fa[x] = y;
}

inline void cut(int x,int y)
{
	move(x); access(y);Splay(y);
	ch[y][0] = fa[x] = 0;
	updata(y); root[x] = 1;
}

inline int find(int x)
{
	while(fa[x]) x = fa[x];
	return x;
}

inline int ask(int x,int y)
{
	if(find(x) != find(y)) return -1;
	move(x); access(y); Splay(y);
	return tr[y];
}

struct graph
{
	int from , to , a , b;
	bool operator < (const graph &z)const
	{
		return a ^ z.a ? a < z.a : b < z.b;
	}
}edge[M];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	n = read(), m = read();
	for(int i=1;i<=m;++i) edge[i].from = read(),edge[i].to = read(),edge[i].a = read(), edge[i].b = read();
	for(int i=1;i<=m+n;++i) root[i] = 1, tr[i] = 0, pos[i] = i;
	int ans = 0x7fffffff; sort(edge+1,edge+m+1);
	for(int i=1;i<=m;++i)
		if(edge[i].from != edge[i].to)
		{
			int x = edge[i].from , y = edge[i].to;
			if(find(x) != find(y))
			{
				tr[i+n] = val[i+n] = edge[i].b;
				link(x,i+n); link(y,i+n);
			}
			else
			{
				move(x); access(y); Splay(y);
				int tmp = pos[y];
				if(val[tmp] > edge[i].b)
				{
					cut(tmp,edge[tmp-n].from);
					cut(tmp,edge[tmp-n].to);
					link(x,i+n); link(y,i+n);
					tr[i+n] = val[i+n] = edge[i].b;
				}
			}
			int tt = ask(1,n);
			if(tt != -1)
				ans = min(ans,tt + edge[i].a);
		}
	if(ans == 0x7fffffff)
		puts("-1");
	else cout << ans << endl;
	
}
