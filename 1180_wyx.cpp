
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define updata(k) tr[k] = tr[ch[k][0]] + tr[ch[k][1]] + a[k]
#define solve(k) rev[k] ^= 1, swap(ch[k][0],ch[k][1])
const int N = 30000+5;
using namespace std;

int ch[N][2],tr[N],a[N],fa[N];
bool rev[N],root[N];

void pushdown(int k)
{
	if(rev[k])
	{
		rev[k] = 0;
		if(ch[k][0]) solve(ch[k][0]);
		if(ch[k][1]) solve(ch[k][1]);
	}
}

void down(int k)
{
	if(!root[k]) down(fa[k]);
	pushdown(k);
}

void rotate(int x)
{
	int y = fa[x], k = ch[y][1] == x;
	ch[y][k] = ch[x][!k], fa[ch[y][k]] = y;
	fa[x] = fa[y]; ch[x][!k] = y, fa[y] = x;
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
		else if((ch[y][1] == x) == (ch[z][1] == y)) rotate(y),rotate(x);
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

int find(int x)
{
	while(fa[x]) x = fa[x];
	return x;
}

inline void link(int x,int y)
{
	move(x);
	fa[x] = y;
}

inline int ask(int x,int y)
{
	move(x);
	access(y);
	Splay(y);
	return tr[y];
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
	int n = read();
	for(int i=1;i<=n;++i) tr[i] = a[i] = read(),root[i] = 1;
	int q = read(),x,y;
	char str[11];
	for(int i=1;i<=q;++i)
	{
		scanf("%s",str); x = read(), y = read();
		if(str[0] == 'e')
		{
			if(find(x) != find(y)) puts("impossible");
			else printf("%d\n",ask(x,y));
		}
		else if(str[0] == 'p')
		{
			move(x);
			a[x] = y;
			updata(x);
		}
		else
		{
			if(find(x) == find(y)) puts("no");
			else puts("yes"), link(x,y);
		}
	}
}
