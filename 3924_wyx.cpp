
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
const int N = 2e5+5;
const int M = N << 1;
typedef long long LL;
const int inf = 0x3f3f3f3f;
using namespace std;

int log_2[N<<1],n;

int head[N];
struct graph{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,int z){
	static int cnt = 1;
	edge[++cnt] = graph(head[x],y,z); head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z); head[y] = cnt;
}

LL dis[N];
int pos[N];
int a[N][20];
int fa[N];

void DFS(int x)
{
	static int dfn=0;
	int i;
	a[pos[x]=++dfn][0]=dis[x];
	for(i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]) {
			fa[edge[i].to]=x;
			dis[edge[i].to]=dis[x]+edge[i].val;
			DFS(edge[i].to);
			a[++dfn][0]=dis[x];
		}
}

void init(){
	register int i,j;
	int Max = (n-1)<<1;
	for(i=2;i<=Max;++i) log_2[i] = log_2[i>>1] + 1;
	for(j=1;j<=log_2[Max];++j)
		for(i=1;i+(1<<j)-1 <= Max;++i)
			a[i][j] = min(a[i][j-1],a[i+(1<<(j-1))][j-1]);
}

inline int calc_dis_lca(int x,int y){
	x = pos[x],y = pos[y];
	if(x>y)swap(x,y);
	int l = log_2[y-x+1];
	return min(a[x][l],a[y-(1<<l)+1][l]);
}

inline int calc(int x,int y){
	return dis[x] + dis[y] - 2*calc_dis_lca(x,y);
}


int _head[N],last[N],size[N],sum;
LL sum1[N],sum2[N];
LL dis1[N],dis2[N],F[N];
bool vis[N];

struct _graph{
	int _next,_to,_val;
	_graph () {}
	_graph (int __next,int __to,int __val)
	:_next(__next),_to(__to),_val(__val){}
}_edge[M];

inline void _add(int x,int y,int z){
	static int cnt = 0;
	_edge[++cnt] = _graph(_head[x],y,z); _head[x] = cnt;
}

int root;

void DFS1(int x,int fa){
	size[x] = 1, F[x] = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to]){
			DFS1(edge[i].to,x); size[x] += size[edge[i].to]; 
			F[x] = max(F[x],(LL)size[edge[i].to]);
		}
	F[x] = max(F[x],(LL)sum-size[x]);
	if(F[x] < F[root]) root = x;
}

void solve(int x){
	vis[x] = 1; 
	for(int i=head[x];i;i=edge[i].next)
		if(!vis[edge[i].to]){
			root = 0, sum = size[edge[i].to];
			DFS1(edge[i].to,x); last[root] = x; 
//			cout << root << endl;
			_add(x,root,edge[i].to); solve(root);
		}
}

void change(int x,LL val){
	int i;
	sum1[x] += val;
	for(i=x;last[i];i=last[i]){
		LL tmp = calc(x,last[i]);
		dis1[last[i]] += val * tmp;
		dis2[i] += val * tmp;
		sum1[last[i]] += val;
		sum2[i] += val;
	}
}

LL calc(int x){
	int i;
	LL ans = dis1[x];
	for(i=x;last[i];i=last[i]){
		LL tmp = calc(x,last[i]);
		ans += dis1[last[i]] - dis2[i];
		ans += (sum1[last[i]] - sum2[i])*tmp;
	}
	return ans;
}

LL ask(int x){
	int i;
	LL tmp1;
	LL tmp = calc(x);
	for(i=_head[x];i;i = _edge[i]._next){
		tmp1 = calc(_edge[i]._val);
		if(tmp1 < tmp) return ask(_edge[i]._to);
	}
	return tmp;
}

int tmp; 

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main(){ //freopen("zjoi.in","r",stdin);freopen("zjoi.out","w",stdout);
	int Q;
	cin >> n >> Q;
	int x,y,z;
	for(int i=1;i<n;++i){
		x = read(), y = read(), z = read();
		add(x,y,z);	
	}
	DFS(1); init();
	root = 0; F[0] = inf;
	sum = n ;DFS1(1,0); 
	tmp = root;
	sum = n; 
	DFS1(root,0);
	solve(tmp);   
	while(Q--){
		x = read(), y = read();
		change(x,y);
		printf("%lld\n",ask(tmp));
	}
}
