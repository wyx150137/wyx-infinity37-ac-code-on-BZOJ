
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 100000+5;
const int M = N << 1;
const int MAXM = N << 5;

using namespace std;

int head[N];

struct graph
{
	int next,to;
	graph ()  {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

int fa[N][20],root[N],n;
int ls[MAXM],rs[MAXM],val[N],T[N];
int tr[MAXM],sz,depth[N],m;

void insert(int L,int R,int x,int &y,int pos)
{
	y = ++sz;ls[y] = ls[x],rs[y] = rs[x],tr[y] = tr[x] +1;
	if(L==R) return;
	int mid = (L+R) >> 1;
	if(pos <= mid) insert(L,mid,ls[x],ls[y],pos);
	else insert(mid+1,R,rs[x],rs[y],pos);
}

int ask(int L,int R,int k1,int k2,int k3,int k4,int pos)
{
	if(L==R) return T[L];
	int mid = (L+R) >> 1;
	if(tr[ls[k3]]+tr[ls[k4]]-tr[ls[k1]]-tr[ls[k2]] >= pos)return ask(L,mid,ls[k1],ls[k2],ls[k3],ls[k4],pos);
	else return  ask(mid+1,R,rs[k1],rs[k2],rs[k3],rs[k4],pos-(tr[ls[k3]]+tr[ls[k4]]-tr[ls[k1]]-tr[ls[k2]]));
}

void DFS(int x)
{
	insert(1,n,root[fa[x][0]],root[x],val[x]);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x][0])
		{
			fa[edge[i].to][0] = x;
			depth[edge[i].to] = depth[x] + 1; 
			DFS(edge[i].to);
		}
}

int lca(int x,int y)
{
	if(depth[x] < depth[y]) swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=19;~i;--i)
		if((1<<i)&tt)
			x = fa[x][i];
	if(x == y) return x;
	for(int i=19;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int find(int x)
{
	int l = 1,r = n;
	while(l<=r)
	{
		int mid = (l+r) >> 1;
		if(T[mid] == x) return mid;
		if(T[mid] < x) l = mid + 1;
		else r = mid - 1;
	}
	return -1;
}

int main(){
	int ans = 0;
	n = read(), m = read();
	for(int i=1;i<=n;++i) T[i] = val[i] = read();
	for(int i=1;i<n;++i) add(read(),read());
	sort(T+1,T+n+1);
	for(int i=1;i<=n;++i) val[i] = find(val[i]);
	DFS(1);
	for(int j=1;j<=19;++j)
		for(int i=1;i<=n;++i)
			fa[i][j] = fa[fa[i][j-1]][j-1];
	for(int i=1;i<=m;++i)
	{
		int x = read()^ans,y = read(), tmp = read();
		int tt = lca(x,y); 
//		cout << "LCA = " << tt << endl;
		ans = ask(1,n,root[fa[tt][0]],root[tt],root[x],root[y],tmp);
		if(i!=m)printf("%d\n",ans);
		else cout << ans;
	}
	
}
