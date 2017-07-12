
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 50000+5;	
using namespace std;

int size[N],fa[N],ch[N][2];
int val[N],add[N],rev[N],MAX[N];
int sz,root;

void newnode(int &k,int F,int Val)
{
	k = ++sz;
	fa[k] = F,size[k] = 1;
	ch[k][0] = ch[k][1] = rev[k] = add[k] =0;
	MAX[k] = val[k] = Val;
}

void update(int k)
{
	size[k] = 1, MAX[k] = val[k];
	if(ch[k][0])
		size[k] = size[k] + size[ch[k][0]], MAX[k] = max(MAX[k],MAX[ch[k][0]]);
	if(ch[k][1])
		size[k] = size[k] + size[ch[k][1]], MAX[k] = max(MAX[k],MAX[ch[k][1]]);
}

void down(int k)
{
	if(!k) return;
	if(add[k])
	{
		if(ch[k][0])
			add[ch[k][0]] += add[k],MAX[ch[k][0]] += add[k],val[ch[k][0]] += add[k];
		if(ch[k][1])
			add[ch[k][1]] += add[k],MAX[ch[k][1]] += add[k],val[ch[k][1]] += add[k];
		add[k] = 0;
	}
	if(rev[k])
	{
		if(ch[k][0])
		{
			rev[ch[k][0]] ^= 1;
			swap(ch[ch[k][0]][0],ch[ch[k][0]][1]);
		}
		if(ch[k][1])
		{
			rev[ch[k][1]] ^= 1;
			swap(ch[ch[k][1]][0],ch[ch[k][1]][1]);
		}
		rev[k] = 0;
	}
}

void rotate(int x)
{
	int y = fa[x], k = (ch[y][1] == x); 
	down(y),down(x);
	ch[y][k] = ch[x][!k], fa[ch[y][k]] = y;ch[x][!k] = y;
	fa[x] = fa[y],fa[y] = x; ch[fa[x]][ch[fa[x]][1] == y] = x;
	update(y),update(x);
}

void build(int &k,int L,int R,int F)
{
	if(L>R) return ;
	int mid = (L+R)>>1;
	newnode(k,F,0);
	build(ch[k][0],L,mid-1,k);
	build(ch[k][1],mid+1,R,k);
	update(k);
}

void splay(int x,int G)
{
	while(fa[x] != G)
	{
		int y = fa[x], z = fa[y];
		if(z == G)
			rotate(x);
		else if((ch[y][1] == x) == (ch[z][1] == y)) rotate(y),rotate(x);
		else rotate(x),rotate(x);
	}
	if(!G) root = x;
}

int find(int x,int rank)
{
	down(x);
	int tmp = size[ch[x][0]] + 1;
	if(tmp == rank) return x;
	if(tmp < rank) return find(ch[x][1],rank-tmp);
	else return find(ch[x][0],rank);
}

void change(int L,int R,int V)
{
	splay(find(root,L),0);
	splay(find(root,R+2),root);
	add[ch[ch[root][1]][0]] += V;
	val[ch[ch[root][1]][0]] += V;
	MAX[ch[ch[root][1]][0]] += V;
}

void Rev(int L,int R)
{
	splay(find(root,L),0);
	splay(find(root,R+2),root);int tmp;
	rev[tmp = ch[ch[root][1]][0]] ^= 1;
	swap(ch[tmp][0],ch[tmp][1]);
}

inline int ask(int L,int R)
{
	splay(find(root,L),0);
	splay(find(root,R+2),root);
	return MAX[ch[ch[root][1]][0]];
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1) + (x<<3) + ch - '0'; ch = getchar();}
	return x*f;
}
	
int main()
{
	int n = read(), m = read();
	newnode(root,0,-1);
	newnode(ch[root][1],root,-1);
	build(ch[ch[root][1]][0],1,n,ch[root][1]);
	for(int i=1;i<=m;++i)
	{
		int opt = read();
		if(opt == 1)
		{
			int L = read(), R = read(),V = read();
			change(L,R,V);
		}
		else if(opt == 2)
		{
			int L = read(), R = read();
			Rev(L,R);
		}
		else
		{
			int L = read(), R = read();
			printf("%d\n",ask(L,R));
		}
	}
}
