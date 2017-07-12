
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e5+5;
const int M = N << 1;
using namespace std;

bool vis[N];

struct data{
	priority_queue <int> q,Del;

	void insert(int x){
		q.push(x);
	}

	void del(int x){
		Del.push(x);
	}

	void pop(){
		while(!Del.empty() && !q.empty() && Del.top() == q.top()) q.pop(), Del.pop();
		q.pop();
	}

	int top(){
		while(!Del.empty() && !q.empty() && Del.top() == q.top()) q.pop(),Del.pop();
		return q.top();
	}

	int sec(){
		int tt = top(); pop();
		int tt2 = top(); insert(tt);
		return tt2;
	}

	int sz(){
		return q.size() - Del.size();
	}
}s1[M],s2[M],ans;

void insert(data &z){
	if(z.sz() >= 2){
		int tmp = z.top() + z.sec();
		ans.insert(tmp);
	}
}

void del(data &z){
	if(z.sz() >= 2){
		int tmp = z.top() + z.sec();
		ans.del(tmp);
	}
}

int head[N];

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
}

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int size[N],f[N],root,sum;
int fa[N][18],depth[N];

void DFS(int x){
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa[x][0]){
			fa[edge[i].to][0] = x;
			depth[edge[i].to] = depth[x] +1;
			DFS(edge[i].to);
		}
}

inline int lca(int x,int y){
	if(depth[x] < depth[y] ) swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=17;~i;--i) if((1<<i)&tt) x = fa[x][i];
	for(int i=17;~i;--i) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return x == y ? x : fa[x][0];
}

inline int calc(int x,int y){
	return depth[x] + depth[y] - (depth[lca(x,y)]<<1);
}

void DFS1(int x,int fa){
	size[x] = 1, f[x] = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to]){
			DFS1(edge[i].to,x); size[x] += size[edge[i].to];
			f[x] = max(f[x],size[edge[i].to]);
		}
	f[x] = max(f[x],sum - size[x]);
	if(f[x] < f[root]) root = x;
}

int dis[N];

void DFS2(int x,int fa,int belong){
	s1[belong].insert(dis[x]);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to]){
			dis[edge[i].to] = dis[x] + 1;
			DFS2(edge[i].to,x,belong);
		}
}

int last[N];

void solve(int x){
	vis[x] = 1; dis[x] = 0;
	s2[x].insert(0);
	for(int i=head[x];i;i=edge[i].next)
		if(!vis[edge[i].to]){
			dis[edge[i].to] = dis[x] + 1;
			root = 0, sum = size[edge[i].to];
			DFS1(edge[i].to,x); DFS2(edge[i].to,x,root);
			last[root] = x; s2[x].insert(s1[root].top());
			solve(root);
		}
	insert(s2[x]);
}

void on(int x){
	del(s2[x]);
	s2[x].insert(0);
	insert(s2[x]);
	for(int i=x;last[i];i=last[i]){
		del(s2[last[i]]);
		if(s1[i].sz()) s2[last[i]].del(s1[i].top());
		s1[i].insert(calc(last[i],x));
		if(s1[i].sz()) s2[last[i]].insert(s1[i].top());
		insert(s2[last[i]]);
	}
}

void off(int x){
	del(s2[x]);
	s2[x].del(0);
	insert(s2[x]);
	for(int i=x;last[i];i=last[i]){
		del(s2[last[i]]);
		if(s1[i].sz()) s2[last[i]].del(s1[i].top());
		s1[i].del(calc(last[i],x));
		if(s1[i].sz()) s2[last[i]].insert(s1[i].top());
		insert(s2[last[i]]);
	}
}

bool v[N];

int main(){// freopen("1095.in","r",stdin); freopen("1095.out","w",stdout);
	int n = read(); 
	for(int i=1;i<n;++i) add(read(),read());
	for(int i=1;i<=n;++i) v[i] = 1;
	DFS(1); root = 0; f[0] = 0x7fffffff; ::sum = n ;
	DFS1(1,0); int tmp = root; DFS1(root,0); 
	for(int j=1;j<=17;++j) for(int i=1;i<=n;++i) fa[i][j] = fa[fa[i][j-1]][j-1];
	solve(tmp);
//	for(int i=1;i<=n;++i) cout << last[i] << " ";
	int Q = read(); char str[10];
	int sum = n;
	while(Q--){
		scanf("%s",str);
		if(str[0] == 'C'){
			int x = read(); 
			if(v[x]) sum --, off(x), v[x] = false;
			else on(x), v[x] = true, sum ++;
		}
		else{
			if(sum <= 1) printf("%d\n",sum-1);
			else printf("%d\n",ans.top());
		}
	}
}

