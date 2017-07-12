
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define reverse(k) rev[k]^=1, swap(ch[k][0],ch[k][1])
#define change(x) (x = (!type) ? (x) : (x ^ lastans))
const int N = (200000+5)<<1;
const int Maxm = N * 26;
const int M = N << 1;
const int inf = 0x7fffffff;
using namespace std;
int K;
int ch[N][2],tr[N],pos[N],val[N],fa[N],n,m,type;
bool root[N],rev[N];

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
  
int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}

inline void updata(int k)
{
	tr[k] = val[k]; pos[k] = k;
	if(tr[k] > tr[ch[k][0]]) tr[k] = tr[ch[k][0]], pos[k] = pos[ch[k][0]];
	if(tr[k] > tr[ch[k][1]]) tr[k] = tr[ch[k][1]], pos[k] = pos[ch[k][1]];
}

void push(int k)
{
	if(rev[k])
	{
		rev[k] = 0; 
		if(ch[k][0]) reverse(ch[k][0]);
		if(ch[k][1]) reverse(ch[k][1]);
	}
}

void down(int k)
{
	if(!k) return ;
	if(!root[k]) down(fa[k]);
	push(k);
}

void rotate(int x)
{
	if(!x) return ;
	int y = fa[x], k = ch[y][1] == x;
	ch[y][k] = ch[x][!k],fa[ch[y][k]] = y;
	ch[x][!k] = y; fa[x] = fa[y];fa[y] = x;
	if(root[y]) swap(root[x],root[y]);
	else ch[fa[x]][ch[fa[x]][1] == y] = x;
	updata(y);
}

void Splay(int x)
{
	if(!x) return;
	down(x);
	while(!root[x])
	{
		int y = fa[x], z = fa[y];
		if(root[y]) rotate(x);
		else if((ch[y][1] == x) == (ch[z][1]==y)) rotate(y),rotate(x);
		else rotate(x),rotate(x);
	}
	updata(x);
}

void access(int x)
{
	int y = 0;
	while(x)
	{
		Splay(x);root[ch[x][1]] = 1; root[y] = 0;
		ch[x][1] = y; updata(x); y = x; x = fa[x];
	}
}

void move(int x)
{
	access(x);
	Splay(x);
	reverse(x);
}

void link(int x,int y)
{
	move(x);
	fa[x] = y;
}

void cut(int x,int y)
{
	move(x);access(y);Splay(y);
	ch[y][0] = fa[x] = 0;root[x] = 1;
	updata(y);
}

inline int find(int x)
{
	while(fa[x]) 
		x = fa[x];
	return x;
}

namespace seg_tree
{
	int T[Maxm],ls[Maxm],rs[Maxm],rt[N];
	int sz;

	void insert(int L,int R,int x,int &y,int pos)
	{
		y = ++sz; T[y] = T[x] + 1; ls[y] = ls[x],rs[y] = rs[x];
		if(L==R) return ;
		int mid = (L+R) >> 1;
		if(pos <= mid) insert(L,mid,ls[x],ls[y],pos);
		else insert(mid+1,R,rs[x],rs[y],pos);
	}

	int ask(int L,int R,int y,int pos)
	{
		if(!y) return 0;
		if(L==R) return T[y];
		int mid = (L+R) >> 1;
		if(pos <= mid) return ask(L,mid,ls[y],pos);
		else return T[ls[y]] + ask(mid+1,R,rs[y],pos);
	}
}

using namespace seg_tree;

struct graph
{
	int from,to,val;
}edge[M];

int main()
{
	tr[0] = val[0] = inf;
	n = read(), m = read(), K = read(), type = read();
	for(int i=1;i<=m;++i) edge[i].from = read(),edge[i].to = read(),edge[i].val = i;
	for(int i=1;i<=m;++i) tr[i+n] = val[i+n] = edge[i].val;
	for(int i=1;i<=m+n;++i) root[i] = 1 ,pos[i] = i;
	for(int i=1;i<=n;++i) val[i] = inf;
	for(int i=1;i<=m;++i)
	{
		int x = edge[i].from, y = edge[i].to, tmp;
		if(x==y) {
			seg_tree::insert(0,m,seg_tree::rt[i-1],seg_tree::rt[i],i);
			continue;
		}
		if(find(x) == find(y)) {
			move(x); access(y); Splay(y);tmp = pos[y];
			seg_tree::insert(0,m,seg_tree::rt[i-1],seg_tree::rt[i],tmp-n);
			cut(tmp,edge[tmp-n].from); cut(tmp,edge[tmp-n].to);
			link(x,i+n); link(y,i+n);
		}
		else
			seg_tree::insert(0,m,seg_tree::rt[i-1],seg_tree::rt[i],0),link(x,i+n),link(y,i+n);
	}	
	int lastans = 0;

	for(int i=1;i<=K;++i)
	{
		int L = read(), R = read();
		if(type) L ^= lastans,R ^= lastans;
		lastans = seg_tree::ask(0,m,seg_tree::rt[R],L-1) - seg_tree::ask(0,m,seg_tree::rt[L-1],L-1);
		printf("%d\n",lastans=(n-lastans));
	}
}
