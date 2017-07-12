
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long LL;
 
const int N = 500000 + 10;
const int M = N << 1;

int head[N];
 
inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
} 
 
int n, m;
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
 
int l[N], r[N];
 
LL ans;
 
void dfs(int x, int fa = -1) {
	if (x <= m) return;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa)
			dfs(edge[i].to,x);
	static int cur[2 * N];
	int tot = 0, cnt = 0;
	LL sum = 0;
	for(int i=head[x];i;i=edge[i].next) 
		if(edge[i].to != fa){
			int b = edge[i].to;
			cur[++tot] = l[b], cur[++tot] = r[b];
			sum += l[b];
			--cnt;
		}
	std::sort(cur + 1, cur + tot + 1);
	LL min = 1LL << 60;
	for(int i=1;i<=tot;++i) {
		sum -= cur[i];
		LL val = sum + (LL)++cnt * cur[i];
		if (val < min) min = val, l[x] = cur[i];
		if (val == min) r[x] = cur[i];
	}
	ans += min;
}
 
int main() {
	n = read(), m = read();
	for(int i=1;i<n;++i) add(read(),read());
	for(int i=1;i<=m;++i) l[i] = r[i] = read();
	if (n == m) 
		return printf("%d\n", abs(l[1] - r[2])),0;
	dfs(n);
	cout << ans << endl;
}
