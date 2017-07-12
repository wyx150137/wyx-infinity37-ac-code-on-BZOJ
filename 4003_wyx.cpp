
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 3e5+5;
const int M = N;
typedef long long LL;

inline LL read(){
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct Heap{
	Heap *ls,*rs;
	LL h,val,pos,tmp1,tmp2;
	Heap (LL tmp1=0,LL tmp2=0) {
		ls = rs = NULL;
		h = 1, val =  tmp1, pos = tmp2;
		tmp1 = 1 , tmp2 = 0;
	}
	void *operator new (size_t);

	void mul(LL x){
		val *= x;
		tmp1 *= x;
		tmp2 *= x;
	}

	void add(LL x){
		val += x;
		tmp2 += x;
	}

	inline void down(){
		if(tmp1 == 1 && tmp2 == 0) return ;
		if(ls) {
			ls -> mul(tmp1);
			ls -> add(tmp2);
		}
		if(rs) {
			rs -> mul(tmp1);
			rs -> add(tmp2);
		}
		tmp1 = 1, tmp2 = 0;
	}
}*heap[N];

void* Heap::operator new (size_t){
	static Heap mempool[N], *c = mempool;
	return c ++;
}

Heap *merge(Heap *a,Heap *b){
	if(a == NULL) return b;
	if(b == NULL) return a;
	if(a -> val > b -> val) swap(a,b);
	a -> down();
	a -> rs = merge(a -> rs, b);
	int tt1=0,tt2=0;
	if(a -> ls) tt1 = a -> ls -> h;
	if(a -> rs) tt2 = a -> rs -> h;
	if(tt2 > tt1) swap(a -> ls,a -> rs);
	a -> h = min(tt1,tt2)+1;
	return a;
		
}

int head[N],depth[N],pos[N];
int n,m,fa[N],a[N];
LL v[N],T[N];

struct graph{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y){
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
}

int q[N],ans1[N],ans2[N];

void BFS(){
	int l = 1, r = 0;
	q[r = 1] = 1;
	while(l<=r){
		int tt = q[l++];
		for(int i=head[tt];i;i=edge[i].next)
			depth[q[++r] = edge[i].to] = depth[tt] + 1;
	}
	for(int i=n;i;--i){
		int tt = q[i];
		for(int i=head[tt];i;i=edge[i].next) heap[tt] = merge(heap[tt],heap[edge[i].to]);
		while(heap[tt] && heap[tt] -> val < T[tt]) {
			ans1[tt] ++ ;
			ans2[heap[tt]->pos] = depth[pos[heap[tt] -> pos]] - depth[tt];
			heap[tt] -> down();
			heap[tt] = merge(heap[tt]->ls,heap[tt]->rs);
		}
		if(heap[tt]) {
			if(a[tt] == 0) heap[tt] -> add(v[tt]);
			else heap[tt] -> mul(v[tt]);
		}
	}
	while(heap[1]) {
		ans2[heap[1]->pos] = depth[pos[heap[1]->pos]] + 1;
		heap[1] -> down();
		heap[1] = merge(heap[1]->ls,heap[1]->rs);
	}
}

int main(){// freopen("07.in","r",stdin);
	n = read(), m = read();
	for(int i=1;i<=n;++i) T[i] = read();
	for(int i=2;i<=n;++i) fa[i] = read(), a[i] = read(), v[i] = read(),add(fa[i],i);
	for(int i=1;i<=m;++i) {
		LL tmp = read(), y;
		y = pos[i] = read();
		Heap *tt = new Heap(tmp,i);
		heap[y] = merge(heap[y],tt);
	}
	BFS();
	for(int i=1;i<=n;++i) printf("%d\n",ans1[i]);
	for(int i=1;i<=m;++i) printf("%d\n",ans2[i]);
}
