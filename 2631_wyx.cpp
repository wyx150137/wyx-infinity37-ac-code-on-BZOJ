
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int mod = 51061;
const int N = 1e5+5;
#define updata(k) tr[k] = (tr[ch[k][0]] + tr[ch[k][1]] + a[k])%mod, size[k] = size[ch[k][0]] + size[ch[k][1]] + 1
#define reverse(k) rev[k] ^= 1, swap(ch[k][0],ch[k][1])
typedef unsigned int LL;
using namespace std;
int ch[N][2],fa[N];
int root[N],rev[N];
LL tr[N],add[N],mul[N],a[N],size[N];

void pushdown(int k)
{
	if(ch[k][0])
	{
		int t = ch[k][0];
		mul[t] =  mul[t] * mul[k]%mod;
		add[t] = (add[t] * mul[k]%mod + add[k])%mod;
		tr[t] = ((mul[k] * tr[t])%mod + (add[k] * size[t])%mod)%mod;
		a[t] = (mul[k] * a[t]%mod + add[k])%mod;
	}
	if(ch[k][1])
	{
		int t = ch[k][1];
		mul[t] =  mul[t] * mul[k]%mod;
		add[t] = (add[t] * mul[k]%mod + add[k])%mod;
		tr[t] = ((mul[k] * tr[t])%mod + (add[k] * size[t])%mod)%mod;
		a[t] = (mul[k] * a[t]%mod + add[k])%mod;
	}
	mul[k] = 1;
	add[k] = 0;
	if(rev[k])
	{
		rev[k] = 0;
		if(ch[k][0]) reverse(ch[k][0]);
		if(ch[k][1]) reverse(ch[k][1]);
	}
}

inline void down(int k)
{
	if(!root[k]) down(fa[k]);
	pushdown(k);
}

void rotate(int x)
{
	int y = fa[x] , k = ch[y][1] == x;
	ch[y][k] =  ch[x][!k] , fa[ch[y][k]] = y;
	fa[x] = fa[y] ; ch[x][!k] = y, fa[y] = x;
	if(root[y]) swap(root[x],root[y]);
	else ch[fa[x]][ch[fa[x]][1] == y] = x;
	updata(y);
}

void Splay(int x)
{
	down(x);
	while(!root[x])
	{
		int  y = fa[x] , z= fa[y];
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
		root[ch[x][1]] = 1, root[y] = 0;
		ch[x][1] = y;
		y = x; x = fa[x];
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
	move(x);
	access(y);
	Splay(y);
	ch[y][0] = fa[x] = 0;
	root[x] = 1;
	updata(y);
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
	int n = read(), q = read();
	for(int i=1;i<=n;++i)
		mul[i] = tr[i] = size[i] = root[i] = a[i] = 1;
	for(int i=1;i<n;++i)
	{
		int x = read(), y = read();
		link(x,y);
	}
	char str[10];
	while(q--)
	{
		scanf("%s",str);
		if(str[0] == '+'){
			int x = read(), y = read(), c = read();
			move(x);
			access(y);
			Splay(y);
			(add[y] += c) %= mod;
			(tr[y] += (LL)c * size[y]%mod) %= mod;
			(a[y] += c) %= mod;
		}
		else if(str[0] == '-')
		{
			int x = read(), y = read();
			cut(x,y);
			x = read(), y = read();
			link(x,y);
		}
		else if(str[0] == '*'){
			int x = read(), y = read() , c = read();
			move(x);
			access(y);
			Splay(y);
			(mul[y] *= c) %= mod;
			(add[y] *= c) %= mod;
			(a[y] *= c) %= mod ;
			(tr[y] *= c) %= mod ;
		}
		else if(str[0] == '/')
		{
			int x = read(), y = read();
			move(x);
			access(y);
			Splay(y);
			printf("%d\n",tr[y] % mod) ;
		}
	}
}
