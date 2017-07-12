
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
const int M = N << 1;

int head[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct graph{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

int col[N], stack[N], top, c[N];
bool vis[N];

inline int DFS(int x,int fa) {
	if(col[x] > 0) c[x] = 0;
	else if(col[x] == -1) return (c[x] = -1);
		else if(col[x] == -2) return (c[x] = 1);
		else return c[x];
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa) {
			c[x] += DFS(edge[i].to,x);
		}
	}
	if(c[x] < 0) c[x] = -1;
	if(c[x] > 0) c[x] = 1;
	return c[x];
}

inline void DFS2(int x,int fa) {
	bool flag = false;
	int sum = 0;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa) {
			sum += c[edge[i].to];
			DFS2(edge[i].to,x);
			flag = 1;
		}
	}
	if(!flag) return;
	if(sum == 0 || sum == -1) vis[x] = 1;
}

inline void DFS3(int x,int fa) {
	bool flag = false;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa ) 
			if(vis[edge[i].to] || c[edge[i].to] == 0){
			DFS3(edge[i].to, x); flag = 1;
		} 
	}
	if(!flag && c[x] == 0) stack[++top] = x;
}

int main() {//freopen("battle.in","r",stdin); freopen("battle.out","w",stdout);
	int n = read();
	for(int i=1;i<=n;++i) {
		col[i] = read();
		for(int j=1;j<=col[i];++j) add(i,read());
	}
	DFS(1,-1);
	if(c[1] == 1)  {
		for(int i=1;i<=n;++i) if(col[i] == 0) stack[++top] = i;
		printf("TAK %d\n", top);
		for(int i=1;i<top;++i) printf("%d ",stack[i]);
		if(top) cout << stack[top] << endl;
		return 0;
	}
	if(c[1] == -1) {
		puts("NIE");
		return 0;
	}
	DFS2(1,-1);
	DFS3(1,-1);
	sort(stack+1,stack+top+1);
	printf("TAK %d\n", top);
	for(int i=1;i<top;++i) printf("%d ",stack[i]);
	if(top) cout << stack[top] << endl;
}
