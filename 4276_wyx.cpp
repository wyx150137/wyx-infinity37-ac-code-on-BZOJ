
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 25000+5;
const int M = 100000;
const int inf = 0x3f3f3f3f;
using namespace std;
int pre[N];
int head[N];
bool in[N];
struct graph{
	int next,to,val,f;
	graph () {}
	graph (int _next,int _to,int _val,int _f)
	:next(_next),to(_to),val(_val),f(_f){}
}edge[M*20];

inline void add(int x,int y,int z,int f){
	static int cnt = 1;
//	printf("%d->%d %d %d\n",x,y,z,f == inf ? 1000 : f);
	edge[++cnt] = graph(head[x],y,z,f); head[x] = cnt;
	edge[++cnt] = graph(head[y],x,-z,0); head[y] = cnt;
}

int dis[N],S,T;

bool spfa(){
	memset(dis,0x3f,sizeof dis);
	queue <int> q;
	dis[S] = 0; in[S] = 1; q.push(S);
	while(!q.empty()){
		int tt = q.front(); q.pop(); in[tt] = false;
		for(int i=head[tt];i;i=edge[i].next)
			if(dis[edge[i].to] > dis[tt] + edge[i].val && edge[i].f){
				dis[edge[i].to] = dis[tt] + edge[i].val;
				pre[edge[i].to] = i;
				if(!in[edge[i].to]){
					in[edge[i].to] = 1;
					q.push(edge[i].to);
				}
			}
	}
	return dis[T] != inf;
}

int mcmf(){
	int mx = inf,ans = 0;
	for(int i=pre[T];i;i=pre[edge[i^1].to]) mx = min(mx,edge[i].f);
	for(int i=pre[T];i;i=pre[edge[i^1].to]) {
		edge[i].f -= mx, edge[i^1].f += mx;
		ans += mx * edge[i].val;
	}
	return ans;
}

int No,val,flow;

void ask(int k,int l,int r,int x,int y){
	if(l==x && r==y){
		add(No,k,val,flow);
		return;
	}
	int mid = (l+r) >> 1;
	if(y <= mid) ask(k<<1,l,mid,x,y);
	else if(x > mid) ask(k<<1|1,mid+1,r,x,y);
	else ask(k<<1,l,mid,x,mid), ask(k<<1|1,mid+1,r,mid+1,y);
}

const int Max = 16369+5;

void build(int k,int l,int r){
//	Max = max(Max,k);
	if(l==r){
		add(k,T,0,1);
		return;
	}
	add(k,k<<1,0,inf);
	add(k,k<<1|1,0,inf);
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int a[N];

int main(){
	int n = read();
	S = 0, T = 25000;
	build(1,1,5000); 
	for(int i=1;i<=n;++i){
		int L = read(), R = read(),val = read();
		::flow = inf,::val = 0,::No = Max + i;
		ask(1,1,5000,L,R-1);
		add(S,No,-val,1);
	}
	int ans = 0;
	while(spfa()) ans += mcmf();
	cout << -ans << endl;
}
