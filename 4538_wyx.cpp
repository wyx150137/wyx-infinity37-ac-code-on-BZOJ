
#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e5+5;
const int M = 270000;
#define mp make_pair
#define pb push_back
#define fir first
#define sec second
using namespace std;

struct Heap {
	priority_queue <int> a,b;
	void del(int x) {b.push(x);}
	void push(int x){a.push(x);}
	int top() {
		while(!b.empty() && !a.empty() && a.top() == b.top()) a.pop(), b.pop();
		if(a.empty()) return -1;
		else return a.top();
	}
}tr[M];

vector <pair<int,int> > stack;

int head[N], n, m;

struct graph{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to) {}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt; 
}

int size[N], top[N],depth[N], w[N], fa[N], sz;

void DFS1(int x) {
	size[x] = 1;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x]) {
			fa[edge[i].to] = x;
			depth[edge[i].to] = depth[x] + 1;
			DFS1(edge[i].to);
			size[x] += size[edge[i].to];
		}
	}
}

void DFS2(int x,int chain) {
	top[x] = chain; w[x] = ++sz; int k = 0;
	for(int i=head[x];i;i=edge[i].next) if(edge[i].to != fa[x] && size[k] <= size[edge[i].to]) k = edge[i].to;
	if(!k) return; DFS2(k,chain); 
	for(int i=head[x];i;i=edge[i].next) if(edge[i].to != fa[x] && edge[i].to != k) DFS2(edge[i].to,edge[i].to);
}

inline void change(int k,int l,int r,int x,int y,int val,int flag) {
	if(x > y) return;
	if(l==x && r==y)  {
		if(flag) tr[k].push(val);
		else tr[k].del(val);
		return;
	}
	int mid = (l+r) >> 1;
	if(y <= mid) change(k<<1,l,mid,x,y,val,flag);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y,val,flag);
	else change(k<<1,l,mid,x,mid,val,flag), change(k<<1|1,mid+1,r,mid+1,y,val,flag);
}

inline int ask(int k,int l,int r,int pos) {
	if(l==r) return tr[k].top();
	int mid = (l+r) >> 1;
	if(pos <= mid) return max(tr[k].top(),ask(k<<1,l,mid,pos));
	else return max(tr[k].top(),ask(k<<1|1,mid+1,r,pos));
}

inline void solve_change(int x,int y,int val,int flag) {
	stack.clear();
	while(top[x]!=top[y]) {
		if(depth[top[x]] < depth[top[y]]) swap(x,y);
		stack.pb(mp(w[top[x]],w[x])); x = fa[top[x]];
	}
	if(depth[x] > depth[y]) swap(x,y); stack.pb(mp(w[x],w[y]));
	sort(stack.begin(), stack.end());
	vector <pair<int,int> > :: iterator it;
	int tt = 1;
	for(it = stack.begin(); it != stack.end(); it ++) {
		change(1,1,n,tt,(*it).fir-1,val,flag); tt = (*it).sec + 1;
	}
	change(1,1,n,tt,n,val,flag);
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int x[N<<1], y[N<<1], z[N<<1];

int main() {
//	freopen("4358.in","r",stdin);
	n = read(), m = read();
	int opt;
	for(int i=1;i<n;++i) add(read(),read());
	int root = rand() % n + 1;
	DFS1(root);DFS2(root,root);
	for(int i=1;i<=m;++i) {
		opt = read();
		if(opt == 0) {
			x[i] = read(), y[i] = read(), z[i] = read(); 
			solve_change(x[i],y[i],z[i],1);
		}
		else if(opt == 1) {
			x[i] = read();
			solve_change(x[x[i]],y[x[i]],z[x[i]],0);
		}
		else {
			x[i] = read();
			printf("%d\n",ask(1,1,n,w[x[i]]));
		}
	}
}
