
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 20000+5;
const int M = 400000+5;
const int inf = 0x3f3f3f3f;
using namespace std;

int head[N];

struct graph {
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

int cnt = 1;

inline void add(int x,int y,int z){
	edge[++cnt] = graph(head[x],y,z); head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z); head[y] = cnt;
}

int depth[N];
int S,T;

bool BFS(){
	memset(depth,-1,sizeof depth);
	queue <int> q;
	depth[S] = 0; q.push(S);
	while(!q.empty()){
		int tt = q.front(); q.pop();
		for(int i=head[tt];i;i=edge[i].next)
			if(depth[edge[i].to] < 0 && edge[i].val)
				depth[edge[i].to] = depth[tt] + 1, q.push(edge[i].to);
	}
	return ~depth[T];
}

int DFS(int x,int f){
	if(x== T)return f;
	int w,used=0;
	for(int i=head[x];i;i=edge[i].next)
		if(depth[edge[i].to] == depth[x] + 1 && edge[i].val){
			w = DFS(edge[i].to,min(edge[i].val,f-used));
			edge[i].val -= w, edge[i^1].val += w; used += w;
			if(f == used) return f;
		}
	depth[x] = -1;
	return used;
}

struct data {
	int from,to,val;
}a[M];

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}\
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	int n = read(), m = read();
	for(int i=1;i<=m;++i) a[i].from = read(), a[i].to = read(), a[i].val = read();
	S = read(), T = read();int lmt = read();
	for(int i=1;i<=m;++i) if(a[i].val < lmt) add(a[i].from,a[i].to,1);
	int ans = 0, now = 0;
	while(BFS()) while((now = DFS(S,inf))) ans += now;
	memset(head,0,sizeof head); cnt = 1;
	for(int i=1;i<=m;++i) if(a[i].val > lmt) add(a[i].from,a[i].to,1);
	now = 0;
	while(BFS()) while((now = DFS(S,inf))) ans += now;
	cout << ans << endl;
}
