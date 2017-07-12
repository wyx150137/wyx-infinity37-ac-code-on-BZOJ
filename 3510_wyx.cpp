
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = N << 1;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int fa[N], size[N], tr[N], ch[N][2];
int rt[N], head[N];
bool rev[N], root[N];

struct graph{
	int next, to;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to) {}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x], y); head[x] = cnt;
	edge[++cnt] = graph(head[y], x); head[y] = cnt;
}

inline void updata(int k) {
	if(!k) return;
	size[k] = size[ch[k][0]] + size[ch[k][1]] + 1 + tr[k];
}

inline void solve(int k) {
	if(!k) return;
	rev[k] ^= 1;
	swap(ch[k][0], ch[k][1]);
}

inline void push_down(int k) {
	if(rev[k]) {
		solve(ch[k][0]);
		solve(ch[k][1]);
		rev[k] ^= 1;
	}
}

inline void down(int k) {
	if(!root[k]) down(fa[k]);
	push_down(k);
}

inline void rotate(int x) {
	int y = fa[x], z = ch[y][1] == x;
	ch[y][z] = ch[x][!z]; fa[ch[y][z]] = y;
	ch[x][!z] = y; fa[x] = fa[y]; fa[y] = x;
	if(root[y]) swap(root[x], root[y]);
	else ch[fa[x]][ch[fa[x]][1] == y] = x;
	updata(y);
	updata(x);
}

inline void splay(int x) {
	down(x);
	while(!root[x]) {
		int y = fa[x], z = fa[y];
		if(root[y]) rotate(x);
		else if((ch[y][1] == x) == (ch[z][1] == y)) rotate(y), rotate(x);
		else rotate(x), rotate(x);
	}
}

inline void access(int x) {
	int y = 0;
	while(x) {
		splay(x);
		root[ch[x][1]] = true;
		tr[x] += size[ch[x][1]];
		root[ch[x][1] = y] = false;
		tr[x] -= size[y];
		updata(x);
		y = x;
		x = fa[x];
	}
}

int Ans;

int F[N], Siz[N];

inline int find(int x) {
	return F[x] ^ x ? F[x] = find(F[x]) : F[x];
}

inline void move(int x) {
	access(x);
	splay(x);
	solve(x);
}

inline void link(int x,int y) {
	move(x);
	move(y);
	fa[x] = y;
	tr[y] += size[x];
	updata(y);
	int temp = rt[find(y)];	
	move(temp);
	access(x);
	splay(temp);
	int now = size[temp];
	int s = ch[temp][1];
	push_down(s);
	while(ch[s][0]) {
		s = ch[s][0];
		push_down(s);
	}
	access(s);
	int now1 = tr[s];
	if((now1+1)*2>now || ((now1+1)*2==now && s<temp)) {
		Ans ^= temp;
		Ans ^= s;
		rt[find(y)] = s;
	}
}

inline void DFS(int x,int y) {
	tr[x] = 0, size[x] = 1; fa[x] = 0;
	ch[x][1] = ch[x][0] = 0; root[x] = 1;
	link(x,y);
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != y) {
			DFS(edge[i].to, x);
		}
	}
}


int main() {
//	freopen("tt.in","r",stdin);
	int n = read();
	for(int i=1;i<=n;++i) F[i] = i, root[i] = 1, size[i] = Siz[i] = 1, Ans ^= i, rt[i] = i;
	int m = read();
	char str[10];
	for(int i=1;i<=m;++i) {
		scanf("%s", str);
		if(str[0] == 'A') {
			int x = read(), y = read();
			int fx = find(x), fy = find(y);
			if(Siz[fx] < Siz[fy]) {
				swap(fx, fy);
				swap(x, y);
			}
			Ans ^= rt[find(y)];
			Siz[fx] += Siz[fy];
			F[fy] = fx;
			DFS(y,x);
			add(x,y);
		}
		else if(str[0] == 'Q') {
			int x = read();
			printf("%d\n", rt[find(x)]);
		} 
		else {
			printf("%d\n", Ans);
		}
	}
}
