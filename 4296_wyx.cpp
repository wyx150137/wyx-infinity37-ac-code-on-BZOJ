
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200000+5;
const int M = N << 1;

int deg[N],head[N];

struct graph{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y){
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
	deg[x] ++, deg[y] ++;
}

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

queue <int> q;

int vis[N],n,m,lmt;
int size[N];

void DFS(int x){
	size[vis[x]] ++;
	for(int i=head[x];i;i=edge[i].next)
		if(!vis[edge[i].to] && deg[edge[i].to] >= lmt)
			vis[edge[i].to] = vis[x] , DFS(edge[i].to);
}

int T[N],tt;
int G[N];

void getans(int x){
	T[++T[0]] = x;G[x] = 1;
	for(int i=head[x];i;i=edge[i].next)
		if(vis[edge[i].to] == vis[x] && !G[edge[i].to])
			getans(edge[i].to);
}

int main(){
	n = read(), m = read(), lmt = read();
	for(int i=1;i<=m;++i) add(read(),read());
	for(int i=1;i<=n;++i) if(deg[i] < lmt) q.push(i);
	while(!q.empty()) {
		int tt = q.front(); q.pop();
		for(int i=head[tt];i;i=edge[i].next)
			if((--deg[edge[i].to]) == lmt-1)
				q.push(edge[i].to);
	}
	for(int i=1;i<=n;++i)
		if(deg[i] >= lmt && !vis[i]) {
			vis[i] = ++tt;
			DFS(i);
		}
	int ans = 0;
	for(int i=1;i<=tt;++i)
		ans = max(ans,size[i]);
	if(ans == 0) {
		puts("NIE");
		return 0;
	}
	cout << ans << endl;
	for(int i=1;i<=n;++i)
		if(size[vis[i]] == ans) {
			getans(i);
			break;
		}
	int tmp = T[0];
	sort(T+1,T+tmp+1);
	for(int i=1;i<=T[0];++i)
		printf("%d%c",T[i],i==T[0]?'\n':' ');
}
