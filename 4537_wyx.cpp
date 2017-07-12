
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5+5;

int sz, n, m, top, F[N], Maxa[N], Maxb[N], ans[N];
int size[N], opcnt;

struct data{
	int x, y, a, b, id;
} edge[N], q[N], stack[N];

struct opt{
	int x, y, f, Maxa, Maxb, size;
}op[N];

bool cmp1(const data &a,const data &b) {
	return a.a ^ b.a ? a.a < b.a : a.b < b.b;
}

bool cmp2(const data &a,const data &b) {
	return a.b ^ b.b ? a.b < b.b : a.a < b.a;
}

inline int find(int x) {
	return F[x] ^ x ? find(F[x]) : F[x];
}

void merge(int x,int y,int a,int b) {
	x = find(x), y = find(y);
	if(size[x] > size[y]) swap(x,y);
	op[++opcnt] = (opt) {x,y,F[x],Maxa[y],Maxb[y],size[y]};
	if(x==y) {
		Maxa[y] = max(Maxa[y],a);
		Maxb[y] = max(Maxb[y],b);
		return ;
	}
	F[x] = y; size[y] += size[x];
	Maxa[y] = max(Maxa[x],max(Maxa[y],a));
	Maxb[y] = max(Maxb[x],max(Maxb[y],b));	
}

void back() {
	for(int i=opcnt;i;--i) {
		int x = op[i].x, y = op[i].y;
		F[x] = op[i].f, 
		Maxa[y] = op[i].Maxa, 
		Maxb[y] = op[i].Maxb, 
		size[y] = op[i].size;
	}
	opcnt = 0;
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	n = read(), m = read(), sz = (int)sqrt(m);
	for(int i=1;i<=m;++i)  edge[i].x = read(), edge[i].y = read(), edge[i].a = read(), edge[i].b = read(), edge[i].id = i;
	sort(edge+1,edge+m+1,cmp1); int Q = read();
	for(int i=1;i<=Q;++i) q[i].x = read(), q[i].y = read(), q[i].a = read(), q[i].b = read(), q[i].id = i;
	sort(q+1,q+Q+1,cmp2);
	for(int i=1;i<=m;i+=sz) {
		top = 0;
		for(int j=1;j<=Q;++j)  if(q[j].a >= edge[i].a && (i+sz>m||q[j].a<edge[i+sz].a)) stack[++top] = q[j];
		sort(edge+1,edge+i+1,cmp2);
		for(int j=1;j<=n;++j) F[j] = j, Maxa[j] = Maxb[j] = -1, size[j] = 1;
		for(int j=1,k=1;j<=top;++j) {
			for(;k<i&& edge[k].b<=stack[j].b;++k) merge(edge[k].x,edge[k].y,edge[k].a,edge[k].b);
			opcnt = 0;
			for(int l=i;l<i+sz&&l<=m;++l) if(edge[l].a <= stack[j].a && edge[l].b <= stack[j].b) merge(edge[l].x,edge[l].y,edge[l].a,edge[l].b);
			int fx = find(stack[j].x), fy = find(stack[j].y);
			ans[stack[j].id] = (fx == fy && Maxa[fx] == stack[j].a && Maxb[fx] == stack[j].b);
			back();
		}
	}
	for(int i=1;i<=Q;++i) puts(ans[i] ? "Yes" : "No");
}
