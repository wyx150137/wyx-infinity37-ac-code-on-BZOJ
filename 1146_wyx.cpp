
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 8e4+100;
const int M = N << 1;
const int Maxm = 110 * N;
using namespace std;

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N],Max;

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

int fa[N][18],T[M];
int in[N],out[N];
int depth[N],DFN;

void DFS(int x){
	in[x] =  ++DFN;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa[x][0]){
			fa[edge[i].to][0] = x;
			depth[edge[i].to] = depth[x] + 1;
			DFS(edge[i].to);
		}
	out[x] = DFN;
}

std::vector<int> ask1,ask2;

inline int lca(int x,int y){
	if(depth[x] < depth[y]) swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=17;~i;--i) if((1<<i)&tt) x =fa[x][i];
	for(int i=17;~i;--i) if(fa[x][i]!=fa[y][i]) x = fa[x][i], y = fa[y][i];
	return x == y ? x : fa[x][0];
}

int tr[Maxm],sz,val[N];
int ls[Maxm],rs[Maxm];

void change(int l,int r,int &y,int pos,int val){
	if(!y)y = ++sz; tr[y] += val;
	if(l==r) return;
	int mid = (l+r) >> 1;
	if(pos <= mid) change(l,mid,ls[y],pos,val);
	else change(mid+1,r,rs[y],pos,val);
}

int ask(int l,int r,int rank){
	if(l==r) return T[l];
	int  ans = 0,mid = (l+r) >> 1;
	for(int j=0;j<ask1.size();++j) ans += tr[rs[ask1[j]]];
	for(int j=0;j<ask2.size();++j) ans -= tr[rs[ask2[j]]];
	int sum = 0;
	for(int j=0;j<ask1.size();++j) sum += tr[ask1[j]];
	for(int j=0;j<ask2.size();++j) sum -= tr[ask2[j]];
	if(sum < rank) return -1;			
	if(rank <= ans) {
		for(int j=0;j<ask1.size();++j) ask1[j] = rs[ask1[j]];
		for(int j=0;j<ask2.size();++j) ask2[j] = rs[ask2[j]];
		return ask(mid+1,r,rank);
	}
	else{
		for(int j=0;j<ask1.size();++j) ask1[j] = ls[ask1[j]];
		for(int j=0;j<ask2.size();++j) ask2[j] = ls[ask2[j]];
		return ask(l,mid,rank-ans);
	}
}

int tree[M];

#define lowbit(x) ((x)&(-x))

void clear(){
	ask1.clear(); ask2.clear();
}

void updata(int x,int pos,int val){
	while(x <= DFN){
		change(1,Max,tree[x],pos,val);
		x += lowbit(x);
	}		
}

inline void Ask1(int x){
	for(int i=in[x];i;i-=lowbit(i)) {
			ask1.push_back(tree[i]);
	}
}

inline void Ask2(int x){
	for(int i=in[x];i;i-=lowbit(i)) 
		ask2.push_back(tree[i]);	

}

struct query
{
	int opt;
	int x,y,z;
}q[M];

inline int find(int x){
	int l = 1,r = Max ;
	while(l <= r){
		int mid = (l+r) >> 1;
		if(T[mid] == x)return mid;
		if(T[mid] < x) l = mid + 1;
		else r = mid - 1;
	}
	return -1;
}

int main(){// freopen("tt.in","r",stdin);
	int n = read(),Q = read();
	for(int i=1;i<=n;++i) T[i] = val[i] = read();
	int tt = n; for(int i=1;i<n;++i) add(read(),read());
	DFS(1); for(int j=1;j<=17;++j) for(int i=1;i<=n;++i) fa[i][j] = fa[fa[i][j-1]][j-1];
	for(int i=1;i<=Q;++i) {
		q[i].opt = read(), q[i].x = read(), q[i].y = read();
		if(q[i].opt) q[i].z = lca(q[i].x,q[i].y);
		else T[++tt] = q[i].y;
	}
	sort(T+1,T+tt+1); Max = tt; tt = 0;
	for(int i=1;i<=Max;++i) if(T[i] != T[i-1]) T[++tt] = T[i]; Max = tt;
	for(int i=1;i<=n;++i) val[i] = find(val[i]);
	for(int i=1;i<=Q;++i) if(q[i].opt == 0) q[i].y = find(q[i].y);
	for(int i=1;i<=n;++i) updata(in[i],val[i],1), updata(out[i]+1,val[i],-1);
	for(int i=1;i<=Q;++i){
		if(!q[i].opt){
			int x = q[i].x, y = q[i].y;
			updata(in[x],val[x],-1); updata(out[x]+1,val[x],1);
			updata(in[x],y,1); updata(out[x]+1,y,-1); val[x] = y;
		}
		else{
			int x = q[i].x, y = q[i].y, z = q[i].z;
			clear();Ask1(x); Ask1(y); Ask2(z); Ask2(fa[z][0]);
			int ans = ask(1,Max,q[i].opt);
			if(ans == -1) puts("invalid request!");
			else printf("%d\n",ans);
		}
	}
}
	
