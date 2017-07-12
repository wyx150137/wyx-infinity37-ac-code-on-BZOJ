
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define lowbit(x) ((x)&(-x))
#define updata(k) size[k] = size[ch[k][0]] + size[ch[k][1]] + 1
#define newnode(k,F,V) k = ++sz; fa[k] = F;tr[k] = V; size[k] = 1
const int N =  100000+5;
using namespace std;

int fa[N],ch[N][2],root,tr[N],sz,size[N],F[N];

void rotate(int x)
{
	int y = fa[x] , k = ch[y][1] == x;
	ch[y][k] = ch[x][!k], fa[ch[y][k]] = y;
	fa[x] = fa[y], ch[fa[x]][ch[fa[x]][1] == y] = x;
	ch[x][!k] = y; fa[y] = x;
	updata(y); updata(x);
}

void Splay(int x,int w)
{
	while(fa[x] != w)
	{
		int y = fa[x], z = fa[y];
		if(z == w) rotate(x);
		else if((ch[z][1] == y) == (ch[y][1] == x) ) rotate(y),rotate(x);
		else rotate(x),rotate(x);
	}
	if(!w) root = x;
}

int find(int x,int rank)
{
	int tmp = size[ch[x][0]];
	if(rank <= tmp) return find(ch[x][0],rank);
	else if(rank == tmp + 1) return x;
	else return find(ch[x][1],rank - tmp - 1);
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int T[N];

void change(int x,int tt)
{
	while(x < N)
	{
		T[x] = max(T[x],tt);
		x += lowbit(x);
	}
}

int ask(int x)
{
	int ans = 0;
	while(x)
	{
		ans = max(ans,T[x]);
		x -= lowbit(x);
	}
	return ans;
}

void DFS(int x)
{
	if(ch[x][0]) DFS(ch[x][0]);
	F[tr[x]] = ask(tr[x]) + 1;
	change(tr[x],F[tr[x]]);
	if(ch[x][1]) DFS(ch[x][1]);
}

int main()
{
	int n = read();
	newnode(root,0,-1); size[root] = 2;
	newnode(ch[root][1],root,-1); 
	for(int i=1;i<=n;++i)
	{
		int x = read() + 1;
		int tmp1 = find(root,x),tmp2 = find(root,x+1);
		Splay(tmp1,0);
		Splay(tmp2,root);
		int tmp = ch[root][1];
		newnode(ch[tmp][0],tmp,i);
		Splay(tmp,0);
		Splay(sz,0);
	}
	Splay(find(root,1),0); Splay(find(root,n+2),root);
	DFS(ch[ch[root][1]][0]);
	int ans = 0;
	for(int i=1;i<=n;++i) 
		printf("%d\n",ans = max(F[i],ans));
}

