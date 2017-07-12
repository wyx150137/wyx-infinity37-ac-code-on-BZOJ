
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 1500+5;
const int M = (100005+5) << 1;
const int inf = 0x3f3f3f3f;
int head[N];

struct graph{
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
			if(edge[i].val && depth[edge[i].to] < 0){
				depth[edge[i].to] = depth[tt] + 1;
				q.push(edge[i].to);
			}
	}
	return ~depth[T];
}

int DFS(int x,int f){
	int used = 0, w;
	if(x == T) return f;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].val && depth[edge[i].to] == depth[x] + 1){
			w = DFS(edge[i].to,min(edge[i].val,f-used));
			used += w; edge[i].val -= w, edge[i^1].val += w;
			if(used == f)return f;
		}
	depth[x] = -1;
	return used;
}

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch= getchar();}
	return x*f;
}

int a[N],A[N];
bool mark[N];

void divede(int x){
	mark[x] = 1;
	for(int i=head[x];i;i=edge[i].next) 
		if(edge[i].val && !mark[edge[i].to]) 
			divede(edge[i].to);
}

inline void restore(){
	for(int i=2;i<=cnt;i+=2) 
		edge[i].val = edge[i^1].val = (edge[i].val + edge[i^1].val) >> 1;
}

int ans[N][N],n,m;

void solve(int l,int r){
	if(l==r)return;
	restore();
	S = a[l],T = a[r];
	int tmp = 0;
	while(BFS()) tmp += DFS(S,inf);
	memset(mark,false,sizeof mark);
	divede(S);
	for(int i=1;i<=n;i++)
		if(mark[i])
			for(int j=1;j<=n;j++)
				if(!mark[j])	
					ans[i][j]=ans[j][i]=min(ans[i][j],tmp);
	int L = l,R = r;
	for(int i=l;i<=r;++i)
		if(mark[a[i]]) A[L++] = a[i];
		else A[R--] = a[i];
	for(int i=l;i<=r;++i) a[i] = A[i];
	solve(l,L-1); solve(R+1,r);
}

int main()
{
	int T = read();
	while(T--){
		memset(head,0,sizeof head);
		memset(ans,0x3f,sizeof ans);
		cnt = 1;
		n = read(), m = read();
		for(int i=1;i<=m;++i) {
			int x = read(), y = read(),val = read();
			add(x,y,val);
		}
		for(int i=1;i<=n;++i) a[i] = i;
		solve(1,n); int Q = read();
		while(Q--){
			int tmp = 0, lmt = read();
			for(int i=1;i<=n;++i)
				for(int j=i+1;j<=n;++j)
					if(ans[i][j] <= lmt)
						tmp ++;
			printf("%d\n",tmp);
		}
		puts("");
	}
}
