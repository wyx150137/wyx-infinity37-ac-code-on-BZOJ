
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define updata(k) tr[k] = tr[ch[k][0]] ^ tr[ch[k][1]] ^ a[k]
#define solve(k) rev[k] ^= 1, swap(ch[k][0],ch[k][1])
using namespace std;
const int N = 300000+5;
int ch[N][2],root[N],fa[N];
int tr[N],a[N],rev[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

void pushdown(int x)
{
	if(rev[x])
	{
		rev[x] = 0;
		if(ch[x][0]) solve(ch[x][0]);
		if(ch[x][1]) solve(ch[x][1]);
	}
}

void down(int x)
{
	if(!root[x]) down(fa[x]);
	pushdown(x);
}

void rotate(int x)
{
	int y = fa[x] , k = ch[y][1] == x;
	ch[y][k] = ch[x][!k] , fa[ch[y][k]] = y;
	fa[x] = fa[y]; ch[x][!k] = y , fa[y] = x;
	if(root[y]) swap(root[x],root[y]);
	else ch[fa[x]][ch[fa[x]][1] == y] = x;
	updata(y);
}

void Splay(int x)
{
	down(x);
	while(!root[x])
	{
		int y = fa[x] , z = fa[y];
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
		Splay(x);
		root[ch[x][1]] = 1, root[y] = 0; ch[x][1] = y;
		y = x; x = fa[x];
	}
}

void move(int x)
{
	access(x);
	Splay(x);
	solve(x);
}

inline void link(int x,int y)
{
	move(x);
	fa[x] = y;
}

inline void cut(int x,int y)
{
	move(x);
	access(y);
	Splay(y);
	if(ch[y][0] == x)
	{
		ch[y][0] = fa[x] = 0;
		root[x] = 1;
	}
	updata(y);
}

void change(int x,int val)
{
	a[x] = val;
	Splay(x);
	updata(x);
}

inline int find(int x)
{
	while(fa[x]) x = fa[x];
	return x;
}

int main()
{
	int n = read(), m = read();
	for(int i=1;i<=n;++i) tr[i] = a[i] = read() , root[i] = 1;
	for(int i=1;i<=m;++i)
	{
		int opt = read();
		int x = read(), y = read();
		if(opt == 0)
		{
			move(x); access(y); Splay(y);
			printf("%d\n",tr[y]);
		}
		else if(opt == 1)
		{
			if(find(x) != find(y)) 
				link(x,y);
		}
		else if(opt == 2)
			cut(x,y);
		else change(x,y);
	}
}
