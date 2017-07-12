
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define updata(k) size[k] = size[ch[k][0]] + size[ch[k][1]] + 1
#define newnode(k,F,V) k = ++sz;  fa[k] = F; tr[k] = V; size[k] = 1
const int N = 100000 + 5;
using namespace std;

int ch[N][2];
int size[N],tr[N];
int sz,fa[N],root;
int rev[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void down(int k)
{
	if(rev[k])
	{
		if(ch[k][0])
		{
			int t = ch[k][0] ; rev[t] ^= 1;
			swap(ch[t][0],ch[t][1]);
		}
		if(ch[k][1])
		{
			int t = ch[k][1] ; rev[t] ^= 1;
			swap(ch[t][0],ch[t][1]);
		}
		rev[k] = 0;
	}
}

struct Lux
{
	int x, pos;
}a[N];

bool cmp1(const Lux &a,const Lux &b)
{
	return a.x ^ b.x ? a.x < b.x : a.pos < b.pos;
}

bool cmp2(const Lux &a,const Lux &b)
{
	return a.pos < b.pos;
}

int T[N];

void build(int &k,int L,int R,int F)
{
	if(R < L) return ;
	int mid = (L+R) >> 1;
	newnode(k,F,a[mid].x);
	T[a[mid].x] = k;
	build(ch[k][0],L,mid-1,k);
	build(ch[k][1],mid+1,R,k);
	updata(k);
}

void rotate(int x)
{
	int y = fa[x], k = ch[y][1] == x;
	down(y),down(x);
	ch[y][k] = ch[x][!k] , fa[ch[y][k]] = y;
	fa[x] = fa[y]; ch[fa[y]][ch[fa[y]][1] == y] = x;
	ch[x][!k] = y; fa[y] = x;
	updata(y); updata(x);
}

void Splay(int x,int w)
{
	while(fa[x] != w)
	{
		int y = fa[x], z = fa[y];
		if(z == w) rotate(x);
		else if((ch[z][1] == y) == (ch[y][1] == x)) rotate(y),rotate(x);
		else rotate(x),rotate(x);
	}
	if(!w) root = x;
}

int find(int k,int rank)
{
	down(k);
	if(size[ch[k][0]] >= rank) return find(ch[k][0],rank);
	else if(size[ch[k][0]] + 1 == rank) return k;
	else return find(ch[k][1],rank - size[ch[k][0]] -1);
}

int main()
{
	int n = read();
	for(int i=1;i<=n;++i) a[i].x = read(), a[i].pos = i;
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;++i) a[i].x = i;
	sort(a+1,a+n+1,cmp2);
	newnode(root,0,-1);
	newnode(ch[root][1],root,-1);
	build(ch[ch[root][1]][0],1,n,ch[root][1]);
	updata(ch[root][1]);updata(root);
	
	for(int i=1;i<=n;++i)
	{
		Splay(T[i],0);
		printf("%d%c",size[ch[root][0]],i == n ? '\n' : ' ');
		int tmp1 = find(root,i);
		int tmp2 = size[ch[root][0]] + 2;
		tmp2 = find(root,tmp2);
		Splay(tmp1,0);Splay(tmp2,root);
		int tt = ch[root][1];
		rev[ch[tt][0]] ^= 1;
		swap(ch[ch[tt][0]][0],ch[ch[tt][0]][1]);
	}
}
